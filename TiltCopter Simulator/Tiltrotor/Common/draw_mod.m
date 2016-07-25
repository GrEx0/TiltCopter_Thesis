function draw_mod(input)
% ----------------------------------------------------
% TILTROTOR VERSION
% Draws the quadrotor in 3 dimensions during the simulation.
% This script is invoked once for each animation frame.
% ----------------------------------------------------
%#codegen

global old_position;
global index_view;
global quad;
THROTTLE_MAX = 0.5;
x = input(1);
y = -input(2);
z = -input(3);
phi = input(4);
theta = -input(5);
psi = -input(6);
th_1 = input(7);
th_2 = input(8);
th_3 = input(9);
th_4 = input(10);
alpha_1 = input(11);
alpha_2 = input(12);
alpha_3 = input(13);
alpha_4 = input(14);


Sphi = sin(phi);
Cphi = cos(phi);
Stheta = sin(theta);
Ctheta = cos(theta);
Spsi = sin(psi);
Cpsi = cos(psi);

% Rotation matrix
TBE = [        Ctheta*Cpsi               Ctheta*Spsi          -Stheta    ;
       Sphi*Stheta*Cpsi-Cphi*Spsi Sphi*Stheta*Spsi+Cphi*Cpsi Sphi*Ctheta ;
       Cphi*Stheta*Cpsi+Sphi*Spsi Cphi*Stheta*Spsi-Sphi*Cpsi Cphi*Ctheta];
rot = TBE';

psi = 0;
phi = alpha_1;
R_BPi = [cos(psi), -cos(phi)*sin(psi),  sin(phi)*sin(psi);
        sin(psi),  cos(phi)*cos(psi), -cos(psi)*sin(phi);
         0,           sin(phi),           cos(phi)];
rot_braccio_1 = rot*R_BPi;

psi =pi/2;
phi = -alpha_2;
R_BPi = [cos(psi), -cos(phi)*sin(psi),  sin(phi)*sin(psi);
        sin(psi),  cos(phi)*cos(psi), -cos(psi)*sin(phi);
         0,           sin(phi),           cos(phi)];
rot_braccio_2 = rot*R_BPi;

psi =pi;
phi = alpha_3;
R_BPi = [cos(psi), -cos(phi)*sin(psi),  sin(phi)*sin(psi);
        sin(psi),  cos(phi)*cos(psi), -cos(psi)*sin(phi);
         0,           sin(phi),           cos(phi)];
rot_braccio_3 = rot*R_BPi;

psi =3*pi*1/2;
phi = -alpha_4;
R_BPi = [cos(psi), -cos(phi)*sin(psi),  sin(phi)*sin(psi);
        sin(psi),  cos(phi)*cos(psi), -cos(psi)*sin(phi);
         0,           sin(phi),           cos(phi)];
rot_braccio_4 = rot*R_BPi;

% Code executed only the first time that the script is
% called.
if index_view == 0
   
%     % Initialize the figure
%     screen = get(0,'screensize');
%     visual = figure(1);
%  %set(visual,'position',[2 65 screen(3)-40 screen(4)-300]);
%     clf(visual);
%     hold on;
%     cameratoolbar('show');
%     axis vis3d;
%     view(3);
%     zoom(0.6);
%         
%     % The following two lines can be deleted for better performances.
%     set(gcf,'menubar','figure','renderer','opengl');
%     set(gca,'Visible','On','Box','On','XGrid', 'on','YGrid', 'on','ZGrid',...
%         'on','projection','perspective');    
        
    % Draw fixed frame reference
    %N
    line([0,0.5],[0,0],[0,0],'linewidth',2,'color','red');
    text(0.6,0,0,'N','fontsize',13);
    %E
    line([0,0],[0,0],[0,-0.5],'linewidth',2,'color','green');
    text(0,-0.6,0,'E','fontsize',13);
    %D
    line([0,0],[0,-0.5],[0,0],'linewidth',2,'color','black');
    text(0,0,-0.6,'D','fontsize',13);
    %Ground square
    line([-1,1],[1,1],[0,0],'linewidth',2,'color','black');
    line([-1,1],[-1,-1],[0,0],'linewidth',2,'color','black');
    line([1,1],[-1,1],[0,0],'linewidth',2,'color','black');
    line([-1,-1],[-1,1],[0,0],'linewidth',2,'color','black');
        
    
