%% This script resumes the obtained results
close all;
Parameters

EXPERIMENTAL_DATA = 'RBS_2a_deltaTH1_290716';
start_sample = 1300;
tau_f = 1/30;                         % FIlter constant use 30 or 100

% Identified  avg greyest system - Test A
A1_a = ureal('A1',-3.878866607,'PlusMinus',0.15015509);
B1_a = ureal('B1',5.662050517,'PlusMinus',0.130973455);

A_gA = A1_a;
B_gA = B1_a;
C_gA= 1 ;
D_gA = 0;

% Identified  avg greyest system - Test B
A1_b = ureal('A1_b',-3.834685535,'PlusMinus',0.136170331);
B1_b = ureal('B1_b',5.363684853,'PlusMinus',0.122543954);

A_gB = A1_b;
B_gB = B1_b;
C_gB= 1 ;
D_gB = 0

% Identified  avg greyest system - Test B
A1_c = ureal('A1_c',-4.047992791,'PlusMinus',0.215205335);
B1_c = ureal('B1_c',6.431602502,'PlusMinus',0.217415498);

A_gC = A1_c;
B_gC = B1_c;
C_gC= 1 ;
D_gC = 0;

G_greyA = ss(A_gA,B_gA,C_gA,D_gA);
% Identified transfer function
if 0
    G_greyA = ss(A_gA,B_gA,C_gA,D_gA);
    figure;
    bode(G_greyA);
    title('Greyest identified system - test A');
    hold on
    % Identified transfer function
    G_greyB = ss(A_gB,B_gB,C_gB,D_gB);
    %figure;
    bode(G_greyB);
    title('Greyest identified system - test B');
    
    % Identified transfer function
    G_greyC = ss(A_gC,B_gC,C_gC,D_gC);
    %figure;
    bode(G_greyC);
    title('Greyest identification results');
    hold off;
end
% best SINGLE RESULT

% Identified  BEST greyest system
A1_best = ureal('A1_best',-3.414467,'PlusMinus',0.2770);
B1_best = ureal('B1_best',5.348863,'PlusMinus',0.2653);

A_gBest = A1_best;
B_gBest = B1_best;
C_gBest= 1 ;
D_gBest = 0;

% Identified transfer function BEST
if 0
    G_greyBest = ss(A_gBest,B_gBest,C_gBest,D_gBest);
    figure;
    bode(G_greyBest);
    title('Greyest identified system - BEST CASE');
end


%% SRIVC identified system
s = tf('s');
% Identified  avg srivc system - Test A
A1_sA = ureal('A1_sA',8.387902003,'PlusMinus',0.006483558);
B1_sA = ureal('B1_sA',6.844908507,'PlusMinus',0.006598076);

num_i = A1_sA;
den_i = [1 B1_sA];
G_srivcA = tf(num_i,den_i)*exp(-0.09006*s);
%G_srivc = tf(num_i,den_i);

% Identified  avg srivc system - Test B
A1_sB = ureal('A1_sB',7.220178833,'PlusMinus',0.006117453);
B1_sB = ureal('B1_sB',5.947931243,'PlusMinus',0.006171678);

num_i = A1_sB;
den_i = [1 B1_sB];
G_srivcB = tf(num_i,den_i)*exp(-0.0752*s);
%G_srivc = tf(num_i,den_i);

% Identified  avg srivc system - Test C
A1_sC = ureal('A1_sC',10.34957272,'PlusMinus',0.008299512);
B1_sC = ureal('B1_sC',8.114930505,'PlusMinus',0.00835059);

num_i = A1_sC;
den_i = [1 B1_sC];
G_srivcC = tf(num_i,den_i)*exp(-0.0752*s);
%G_srivc = tf(num_i,den_i);

% Plot everything
if 0
    figure;
    hold on
    bode(G_srivcA);
    bode(G_srivcB);
    bode(G_srivcC);
    title('SRIVC identification results');
    hold off
end

% Identified  BEST srivc system
A1_sBest = ureal('A1_sBest',6.984955,'PlusMinus',0.0145);
B1_sBest = ureal('B1_sBest',5.252496,'PlusMinus',0.0139);

num_i = A1_sBest;
den_i = [1 B1_sBest];
G_srivcBest = tf(num_i,den_i)*exp(-0.0674*s);
%G_srivc = tf(num_i,den_i);

if 0
    figure;
    bode(G_srivcBest);
    title('SRIVC identified system - BEST CASE');
end

%% Import experimental data for cross validation

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

% Noise reduction
u = delta_omega_ctr;
y = imu_raw_gyro_x(1:length(u));


t  = .01 * [0:numel(u)-1];

if 0
    figure;
    plot(t,y);
    title('unfiltered data output');
    figure;
    plot(t,u);
    title('Input signal - NOT filtered');
