clear all
close all 
clc

%% Import parameters
Parameters

%% Launch SIMULATOR
tsim = 10;

%Set point 
% T = -20;
% L = 0 ;
% M = 0 ;
% N = 0;
Fx = 0;
Fy = 0;

%Set point u = [height[m] roll_a[rad] pitch_a[rad] yaw_r[rad/s]]
U = [-1; 0; 0; 0];

sim Simulator_matlab2015_weighted_inv

P_e = yout(: ,1:3);
V_b = yout(: ,4:6);
Ome_b = yout(: ,7:9);
Alpha_e = yout(: ,10:12);
%initial_value = (length(Uscita_quad.signals.values) - length(yout));
Motor_thr = Uscita_quad.signals.values(:,1:4);
Tilt_angles = pi/180*(Uscita_quad.signals.values(:,5:8)- q_servo)*1/m_servo;

%% Plot OUTPUT
figure('name','POSITION_EARTH')
plot(tout, P_e*diag([1 1 -1]));
grid minor
xlabel('[s]')
ylabel('[m]')
legend('N', 'E', 'Height')

figure('name','VELOCITY_BODY')
plot(tout, V_b);
grid minor
xlabel('[s]')
ylabel('[m/s]')
legend('u', 'v', 'w')

figure('name','ANGULAR SPEED_BODY')
plot(tout, Ome_b);
grid minor
xlabel('[s]')
ylabel('[rad/s]')
legend('p', 'q', 'r')
 
figure('name','ATTITUDE_EARTH')
plot(tout, Alpha_e);
grid minor
xlabel('[s]')
ylabel('[rad]')
legend('phi', 'theta', 'psi')
% 
%% 3D Animation
global index_view;
global old_position;

index_view = 0;
old_position = [0 0 0];
for i = 1:length(tout)
    draw_mod( [P_e(i,:) Alpha_e(i,:) Motor_thr(i,:) Tilt_angles(i,:)]);
end

 %% End of code