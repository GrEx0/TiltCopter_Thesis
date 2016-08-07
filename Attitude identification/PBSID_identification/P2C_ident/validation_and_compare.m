clc
close all
clear all

Ts = 0.02; % identification data sample time 

% previous PI-MOESP test-bed P2A2 n=2 p=32 rit=0.06s
sys_moesp_tb_p2a2 = tf([12.11 24.28],[1 4.643 16.76]);

% previous PBSID test-bed P2A2 n=2 f=6 p=35 rit=0.06s
sys_pbsid_tb_p2a2 = tf([12.517 (12.517*2.906)],[1 5.583 21.3]);

% test-bed P2C PI-MOESP, rit=2(0.04s) - n=2 - p=39, campaign 3, dataset type == 2

sys_moesp_tb_p2c_1 = tf([10.29 33.68],[1 5.112 14.72]);

% test-bed P2C PI-MOESP, rit=3(0.06s) - n=2 - p=39, campaign 3, dataset type == 2

sys_moesp_tb_p2c_2 = tf([11.58 27.78],[1 5.117 13.46]);

% test-bed P2C PBSID, rit=3(0.06s) - n=2 - p=49, f=4, campaign 3, dataset type == 2

sys_pbsid_tb_p2c_1 = tf([16.09 25.54],[1 4.581 9.634]);

% test-bed P2C PBSID, rit=2(0.04s) - n=2 - p=45, f=3, campaign 3, dataset type == 2

sys_pbsid_tb_p2c_2 = tf([8.145 241.8],[1 15.63 69.39]);

%%

load var_for_ident_campaign_3
load var_for_valid_campaign_3

u_tot_ = vertcat(u_PRBS_campaign,u_ctrl_campaign);
y_tot_ = vertcat(meas_q_PRBS_campaign,meas_q_ctrl_campaign);
N_tot = length(u_tot_);
t_plot_tot = (0:Ts:((length(u_tot_)-1)*Ts))';

scale = norm(y_tot_);
y_tot = y_tot_/scale;

u_tot = u_tot_ - mean(u_tot_);

% Identificazione da 1 a N/2 e validazione da N/2+1 a end
in_id_i=1;
in_id_f=floor(1/2*N_tot);
in_va_i=in_id_f+1;
in_va_f=N_tot;

u_valid = u_tot(in_va_i:in_va_f);
y_valid = y_tot(in_va_i:in_va_f);
t_plot_valid = (0:Ts:((length(u_valid)-1)*Ts))';

% Simulazione modello identificato su dati di validazione

uv_rit2 = u_valid; 

rit2 = 2;
uv_rit2(rit2+1:end) = uv_rit2(1:end-rit2); 
uv_rit2(1:rit2) = zeros(rit2,1);

uv_rit3 = u_valid; 

rit3 = 3;
uv_rit3(rit3+1:end) = uv_rit3(1:end-rit3); 
uv_rit3(1:rit3) = zeros(rit3,1);

yv = y_valid;

tsim = (0:Ts:((length(uv_rit3)-1)*Ts))';

% Simulazione modello identificato a t cont con scalatura eliminata su dati di validazione (normal ctrl)
yyv_c_moesp_1=lsim(sys_moesp_tb_p2c_1,uv_rit2,tsim);
yyv_c_moesp_2=lsim(sys_moesp_tb_p2c_2,uv_rit3,tsim);
yyv_c_pbsid_1=lsim(sys_pbsid_tb_p2c_1,uv_rit3,tsim);
yyv_c_pbsid_2=lsim(sys_pbsid_tb_p2c_2,uv_rit2,tsim);

% figure
% plot(tsim,yv*scale)
% hold on
% plot(tsim,yyv_c_moesp,'r')
% hold on
% plot(tsim,yyv_c_pbsid_1,'c')
% hold on
% plot(tsim,yyv_c_pbsid_2,'g')
% grid on
% ylabel('angular rate [deg/s]')
% xlabel('time [s]')
% legend('measured','model moesp','model pbsid 1','model pbsid 2')

