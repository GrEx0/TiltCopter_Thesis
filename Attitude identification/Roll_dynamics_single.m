function [AI,BI,CI,DI] = Roll_dynamics_single(stab_der_L,Jxx,dLdu_g,Ts)

%q as input
AI = stab_der_L/Jxx;
BI = dLdu_g/Jxx;
CI = 1;
DI = 0;
end