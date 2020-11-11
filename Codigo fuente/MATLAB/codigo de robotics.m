clc;clear all;close all;
%for x=0:pi/10:2*pi
%brazo izquierdo    
L1=link([  0    0    0     1  0])
L2=link([ pi/2  0   -pi     0  1])
L3=link([ pi/2  0  -pi/2   0  1])
L4=link([-pi/2  0  -pi/2   1  1])
L5=link([  0    1  -pi/2   0  1])
L6=link([  0    1     0    0  0])
pause(5)
rob = robot({L1 L2 L3 L4 L5 L6})
plot(rob, [0 0 0 0 0 0])
%brazo derecho
clc;clear all;close all;
for x=0:pi/10:2*pi
    y=cos(x);
L1=link([  0    0    0     1  0])
L2=link([-pi/2  0   y     0  1])
L3=link([-pi/2  0   pi/2   0  1])
L4=link([-pi/2  0   pi/2   1  1])
L5=link([  0    1   y   0  1])
L6=link([  0    1     0    0  0])

rob = robot({L1 L2 L3 L4 L5 L6})
plot(rob, [0 0 0 0 0 0])
pause(5)
end
%columna
clc;clear all;close all;
clc
close all;
clear all;
for x=0:pi/10:5*pi
   y=cos(2*x);
   y1=sin(x/2);
   y2=cos(4*x);
   y3=sin(x/1.2);
L1=link([  0    1    0    0  0]);
L2=link([  0    1    y    0  1]);
L3=link([  0    y1   0    0  1]);
L4=link([  0    1   0   0  1]);
L5=link([  0    1    y3    0  1]);
pause(5)
%L6=link([  0    1    0    0  0]);
rob = robot({L1 L2 L3 L4 L5})
plot(rob, [0 0 0 0 0])
end