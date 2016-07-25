% script per mediare i dati acquisiti
%% SETUP VALUES
LOGS_FOLDER = 'parsed_logs';
PARSED_LOG_CROSS = 'actuators_ident_3';         % Log for cross validation
Ts = 0.010;
test_duration = 17;
q_servo = 1.5000e+03;
m_servo =   572.9578;
start_sample  = 1;
n_param = 2             % number of statistical parameters you want to keep

% vector_id = char( '12-07-16_act_id_2' , '12-07-16_act_id_3' , '12-07-16_act_id_4' , '12-07-16_act_id_5', ...
%                            '12-07-16_act_id_6' , '12-07-16_act_id_7' , '12-07-16_act_id_8' , '12-07-16_act_id_9', ...
%                            '12-07-16_act_id11_2' ,'12-07-16_act_id11_5' ,'12-07-16_act_id11_6' ,'12-07-16_act_id11_8');


vector_id = char( '12-07-16_act_id_3' , '12-07-16_act_id_4' , '12-07-16_act_id_5', ...
                           '12-07-16_act_id_6' , '12-07-16_act_id_7' , '12-07-16_act_id_8' , '12-07-16_act_id_9')
                       
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
%%
dim = size (vector_id);
dim = dim(1);
% Determino end sample
Freq_sample   = 1/Ts;
NSamples = test_duration*Freq_sample;
vect_sum = zeros(NSamples,1);
matrix_results = zeros(dim,4);
for i= 1:dim
    PARSED_LOG = strtrim(vector_id(i,:));
    
    % loads only the ground_attitude_roll' variable
    disp('Log number');
    PARSED_LOG
    
    load(strcat(LOGS_FOLDER,'/',PARSED_LOG,'/',PARSED_LOG),'ground_attitude_roll','mixer_ctr_servo_4')
    
    % Number of samples recorded
    id_samples = length(ground_attitude_roll);
   
    % Define the "real" sampling time
    Ts = test_duration/id_samples;
    
    %Conversion from [ms] -> [deg]
    ctr_signal  = -(mixer_ctr_servo_4-q_servo)*1/m_servo*180/pi;
    crop_data = ground_attitude_roll;
    
%     if id_samples < NSamples
%         %Padding to obtain 1700 samples
%         ground_attitude_roll = [ground_attitude_roll ; zeros(NSamples - id_samples,1)];
%     end
    %vect_sum = vect_sum + ground_attitude_roll(1:NSamples,1);
    

% Plot input/output signal
figure;
title(PARSED_LOG);
plot(ctr_signal)
hold on
plot(ground_attitude_roll)
hold off

% Identification
data = iddata(crop_data,ctr_signal,Ts,'InterSample','zoh');

% Display input/output data
idplot(data); 
 xlabel('Time (sec)');
 
%Analyzes different model estimated structures
 V=srivcstruc(data,[],NN);
 
% Sorting the models via YIC (Young Information Criterion) and RT2
    [NN_sorted,Vcrit_sorted] = selcstruc(V);
    
    % For each identification experiment we save the model order nb, nf,
    % RT2 parameter and 
        matrix_results(i,1) = NN_sorted(1,1);       % nb
        matrix_results(i,2) = NN_sorted(1,2);       % nf
        matrix_results(i,3) = Vcrit_sorted(1,1);    % RT
        matrix_results(i,4) = Vcrit_sorted(1,2);    %YIC
        nn = [NN_sorted(1,1) NN_sorted(1,2) 0 ];
% % from the table we obtain the best model to be nb = 1 nf = 3
%   nn = [1 3 0];
%   
  Msrivc = srivc(data,nn);
%   [M,RT2,YIC,Cond_IPM,AIC] = srivc(data,nn);  
  present(Msrivc);
  
%     
% %compare the model output with the measured output
%   figure;
%    comparec(data,Msrivc);
    
end
T = table(categorical({'#1';'#2';'#3';'#4';'#5';'#6';'#7'}),matrix_results(:,1),...
    matrix_results(:,2),matrix_results(:,3),...
    matrix_results(:,4),...
    'VariableNames',{'Test' 'nb' 'nf' 'RT' 'YIC'})

% Dall'exel ottengo il modello
final_model = idpoly(1,4670.252,1,1,[1,28.356,598.46,4650.232],0,0);
%compare the model output with the measured output
  figure;
   comparec(data,final_model);

%% Cross-validation
% We take another set of data that has not been used for identification and
% we check the results

load(strcat(LOGS_FOLDER,'/',PARSED_LOG_CROSS,'/',PARSED_LOG_CROSS),'ground_attitude_roll','mixer_ctr_servo_4')
 
% Number of samples recorded
 id_samples = length(ground_attitude_roll);
   
% Define the "real" sampling time
Ts = test_duration/id_samples;
crop_data = ground_attitude_roll;
value_signal  = -(mixer_ctr_servo_4-q_servo)*1/m_servo*180/pi;

data = iddata(crop_data,value_signal,Ts,'InterSample','zoh');

[ys,esti]=comparec(data,final_model);
    t=(1:data.N)'*data.Ts;
    close
    figure;
    shadedplot(t,data.y,ys);
    xlabel('Times (sec)')
    title(['Cross-validation - R_T^2= ',num2str(esti.RT2,3)])
    set(gca,'FontSize',14,'FontName','helvetica');
