%% Rotation matrix
syms phi theta psi real

 M = [cos(theta)*cos(psi) sin(phi)*sin(theta)*cos(psi)-cos(phi)*sin(psi) cos(phi)*sin(theta)*cos(psi)+sin(phi)*sin(psi);
      cos(theta)*sin(psi) sin(phi)*sin(theta)*sin(psi)+cos(phi)*cos(psi) cos(phi)*sin(theta)*sin(psi)-sin(phi)*cos(psi); 
      -sin(theta) sin(phi)*cos(theta) cos(phi)*cos(theta)];
 
 syms g real
 
 Q = [-g*sin(theta);g*cos(theta)*sin(phi);g*cos(theta)*cos(phi)]
 
 
M * Q