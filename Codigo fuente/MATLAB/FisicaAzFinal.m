clc,close all,clear all;

Data = load('FisicaAz.txt');

Az  = Data(:,3);
sensibilidad=0.0039;              %datos del fabricante ADXL345
deltaT=0.0043;                    %tiempo de muestreo
t = ((0:length(Data)-1)*deltaT)'; %vector tiempo normalizado al tiempo de muestreo
g=9.8;                            %valor de la gravedad


Az(356:470)=-95;
Az(536:600)=-95;
Az(649:716)=-95;
Az(776:837)=-95;
Az(886:966)=-95;
Az(1005:1056)=-95;
Az(1102:1159)=-95;

offset=0.0378;                   %mediana de la señal
Azcorregido=Az*sensibilidad/g+offset;

xmin=0;
xmax=5;
ymin=-0.02;
ymax=0.2;
plot(t,Azcorregido);
title('Gráfica de aceleración componente Az vs tiempo','FontSize',25);
xlabel('Tiempo [seg]','FontSize',25);
ylabel('Aceleración [m/s^2]','FontSize',25);
set(gca,'XTick',xmin:xmax/20:xmax,'FontSize',25);
set(gca,'YTick',ymin:ymax/10:ymax,'FontSize',25);
axis([xmin xmax ymin ymax]);
grid on;
