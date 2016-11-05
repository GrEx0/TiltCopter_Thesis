%% Questo script è quello effettivamente usato per fare la taratura H-inf del tiltrotor.
% la differenza fra questo script e quello in /trash/HInftiltrotor.m t sta nel fatto che in quello nella cartella trash la sintesi viene
% effettuata, tramite Hinf, tarando i due anelli di controllo contemporaneamente. 
% Tuttavia con questo approcio non siamo riusciti a
% definire dei requisiti tali da poter ottenere un tuning soddisfacente.
% Con questo script invece,  siamo andati invece a fare la sintesi
% H-inf dei due anelli in modo separato, definendo opportune specifiche per
% entrambi gli anelli.
%% Import parameters
close all;
Parameters;
%% Robust control syntesys - H-INFINITY / SYSTUNE  REQUIREMENT DEFINITIONS BASED ON MANUAL TUNING
s = tf('s');


% Identified roll dynamics
A1_sA = ureal('A1_sA',8.387902003,'PlusMinus',3*0.006483558);           % Confidence bound 3sigma
B1_sA = ureal('B1_sA',6.844908507,'PlusMinus',3*0.006598076);
num_i = A1_sA;
den_i = [1 B1_sA];

% roll rate dynamic model w.o time delay
G_p = tf(num_i,den_i);
G_p = G_p *1/x1(1);                         % Correzione deltaOmega -> deltaTH%, dato che l'identificazione dava in ingresso deltaTH%

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

R_inner_roll = pid(0.58,0.7,0.075,Ts);           % Rate regolator for roll dynamics

% Once the system is defined we can set the point of interests
X1 = AnalysisPoint('deltaL');
X2 = AnalysisPoint('deltaOmega');
X3 = AnalysisPoint('p');
X4 = AnalysisPoint('phi');


L_inner_roll  = X3*motor*G_p*X2*mixer*X1*R_inner_roll ;

if 1 
figure('name','Roll inner loop - valori a mano');
bode(L_inner_roll);margin(L_inner_roll); grid;

end

% funzioni d'anello esterne (sugli angoli)
R_outer = pid(1.9,0,0.005,Ts);
L_outer_roll = G_roll*feedback(L_inner_roll,1)*R_outer;
L_outer_roll.u = 'phi_{ref}';

if 1
figure('name','Roll outer loop - valori a mano');
bode(L_outer_roll);margin(L_outer_roll); grid;
end
%% Sensitivity functions

loops = loopsens(G_roll*feedback(L_inner_roll,1), R_outer);
figure
bodemag(L_outer_roll,'r',loops.Si,'b',loops.Ti,'g')
legend('L','S','T')
xlim([1e-2 1e2]);
grid minor

%% Partendo dalle fdt ottenute, ricaviamo le specifiche per Hinf

% H Inf syntesys on the ROLL

% Innter regulator
% The starting parameters have been obtained by manual tuning the real
% system
Cp0 = tunablePID('Cp0','pid');
Cp0.Kp.Value = 0.58;
Cp0.Ki.Value = 0.7;
Cp0.Kd.Value = 0.075;
Cp0.Tf.Value = 0.01;                % set parameter Tf
Cp0.Tf.Free = false;
Cp0.u = 'e_p';                      % Input error for inner (rate) regulator

% Once the system is defined we can set the point of interests
X1 = AnalysisPoint('deltaL');
X2 = AnalysisPoint('deltaOmega');
X3 = AnalysisPoint('p');
X4 = AnalysisPoint('phi');

InnerLoop0 = feedback(X3*motor*G_p*X2*mixer*X1*Cp0,1);
InnerLoop0.u = 'p_0';

%% TUNING REQUIREMENTS INNER LOOP

% ---- Tracking error ----
% This requirement specifies the maximum relative error 
% (gain from reference input to tracking error) as a function of frequency
% -------------------------------------------------------------------------

% Inner loop speficications
%il test ieri aveva wc_inner = 10
wc_inner = 10;
responsetime = 2/wc_inner;             %[s] In this way we are able to track all the signals in the bandwidth of the system
dcerror = 0.0001;                      %[%] steady state error ( relative gain of input vs output) (default value)
peakerror = 1.25;                    
Req_inner = TuningGoal.Tracking('p_0','p',responsetime,dcerror,peakerror);

attfact = frd([100 1 1],[0.1*wc_inner wc_inner 10*wc_inner]);
R3 = TuningGoal.Rejection('p',attfact);

%Tune the control system
SoftReqs = [];
%HardReqs = [Rtrack Rreject];
HardReqs = [Req_inner];
[CL_inner,fSoft,gHard] = systune(InnerLoop0,SoftReqs,HardReqs);


%Inner loop control tuned
R_inner_tuned = getBlockValue(CL_inner,'Cp0')
R_inner_tuned.u = 'e_q'; R_inner_tuned.y = 'deltaL';

%% Check the performances INNER LOOP

% View requirements
% Plot results
figure('name', 'Tracking Requirement')
viewSpec(Req_inner,CL_inner)
figure('name', 'Disturbance rejection requirements')
viewSpec(R3,CL_inner)

