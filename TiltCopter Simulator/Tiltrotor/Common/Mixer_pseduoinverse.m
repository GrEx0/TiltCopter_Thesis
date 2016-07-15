clear all
close all
clc

%%
syms omega_hover Kt Kq b real

% Linearized Mixer matrix 
%(equilibrium points: omega = omega_hover, alpha = 0)
MM_param_jaco = [    0,     0,     0,    0,                  0,  -Kt*omega_hover^2,                  0,   Kt*omega_hover^2 ;
                     0,     0,     0,    0,   Kt*omega_hover^2,                  0,  -Kt*omega_hover^2,                  0 ;
                   -Kt,   -Kt,   -Kt,  -Kt,                  0,                  0,                  0,                  0 ;
                     0, -Kt*b,     0, Kt*b,                  0,  -Kq*omega_hover^2,                  0,   Kq*omega_hover^2 ;
                  Kt*b,     0, -Kt*b,    0,  -Kq*omega_hover^2,                  0,   Kq*omega_hover^2,                  0 ;
                    Kq,   -Kq,    Kq,  -Kq, Kt*b*omega_hover^2, Kt*b*omega_hover^2, Kt*b*omega_hover^2, Kt*b*omega_hover^2];

% Compute the column vector result
W = [0.001*eye(4)    zeros(4) ; 
        zeros(4)  1e-8*eye(4)];
    
% Mixer - Weighted pseudo-inverse
K = wpinv(MM_param_jaco,W);

%% END OF CODE
