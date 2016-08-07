syms K_tau R L J D K_e real
s = tf('s')

G1 = K_tau/(s*((R+L*s)*(J*s+D)+K_e*K_tau))

syms Kp phi u Kd real
v = Kp*(u- phi) - Kd*s*phi