function [A,B,C,D,K] = Roll_dynamics(stab_der_L,Jxx,Kt,b,omega_hover,Ts)


A = [stab_der_L *1/Jxx 0 ; 1 0 ];
B = [4*Kt*b*omega_hover*1/Jxx; 0 ];
C = eye(2);
D = [0;0];
K = zeros(2);
end