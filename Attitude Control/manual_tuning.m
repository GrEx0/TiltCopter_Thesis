%% Import parameters
close all;
Parameters;
%% Robust control syntesys - H-INFINITY / SYSTUNE  REQUIREMENT DEFINITIONS BASED ON MANUAL TUNING
s = tf('s');


% Identified roll dynamics
A1_sA = ureal('A1_sA',8.387902003,'PlusMinus',0.006483558);           % Confidence bound 3sigma
B1_sA = ureal('B1_sA',6.844908507,'PlusMinus',0.006598076);
num_i = A1_sA;
den_i = [1 B1_sA];

% roll rate dynamic model w.o time delay
G_q = tf(num_i,den_i);
G_q = G_q *1/x1(1);                         % Correzione deltaOmega -> deltaTH%, dato che l'identificazione dava in ingresso deltaTH%

% roll angle dynamic model (it will be in cascade after the G_p model)
G_roll = 1/s ;
G_roll.u = 'p';
G_roll.y = 'phi';

% identified  time delay
sys_delay = exp(-0.09*s);

% Padè approssimation of the time delay
sys_delay_pade = pade(sys_delay,3);             % Padè approx, 3rd order

% Mixer transfer function ( to obtain the real model frol deltaL ->
% deltap), and not from deltaOmega -> deltap)
mixer = ss(1/(4*Kt*b*omega_hover));
mixer.u = 'deltaL'; mixer.y = 'deltaOmega';

% Motor transfer function
motor = 1/(1+tau*s);

%% Controllers definition

Ts = 0.01;                               % Order of the filter for the pids

R_inner_roll = pid(Kpp,Kip,Kdp,Ts);           % Rate regolator for roll dynamics
R_inner_pitch = pid(Kpq,Kiq,Kdq,Ts);          % Rate regolator for pitch dynamics

% Once the system is defined we can set the point of interests
X1 = AnalysisPoint('deltaL');
X2 = AnalysisPoint('deltaOmega');
X3 = AnalysisPoint('p');
X4 = AnalysisPoint('phi');


L_inner_roll  = X3*motor*G_q*X2*mixer*X1*R_inner_roll ;
L_inner_pitch = motor*G_q*mixer*R_inner_pitch;

if 1 
figure('name','Roll inner loop - HINF');
bode(L_inner_roll);margin(L_inner_roll); grid;

figure('name','Pitch inner loop');
bode(L_inner_pitch);margin(L_inner_pitch); grid;

figure;
bodemag(L_inner_roll); hold on ; bodemag(L_inner_pitch); legend('p inner loop','q inner loop');grid;
end

% funzioni d'anello esterne (sugli angoli)
R_outer = pid(KRP,0,KRD,Ts);
L_outer_roll = G_roll*feedback(L_inner_roll,1)*R_outer;
L_outer_roll.u = 'phi_{ref}';
L_outer_pitch = G_roll*feedback(L_inner_pitch,1)*R_outer;
L_outer_pitch.u = 'theta_{ref}';

if 1
figure('name','Roll outer loop - HINF');
bode(L_outer_roll);margin(L_outer_roll); grid;

figure('name','Pitch outer loop');
bode(L_outer_pitch);margin(L_outer_pitch); grid;

figure;
bodemag(L_outer_roll); hold on ; bodemag(L_outer_pitch); legend('roll','pitch');grid;
end
%% Sensitivity functions

loops = loopsens(G_roll*feedback(L_inner_pitch,1), R_outer);
figure
bodemag(L_outer_roll,'r',loops.Si,'b',loops.Ti,'g')
legend('L','S','T')
xlim([1e-2 1e2]);
grid minor

%% Partendo dalle fdt ottenute, ricaviamo le specifiche per Hinf

% H Inf syntesys on the PITCH

% Innter regulator
% The starting parameters have been obtained by manual tuning the real
% system
Cq0 = tunablePID('Cq0','pid');
Cq0.Kp.Value = 0.58;
Cq0.Ki.Value = 0.7;
Cq0.Kd.Value = 0.075;
Cq0.Tf.Value = 0.01;                % set parameter Tf
Cq0.Tf.Free = false;
Cq0.u = 'e_q';                      % Input error for inner (rate) regulator
Cq0.y = 'q';                        % Output of the inner regulator

