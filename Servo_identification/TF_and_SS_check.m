% Tiltrotor Thesis
% Author: Claudio Micheli
% Latest review: 07.08.15


% Dummy script that checks that the derived state-space has the same response
% of the derived SS
% phi/phi_ref = B0/(B1 s^3 + B2 s^2 +B3 s^3 + B4 s)
% B4 and B0 should be very close togheter, see the paper

% B0 =ureal('B0',4670.252,'PlusMinus',72.11);
% B2 =ureal('B2',28.36,'PlusMinus',1.68);
% B3 =ureal('B3',598.45,'PlusMinus',7.97);
% B4 =ureal('B4',4650.23,'PlusMinus',1.55);

B0 = 4670.2519;
B1 = 1;
B2 = 28.355992;
B3 = 598.45913;
B4 = 4650.2325;

num_i = B0;
den_i = [1 B2 B3 B4];
G_i = tf(num_i,den_i);
% bode(G_i.nominal);


% State space representation
A_Servo = [0 1 0; 0 0 1 ; -B4/B1 -B3/B1 -B2/B1];
B_Servo = [0 ; 0 ; B0/B1];
C_Servo = eye(3);
D_Servo = 0 ;

G_2 = ss(A_Servo,B_Servo,C_Servo,D_Servo);

figure;
bode(G_2(1))


%% sintesi regolatore traslazionale
s = tf('s');
G_quadcopter = 1/m * 1/s;
gain_F = 1/ (2*Kt*omega_hover^2);
G_servo = G_i ;

G_overall = G_quadcopter * G_servo * gain_F;
