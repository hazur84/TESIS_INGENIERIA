clc,close all,clear all;

Data = load('FísicaAy.txt');

Ay  = Data(:,2);
sensibilidad=0.0039;              %datos del fabricante ADXL345
deltaT=0.0043;                    %tiempo de muestreo
t = ((0:length(Data)-1)*deltaT)'; %vector tiempo normalizado al tiempo de muestreo
g=9.8;                            %valor de la gravedad

Ay(139:312)=-55;
Ay(364:515)=-55;
Ay(552:711)=-55;
Ay(777:908)=-55;
Ay(942:991)=-55;
Ay(1024:1091)=-55;
Ay(1112:1135)=-55;

offset=0.0219;                  %mediana de la señal
Aycorregido=Ay*sensibilidad/g+offset;


xmin=0;
xmax=5;
ymin=-0.02;
ymax=0.2;
plot(t,Aycorregido);
title('Gráfica de aceleración componente Ay vs tiempo','FontSize',25);
xlabel('Tiempo [seg]','FontSize',15);
ylabel('Aceleración [m/s^2]','FontSize',25);
set(gca,'XTick',xmin:xmax/20:xmax,'FontSize',25);
set(gca,'YTick',ymin:ymax/10:ymax,'FontSize',25);
axis([xmin xmax ymin ymax]);
grid on;