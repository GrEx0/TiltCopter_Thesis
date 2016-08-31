%% Import parameters
close all;
Parameters;
%% Robust control syntesys - H-INFINITY / SYSTUNE  REQUIREMENT DEFINITIONS BASED ON MANUAL TUNING
s = tf('s');


% Traslational dynamics
G_t = 2*Kt*omega_hover^2/m *1/s;

% Mixer transfer function (for the traslational movement)
mixer = ss(1/(2*Kt*omega_hover^2));
mixer.u = 'deltaFx'; mixer.y = 'deltaAlpha';

% ServoMotor transfer function
    B0 =ureal('B0',4670.252,'PlusMinus',72.11);
    B2 =ureal('B2',28.36,'PlusMinus',1.68);
    B3 =ureal('B3',598.45,'PlusMinus',7.97);
    B4 =ureal('B4',4650.23,'PlusMinus',1.55);
    
    num_i = B0;
    den_i = [1 B2 B3 B4];
    servo = tf(num_i,den_i);
%% Controllers definition

Ts = 0.01;                               % Order of the filter for the pids

R_Fx = pid(Kp_u,0,Kd_u,Ts);           % Rate regolator for roll dynamics

% Once the system is defined we can set the point of interests
X1 = AnalysisPoint('deltaFx');
X2 = AnalysisPoint('u_0');
X3 = AnalysisPoint('u');
X4 = AnalysisPoint('deltaAlpha');



L_inner = X3*G_t*servo*X4*mixer*X1*R_Fx;

CL_sys = feedback(L_inner,X3);

%% Sensitivity functions

loops = loopsens(X3*G_t*servo*X4*mixer*X1, R_Fx);
figure('name','Sensitivity functions - MANUAL TUNING');
bodemag(L_inner,'r',loops.Si,'b',loops.Ti,'g')
legend('L','S','T')
xlim([1e-2 1e2]);
grid minor


%% Partendo dalle fdt ottenute, ricaviamo le specifiche per Hinf

% H Inf syntesys 

% Innter regulator
% The starting parameters have been obtained by manual tuning the real
% system
Cu0 = tunablePID('Cu0','pid');
Cu0.Kp.Value = Kp_u;
Cu0.Ki.Value = 0;
Cu0.Kd.Value = Kd_u;
Cu0.Tf.Value = 0.01;                % set parameter Tf
Cu0.Tf.Free = false;
Cu0.u = 'e_u';                      % Input error for inner (rate) regulator
Cu0.y = 'deltaFx';                        % Output of the inner regulator


CL0 = feedback(X3*G_t*servo*X4*mixer*X1*Cu0,1);
CL0.inputName = 'u_0';
CL0.OutputName = 'u';

%% TUNING REQUIREMENTS

% ---- Tracking error ----
% This requirement specifies the maximum relative error 
% (gain from reference input to tracking error) as a function of frequency
% -------------------------------------------------------------------------

wc = 1.2;                               %[rad/s] bandwidth of the system
responsetime = 2/wc;                   %[s] In this way we are able to track all the signals in the bandwidth of the system
dcerror = 0.0001;                      %[%] steady state error ( relative gain of input vs output) (default value)
peakerror = 1.2;                    
R1 = TuningGoal.Tracking('u_0','u',responsetime,dcerror,peakerror);


% Roll-off requirements
%R1 = TuningGoal.MaxLoopGain('theta',wc/s);


attfact = frd([100 1 1],[0.1*wc wc 10*wc]);
R3 = TuningGoal.Rejection('deltaAlpha',attfact);

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
Cu = getBlockValue(CL,'Cu0')
Cu.u = 'e_v'; Cu.y = 'deltaFx';

% Step response
figure('name','Closed-loop response')
step(CL)
grid minor
title('Closed-loop response')

L_inner_opt = X3*G_t*servo*X4*mixer*X1*Cu;
figure;
bode(L_inner_opt);margin(L_inner_opt);
% %% Error parametrization
% %Define the nominal behaviour of the system
% sysnom = G_.NominalValue;
% 
% %Given the uncertainty, I can define a vector of possible system
% parray = usample(G_q,10);
% om = logspace(-2,2);
% parrayg = frd(parray,om);
% 
% %Plot the nominal behaviour plus a "cloud" of possible bode diagram
% figure
% bode(parray,'b',sysnom,'r+',om); grid
% 
% %Creates an uncertain linear, time-invariant objects are used to represent 
% %unknown dynamic objects whose only known attributes are bounds on their frequency response
% unc = ultidyn('unc',[1 1]);
% 
% %Define error and relative error
% error = (sysnom-parray);
% relerror = error/sysnom;
% 
% %Find the multiplicative uncertainty form
% [Pm,InfoPm] = ucover(parrayg,sysnom);
% Wm = InfoPm.W1;   
% figure
% bodemag(relerror,'b--',Wm,'r',om); grid
% title('Multiplicative Uncertainty')
% legend('Relative errors', 'Magnitude of W','location','southwest')
% 
% %Find the additive uncertainty form
% [Pa,InfoPa] = ucover(parrayg,sysnom,1,'additive');
% Wa = InfoPa.W1; 
% figure
% bodemag(error, 'b--',Wa,'r',om); grid
% title('Additive Uncertainty')
% legend('Errors', 'Magnitude of W','location','southwest')
% 
% %Final definition of the system with both uncertainty form
% sysmul = sysnom*(1 + Wm*unc);
% sysadd = sysnom + Wa*unc;
% 
% 
% 
% 
% 
