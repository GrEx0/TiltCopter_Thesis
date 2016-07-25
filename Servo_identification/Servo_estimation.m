%% Servo data analysis - SRVIC approach         %
% Author: Claudio Micheli                       %
% Last review:                                  %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% see http://www.contsid.cran.univ-lorraine.fr/demo/2.Tutorials/tutorial1

LOGS_FOLDER = 'parsed_logs';
PARSED_LOG = 'actuators_ident_1';
PARSED_LOG_CROSS = 'actuators_ident_3';     % Log for crossvalidation
load(strcat(LOGS_FOLDER,'/',PARSED_LOG,'/',PARSED_LOG));
q_servo = 1.5000e+03;
m_servo =   572.9578;
% Sampling time of optitrack is 7ms
Ts = 0.010;
Freq_sample   = 1/Ts;
% Identification test is 22s, thus we have 22*1/7e-3 samples
test_duration = 17;
start_sample  = 903;
end_sample    = start_sample + test_duration*Freq_sample;
crop_data     = ground_attitude_roll(start_sample:end_sample);
time_vec      =0:Ts:test_duration;
plot(time_vec,crop_data);

value_signal  = -(mixer_ctr_servo_4(start_sample:end_sample)-q_servo)*1/m_servo*180/pi;
figure;
plot(time_vec,value_signal);

% Generating Input signal time vector
% t1 = 0:Ts:2-Ts;
% t2 = 2:Ts:4-Ts;
% t3 = 4:Ts:6-Ts;
% t4 = 6:Ts:8-Ts;
% t5 = 8:Ts:10-Ts;
% t6 = 10:Ts:12-Ts;
% t7 = 12:Ts:14-Ts;
% t8 = 14:Ts:16-Ts;
% t9 = 16:Ts:18-Ts;
% t10 = 18:Ts:20-Ts;
% t11 = 20:Ts:22-Ts;
% t12 = 22:Ts:24-Ts;
% 
% time_signal = [t1 t2 t3 t4 t5 t6];
% 
% %Generating input signal values
% v1 = ones(1,length(t1))*10;
% v2 = ones(1,length(t1))*0;
% v3 = ones(1,length(t1))*10;
% v4 = ones(1,length(t1))*0;
% v5 = ones(1,length(t1))*15;
% v6 = ones(1,length(t1))*0;
% v7 = ones(1,length(t1))*15;
% v8 = ones(1,length(t1))*0;
% v9 = ones(1,length(t1))*20;
% v10 = ones(1,length(t1))*0;
% v11 = ones(1,length(t1))*20;
% v12 = ones(1,length(t1))*0;
% value_signal = [v1 v2 v3 v4 v5 v6];
title('Input vs Output');
plot(time_vec,value_signal)
hold on
plot(time_vec,crop_data)

%% Setup of the identification
% A natural way to find the most appropriate model orders is to compare 
% the results obtained from model structures with different orders and
% delays.
 nb_min=1; 
 nb_max=2;
 nf_min=3; 
 nf_max=4;
 nk_min=0; 
 nk_max=0;
 NN=[nb_min nf_min nk_min;
     nb_max nf_max nk_max];

crop_data = crop_data(1:length(value_signal));
%value_signal = value_signal';
data = iddata(crop_data,value_signal,Ts,'InterSample','zoh');

% Display input/output data
idplot(data); 
 xlabel('Time (sec)');

 %Analyzes different model estimated structures
 V=srivcstruc(data,[],NN);
 
 % Sorting the models via YIC (Young Information Criterion) and RT2
    selcstruc(V);
  
 % from the table we obtain the best model to be nb = 1 nf = 3
  nn = [1 1 0];
  
  Msrivc = srivc(data,nn);

  present(Msrivc);
  %compare the model output with the measured output
  figure;
   comparec(data,Msrivc);
   
  % Confidence bounds
[ys,esti]=comparec(data,Msrivc);
t=(1:data.N)'*Ts;
figure;
shadedplot(t,data.y,ys);
xlabel('Times (sec)')
title(['Coefficient of determination R_T^2= ',num2str(esti.RT2,3)])
set(gca,'FontSize',14,'FontName','helvetica');

%% Cross-validation
% We take another set of data that has not been used for identification and
% we check the results

load(strcat(LOGS_FOLDER,'/',PARSED_LOG_CROSS,'/',PARSED_LOG_CROSS));
crop_data = ground_attitude_roll;
value_signal  = -(mixer_ctr_servo_4-q_servo)*1/m_servo*180/pi;

data = iddata(crop_data,value_signal,Ts,'InterSample','zoh');

[ys,esti]=comparec(data,Msrivc);
    t=(1:data.N)'*data.Ts;
    close
    figure;
    shadedplot(t,data.y,ys);
    xlabel('Times (sec)')
    title(['Cross-validation - R_T^2= ',num2str(esti.RT2,3)])
    set(gca,'FontSize',14,'FontName','helvetica');

