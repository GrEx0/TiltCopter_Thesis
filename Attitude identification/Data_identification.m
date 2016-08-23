% Author: Claudio Micheli
% This script elaborates the acquired data and performs the parameter
% estimation of the unknowns 
%close all;
clear all;
clc

%% System parameters 

EXPERIMENTAL_DATA = 'RBS_a_deltaTH1_290716';     % Data you want to do the estimation with
start_sample = 2200;                   % Sample from you wish to start identifying
Ts = 0.01                              %Sampling time
tau_f = 1/30;                         % FIlter constant use 30 or 100

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
%omega_hover = sqrt((m*g/Kt)/4);       % [rad/s] Angular velocity at Hovering 
x1 = [6.0312 80.4859]; 
omega_hover = 50*x1(1)+x1(2);
Cl_alpha = 2*pi;
dCt_dp = Cl_alpha *sigma * 1/(R*omega_hover) * 1/8 *b;
stab_der_L = -2 * ro * A * R^2 *omega_hover^2 * dCt_dp*b            % Stability derivative on roll axis

%% Analytical model state space system definition

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

if 0
bode(roll_ss_p);grid;           % Bode plot of the TF -> bandwith about
figure;bode(G_p);grid;
end
%% Data conditioning

% Input/Output data from the identification campaign
load(EXPERIMENTAL_DATA);

% conversion from pwm -> TH% is TH% = 0.1 * PWM - 100
m_th = 0.1;
q_th = -100;
control_motor_4 = mixer_ctr_motor_4*m_th + q_th;
%figure; plot(control_motor_4);title('Control input motor 4')
control_motor_2 = mixer_ctr_motor_2*m_th + q_th;
%figure;plot(control_motor_2);title('Control input motor 2')

% We are interested in delta_omega sent to the motors;
delta_omega_ctr = control_motor_4 - control_motor_2 ;

%% Noise reduction 
u = delta_omega_ctr*1/x1(1); 
y = imu_raw_gyro_x(1:length(u));

if 1 
    figure;
    plot(y);
    title('unfiltered data output');
end

t  = .01 * [0:numel(u)-1];
num_f = [1];
den_f = [tau_f 1]
G_f   = tf(num_f,den_f)

y_f = lsim(G_f,y,t);
u_f = lsim(G_f,u,t);


if 1                % Enable filter vs non filtered output
  figure;
  plot(t,y,t,y_f);
  title('Filtered output vs NON filtered');
end

if 0               % Enable filter vs non filtered input
  figure;
  plot(t,u,t,u_f);
  title('Filtered input vs NON filtered');
end
 
y_srivc = y_f(start_sample:end);
u_srivc = u_f(start_sample:end);
% Delay correction
  y = y_f(9:end);
  u=u_f(1:end-8);
%  y = y_f;
%  u = u_f;
    u=u(start_sample:end);
    y=y(start_sample:end);    
  
% normalizza e rimuove media
    u = u - mean(u);  
    y = y - mean(y);
    scal_u = norm(u);
    scal_y = norm(y); 
    u = 1/scal_u * u;
    y = 1/scal_y * y;
    
% normalizza e rimuove media srivc
    u_srivc = u_srivc - mean(u_srivc);  
    y_srivc = y_srivc - mean(y_srivc);
    scal_u_srivc = norm(u_srivc);
    scal_y_srivc = norm(y_srivc); 
    u_srivc = 1/scal_u_srivc * u_srivc;
    y_srivc = 1/scal_y_srivc * y_srivc;
    
    
   
    figure;plot(u);title('Normalized input u')  
    figure;plot(y);title('Normalized output y')  

% Conversion to deltaOmega [rad/s]
% x1 = [6.0312 80.4859];                                      %RAD/S vs THROTTLE: Y [RAD/S] = m*X[TH%] + q; x1 = [m q]
% delta_omega_ctr = delta_omega_ctr*x1(1);
% delta_omega_ctr = delta_omega_ctr;
% figure; plot(delta_omega_ctr);title('deltaOmega [rad/s]');

