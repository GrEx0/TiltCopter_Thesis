% Tiltrotor Thesis
% Author: Claudio Micheli
% Latest review: 07.08.15

% Script description: This script plots the figures used in the tesis
%                     for the servomotor identification results.
%                     It loads the data, does a little bit of processing
%                     and then simply plots the results

close all
clear all

%% SETUP VALUES
LOGS_FOLDER = 'parsed_logs';
PARSED_LOG = '12-07-16_act_id_4';
PARSED_LOG_CROSS = 'actuators_ident_3';     % Log for crossvalidation
load(strcat(LOGS_FOLDER,'/',PARSED_LOG,'/',PARSED_LOG));
Ts = 0.010;
test_duration = 17;
q_servo = 1.5000e+03;
m_servo =   572.9578;
start_sample  = 1;
n_param = 2             % number of statistical parameters you want to keep

load(strcat(LOGS_FOLDER,'/',PARSED_LOG,'/',PARSED_LOG),'ground_attitude_roll','mixer_ctr_servo_4')
    
    % Number of samples recorded
    id_samples = length(ground_attitude_roll);
   
    % Define the "real" sampling time
    Ts = test_duration/id_samples;
    
  %Conversion from [ms] -> [deg]
    ctr_signal  = -(mixer_ctr_servo_4-q_servo)*1/m_servo*180/pi;
    crop_data = ground_attitude_roll;
    
% Plot input/output signal
figure;
title(PARSED_LOG);
plot(ctr_signal)
hold on
plot(ground_attitude_roll)
hold off

% Plot in scala dei tempi
if 1
    plot(t,ctr_signal,t,ground_attitude_roll);
end

%% Identified system definition
      
    B0 =ureal('B0',4670.252,'PlusMinus',72.11);
    B2 =ureal('B2',28.36,'PlusMinus',1.68);
    B3 =ureal('B3',598.45,'PlusMinus',7.97);
    B4 =ureal('B4',4650.23,'PlusMinus',1.55);
    
    num_i = B0;
    den_i = [1 B2 B3 B4];
    G_i = tf(num_i,den_i);
    figure;
    bode(G_i);

%% Plot
u = ctr_signal;
u = u(1:1286);
y = ground_attitude_roll;
y = y(1:length(u));
t  = Ts * [0:numel(u)-1];

% Filtering of measured output 
tau_f = 1/30;                               % Filter time constant
num_f = [1];
den_f = [tau_f 1]
G_f   = tf(num_f,den_f)
y_f = lsim(G_f,y,t);

if 0                % Enable filter vs non filtered output
    figure;
    plot(t,y,t,y_f);
    title('Filtered output vs NON filtered');
end
y = y_f;

% Plot input vs output real
figure;
plot(t,u,t,y);
title('Real input vs real output');

% Simulate the identified model with same input
y_i = lsim(G_i,u,t);

% Plot the results with VAF
vaf_i = vaf(y,y_i);
figure;
plot(t,y,t,y_i);
title_str = sprintf('Real output vs model output - VAF %2f \n\r',vaf_i);
title(title_str);