VAF_no_scale_c_moesp_1_all = vaf(yv*scale,yyv_c_moesp_1)
VAF_no_scale_c_moesp_2_all = vaf(yv*scale,yyv_c_moesp_2)
VAF_no_scale_c_pbsid_1_all = vaf(yv*scale,yyv_c_pbsid_1)
VAF_no_scale_c_pbsid_2_all = vaf(yv*scale,yyv_c_pbsid_2)

%%

% % separo dati di validazione a metà: la prima parte (30s) è validazione su
% % dataset PRBS (non usato x identificare), la seconda su dataset in
% % controllato nominale (30s)
% 
% uv_PRBS = uv(1:1500);
% yv_PRBS = yv(1:1500);
% t_PRBS = tsim(1:1500);
% 
% uv_ctrl = uv(1501:3000);
% yv_ctrl = yv(1501:3000);
% t_ctrl = tsim(1501:3000);%-tsim(1501);
% 
% yyv_PRBS_moesp=lsim(sys_moesp_tb_p2c,uv_PRBS,t_PRBS);
% yyv_PRBS_pbsid=lsim(sys_pbsid_tb_p2c,uv_PRBS,t_PRBS);
% 
% yyv_ctrl_moesp=lsim(sys_moesp_tb_p2c,uv_PRBS,t_ctrl);
% yyv_ctrl_pbsid=lsim(sys_pbsid_tb_p2c,uv_PRBS,t_ctrl);
% 
% figure
% plot(t_PRBS,yv_PRBS*scale)
% hold on
% plot(t_PRBS,yyv_PRBS_moesp,'r')
% hold on
% plot(t_PRBS,yyv_PRBS_pbsid,'c')
% grid on
% ylabel('angular rate [deg/s]')
% xlabel('time [s]')
% legend('measured','model moesp','model pbsid')
% 
% VAF_no_scale_c_moesp_PRBS = vaf(yv_PRBS*scale,yyv_PRBS_moesp)
% VAF_no_scale_c_pbsid_PRBS = vaf(yv_PRBS*scale,yyv_PRBS_pbsid)
% 
% figure
% plot(t_ctrl,yv_ctrl*scale)
% hold on
% plot(t_ctrl,yyv_ctrl_moesp,'r')
% hold on
% plot(t_ctrl,yyv_ctrl_pbsid,'c')
% grid on
% ylabel('angular rate [deg/s]')
% xlabel('time [s]')
% legend('measured','model moesp','model pbsid')
% 
% VAF_no_scale_c_moesp_ctrl = vaf(yv_ctrl*scale,yyv_ctrl_moesp)
% VAF_no_scale_c_pbsid_ctrl = vaf(yv_ctrl*scale,yyv_ctrl_pbsid)

%%

figure
subplot(4,1,1)
plot(tsim(1:1500),yv(1:1500)*scale)
hold on
plot(tsim(1:1500),yyv_c_moesp_1(1:1500),'r')
ylabel('angular rate [deg/s]')
xlabel('time [s]')
legend('measured PRBS','model moesp 1')
subplot(4,1,2)
plot(tsim(1:1500),yv(1:1500)*scale)
hold on
plot(tsim(1:1500),yyv_c_moesp_2(1:1500),'r')
ylabel('angular rate [deg/s]')
xlabel('time [s]')
legend('measured PRBS','model moesp 2')
subplot(4,1,3)
plot(tsim(1:1500),yv(1:1500)*scale)
hold on
plot(tsim(1:1500),yyv_c_pbsid_1(1:1500),'c')
ylabel('angular rate [deg/s]')
xlabel('time [s]')
legend('measured PRBS','model pbsid 1')
subplot(4,1,4)
plot(tsim(1:1500),yv(1:1500)*scale)
hold on
plot(tsim(1:1500),yyv_c_pbsid_2(1:1500),'g')
ylabel('angular rate [deg/s]')
xlabel('time [s]')
legend('measured PRBS','model pbsid 2')

