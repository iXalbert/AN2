kR = 5;
Tr = 1;
kE1 = 10;
kE2 = 15;
k1 = 0.08;
T1 = 0.05;
Ti = 0.1;
kem = 0.8;
kEM = 0.02;
kC = 1;
Tc = 0.5;

%HPI = kC*(1+sTr)/sTr;

A = [ k1*Ti*(kE2)/(2*Ti+1) 0 ; 0 k1*Ti*(kE1)/(2*Ti+1)];
B = [ kC/Tc 0 ; 0 -Ti];
C = [1 0 ; 0 1];
D = [0 0 ; 0 0];