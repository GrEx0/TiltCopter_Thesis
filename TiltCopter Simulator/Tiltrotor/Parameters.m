% TiltRotor Simulink Parameters and Setup
% close all;
% clear all;
%Common parameters
g = 9.81;
degtorad = pi/180;              % Degrees to radiant conversion

%% Tiltcopter Properties
%m = 1.510;                      %[kg] Body mass
m = 1.900;                       
Mb = diag([m m m]);              %[Kg] Mass matrix
MbInv = Mb\eye(3);               %[Kg^-1] Inverse of mass matrix
b = 0.55/2;                      %[m] Arm lenght

% OLD VALUES FROM QUADCOPTER
% Ixx = 0.034736;                  %[kg*m^2] Inertia around Xbody axes
% Iyy = Ixx;                       %[kg*m^2] Inertia around Ybody axes

% IDENTIFIED TILTROTOR VALUES
%Ixx = 14e-4;                    % VALORE NN SCALATO
Ixx = 0.0074;
Iyy = Ixx;
Ixx_sigma = 0.0011563;           %[kg*m^2] Uncertainty of Inertia around Xbody axes
Iyy_sigma = Ixx_sigma;           %[kg*m^2] Uncertainty of Inertia around Ybody axes
Izz = 0.05;                      %[kg*m^2] Inertia around Zbody axes

In = diag([Ixx Iyy Izz]);        %[kg*m^2] Inertia tensor
InInv = In\eye(3);               %[kg^-1*m^-2] Inverse of inertia tensor

%% Servomotor Model Parameters

%IDENTIFIED SERVOMOTOR PARAMETERS
B0 = 4670.2519;
B1 = 1;
B2 = 28.355992;
B3 = 598.45913;
B4 = 4650.2325;

% State space representation
A_Servo = [0 1 0; 0 0 1 ; -B4/B1 -B3/B1 -B2/B1];
B_Servo = [0 ; 0 ; B0/B1];
C_Servo = eye(3);
D_Servo = 0 ;

% Let's find a first order relationship y = mx + q
x = [0 pi/4 -pi/4];
y = [1500 1950 1050];
p = polyfit(x,y,1);

m_servo = p(1);
q_servo = p(2);

x_vett = linspace(-45,45)*degtorad;
y1 = polyval(p,x_vett);

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
x1 = [6.0312 80.4859];           % [RAD/S] vs THROTTLE%: Y = m*X + q; x1 = [m q]
Kt = Ct*ro*A*R^2;
Kt_sigma = 1.0832e-07;
Kq = Cq*ro*A*R^3;
OMEhov = sqrt((m*g/Kt)/4);       % Angular velocity at Hovering
omega_hover = OMEhov;            % Conversion nomeclature :)

% TILTROTOR CONTROL DERIVATIVE
dMdu = 4*Kt*b*omega_hover;            %[Nm*s] Control derivative
dMdu_sigma = (4*Kt*b*omega_hover)*Kt_sigma;

%Aerodynamic damping

% IDENTIFIED TILTROTOR VALUES
dMdq =-0.0509;                    %[Nm*s] Stability derivative of the vehicle pitch   
dMdq_sigma = 0.0024164;          %[Nm*s] Uncertainty of stability derivative of the vehicle pitch
dLdp = dMdq;


dNdr = -0.0185;                  %[Nm*s] Stability derivative of the vehicle yaw
dLMN = [dLdp  0    0   ;
         0   dMdq  0   ;
         0    0   dNdr];
     
     
rho = 2*Kt*b*omega_hover;          % Gain on control variable U1
 
%% PROPELLER GROUP INERTIA 
%  VALUES OBTAINED FROM NOVEL OVERACTUATED PAPER
% m_d = 0.01; %[kg]
% r_d = 0.20; %[m]
% Izd = m_d*r_d^2/2;
% Ixd = m_d*r_d^2/4;
% Iyd = Ixd;
%In_Pi = diag([Ixd Iyd Izd]);

I_Pi = diag([8.450e-5 8.450e-5 4.580e-5]);

%% Mixer matrix
% Linearized Mixer matrix 
%(equilibrium points: omega = omega_hover, alpha = 0)