% Outer regulator
Ctheta0 = tunablePID('Ctheta0','pd');                
Ctheta0.Kp.Value = 1.9;                 % initialize Kp
Ctheta0.Kd.Value =  0.005;                % initialize Kd
Ctheta0.Tf.Value = 0.01;                % set parameter Tf
Ctheta0.Tf.Free = false;                % fix parameter Tf to this value
Ctheta0.u = 'e_theta';                  % Input error for Outer regulator                              
Ctheta0.y = 'deltaTheta';               % Output of the outer regualor

% Once the system is defined we can set the point of interests
X1 = AnalysisPoint('deltaM');
X2 = AnalysisPoint('deltaOmega');
X3 = AnalysisPoint('q');
X4 = AnalysisPoint('theta');

InnerLoop0 = feedback(X3*motor*G_q*X2*mixer*X1*Cq0,1);
InnerLoop0.u = 'q_ref';

% the outer loop observed output is theta
CL0 = feedback(G_roll*InnerLoop0*Ctheta0,X4);

% Specifying names for the input and output channels allows you to identify 
% them when you specify tuning requirements for the system.
CL0.inputName = 'theta_0'; 
CL0.OutputName = 'theta';


%% TUNING REQUIREMENTS

% ---- Tracking error ----
% This requirement specifies the maximum relative error 
% (gain from reference input to tracking error) as a function of frequency
% -------------------------------------------------------------------------

wc = 1.8;                               %[rad/s] bandwidth of the system
responsetime = 2/wc;                   %[s] In this way we are able to track all the signals in the bandwidth of the system
dcerror = 0.0001;                      %[%] steady state error ( relative gain of input vs output) (default value)
peakerror = 1.3;                    
R1 = TuningGoal.Tracking('theta_0','theta',responsetime,dcerror,peakerror);


% Roll-off requirements
%R1 = TuningGoal.MaxLoopGain('theta',wc/s);


attfact = frd([100 1 1],[0.1*wc wc 10*wc]);
R3 = TuningGoal.Rejection('deltaOmega',attfact);

%Tune the control system
SoftReqs = [];
%HardReqs = [Rtrack Rreject];
HardReqs = [R1 R3];
[CL,fSoft,gHard] = systune(CL0,SoftReqs,HardReqs);

% Plot results
figure('name', 'Tracking Requirement')
viewSpec(R1,CL)
figure('name', 'Roll-off requirements')
viewSpec(R3,CL)

%
%Control tuned
Cp = getBlockValue(CL,'Cq0')
Cp.u = 'e_q'; Cp.y = 'deltaM';
Ctheta = getBlockValue(CL,'Ctheta0')
Ctheta.u = 'e_{theta}'; Ctheta.y = 'q_0';

% Step response
figure('name','Closed-loop response')
step(CL)
grid minor
title('Closed-loop response')

%% Error parametrization
%Define the nominal behaviour of the system
sysnom = G_q.NominalValue;

%Given the uncertainty, I can define a vector of possible system
parray = usample(G_q,10);
om = logspace(-2,2);
parrayg = frd(parray,om);

%Plot the nominal behaviour plus a "cloud" of possible bode diagram
figure
bode(parray,'b',sysnom,'r+',om); grid

%Creates an uncertain linear, time-invariant objects are used to represent 
%unknown dynamic objects whose only known attributes are bounds on their frequency response
unc = ultidyn('unc',[1 1]);

%Define error and relative error
error = (sysnom-parray);
relerror = error/sysnom;

%Find the multiplicative uncertainty form
[Pm,InfoPm] = ucover(parrayg,sysnom);
Wm = InfoPm.W1;   
figure
bodemag(relerror,'b--',Wm,'r',om); grid
title('Multiplicative Uncertainty')
legend('Relative errors', 'Magnitude of W','location','southwest')

%Find the additive uncertainty form
[Pa,InfoPa] = ucover(parrayg,sysnom,1,'additive');
Wa = InfoPa.W1; 
figure
bodemag(error, 'b--',Wa,'r',om); grid
title('Additive Uncertainty')
legend('Errors', 'Magnitude of W','location','southwest')

%Final definition of the system with both uncertainty form
sysmul = sysnom*(1 + Wm*unc);
sysadd = sysnom + Wa*unc;





