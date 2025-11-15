kE = 1000;
Tp = 60;
kp = 500;
kc = 125;
Tc = 300;
uc = 2.5;
Oe = -10;
Cp = Tp * kp;
Cc = Tc * kc;


A = [-1/Tp 1/Tp ; kp/(kc*Tc) -((1+kp/kc)/Tc)];
B = [ kE/(kp * Tp) 0 ; 0 1/Tc];
C = [1 0 ; 0 1];
D = [0 0 ; 0 0];
