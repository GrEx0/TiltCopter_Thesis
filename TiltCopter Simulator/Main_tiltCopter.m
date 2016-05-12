clear all
close all 
clc

%% Import parameters
TiltCopter_Parameters
 
%% Launch SIMULATOR
tsim = 20;

%Set point 
T = -m*g;
L = 1 ;
M = 0 ;
N = 0;
Fx = 0;
Fy = 0;

%Set point u = [height[m] roll_a[rad] pitch_a[rad] yaw_r[rad/s]]
U = [15; 0; 0; 0];


sim TiltCopter_Simulator

P_e = yout(: ,1:3);
V_b = yout(: ,4:6);
Ome_b = yout(: ,7:9);
Alpha_e = yout(: ,10:12);

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

%% 3D Animation
 
global index_view;
global old_position;

index_view = 0;
old_position = [0 0 0];

for i = 1:length(tout)
    draw_mod([P_e(i,:) Alpha_e(i,:)]);
end


 %% End of code