% Step CL_inner
figure;
step(CL_inner);
% Ricalcolo L_inner
L_inner_roll  = X3*motor*G_p*X2*mixer*X1*R_inner_tuned ;
if 1 
figure('name','Roll inner loop - HINF Tuned');
bode(L_inner_roll);margin(L_inner_roll); grid;
end

% Sensitivity functions
loops = loopsens(X3*motor*G_p*X2*mixer*X1, R_inner_tuned);
figure
bodemag(loops.Li,'r',loops.Si,'b',loops.Ti,'g')
legend('L','S','T')
%xlim([1e-2 1e4]);
grid minor



%% DEFINE THE NEW FUNCTIONS FOR OUTER LOOP

% Outer regulator
Cphi0 = tunablePID('Cphi0','pd');                
Cphi0.Kp.Value = 1.9;                 % initialize Kp
Cphi0.Kd.Value =  0.005;                % initialize Kd
Cphi0.Tf.Value = 0.01;                % set parameter Tf
Cphi0.Tf.Free = false;                % fix parameter Tf to this value
Cphi0.u = 'e_theta';                  % Input error for Outer regulator                              
Cphi0.y = 'deltaTheta';               % Output of the outer regualor

% Redefine the outer regulator with the HINF parameters
Cp0 = tunablePID('Cp0','pid');
% Cp0.Kp.Value = 0.636;
% Cp0.Ki.Value = 5.75;
% Cp0.Kd.Value = 0.0583;
% Cp0.Tf.Value = 0.01;                % set parameter Tf
% Valori di partenza test #2
% Cp0.Kp.Value = 0.578;
% Cp0.Ki.Value = 0.7;
% Cp0.Kd.Value = 0.0158;
% Cp0.Tf.Value = 0.01;                % set parameter Tf
%valori di partenza test #3
% Cp0.Kp.Value = 0.188;
% Cp0.Ki.Value = 3.25;
% Cp0.Kd.Value = 0.0111;
% Cp0.Tf.Value = 0.01;                % set parameter Tf
% RESULT NON FUNZIONANO
%valori di partenza test #6
Cp0.Kp.Value = 0.3;
Cp0.Ki.Value = 0.697;
Cp0.Kd.Value = 0.00534;
Cp0.Tf.Value = 0.01;                % set parameter Tf
% RESULT OK
Cp0.Tf.Free = false;
Cp0.Kp.Free = false;
Cp0.Ki.Free = false;
Cp0.Kd.Free = false;
Cp0.u = 'e_p';                      % Input error for inner (rate) regulator

% Tunable L-inner
L_inner_roll = X3*motor*G_p*X2*mixer*X1*Cp0;

% the outer loop observed output is theta
CL0 = feedback(G_roll*feedback(L_inner_roll,1)*Cphi0,X4);

% Specifying names for the input and output channels allows you to identify 
% them when you specify tuning requirements for the system.
CL0.inputName = 'phi_0'; 
CL0.OutputName = 'phi';

%% TUNING REQUIREMENTS OUTER LOOP
% Outer loop specifications
wc = 1.6;                               %[rad/s] bandwidth of the system
responsetime = 2/wc;                   %[s] In this way we are able to track all the signals in the bandwidth of the system
dcerror = 0.0001;                      %[%] steady state error ( relative gain of input vs output) (default value)
peakerror = 1.3;                    
R1 = TuningGoal.Tracking('phi_0','phi',responsetime,dcerror,peakerror);

attfact = frd([10 1 1],[0.1*wc wc 10*wc]);
R3_outer = TuningGoal.Rejection('phi',attfact);

%Tune the control system
SoftReqs = [];
%HardReqs = [Rtrack Rreject];
HardReqs = [R1 R3_outer];
[CL,fSoft,gHard] = systune(CL0,SoftReqs,HardReqs);

% Plot results
figure('name', 'Tracking Requirement')
viewSpec(R1,CL)
figure('name', 'Disturbance rejection requirements')
viewSpec(R3_outer,CL)

%
%Control tuned
Cp = getBlockValue(CL,'Cp0')
Cp.u = 'e_p'; Cp.y = 'deltaL';
Ctheta = getBlockValue(CL,'Cphi0')
Ctheta.u = 'e_{theta}'; Ctheta.y = 'p_0';

%% Check the performances OUTER LOOP

% Step CLOSED LOOP OUTER
figure;
step(CL);

% Ricalcolo L_outer
L_inner_roll_tuned = X3*motor*G_p*X2*mixer*X1*Cp; 
L_outer  = G_roll*feedback(L_inner_roll_tuned,1)*Ctheta ;
if 1 
figure('name','Roll outer loop - HINF Tuned');
bode(L_outer);margin(L_outer); grid;
end

% Sensitivity functions
loops = loopsens(L_outer,Ctheta);
figure
bodemag(loops.Li,'r',loops.Si,'b',loops.Ti,'g')
legend('L','S','T')
%xlim([1e-2 1e2]);
grid minor

