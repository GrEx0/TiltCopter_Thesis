% Author: Claudio Micheli
% This script elaborates the acquired data and performs the parameter
% estimation of the unknowns 
close all;
clear all;

EXPERIMENTAL_DATA = 'RBS_IDENT_1_deltaTH3';     % Data you want to do the estimation with
Ts = 0.01                              %Sampling time

% Analytical model
m = 1.900                             %[Kg] Mass of the tiltrotor
g = 9.81;                             %[m/s^2] gravity acceleration
b = 0.55/2;                           %[m] length of the arm
Jxx = 0.034736;                       % Inertia on X axis, taken from identified Quadcopter
%Propellers information
nb = 2;                               %[1] Number of blades
D = 12*(0.0254);                      %[m] Propeller diameter
R = D/2;                              %[m] Propeller radius
A = pi*R^2;                           %[m^2] Disk area
ChordAv = .01;                        %[m] Average chord length
Ab = nb*R*ChordAv;                    %[m] Blade area
sigma = Ab/A;                         %[1] Solid ratio
ro = 1.225;                           %[kg*m^-3] Air density
nb = 2;                               %[1] Number of blades
Ct = 0.011859;                        %[1] Thrust coefficent
Kt = Ct*ro*A*R^2;
omega_hover = sqrt((m*g/Kt)/4);       % [rad/s] Angular velocity at Hovering 
Cl_alpha = 2*pi;
dCt_dp = Cl_alpha *sigma * 1/(R*omega_hover) * 1/8 *b;
stab_der_L = -2 * ro * A * R^2 *omega_hover^2 * dCt_dp*b            % Stability derivative on roll axis

% State space system definition
A = [stab_der_L *1/Jxx 0 ; 1 0 ];
B = [4*Kt*b*omega_hover*1/Jxx; 0 ];
C = [1 0;0 1];
D = 0;

states = {'p' 'phi'};
inputs = {'deltaOmega'};
outputs = {'p' 'phi'};

% Analytical roll model (guess)
roll_ss = ss(A,B,C,D,'statename',states,'inputname',inputs,'outputname',outputs);

roll_ss_p = roll_ss(1);         % Transfer function from Input dOmega -> roll rate p

% This can be written also in a TF representation (G_o is the same of
% roll_ss_p)
gain_p = 4*Kt*b*omega_hover*1/Jxx; 
den_p  = [1 -1/Jxx*stab_der_L] 
G_p = tf(gain_p,den_p);
roll_ss_phi = roll_ss(2);       % Transfer function from Input dOmega -> roll angle phi
bode(roll_ss_p);grid;           % Bode plot of the TF -> bandwith about

%% Identification

% Input/Output data from the identification campaign
load(EXPERIMENTAL_DATA);

% conversion from pwm -> TH% is TH% = 0.1 * PWM - 100
m_th = 0.1;
q_th = -100;
control_motor_4 = mixer_ctr_motor_4*m_th + q_th;
figure; plot(control_motor_4);title('Control input motor 4')
control_motor_2 = mixer_ctr_motor_2*m_th + q_th;
figure;plot(control_motor_2);title('Control input motor 2')

% We are interested in delta_omega sent to the motors;
delta_omega_ctr = control_motor_4 - control_motor_2 ; 
figure;plot(delta_omega_ctr);title('deltaTH%')
% Conversion to deltaOmega [rad/s]
x1 = [6.0312 80.4859];                                      %RAD/S vs THROTTLE: Y [RAD/S] = m*X[TH%] + q; x1 = [m q]
delta_omega_ctr = delta_omega_ctr*x1(1) +x1(2);
delta_omega_ctr = delta_omega_ctr;
figure; plot(delta_omega_ctr);title('deltaOmega [rad/s]');

%% Spectral analysis of PRBS signal

signal = delta_omega_ctr;
fftout=fft(signal);                     % Spectral (complex) vector
N = length(delta_omega_ctr);    
fs = 1/Ts;                              % Sampling frequency
T = (N-1)*Ts;
fnyquist = fs/2;                        % Nyquist frequency
df=1/T;                                 % Spectral resolution

vett_freq=0:df:fnyquist;
mod_y(1)=1/N*abs(fftout(1))             % Mean value
mod_y(2:N/2)=2/N*abs(fftout(2:N/2));    % Normalized module

% SPECTRUM PLOT
figure
semilogx(vett_freq,mod_y);grid;xlabel('[]');ylabel('[]');title('Spectrum - Module of PBRS');

X_mags = abs(fft(signal));
bin_vals = [0 : N-1];
fax_Hz = bin_vals*fs/N;
N_2 = ceil(N/2);
figure;
semilogx(fax_Hz(1:N_2), 20*log10(X_mags(1:N_2)))
xlabel('Frequency (Hz)')
ylabel('Power (dB)');
title({'Single-sided Power spectrum of PBRS' ...
    ' (Frequency in shown on a log scale)'});
axis tight


%% Identification - greyest - FULL STATE SPACE (2x2)

% y = imu_raw_gyro_x(1:(length(imu_raw_gyro_x)-1));
y = [ deg2rad(onboard_attitude_roll) imu_raw_gyro_x(1:(length(imu_raw_gyro_x)-1)) ];
u = delta_omega_ctr;
data = iddata(y,u,Ts);
data.InputName = 'deltaOmega';
data.InputUnit = 'rad/s';
data.OutputName = {'Roll angle', 'Roll rate'};
data.OutputUnit = {'rad', 'rad/s'};
data.Tstart = 0;
data.TimeUnit = 's';
%  nn = [1 1 0];
%  Msrivc = srivc(data,nn);
%  present(Msrivc);
%   %compare the model output with the measured output
%   figure;
%   comparec(data,Msrivc);

parameters = {'Stability derivative L',stab_der_L;'Inertia',Jxx;'Kt',Kt;'Arm length',b;'Omega hovering',omega_hover};
fcn_type = 'cd';
init_sys = idgrey('Roll_dynamics',parameters,fcn_type);

% Fixed parameters (those that you don't want to estimate)
init_sys.Structure.Parameters(3).Free = false;
init_sys.Structure.Parameters(4).Free = false;
init_sys.Structure.Parameters(5).Free = false;

%% 
% Estimate stab_der_L and Jxx. 
opt = greyestOptions;
opt.InitialState = 'auto';
opt.DisturbanceModel = 'auto';
opt.Focus = 'prediction';
opt.SearchMethod = 'auto';
sys = greyest(data,init_sys,opt); 

% Analyze the result. 
opt_compare = compareOptions('InitialCondition','zero');
figure;
compare(data,sys,Inf,opt_compare)   

%% Identification greyest - single fdt (only the fdt from dOmega -> p is considered)
dLdu_g = 4*Kt*b*omega_hover;
y = imu_raw_gyro_x(1:(length(imu_raw_gyro_x)-1));
data_single = iddata(y,u,Ts);
data_single.InputName = 'deltaOmega';
data_single.InputUnit = 'rad/s';
data_single.OutputName = {'Roll rate'};
data_single.OutputUnit = {'rad/s'};
data_single.Tstart = 0;
data_single.TimeUnit = 's';

% Again, you want to estimate the stability derivative and the inertia Jxx
parameters = {'Stability derivative L',stab_der_L;'Inertia',Jxx;'dLdu_g',dLdu_g};
init_sys_single = idgrey('Roll_dynamics_single',parameters,fcn_type);
init_sys.Structure.Parameters(3).Free = false;

sys_single = greyest(data_single,init_sys_single,opt);
figure;
compare(data_single,sys_single,Inf,opt_compare)


