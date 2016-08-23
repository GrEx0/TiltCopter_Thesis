function [AI,BI,CI,DI] = Roll_dynamics_single(A1,B1,Ts)

%q as input
% AI = stab_der_L/Jxx;
AI = A1;
% BI = dLdu_g/Jxx;
BI = B1;
CI = 1;
DI = 0;
end