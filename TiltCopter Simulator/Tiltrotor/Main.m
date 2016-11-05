% clear all
% close all 
% clc
opengl software
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
opengl hardwarebasic$

% VERSIONE SIMULATORE CON MIXER MATRIX PSEUDO INVERSA
sim Simulator_weighted_inv

% VERSIONE SIMULATORE CON MIXER MATRIX NON LINEARE
%sim Simulator_nonlinear_inversion

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
if 0
    global index_view;
    global old_position;
    
    index_view = 0;
    old_position = [0 0 0];
    % Initialize the figure
    
    screen = get(0,'screensize');
    visual = figure('Name','3DPlot');
    %set(visual,'position',[2 65 screen(3)-40 screen(4)-300]);
    clf(visual);
    hold on;
    cameratoolbar('show');
    view(3);
    grid;
    axis vis3d;
    %     axis tight
    x_max = 1;
    y_max = 1;
    axis([-1 x_max -1 y_max -0.3 inf])
    zoom(0.2);
    for i = 1:length(tout)
        draw_mod( [P_e(i,:) Alpha_e(i,:) Motor_thr(i,:) Tilt_angles(i,:)]);
        if (P_e(i,1)+0.8)>x_max
            x_max = x_max +1;
            axis([-1 x_max -1 y_max -0.3 inf])
        end
        if (P_e(i,2)+0.8)>y_max
            y_max = y_max +1;
            axis([-1 x_max -1 y_max -0.3 inf])
        end
        
    end
end
 %% End of code