clc;                            %estas insrucciones limpian la memoria y cierra figuras abiertas
clear all;
close all;
Data = load('record1.txt');     %se llama el archivo donde estas guardados los datos y s

deltaT=0.0043;                  %tiempo de muestreo
t = ((0:length(Data)-1)*deltaT)'; %vector tiempo normalizado al tiempo de muestreo

%--------------------Separacion de las señales en vectores-------
sensibilidad=14.375;            %dato facilidato por el fabricante
Wx  = Data(:,1)/sensibilidad;
Wy  = Data(:,2)/sensibilidad;
Wz  = Data(:,3)/sensibilidad;
%-----------------------------------------------------------------
xmin=0;                         %dimensiones de la gráfica
xmax=5;
ymin=-10;
ymax=10;
%----------------tratamiento de Wx--------------------------------


[p1,S1,mu1] = polyfit(t,Wx,3);  %interpolacion de 3er orden
f1 = polyval(p1,t,S1,mu1);
Nx=Wx-f1;                       %resta del polinomio interpolador
plot(t,Nx);
title('Componente Wx','FontSize',13);
xlabel('Tiempo [s]','FontSize',15);
ylabel('Velocidad angular [degº/s]','FontSize',15);
set(gca,'XTick',xmin:xmax/20:xmax,'FontSize',15);
set(gca,'YTick',ymin:ymax/10:ymax,'FontSize',15);
axis([xmin xmax ymin ymax]);
grid on


%--------------------------tratamiento de Wy-------------------------------


[p2,S2,mu2] = polyfit(t,Wy,4);
f2 = polyval(p2,t,S2,mu2);
Ny=Wy-f2;
figure
plot(t,Ny);
title('Componente Wy','FontSize',13);
xlabel('Tiempo [s]','FontSize',15);
ylabel('Velocidad angular [degº/s]','FontSize',15);
set(gca,'XTick',xmin:xmax/20:xmax,'FontSize',15);
set(gca,'YTick',ymin:ymax/10:ymax,'FontSize',15);
axis([xmin xmax ymin ymax]);
grid on


%--------------tratamiento de Wz------------------------


[p3,S3,mu3] = polyfit(t,Wz,4);
f3 = polyval(p3,t,S3,mu3);
Nz=Wz-f3;
figure
plot(t,Nz);
title('Componente Wz','FontSize',13);
xlabel('Tiempo [s]','FontSize',15);
ylabel('Velocidad angular [degº/s]','FontSize',15);
set(gca,'XTick',xmin:xmax/20:xmax,'FontSize',15);
set(gca,'YTick',ymin:ymax/10:ymax,'FontSize',15);
axis([xmin xmax ymin ymax]);
grid on

% %----------------------------------------------------------------


datos = [Wx,Wy,Wz,f1,f2,f3];
figure
plot(t,Wx,'+',t,Wy,'*',t,Wz);
legend('Wx','Wy','Wz');
title('Gráfica de velocidad angular vs tiempo','FontSize',15);
xlabel('Tiempo [s]','FontSize',15);
ylabel('Velocidad angular [degº/s]','FontSize',15);
set(gca,'XTick',xmin:xmax/20:xmax,'FontSize',15);
set(gca,'YTick',ymin:ymax/10:ymax,'FontSize',15);
axis([xmin xmax ymin ymax]);
grid on;



%----------------------------------transformada rapida de fourier----------
T=0.0043;    %tiempo de muestreo
Fs=1/T;      %sampling frecuency
L=1107;      %longitud de la señal
NFFT= 2^nextpow2(L);
Yt=fft(Wy,NFFT)/L;
f=Fs/2*linspace(0,1,NFFT/2+1);
figure
area(f,2*abs(Yt(1:NFFT/2+1)));
title('Single-Sided Amplitude Spectrum of y(t)')
xlabel('Frequency (Hz)')
ylabel('|Y(f)|')
axis([0 15 0 4]);
set(gca,'XTick',0:15/10:15);
set(gca,'YTick',0:0.5:4);