end


num_f = [1];
den_f = [tau_f 1]
G_f   = tf(num_f,den_f)

y_f = lsim(G_f,y,t);
u_f = lsim(G_f,u,t);
y = y_f;
u_nofilter = u;
u = u_f;

if 0                % Enable filter vs non filtered output
    figure;
    plot(t,y,t,y_f);
    title('Filtered output vs NON filtered');
end


u  = u(start_sample+600:start_sample+2500);
u_nofilter = u_nofilter(start_sample+600:start_sample+2500);
y  = y(start_sample+600:start_sample+2500);
t  = .01 * [0:numel(u)-1];

% Non filtered input plot from start_sample
figure;
plot(t,u_nofilter);
title('RBS input signal');

% Filtered input and output from start_sample
if 0
    figure;
    plot(t,y);
    title('Measured output');
    figure;
    plot(t,u);
    title('Input signal');
end
mean_y = mean(y);
mean_u = mean(u);
% normalizza e rimuove media
u = u - mean(u);
y = y - mean(y);
scal_u = norm(u);
scal_y = norm(y);
u = 1/scal_u * u;
y = 1/scal_y * y;

figure;plot(u);title('Normalized Input u');

% Simulation of the identified system;
t  = .01 * [0:numel(u)-1];

%greyest results
if 0
    % test A
    yi_greyA = lsim(G_greyA,u,t);
    vaf_greyA = vaf(y,yi_greyA);
    figure;
    plot(t,y,t,yi_greyA);
    title_str = sprintf('Real output vs grey output - VAF %2f Test A \n\r',vaf_greyA);
    title(title_str);
    
    % test B
    yi_greyB = lsim(G_greyB,u,t);
    vaf_greyB = vaf(y,yi_greyB);
    figure;
    plot(t,y,t,yi_greyB);
    title_str = sprintf('Real output vs grey output - VAF %2f Test B \n\r',vaf_greyB);
    title(title_str);
    
    % test C
    yi_greyC = lsim(G_greyC,u,t);
    vaf_greyC = vaf(y,yi_greyC);
    figure;
    plot(t,y,t,yi_greyC);
    title_str = sprintf('Real output vs grey output - VAF %2f Test C \n\r',vaf_greyC);
    title(title_str);
end
% SRIVC

%% PLOTS USED IN THE THESIS
% test A SRIVC
yi_srivcA= lsim(G_srivcA,u,t);

 % test A GREYEST
yi_greyA = lsim(G_greyA,u,t);


% Read the mean value and scale
yi_srivcA = yi_srivcA *scal_y;
yi_srivcA = yi_srivcA + mean_y ;
y = y *scal_y ;
y = y +mean_y;
u = u * scal_u;
u = u + mean_u;
vaf_srivcA = vaf(y,yi_srivcA);
figure;
plot(t,y,t,yi_srivcA);
title_str = sprintf('Real output vs SRIVC model - VAF %2f A \n\r',vaf_srivcA);
title(title_str);


% Read the mean value and scale
yi_greyA = yi_greyA *scal_y;
yi_greyA = yi_greyA + mean_y ;
vaf_greyA = vaf(y,yi_greyA);
figure;
plot(t,y,t,yi_greyA);
title_str = sprintf('Real output vs grey-box model - VAF %2f A \n\r',vaf_greyA);
title(title_str);

% END PLOTS FOR THESIS
%% 
%test B
if 0
    yi_srivcB= lsim(G_srivcB,u,t);
    vaf_srivcB = vaf(y,yi_srivcB);
    figure;
    plot(t,y,t,yi_srivcB);
    title_str = sprintf('Real output vs SRIVC model - VAF %2f B \n\r',vaf_srivcB);
    title(title_str);
end

%test C
if 0
    yi_srivcC= lsim(G_srivcC,u,t);
    vaf_srivcC = vaf(y,yi_srivcC);
    figure;
    plot(t,y,t,yi_srivcC);
    title_str = sprintf('Real output vs SRIVC model - VAF %2f C \n\r',vaf_srivcC);
    title(title_str);
end

%BEST grey BEST SRIVC
if 0
    yi_srivcBest= lsim(G_srivcBest,u,t);
    vaf_srivcBest = vaf(y,yi_srivcBest);
    figure;
    plot(t,y,t,yi_srivcBest);
    title_str = sprintf('Real output vs SRIVC BEST model - VAF %2f BEST \n\r',vaf_srivcBest);
    title(title_str);
    
    yi_greyBest = lsim(G_greyBest,u,t);
    vaf_greyBest = vaf(y,yi_greyBest);
    figure;
    plot(t,y,t,yi_greyBest);
    title_str = sprintf('Real output vs grey BEST output - VAF %2f Test BEST \n\r',vaf_greyBest);
    title(title_str);
end