% VERSIONE CON YAW INVERTITO
% K = [    0,     0,     0,    0,                  0,  -Kt*omega_hover^2,                  0,   Kt*omega_hover^2 ;
%          0,     0,     0,    0,   Kt*omega_hover^2,                  0,  -Kt*omega_hover^2,                  0 ;
%        -Kt,   -Kt,   -Kt,  -Kt,                  0,                  0,                  0,                  0 ;
%          0, -Kt*b,     0, Kt*b,                  0,  -Kq*omega_hover^2,                  0,   Kq*omega_hover^2 ;
%       Kt*b,     0, -Kt*b,    0,  -Kq*omega_hover^2,                  0,   Kq*omega_hover^2,                  0 ;
%         Kq,   -Kq,    Kq,  -Kq, Kt*b*omega_hover^2, Kt*b*omega_hover^2, Kt*b*omega_hover^2, Kt*b*omega_hover^2];

omega_hover_sq = omega_hover^2;
K = [    0,     0,     0,    0,                   0,  -Kt*omega_hover_sq,                   0,   Kt*omega_hover_sq;
    0,     0,     0,    0,   Kt*omega_hover_sq,                   0,  -Kt*omega_hover_sq,                   0;
  -Kt,   -Kt,   -Kt,  -Kt,                   0,                   0,                   0,                   0;
    0, -Kt*b,     0, Kt*b,                   0,   Kq*omega_hover_sq,                   0,  -Kq*omega_hover_sq;
 Kt*b,     0, -Kt*b,    0,   Kq*omega_hover_sq,                   0,  -Kq*omega_hover_sq,                   0;
  -Kq,    Kq,   -Kq,   Kq, Kt*b*omega_hover_sq, Kt*b*omega_hover_sq, Kt*b*omega_hover_sq, Kt*b*omega_hover_sq];

% Compute the column vector result
W = [0.001*eye(4)   zeros(4) ; 
        zeros(4)  1e8*eye(4)];
    
% Mixer - Weighted pseudo-inverse
Kinv = wpinv(K,W);

%% Saturations
rollMax = pi/6;     %[rad]
pitchMax = pi/6;    %[rad]
yawRateMax = pi/2;  %[rad/s]

%% FCU characteristics
fc = 100;   %[Hz]
tc = 1/fc;  %[s]

delay_altitude = 1;
delay_attitude = 1;
delay_mixer = 1;
delay_OptiTrack = 0;
delay_IMU = 1;
delay_Kaltitude = 1;

%% Angular-rate regulators
Tf = .01;
N = 1/Tf;

%p PID
%Guess
% Kpp = 0.3;
% Kip = 0.3;
% Kdp = 0.05;
%H-Infinity

% VALORI QUADCOPTER
if 0
 Kpp = 0.298;
 Kip = 0.304;
 Kdp = 0.0499;
else
% VALORI PERFETTI ----------------------------------------
%roll ridotto 30% rispetto a pitch
% Kpp = 0.4;
% Kip = 0.44;
% Kdp = 0.06;
% % RESULT: PERFECT!

%pitch VALORI PERFETTI
% Kpq = 0.58;
% Kiq = 0.7;
% Kdq = 0.075;

% VALORI COMMIT 8e4458c
% Kdp = 0.065;
% Kip = 0.8;
% Kpp = 0.65;
% Kpq = Kpp;
% Kiq = Kip;
% Kdq = Kdp;
%-------------------------------------------------

% HINF Funzionante  -test 1  - SONO QUELLI DI SABATO NON VANNO PIU
% Kpp = 0.041;
% Kip = 0.234;
% Kdp = 0.00194;
% Kpq = Kpp;
% Kiq = Kip;
% Kdq = Kdp;

% HINF 3008 #1
% Kpp = 0.636;
% Kip = 5.75;
% Kdp = 0.0583;
% Kpq = Kpp;
% Kiq = Kip;
% Kdq = Kdp;
% RESULT : NO VOLA

% % HINF 3008 #2
%  Kpp = 0.578;
%  Kip = 0.7;
%  Kdp = 0.0158;
%  Kpq = Kpp;
%  Kiq = Kip;
%  Kdq = Kdp;
% % RESULT: VOLA!

