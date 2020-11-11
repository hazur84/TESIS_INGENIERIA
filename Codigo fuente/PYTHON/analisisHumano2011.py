#APENDICE E programa modelo 3D del avatar deportista.

import direct.directbase.DirectStart
from pandac.PandaModules import*
from direct.task import Task
from direct.actor import Actor

#actor importa el avatar3d
#Task me permite manejar tareas

from direct.interval.IntervalGlobal import*
from direct.showbase import DirectObject

from math import *

class human_class(DirectObject.DirectObject):
    def __init__ (self):

        self.file = open('record1.txt', 'r')
        self.fileList = self.file.readlines()
        self.totalLineas = len(self.fileList)
        self.file.close()

        self.posTiempo = 0

        #importacion del avatar *.egg al motor de juegos.
        self.human = Actor.Actor('hombre_base2')
        self.human.reparentTo(render)
        base.camera.reparentTo(self.human)
        base.camera.setY(-16)
        base.camera.setZ(3)
        base.disableMouse()

        self.accept("q",self.cambiaFun,[1])
        self.accept("a",self.cambiaFun,[-1])

        self.accept("w",self.selectPart,[0])
        self.accept("e",self.selectPart,[1])
        self.accept("r",self.selectPart,[2])
        self.accept("s",self.selectPart,[4])
        self.accept("d",self.selectPart,[5])
        self.accept("f",self.selectPart,[6])
        self.accept("x",self.selectPart,[8])
        self.accept("c",self.selectPart,[9])
        self.accept("v",self.selectPart,[10])

        self.creaProxy()
                
        #asignacion del avatar al nodo principal del motor grafico

        self.human.reparentTo(render)

        #seccion de control de articulacion del avatar

        self.Pelvis          = self.human.controlJoint(None,"modelRoot","Pelvis")        
        self.Hip_L           = self.human.controlJoint(None,"modelRoot","Hip_L")        
        self.UpperLeg_L      = self.human.controlJoint(None,"modelRoot","UpperLeg_L")        
        self.LowerLeg_L      = self.human.controlJoint(None,"modelRoot","LowerLeg_L")        
        self.Foot_L          = self.human.controlJoint(None,"modelRoot","Foot_L")        
        self.Hip_R           = self.human.controlJoint(None,"modelRoot","Hip_R")        
        self.UpperLeg_R      = self.human.controlJoint(None,"modelRoot","UpperLeg_R")        
        self.LowerLeg_R      = self.human.controlJoint(None,"modelRoot","LowerLeg_R")        
        self.Foot_R          = self.human.controlJoint(None,"modelRoot","Foot_R")        
        self.Back            = self.human.controlJoint(None,"modelRoot","Back")        
        self.Neck            = self.human.controlJoint(None,"modelRoot","Neck")        
        self.Head            = self.human.controlJoint(None,"modelRoot","Head")        
        self.Shoulder_L      = self.human.controlJoint(None,"modelRoot","Shoulder_L")        
        self.UpperArm_L      = self.human.controlJoint(None,"modelRoot","UpperArm_L")        
        self.LowerArm_L      = self.human.controlJoint(None,"modelRoot","LowerArm_L")        
        self.Palm_L          = self.human.controlJoint(None,"modelRoot","Palm_L")
        self.Fingers_L       = self.human.controlJoint(None,"modelRoot","Fingers_L")
        self.Thumb_L         = self.human.controlJoint(None,"modelRoot","Thumb_L")
        self.Shoulder_R      = self.human.controlJoint(None,"modelRoot","Shoulder_R")        
        self.UpperArm_R      = self.human.controlJoint(None,"modelRoot","UpperArm_R")        
        self.LowerArm_R      = self.human.controlJoint(None,"modelRoot","LowerArm_R")        
        self.Palm_R          = self.human.controlJoint(None,"modelRoot","Palm_R")
        self.Fingers_R       = self.human.controlJoint(None,"modelRoot","Fingers_R")
        self.Thumb_R         = self.human.controlJoint(None,"modelRoot","Thumb_R")

        self.lista = []
            
        self.parteEscogida = 0
        self.tiempoReplay = 0.043
        self.tiempoInc = 1
        self.lastSentido = 1

        self.lista.append(self.Palm_R)
        self.lista.append(self.LowerArm_R)
        self.lista.append(self.UpperArm_R)
        self.lista.append(self.Shoulder_R)
        
        self.lista.append(self.Palm_L)
        self.lista.append(self.LowerArm_L)
        self.lista.append(self.UpperArm_L)
        self.lista.append(self.Shoulder_L)
        
        self.lista.append(self.Head)
        self.lista.append(self.Neck)        
        self.lista.append(self.Back)
        
        
        self.lista.append(self.Fingers_R)
        self.lista.append(self.Fingers_L)
        self.lista.append(self.Thumb_R)
        self.lista.append(self.Thumb_L)

        self.lista.append(self.Pelvis)
        self.lista.append(self.Hip_L)    
        self.lista.append(self.Foot_L)
        self.lista.append(self.Hip_R  )
        self.lista.append(self.Foot_R)

        self.accept('arrow_up', self.cambiaTiempoReplay, [-0.01])
        self.accept('arrow_down', self.cambiaTiempoReplay, [0.01])
        
        self.accept('arrow_left', self.cambiaSentido, [-1])
        self.accept('arrow_right', self.cambiaSentido, [1])
        self.accept('space', self.pausa)

        taskMgr.add(self.update, "Update human")

    def pausa(self):
        
        if self.tiempoInc != 0:
            self.lastSentido = self.tiempoInc
            self.tiempoInc = 0
        else:
            self.tiempoInc = self.lastSentido
        
    def cambiaSentido(self, num):
        self.tiempoInc = num

    def cambiaTiempoReplay(self, inc):
        
        self.tiempoReplay += inc
        
        if self.tiempoReplay <= 0:
            self.tiempoReplay = 0.01

    def creaProxy(self):
        self.esfera = loader.loadModel('esfera')
        self.esfera.reparentTo(render)
        self.esfera.setTransparency(True)
        self.esfera.setTransparency(TransparencyAttrib.MAlpha)
        self.esfera.setScale(0.3)
        
        self.listaExposeJoints = []

        self.listaExposeJoints.append(self.human.exposeJoint(None,"modelRoot","Palm_R"))
        self.listaExposeJoints.append(self.human.exposeJoint(None,"modelRoot","LowerArm_R"))
        self.listaExposeJoints.append(self.human.exposeJoint(None,"modelRoot","UpperArm_R"))
        self.listaExposeJoints.append(self.human.exposeJoint(None,"modelRoot","Shoulder_R"))
        self.listaExposeJoints.append(self.human.exposeJoint(None,"modelRoot","Palm_L"))
        self.listaExposeJoints.append(self.human.exposeJoint(None,"modelRoot","LowerArm_L"))
        self.listaExposeJoints.append(self.human.exposeJoint(None,"modelRoot","UpperArm_L"))
        self.listaExposeJoints.append(self.human.exposeJoint(None,"modelRoot","Shoulder_L"))
        self.listaExposeJoints.append(self.human.exposeJoint(None,"modelRoot","Head"))
        self.listaExposeJoints.append(self.human.exposeJoint(None,"modelRoot","Neck"))
        self.listaExposeJoints.append(self.human.exposeJoint(None,"modelRoot","Back"))
        self.listaExposeJoints.append(self.human.exposeJoint(None,"modelRoot","Fingers_R"))
        self.listaExposeJoints.append(self.human.exposeJoint(None,"modelRoot","Fingers_L"))
        self.listaExposeJoints.append(self.human.exposeJoint(None,"modelRoot","Thumb_R"))
        self.listaExposeJoints.append(self.human.exposeJoint(None,"modelRoot","Thumb_L"))
        self.listaExposeJoints.append(self.human.exposeJoint(None,"modelRoot","Pelvis"))
        self.listaExposeJoints.append(self.human.exposeJoint(None,"modelRoot","Hip_L"))
        self.listaExposeJoints.append(self.human.exposeJoint(None,"modelRoot","Foot_L"))
        self.listaExposeJoints.append(self.human.exposeJoint(None,"modelRoot","Hip_R"))
        self.listaExposeJoints.append(self.human.exposeJoint(None,"modelRoot","Foot_R"))
        
    def cambiaFun(self, num):
        
        self.parteEscogida += num
        self.parteEscogida = self.parteEscogida%len(self.lista)

    def selectPart(self, num):
        
        self.parteEscogida = num
    
    def update(self, task):
    
        self.posTiempo += self.tiempoInc
        self.posTiempo = self.posTiempo%self.totalLineas
    
        print self.posTiempo
    
        self.lista[self.parteEscogida].setHpr(float(self.fileList[self.posTiempo].split()[0]),float(self.fileList[self.posTiempo].split()[1]),float(self.fileList[self.posTiempo].split()[2]))
        self.esfera.setPos(self.listaExposeJoints[self.parteEscogida].getPos())
        self.esfera.setH(self.esfera.getH() + 20)
    
        frec = 1
        self.esfera.setScale(0.2+0.1*sin(task.time*frec*2*3.14))
    
        print self.lista[self.parteEscogida].getHpr()
    
        taskMgr.doMethodLater(self.tiempoReplay, self.update, 'update') 
    
        return Task.done

human = human_class()

run()