%% 
% % Estimate A1 and B1 parameters
opt = greyestOptions;
opt.InitialState = 'auto';
opt.DisturbanceModel = 'auto';
opt.Focus = 'simulation';
opt.SearchMethod = 'auto';
opt_compare = compareOptions('InitialCondition','zero');
%  sys = greyest(data,init_sys,opt); 
% 
% % Analyze the result. 
% %
%  figure;
% compare(data,sys,Inf,opt_compare)   

%% Identification greyest - single fdt (only the fdt from dOmega -> p is considered)
fcn_type = 'c';
dLdu_g = 4*Kt*b*omega_hover;

% parameter guess
A1 =  stab_der_L/Jxx;
B1 = dLdu_g/Jxx;
 
data_single = iddata(y,u,Ts);
data_single.InputName = 'deltaOmega';
data_single.InputUnit = 'rad/s';
data_single.OutputName = {'Roll rate'};
data_single.OutputUnit = {'rad/s'};
data_single.Tstart = 0;
data_single.TimeUnit = 's';

% SRIVC
data_single_srivc = iddata(y_srivc,u_srivc,Ts);
data_single_srivc.InputName = 'deltaOmega';
data_single_srivc.InputUnit = 'rad/s';
data_single_srivc.OutputName = {'Roll rate'};
data_single_srivc.OutputUnit = {'rad/s'};
data_single_srivc.Tstart = 0;
data_single_srivc.TimeUnit = 's';

% Again, you want to estimate the stability derivative and the inertia Jxx
parameters = {'A1',A1;'B1',B1};
%parameters = {'stab_der_L',stab_der_L;'Jxx',Jxx;'dLdu_g',dLdu_g};

init_sys_single = idgrey('Roll_dynamics_single',parameters,fcn_type);
% init_sys_single.Structure.Parameters(3).Free = false;

sys_single = greyest(data_single,init_sys_single,opt);
% figure;
% compare(data_single,sys_single,Inf,opt_compare);

% VAF computation
t  = .01 * [0:numel(u)-1];
yi = lsim(sys_single,u,t);
vaf_grey = vaf(y,yi);

figure;
plot(t,y,t,yi);
title('Real output VS Model output GREY');

% SRIVC Identification
t  = .01 * [0:numel(u_srivc)-1];
 nn = [1 1 0];
 Msrivc = tdsrivc(data_single_srivc,nn);
 present(Msrivc);
  %compare the model output with the measured output
  if 0 
    figure;
    comparec(data_single_srivc,Msrivc);
  end
  yi_srivc = lsim(Msrivc,u_srivc,t);
  vaf_srivc= vaf(y_srivc,yi_srivc);
 
  if 1
      figure;
      plot(t,y_srivc,t,yi_srivc);
      title('Real output VS Model output SRIVC');
  end
 % Present results
fprintf('VAF GREY : %2f  VAF SRIVC %2f \n',round(vaf_grey,2),round(vaf_srivc,2));
%grey est
res_grey = getpvec(sys_single);
fprintf('A1 grey:%3f , B1 grey: %3f \n',res_grey(1),res_grey(2));
res_cov_grey =getcov(sys_single); 
fprintf('A1 var:%3f , B1 var: %3f \n',res_cov_grey(1,1),res_cov_grey(2,2));

%srivc
res_grey = getpvec(Msrivc);
fprintf('A1 srivc:%3f , B2 srivc: %3f \n',res_grey(1),res_grey(2));
res_cov_grey =getcov(Msrivc); 
fprintf('A1S var:%3f , B2s var: %3f \n',res_cov_grey(1,1),res_cov_grey(2,2));
  
 figure;
 t  = .01 * [0:numel(u)-1];
 plot(t,y,t,yi,t,yi_srivc(1:numel(yi)))
 title('GREY MODEL VS SRIVC MODEL');
 
