% This script plot the obtained loop functions (inner and outer) of the
% attitude control for the roll dynamics
% It also performs a robustness analysis based on additive and
% multiplicative system uncertainty, sampling 50 random transfer functions
% from the uncertain model G_p.

%% Import parameters
close all;
Parameters;
%% Define the transfer functions
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
sys_delay_pade = pade(sys_delay,1);             % Padè approx, 1rd order

% Mixer transfer function ( to obtain the real model frol deltaL ->
% deltap), and not from deltaOmega -> deltap)
mixer = ss(1/(4*Kt*b*omega_hover));
mixer.u = 'deltaL'; mixer.y = 'deltaOmega';

% Motor transfer function
motor = 1/(1+tau*s);

Ts = 0.01;                               % Order of the filter for the pids

%% Inner loop analysis

R_inner_roll_man  = pid(0.58,0.7,0.075,Ts);   % Manual PID values
R_inner_roll_hinf = pid(Kpp,Kip,Kdp,Ts);

% Inner open-loop transfer function
L_inner_roll_man  = motor*G_p*mixer*R_inner_roll_man ;
L_inner_roll_hinf = motor*G_p*mixer*R_inner_roll_hinf;

% Plots inner loop bode diagrams
if 1 
figure('name','Roll inner loop - Manual values');
bode(L_inner_roll_man);margin(L_inner_roll_man); grid;

figure('name','Roll inner loop - HINF values');
bode(L_inner_roll_hinf);margin(L_inner_roll_hinf); grid;
end

T_inner_man  = feedback(L_inner_roll_man,1);
T_inner_hinf = feedback(L_inner_roll_hinf,1);


% Sensitivity functions INNER LOOP -  ONLY TUNED SYSTEM
loops = loopsens(motor*G_p*mixer,R_inner_roll_hinf);
figure
bodemag(loops.Li,'r',loops.Si,'b',loops.Ti,'g')
legend('L_{iner}','S_{inner}','T_{inner}')
%xlim([1e-2 1e2]);
grid minor

%% Outer loop analysis

% Manual tuning
R_outer_man = pid(1.9,0,0.005,Ts);
L_outer_roll_man = G_roll*T_inner_man*R_outer_man;
L_outer_roll_man.u = 'phi_0';

%HINF tuning
R_outer_hinf = pid(KRP,0,KRD,Ts);
L_outer_roll_hinf = G_roll*T_inner_hinf*R_outer_hinf;
L_outer_roll_hinf.u = 'phi_0';

% Plot Outer loops bode diagrams
if 1
% figure('name','Roll outer loop - Manual tuning');
% bode(L_outer_roll_man);margin(L_outer_roll_man); grid;

figure('name','Roll outer loop - HINF tuning');
bode(L_outer_roll_hinf);margin(L_outer_roll_hinf); grid;
end

% Sensitivity functions OUTER LOOP -  ONLY TUNED SYSTEM
loops = loopsens(G_roll*T_inner_hinf,R_outer_hinf);
figure
bodemag(loops.Li,'r',loops.Si,'b',loops.Ti,'g')
legend('L','S','T')
%xlim([1e-2 1e2]);
grid minor

% Step response ( from phi_0 -> phi)
if 1
% T_outer_man  = feedback(L_outer_roll_man,1);
T_outer_hinf = feedback(L_outer_roll_hinf,1);
figure;
%step(T_outer_man); 
%hold on
step(T_outer_hinf);
%hold off
end

%% Uncertainty analysis

%Define the nominal behaviour of the system
sysnom = G_p.NominalValue;
%Given the uncertainty, I can define a vector of possible system
parray = usample(G_p,50);           % Takes 50 random uncertain transfer functions from G_p (Monte Carlo extractions)
om = logspace(-2,2);                % Defines a logarithmic vector from 10^-2 to 10^2
parrayg = frd(parray,om);           % Computes the frequency response for the 50 random tf in the om range

%Plot the nominal behaviour plus a "cloud" of possible bode diagrams
figure
bode(parray,'b',sysnom,'r+',om); grid

%Creates an uncertain linear, time-invariant objects are used to represent 
%unknown dynamic objects whose only known attributes are bounds on their frequency response
unc = ultidyn('unc',[1 1]);

%Define error and relative error
error = (sysnom-parray);
relerror = error/sysnom;

% Find the multiplicative uncertainty form
% For more details see: http://www.mathworks.com/help/robust/ref/ucover.html
[Pm,InfoPm] = ucover(parrayg,sysnom);
Wm = InfoPm.W1;                             % Is the shaping filter that describes the maximum relative error for the multiplicative uncertainty
figure
bodemag(relerror,'b--',Wm,'r',om); grid
title('Multiplicative Uncertainty')
legend('Relative errors', 'Magnitude of W','location','southwest')

%Find the additive uncertainty form
[Pa,InfoPa] = ucover(parrayg,sysnom,1,'additive');
Wa = InfoPa.W1;                             % Is the shaping filter that describes the maximum relative error for the additive uncertainty
figure
bodemag(error, 'b--',Wa,'r',om); grid
title('Additive Uncertainty')
legend('Errors', 'Magnitude of W','location','southwest')

%Final definition of the system with both uncertainty form
sysmul = sysnom*(1 + Wm*unc);
sysadd = sysnom + Wa*unc;

% Monte carlo analysis on the closed loop system
L_inner_roll_uncert = motor*parray*mixer*R_inner_roll_hinf;
T_inner_uncert = feedback(L_inner_roll_uncert,1);
L_outer_robustness =G_roll*T_inner_uncert*R_outer_hinf;
L_outer_robustness.u = 'e_{phi}';
figure; 
bode(L_outer_robustness,'b');
hold on
bode(L_outer_roll_hinf, 'r+')
hold off
grid minor
legend('Uncertain Models','Nominal Model','location','southwest')

T_uncert = feedback(L_inner_roll_uncert,1);
figure; step(T_uncert);