VAF_no_scale_c_moesp_1_PRBS = vaf(yv(1:1500)*scale,yyv_c_moesp_1(1:1500))
VAF_no_scale_c_moesp_2_PRBS = vaf(yv(1:1500)*scale,yyv_c_moesp_2(1:1500))
VAF_no_scale_c_pbsid_1_PRBS = vaf(yv(1:1500)*scale,yyv_c_pbsid_1(1:1500))
VAF_no_scale_c_pbsid_2_PRBS = vaf(yv(1:1500)*scale,yyv_c_pbsid_2(1:1500))

figure
subplot(4,1,1)
plot(tsim(1501:3000),yv(1501:3000)*scale)
hold on
plot(tsim(1501:3000),yyv_c_moesp_1(1501:3000),'r')
ylabel('angular rate [deg/s]')
xlabel('time [s]')
legend('measured normal ctrl','model moesp 1')
subplot(4,1,2)
plot(tsim(1501:3000),yv(1501:3000)*scale)
hold on
plot(tsim(1501:3000),yyv_c_moesp_2(1501:3000),'r')
ylabel('angular rate [deg/s]')
xlabel('time [s]')
legend('measured normal ctrl','model moesp 2')
subplot(4,1,3)
plot(tsim(1501:3000),yv(1501:3000)*scale)
hold on
plot(tsim(1501:3000),yyv_c_pbsid_1(1501:3000),'c')
ylabel('angular rate [deg/s]')
xlabel('time [s]')
legend('measured normal ctrl','model pbsid 1')
subplot(4,1,4)
plot(tsim(1501:3000),yv(1501:3000)*scale)
hold on
plot(tsim(1501:3000),yyv_c_pbsid_2(1501:3000),'g')
ylabel('angular rate [deg/s]')
xlabel('time [s]')
legend('measured normal ctrl','model pbsid 2')

VAF_no_scale_c_moesp_1_ctrl = vaf(yv(1501:3000)*scale,yyv_c_moesp_1(1501:3000))
VAF_no_scale_c_moesp_2_ctrl = vaf(yv(1501:3000)*scale,yyv_c_moesp_2(1501:3000))
VAF_no_scale_c_pbsid_1_ctrl = vaf(yv(1501:3000)*scale,yyv_c_pbsid_1(1501:3000))
VAF_no_scale_c_pbsid_2_ctrl = vaf(yv(1501:3000)*scale,yyv_c_pbsid_2(1501:3000))

%%

figure
bodeplot(sys_moesp_tb_p2a2,'m--')
hold on
bodeplot(sys_pbsid_tb_p2a2,'g--')
hold on
bodeplot(sys_moesp_tb_p2c_1,'r')
hold on
bodeplot(sys_moesp_tb_p2c_2,'k')
hold on
bodeplot(sys_pbsid_tb_p2c_1,'b')
hold on
bodeplot(sys_pbsid_tb_p2c_2,'c')
grid on 
legend('moesp p2a2','pbsid p2a2','moesp 1 p2c','moesp 2 p2c','pbsid 1 p2c','pbsid 2 p2c')

figure
step(sys_moesp_tb_p2a2,'m--')
hold on
step(sys_pbsid_tb_p2a2,'g--')
hold on
step(sys_moesp_tb_p2c_1,'r')
hold on
step(sys_moesp_tb_p2c_2,'k')
hold on
step(sys_pbsid_tb_p2c_1,'b')
hold on
step(sys_pbsid_tb_p2c_2,'c')
grid on 
legend('moesp p2a2','pbsid p2a2','moesp 1 p2c','moesp 2 p2c','pbsid 1 p2c','pbsid 2 p2c')

figure
pzmap(sys_moesp_tb_p2a2,'m--')
hold on
pzmap(sys_pbsid_tb_p2a2,'g--')
hold on
pzmap(sys_moesp_tb_p2c_1,'r')
hold on
pzmap(sys_moesp_tb_p2c_2,'k')
hold on
pzmap(sys_pbsid_tb_p2c_1,'b')
hold on
pzmap(sys_pbsid_tb_p2c_2,'c')

legend('moesp p2a2','pbsid p2a2','moesp 1 p2c','moesp 2 p2c','pbsid 1 p2c','pbsid 2 p2c')