% This part is not executed the first time the script
% is called.
else
    
    % Delete the quadrotor drawing in the old position
    drawnow;
    delete(quad.a);
    delete(quad.b);
    delete(quad.c);
    delete(quad.d);
    delete(quad.e);
    delete(quad.f);    
    delete(quad.g);
    delete(quad.h);
    delete(quad.i);
    delete(quad.l);
    line([old_position(1),x],[old_position(2),y],[old_position(3),z],...
        'linewidth',1,'color','magenta');
end

% Draw the quadrotor
%frame
points = [-0.4 +0.4;0 0;0 0];
quad.a = line(x+rot(1,:)*points,y+rot(2,:)*points,z+rot(3,:)*points,...
            'linewidth',2,'color','black');
points = [0 0;-0.4 +0.4;0 0];
quad.b = line(x+rot(1,:)*points,y+rot(2,:)*points,z+rot(3,:)*points,...
            'linewidth',2,'color','black');

%propellers
circ_x = [0.15 0.1 0 -0.1 -0.15 -0.1 0 0.1 0.15];
circ_y = [0 0.1 0.15 0.1 0 -0.1 -0.15 -0.1 0];
circ_z = [0 0 0 0 0 0 0 0 0];

points = [circ_x+0.4;circ_y;circ_z];
quad.c = line(x+rot(1,:)*points,y+rot(2,:)*points,z+rot(3,:)*points,...
            'linewidth',2,'color','red');
points = [circ_x-0.4;circ_y;circ_z];
quad.d = line(x+rot(1,:)*points,y+rot(2,:)*points,z+rot(3,:)*points,...
            'linewidth',2,'color','red');
points = [circ_x;circ_y-0.4;circ_z];
quad.e = line(x+rot(1,:)*points,y+rot(2,:)*points,z+rot(3,:)*points,...
            'linewidth',2,'color','blue');
points = [circ_x;circ_y+0.4;circ_z];
quad.f = line(x+rot(1,:)*points,y+rot(2,:)*points,z+rot(3,:)*points,...
            'linewidth',2,'color','blue');

% quad.g = arrow([x ;y ;z]+rot*[0 ;-0.4;0],[x ;y ;z]+rot*[0 ;-0.4; 0.3],10,'BaseAngle',20,'Color','r');
% quad.h = arrow([x ;y ;z]+rot*[0 ;0.4; 0],[x ;y ;z]+rot*[0 ;0.4 ;0.3],10,'BaseAngle',20,'Color','r');
% quad.i = arrow([x ;y ;z]+rot*[0.4 0 0],[x ;y ;z]+rot*[0.4 0 0.3],10,'BaseAngle',20,'Color','r');
% quad.l = arrow([x ;y ;z]+rot*[-0.4 0 0],[x ;y ;z]+rot*[-0.4 0 0.3],10,'BaseAngle',20,'Color','r');
points = [0.4 0.4;0 0;THROTTLE_MAX*th_1/100 0];
quad.g = line(x+rot_braccio_1(1,:)*points,y+rot_braccio_1(2,:)*points,z+rot_braccio_1(3,:)*points,...
            'linewidth',2,'color','red');
points = [-0.4 -0.4;0 0;THROTTLE_MAX*th_2/100 0];
quad.h = line(x+rot_braccio_2(1,:)*points,y+rot_braccio_2(2,:)*points,z+rot_braccio_2(3,:)*points,...
            'linewidth',2,'color','blue');
points = [0.4 0.4 ;0 0;THROTTLE_MAX*th_3/100 0];
quad.i = line(x+rot_braccio_3(1,:)*points,y+rot_braccio_3(2,:)*points,z+rot_braccio_3(3,:)*points,...
            'linewidth',2,'color','red');
points = [-0.4 -0.4;0 0 ;THROTTLE_MAX*th_4/100 0];
quad.l = line(x+rot_braccio_4(1,:)*points,y+rot_braccio_4(2,:)*points,z+rot_braccio_4(3,:)*points,...
            'linewidth',2,'color','blue');
            

% Save the current position for the path plot
old_position = [x,y,z];

% Set the camera position and target
% camtarget_x = x;
% camtarget_y = y;
% camtarget_z = z;
% campos_x = (camtarget_x/2 + camtarget_y)*10 - 2;
% campos_y = (camtarget_y/2 - camtarget_x)*10 - 1;
% campos_z = camtarget_z + sqrt(campos_x^2+campos_y^2)/6 + 3;
% 
% camtarget([camtarget_x,camtarget_y,camtarget_z]);     
% campos([campos_x,campos_y,campos_z]);

% Count the iterations
index_view = index_view + 1;