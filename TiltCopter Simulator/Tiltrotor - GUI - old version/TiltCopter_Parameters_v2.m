% TiltRotor Simulink Parameters and Setup
% close all;
% clear all;
%Common parameters
g = 9.81;
degtorad = pi/180;              % Degrees to radiant conversion
%% Tiltcopter Properties
m = 1.510;                       %[kg] Body mass
Mb = diag([m m m]);              %[Kg] Mass matrix
MbInv = Mb\eye(3);               %[Kg^-1] Inverse of mass matrix
b = 0.55/2;                      %[m] Arm lenght

% Approximated Inertia
m_c =  0.9;                            %[Kg] Mass of the center cylinder 
r_c =  0.17;                           %[m] Radius of the center cylinder
h_c =  0.15;                              %[m] Height of th ecenter cylinder

m_r =  0.13;                         %[Kg] Mass of the rotor group

% Ixx = m_c/12 *(3*r_c^2+h_c^2)+ m_r*b^2; %[kg*m^2] Estimated Inertia around Xbody axes
% Iyy = Ixx;                              %[kg*m^2] Estimated Inertia around Ybody axes
% Izz = m_c*r_c^2/2 +m_r*b^2;             %[kg*m^2] Estimated Inertia around Zbody axes

Ixx = 0.034736;                  %[kg*m^2] Inertia around Xbody axes
Ixx_sigma = 0.0011563;           %[kg*m^2] Uncertainty of Inertia around Xbody axes
Iyy = Ixx;                       %[kg*m^2] Inertia around Ybody axes
Iyy_sigma = Ixx_sigma;           %[kg*m^2] Uncertainty of Inertia around Ybody axes
Izz = 0.05;                      %[kg*m^2] Inertia around Zbody axes

In = diag([Ixx Iyy Izz]);        %[kg*m^2] Inertia tensor
InInv = In\eye(3);               %[kg^-1*m^-2] Inverse of inertia tensor

%% Servomotor Model Parameters
B0 = 1.399e04;
B1 =    1150;
B2 = 37.46;
B3 = 1;
ServoMotor_Gain = 1.409e04;

%s = tf('s');
%G_servo = B0/(B3+B2*s+B1*s+B0);

% Conversion angle -> pulse width
% Relationship between pulse and position:
% Neutral position -> 1500ms
% Maximum position (45deg)  -> 1950ms
% Minimum position (-45deg) -> 1050ms

% Let's find a first order relationship y = mx + q
x = [0 pi/4 -pi/4];
y = [1500 1950 1050];
p = polyfit(x,y,1);

m_servo = p(1);
q_servo = p(2);

x_vett = linspace(-45,45)*degtorad;
y1 = polyval(p,x_vett);

% Plot of the result
% figure
% plot(x/degtorad,y,'o')
% hold on
% plot(x_vett/degtorad,y1)
% xlabel('[deg]');ylabel('[ms]');grid;title('Angolar position/Pulse witdh relation');
% hold off
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
dMdq = -0.046271;                %[Nm*s] Stability derivative of the vehicle pitch
dMdq_sigma = 0.0024164;          %[Nm*s] Uncertainty of stability derivative of the vehicle pitch
dLdp = dMdq;
dNdr = -0.0185;                  %[Nm*s] Stability derivative of the vehicle yaw
dLMN = [dLdp  0    0   ;
         0   dMdq  0   ;
         0    0   dNdr];
     
     
 rho = 2*Kt*b*omega_hover;          % Gain on control variable U1

%% Saturations
rollMax = pi/6;     %[rad]
pitchMax = pi/6;    %[rad]
yawRateMax = pi/2;  %[rad/s]

%% FCU characteristics
fc = 100;   %[Hz]
tc = 1/fc;  %[s]

delay_altitude = 2;
delay_attitude = 2;

%% Angular-rate regulators
Tf = .01;
N = 1/Tf;

%p PID
%Guess
% Kpp = 0.3;
% Kip = 0.3;
% Kdp = 0.05;
%H-Infinity
Kpp = 0.298;
Kip = 0.304;
Kdp = 0.0499;
%Anti-Windup (Back-calculation)
% Kbp = 0;
Kbp = sqrt(Kdp/Kip);
satp = 1.5;

%q PID
%Guess
% Kpq = 0.3;
% Kiq = 0.3;
% Kdq = 0.05;
%H-Infinity
Kpq = 0.298;
Kiq = 0.304;
Kdq = 0.0499;
%Anti-Windup (Back-calculation)
% Kbq = 0;
Kbq = sqrt(Kdq/Kiq);
satq = 1.5;

%r PID
%Guess
Kpr = 0.135;
Kir = 0.125;
Kdr = 0.0153;
%H-Infinity
% Kpr = 0.276;
% Kir = 0.101;
% Kdr = 0.0151;
%Anti-Windup (Back-calculation)
% Kbr = 0;
Kbr = sqrt(Kdr/Kir);
satr = 1;

%% Attitude regulators
%phi PD
%Guess
% KRP = 1.2;
% KRD = 0.005;
%H-Infinity
KRP = 1.61;
KRD = 0.00512;

%theta PD
%Guess
% KPP = 1.2;
% KPD = 0.005;
%H-Infinity
KPP = 1.61;
KPD = 0.00512;
% KPP = 1.33;
% KPD = 0.00696;

%% Altitude regulator
KaN = 38;

KaP = 8.0;
KaI = 3.6;
KaD = 5.4;

%Anti-Windup (Back-calculation)
% Kba = 0;
Kba = sqrt(KaD/KaI);
sata = 5;

 %% End of code