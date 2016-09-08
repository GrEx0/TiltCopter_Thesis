for i=1:4
     psi = (i-1)*pi/2;
     phi = vector_alpha(1)
     R_PiB(i) = [cos(psi),           sin(psi),        0;
       -cos(phi)*sin(psi),  cos(phi)*cos(psi), sin(phi);
        sin(phi)*sin(psi), -cos(psi)*sin(phi), cos(phi)];
     
 end