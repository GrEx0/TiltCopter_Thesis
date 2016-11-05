%% Questo script non è quello effettivamente usato per fare la taratura H-inf del tiltrotor.
% vedi lo script "manual_tuning_parametri290816.m" per la taratura
% effettiva.
% la differenza fra i due script sta nel fatto che in questo script viene
% effettuata, tramite Hinf, la taratura dei due anelli in cascata
% contemporaneamente. Tuttavia con questo approcio non siamo riusciti a
% definire dei requisiti tali da poter ottenere un tuning soddisfacente.
% Con manual_tuning_parametri290816.m siamo andati invece a fare la sintesi
% H-inf dei due anelli in modo separato, definendo opportune specifiche per
% entrambi gli anelli.
%% Import parameters
close all;
Parameters;
%% Robust control syntesys - H-INFINITY / SYSTUNE
s = tf('s');

% Identified roll dynamics
A1_sA = ureal('A1_sA',8.387902003,'PlusMinus',0.006483558);
B1_sA = ureal('B1_sA',6.844908507,'PlusMinus',0.006598076);
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
sys_delay = pade(sys_delay,3);

% Mixer transfer function ( to obtain the real model frol deltaL ->
% deltap), and not from deltaOmega -> deltap)
mixer = ss(1/(4*Kt*b*omega_hover));
mixer.u = 'deltaL'; mixer.y = 'deltaOmega';

% Motor transfer function
motor = 1/(1+tau*s);

% For the outer loop we will use a PD (Intrinsic integrator of the system
% Inner loop -> PID

% Outer regulator
Cphi0 = tunablePID('Cphi0','pd');                
Cphi0.Kp.Value = 1.9;                % initialize Kp
Cphi0.Kd.Value =  0.005;           % initialize Kd
Cphi0.Tf.Value = 0.01;              % set parameter Tf
Cphi0.Tf.Free = false;              % fix parameter Tf to this value
Cphi0.u = 'e_phi';                  % Input error for Outer regulator                              
Cphi0.y = 'deltaPhi';               % Output of the outer regualor

% Innter regulator
Cp0 = tunablePID('Cp0','pid');
Cp0.Kp.Value = Kpp;
Cp0.Ki.Value = Kip;
Cp0.Kd.Value = Kdp;
Cp0.Tf.Value = 0.01;                % set parameter Tf
Cp0.Tf.Free = false;
Cp0.u = 'e_p';                      % Input error for inner (rate) regulator
Cp0.y = 'p';                        % Output of the inner regulator


% Once the system is defined we can set the point of interests
X1 = AnalysisPoint('deltaL');
X2 = AnalysisPoint('deltaOmega');
X3 = AnalysisPoint('p');
X4 = AnalysisPoint('phi');



% Connect these components to build a model of the entire closed-loop control system
% -->| Cphi0 |-- p_ref ---> | Cp0 | -- deltaL --> | Mixer | -- deltaOmega --> | delay |
% -- deltaOmega_delayed --> | Gp | -- p --> | Motor | --> | 1/s | -->

% First try, neglect motor dynamics
%InnerLoop0 = feedback(X3*motor*G_p*X2*sys_delay*mixer*X1*Cp0,1); % VERSIONE CON DELAY
InnerLoop0 = feedback(X3*motor*G_p*X2*mixer*X1*Cp0,1);
InnerLoop0.u = 'p_ref';

% the outer loop observed output is phi
CL0 = feedback(G_roll*InnerLoop0*Cphi0,X4);

% Specifying names for the input and output channels allows you to identify 
% them when you specify tuning requirements for the system.
CL0.inputName = 'phi_0'; 
CL0.OutputName = 'phi';


%% TUNING REQUIREMENTS

% ---- Tracking error ----
% This requirement specifies the maximum relative error 
% (gain from reference input to tracking error) as a function of frequency
% -------------------------------------------------------------------------

wc = 3;                               %[rad/s] bandwidth of the system
responsetime = 2/wc;                  %[s] In this way we are able to track all the signals in the bandwidth of the system
dcerror = 0.0001;                      %[%] steady state error ( relative gain of input vs output) (default value)
peakerror = 1.2;                    
% freq_err = frd([0.01 0.01 1],[0 2 10*wc]); % Maximum relative error is 0.1 (1%) in the frequency range [0.1wc wc], the relative error increases to 100% after 2 decades (100*wc)         
% R1 = TuningGoal.Tracking('phi_0','phi',freq_err);
R1 = TuningGoal.Tracking('phi_0','phi',responsetime,dcerror,peakerror);
%R1 = TuningGoal.Tracking('phi_0','phi',1,0.0001,1.2);

figure;
viewSpec(R1);                       % Shows the first request

% Roll-off requirements
R2 = TuningGoal.MaxLoopGain('phi',wc/s);
%R2.Focus = [0.1*wc,1000*wc];

% R2 = TuningGoal.MaxLoopGain('p_disturb',100,0.1);
 %R2 = TuningGoal.MaxLoopGain('phi',wc/s);
% R2 = TuningGoal.MaxLoopGain('p',100/s);
% R2.Openings = 'phi';
figure;
viewSpec(R2);

% ---- Disturbance rejection ----
% This requirement specifies the minimum attenuation of a disturbance 
% injected at a specified location in a control system
% -------------------------------------------------------------------------

% we want an attenuation of 100 (40db) from 0.1*wc to wc*5, and a decade
% after we don't care since we are out of the bandwidth of the system
% attfact = frd([100 100 1],[0.1*wc wc*5 wc*50]); 
% attfact = frd([100 1 1],[0.1*wc wc 10*wc]);
% attfact = frd([100 1 1],[0.1*100 100 10*100]);
%R3 = TuningGoal.Rejection('deltaOmega',attfact);

% figure;
% viewSpec(R3);                       % Shows the first request

%Tune the control system
SoftReqs = [];
%HardReqs = [Rtrack Rreject];
HardReqs = [R1 R2];
[CL,fSoft,gHard] = systune(CL0,SoftReqs,HardReqs);

% Plot results
figure('name', 'Tracking Requirement')
viewSpec(R1,CL)
figure('name', 'Roll-off requirements')
viewSpec(R2,CL)
% figure('name', 'Disturbance rejection requirements')
% viewSpec(R3,CL)

figure('name','Closed-loop response')
step(CL)
grid minor
title('Closed-loop response')


%Control tuned
Cp = getBlockValue(CL,'Cp0')
Cp.u = 'e_q'; Cp.y = 'deltaL';
Cphi = getBlockValue(CL,'Cphi0')
Cphi.u = 'e_{phi}'; Ctheta.y = 'p_0';
%Loop and transfer function
InnerLoop = feedback(G_p*sys_delay*mixer*Cp,1);
L = G_roll*InnerLoop*Cphi;

%Loop function and sensitivity functions
loops = loopsens(G_roll*InnerLoop, Cphi);
figure
bodemag(CL,'r',loops.Si,'b',Cphi/(1+L),'g',{1e-3,1e3})
legend('F','S','Q')
grid minor