% HINF 3008 #3
% Kpp = 0.188;
% Kip = 3.25;
% Kdp = 0.0111;
% Kpq = Kpp;
% Kiq = Kip;
% Kdq = Kdp;
%RESULT: SHIT

% % HINF 3008 #4
% % Kpp = 0.104;
% % Kip = 0.586;
% % Kdp = 0.00483;
% % Kpq = Kpp;
% % Kiq = Kip;
% % Kdq = Kdp;
% % RESULT: SHIT

% HINF 3008 #5
% Kpp = 0.394;
% Kip = 2.84;
% Kdp = 0.0254;
% Kpq = Kpp;
% Kiq = Kip;
% Kdq = Kdp;
% RESULT: SHIT

% HINF 3008 #6
% Kpp = 0.3;
% Kip = 0.697;
% Kdp = 0.00534;
% Kpq = Kpp;
% Kiq = Kip;
% Kdq = Kdp;
% RESULT: VALORI UTILIZZATI IN VOLO

% HINF 3108 #1
% Kpp = 0.252;
% Kip = 0.697;
% Kdp = 0.00834;
% Kpq = Kpp;
% Kiq = Kip;
% Kdq = Kdp;
% RESULT: MERDA

% HINF 3108 #2
% Kpp = 0.225;
% Kip = 1.36;
% Kdp = 0.01;
% Kpq = Kpp;
% Kiq = Kip;
% Kdq = Kdp;
% RESULT: MERDA

% HINF 3108 #3
Kpp = 0.3;
Kip = 0.72;
Kdp = 0.006;
Kpq = Kpp;
Kiq = Kip;
Kdq = Kdp;
% RESULT:SUPER


end
%Anti-Windup (Back-calculation)
Kbp = sqrt(Kdp/Kip);
satp = 1.5;

%q PID
%Guess
% Kpq = 0.3;
% Kiq = 0.3;
% Kdq = 0.05;
%H-Infinity

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

% VALUES QUADCOPTER
if 0
 KRP = 1.61;
 KRD = 0.00512;
else
    % VALUES TILTROTOR
% VALORI TILTROTOR  "BUONI"
% KRP = 1.9;
% KRD = 0.005;

% HINF funzionante - test 1 - VALORI DI SABATO
%  KRP = 1.43;
%  KRD = 0.01;

% HINF 3008 #2 - VALORI BUONI DA USARE 
% KRP = 1.9;
% KRD = 0.005;

% TEST HINF ANELLO ESTERNO #7
% KRP = 2.41;
% KRD = 0.0868;

% TEST HINF ANELLO ESTERNO #8 - OK
KRP = 1.61;
KRD = 0.0584;

end

KPP = KRP;
KPD = KRD;

%psi PD
%H-Infinity
KYP = 1.41;
KYD = 0.216;

%% Altitude regulator
KaN = 38;

KaP = 8.0;
KaI = 3.6;
KaD = 5.4;

%Anti-Windup (Back-calculation)
% Kba = 0;
Kba = sqrt(KaD/KaI);
sata = 5;

%% Traslational Controller

% VALORI TILTING FUNZIONANTI

 N_tras = 100;

% PARAMETRI FUNZIONANTI OTTENUTI A MANO
%N_tras = 150;
% Kp_v = 4;
% Kp_u = 4;
% Kd_v = 0.01;
% Kd_u = 0.01;
%--------------------------------------------------

% PARAMETRI HINF ORIGINALI - NON USARE! VANNO MEGLIO QUELLI AGGIUSTATI
%È  un PID
% Kp_v = 6.44;
% Ki_v = 5.6;
% Kd_v = 0.365;

%PARAMETRI AGGIUSTATI 300816
Kp_v = 6.3;
Ki_v = 5.6;
Kd_v = 0.290;

Kp_u = Kp_v;
Ki_u = Ki_v;
Kd_u = Kd_v;

umax = 1;
vmax = 1;

%% Position controller - tiltrotor

% Kp_N = 0.3;
% Kd_N = 0.01;
% Kp_E = Kp_N;
% Kd_E = Kd_N;

% Valori a mano 3008
Kp_N = 0.15;
Kd_N = 0.01;
Kp_E = Kp_N;
Kd_E = Kd_N;

 %% End of code