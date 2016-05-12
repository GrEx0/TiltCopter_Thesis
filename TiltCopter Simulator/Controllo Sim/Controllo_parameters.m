% TiltRotor Simulink Parameters and Setup
close all;
clear all;
%Common parameters
g = 9.81;
degtorad = pi/180;              % Degrees to radiant conversion

%% Tiltcopter Properties
m = 1.478;                       %[kg] Body mass
Mb = diag([m m m]);              %[Kg] Mass matrix
MbInv = Mb\eye(3);               %[Kg^-1] Inverse of mass matrix
b = 0.55/2;                      %[m] Arm lenght

% Approximated Inertia
m_c =  0.9;                            %[Kg] Mass of the center cylinder 
r_c =  0.17;                           %[m] Radius of the center cylinder
h_c =  0.15;                              %[m] Height of th ecenter cylinder

m_r =  0.13;                         %[Kg] Mass of the rotor group

Ixx = m_c/12 *(3*r_c^2+h_c^2)+ m_r*b^2; %[kg*m^2] Estimated Inertia around Xbody axes
Iyy = Ixx;                              %[kg*m^2] Estimated Inertia around Ybody axes
Izz = m_c*r_c^2/2 +m_r*b^2;             %[kg*m^2] Estimated Inertia around Zbody axes

In = diag([Ixx Iyy Izz]);        %[kg*m^2] Inertia tensor
InInv = In\eye(3);               %[kg^-1*m^-2] Inverse of inertia tensor

%% Aerodynamic parameters

%Propellers information
D = 12*(0.0254);                 %[m] Propeller diameter
R = D/2;                         %[m] Propeller radius
A = pi*R^2;                      %[m^2] Disk area
ro = 1.225;                      %[kg*m^-3] Air density
nb = 2;                          %[1] Number of blades
ChordAv = .01;                   %[m] Average chord length
Ab = nb*R*ChordAv;               %[m] Blade area
sigma = Ab/A;                    %[1] Solid ratio
Ct = 0.011859;                   %[1] Thrust coefficent
Cq = 0.00091322;                 %[1] Torque coefficent
tau = 0.055257;                  %[s] Motor+Propeller time constant
x1 = [6.0312 80.4859];           %RPM vs THROTTLE: Y = m*X + q; x1 = [m q]
Kt = Ct*ro*A*R^2;
Kt_sigma = 1.0832e-07;
Kq = Cq*ro*A*R^3;
OMEhov = sqrt((m*g/Kt)/4);       % Angular velocity at Hovering
omega_hover = OMEhov;            % Conversion nomeclature :)
dMdu = 4*sqrt(2)*Kt*b*OMEhov;    %[Nm*s] Control derivative
dMdu_sigma = (4*sqrt(2)*b*OMEhov)*Kt_sigma;


%Aerodynamic damping
C_Lalpha = 2*pi;
dCt_dp = C_Lalpha/8 *sigma/(R*OMEhov)*b;
dL_dp = -4*ro*A*R^2*OMEhov^2*dCt_dp *b;             %[Nm*s] Guess of Stability derivative of the vehicle roll
dNdr = -0.0185;                                     %[Nm*s] Stability derivative of the vehicle yaw
% Identified stability derivatives
% dMdq = -0.046271;                                   %[Nm*s] Stability derivative of the vehicle pitch
% dMdq_sigma = 0.0024164;                             %[Nm*s] Uncertainty of stability derivative of the vehicle pitch
% dLdp = dMdq;

% dLMN = [dLdp  0    0   ;
%          0   dMdq  0   ;
%          0    0   dNdr];

%% Parte per il controllo

rho = 2*Kt*b*omega_hover;
mu  =Kq*omega_hover^2;

A = [ 1/Ixx*dL_dp 0 ; 1 0];
B = [1/Ixx 1/Ixx; 0 0 ];
C = [1 0];
D = [0 0];


[num1 den1] = ss2tf(A,B,C,D,1);
[num2 den2] = ss2tf(A,B,C,D,2);
G1 = tf(num1,den1);
G2 = tf(num2,den2);

% Parametri
% Kp = 23.25;
% Kd = 129.5;
Kp = 0.193;
Ki = 0.892;

Reg = pid(Kp,Ki);

integrator = tf([1],[1 0])
G_2 = Reg*G1*integrator;

Kp_ext = 0.0571;
Ki_ext = 0.312;