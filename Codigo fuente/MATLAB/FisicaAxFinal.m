clc,close all,clear all;

Data = load('FisicaAx.txt');

Ax  = Data(:,1);
sensibilidad=0.0039;              %datos del fabricante ADXL345
deltaT=0.0043;                    %tiempo de muestreo
t = ((0:length(Data)-1)*deltaT)'; %vector tiempo normalizado al tiempo de muestreo
g=9.8;                            %valor de la gravedad

Ax(53:218)=-30;
Ax(306:436)=-30;
Ax(489:568)=-30;
Ax(646:727)=-30;
Ax(817:888)=-30;
Ax(975:1044)=-30;

offset=0.0119;                  %mediana de la señal
Axcorregido=Ax*sensibilidad/g+offset;

xmin=0;
xmax=5;
ymin=-0.02;
ymax=0.2;
plot(t,Axcorregido);
title('Gráfica de aceleración componente Ax vs tiempo','FontSize',25);
xlabel('Tiempo [seg]','FontSize',15);
ylabel('Aceleración [m/s^2]','FontSize',25);
set(gca,'XTick',xmin:xmax/20:xmax,'FontSize',25);
set(gca,'YTick',ymin:ymax/10:ymax,'FontSize',25);
axis([xmin xmax ymin ymax]);
grid on;



