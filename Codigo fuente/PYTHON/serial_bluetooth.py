##APENDICE C CÓDIGO PYTHON DE LECTURA DEL PUERTO SERIAL

#------------------- importar modulos incluyendo al actor --------------------


from direct.showbase import DirectObject
from pandac.PandaModules import *
from direct.task.Task import Task
from direct.actor import Actor

import sys
import Gnuplot, Gnuplot.funcutils
import time
import serial
import os


if __name__ == '__main__':
    import direct.directbase.DirectStart
    

#---------- definición de todos los métodos en la clase principal ------------

class seri_class(DirectObject.DirectObject):
    def __init__ (self):
        
#---------------- tecla ESC termina al ejecucion del programa ----------------
        self.accept('escape',sys.exit)
        self.nodoBase=render.attachNewNode('legraf nodoBase')
        self.config()
        self.peticion()
        self.lectura()
        self.ar= open('tt.txt','w')
        self.ar.writelines('0 0 0 0 0 0\n')
        self.ar.close()
        self.graf=Gnuplot.Gnuplot(debug=0)
        self.graf.title('Datos IMUs')
        self.graf.plot(
                       ## Gnuplot.File('tt.txt',using='1',with_='linespoints', title = 'Ax'),
                       ## Gnuplot.File('tt.txt',using='2',with_='linespoints', title = 'Ay'),
                       ## Gnuplot.File('tt.txt',using='3',with_='linespoints', title = 'Az'),
                       Gnuplot.File('tt.txt',using='4',with_='linespoints', title = 'Wx'),
                       Gnuplot.File('tt.txt',using='5',with_='linespoints', title = 'Wy'),
                       Gnuplot.File('tt.txt',using='6',with_='linespoints', title = 'Wz')
                      ) 
        taskMgr.add(self.update, "Update comm")
    
#---------------------- configuracion de puerto serial -----------------------
    
    def config(self):
        self.ser = serial.Serial(4)
        self.ser.baudrate =115200
        self.ser.open()
    
    def peticion(self):
        self.ser.write("@")
        
    def lectura(self):
        self.p = self.ser.read(42)
        self.datos = []
        for algo in self.p.split():
            self.datos.append(int(algo))

#-------------------- creaccion de la base de datos tt.txt -------------------
    
    def graficacion(self):
        self.ar= open('tt.txt','a')
        self.ar.writelines(
                           str(self.datos[0])+' '+
                           str(self.datos[1])+' '+
                           str(self.datos[2])+' '+
                           str(self.datos[3])+' '+
                           str(self.datos[4])+' '+
                           str(self.datos[5])+' '+
                         '\n')
        self.ar.close()        
    
#-------------------------- administrador de tareas --------------------------

    def update(self, task):
        if  time.clock() > 60:
            self.ser.close()
            sys.exit()
        self.peticion()
        self.lectura()
        self.graficacion()
        messenger.send("Datos Serial", [self.datos])
        return Task.cont
    
comm_blue = seri_class()

if __name__ == '__main__':
    run()