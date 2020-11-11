//ESTE PROGRAMA GESTIONA UN IMU DE 6 DOF DE SALIDAS DIGITALES COMPATIBLE CON EL PROTOCOLO I2C



void main()
{
// DECLARACION DE LOS REGISTROS DEL ACELEROMETRO
 #define READ_ADXL    0xA7
 #define WRITE_ADXL   0xA6
 #define DATA_FORMAT  0x31
 #define POWERCTL     0x2D
 #define INT_ENABLE   0x2E
 #define BWRATE       0x2C
 #define DATAX0       0x32
 #define DATAX1       0x33
 #define DATAY0       0x34
 #define DATAY1       0x35
 #define DATAZ0       0x36
 #define DATAZ1       0x37

 // DECLARACION DE LOS REGISTROS DEL GIROSCOPO

 #define READ_ITG     0xD3
 #define WRITE_ITG    0xD2
 #define SAMPLE_DIV   0x15
 #define DLPF_FS      0x16
 #define GYRO_X1      0x1D
 #define GYRO_X0      0x1E
 #define GYRO_Y1      0x1F
 #define GYRO_Y0      0x20
 #define GYRO_Z1      0x21
 #define GYRO_Z0      0x22                                                                                                                                     ·

int i,k,A,B,C1;
//C[2];
int Cf;
//ofsetA[2],ofsetG[2];
char txt[7];
// CONFIGURACION DEL PUERTO B Y C COMO SALIDA

 DDRC =  1;
 DDRB =  3;
 PORTC = 1;
 PORTB = 2;



 TWI_Init(400000);         // initialize TWI communication at 100KHz

  //---------------------  INICIACLIZACION DEL ACELEROMETRO  -------------------
   Delay_ms(1);
   TWI_Start();              // issue TWI start signal
   TWI_Write(WRITE_ADXL);    // send byte via TWI (device address + W)
   TWI_Write(DATA_FORMAT);
   TWI_Write(0X0B);          //escala 16g a 13 bits con signo en full resolution
   TWI_Stop();               // issue TWI stop signal
   Delay_ms(1);

   TWI_Start();
   TWI_Write(WRITE_ADXL);
   TWI_Write(POWERCTL);
   TWI_Write(0X08);
   TWI_Stop();
   Delay_ms(1);

   TWI_Start();
   TWI_Write(WRITE_ADXL);
   TWI_Write(INT_ENABLE);
   TWI_Write(0X80);
   TWI_Stop();
   Delay_ms(1);

//-----------------------CALIBRACION DEL OFFSET ACELEROMETRO ------------------------------//
// PROMEDIO RECURSIVO
   //PORTB=3;
/*Delay_ms(1000);
 for(i=0;i<=200;i++)
   {
          if(i==0)
               {
               ofsetA[0]=0;
               ofsetA[1]=0;
               ofsetA[2]=0;
               C[0]=0;
               C[1]=0;
               C[2]=0;
               }
          else
          {

              TWI_Start();
              TWI_Write(WRITE_ADXL);
              TWI_Write(DATAX0);
              TWI_Start();
              TWI_Write(READ_ADXL);

              for(k=0;k<3;k++)
                 {
                 A=TWI_Read(1);
                 B=TWI_Read(1);
                 C1=B*0x100+A;
                 C[k]=C1;
                 ofsetA[k]=(ofsetA[k]+C[k])/i;
                 A=B=C1=0;
                 }

              TWI_Stop();
              Delay_ms(1);
              TWI_Close();
              Delay_ms(1);

           }
     }
               C[0]=0;
               C[1]=0;
               C[2]=0;*/
     //PORTB=2;
    //---------------------------O-------------------------------------------------//

   TWI_Start();              // INICIALIZACION DEL GYROSCOPIO
   TWI_Write(WRITE_ITG);
   TWI_Write(DLPF_FS);
   TWI_Write(0X1A);
   TWI_Stop();
   Delay_ms(1);

   TWI_Start();              // INICIALIZACION DEL GYROSCOPIO
   TWI_Write(WRITE_ITG);
   TWI_Write(SAMPLE_DIV);
   TWI_Write(0X00);
   TWI_Stop();
   Delay_ms(1);

//----------------------  OFFSET GIROSCOPIO  --------------------------------

 /*for(i=0;i<=200;i++)
    {
          if(i==0)
               {
               ofsetG[0]=0;
               ofsetG[1]=0;
               ofsetG[2]=0;
               C[0]=0;
               C[1]=0;
               C[2]=0;
               }
          else
          {

              TWI_Start();               // issue TWI start signal
              TWI_Write(WRITE_ITG);      // send byte via TWI (device address + W)
              TWI_Write(GYRO_X1);
              TWI_Start();                    // issue TWI start signal
              TWI_Write(READ_ITG);          // send byte via TWI (device address + W)

                     for(k=0;k<3;k++)
                         {
                          A=TWI_Read(1);
                          B=TWI_Read(1);
                          C1=A*0x100+B;
                          C[k]=C1;
                          ofsetG[k]=(ofsetG[k]+C[k])/i;

                          //PORTB=2;                    //PARA PRUEBAS DELTA T
                          A=B=C1=0;
                          //Delay_ms(1);
                         }
            TWI_Stop();
            Delay_ms(1);
            TWI_Close();
            Delay_ms(1);
                          // issue TWI stop signal
            }
     }

               C[0]=0;
               C[1]=0;
               C[2]=0;*/

//------------------------------FIN DEL OFFSET GIROSCOPO--------------------------------------


 UART1_Init(115200);       // INICIALIZA UART a 11520000 bps
 Delay_ms(100);
 while(1)
  {
     if(UART1_Data_Ready()==1)

     {
         if(UART1_Read() == '@')

  //----------------------  DATOS DEL ACELEROMETRO  --------------------------------
             {
     //PORTB=3;                     //PRUEBAS DELTA T
              TWI_Start();                 // issue TWI start signal
              TWI_Write(WRITE_ADXL);       // send byte via TWI (device address + W)
              TWI_Write(DATAX0);            //PUNTO INICIAL DE LA LECTURA
              TWI_Start();
              TWI_Write(READ_ADXL);

                    for(k=0;k<3;k++)                              //PASADA DE LOS REGISTROS DE INTERES X,Y,Z
                         {
                          A=TWI_Read(1);     //LECTURA PARTE BAJA
                          //SWITCHEO ENTRE LA PARTE ALTA Y LA BAJA
                          B=TWI_Read(1);     //LECTURA PARTE ALTA
                          //UART1_Write(B1);
                          //UART1_Write(A1);
                          Cf=(B*0x100+A);                //CONCATENACION DE LA PARTE ALTA Y BAJA
                          //if(Cf < 0.0001)
                               // Cf = 0.0f;
                          IntToStr(Cf, txt);
                          UART1_Write(32);
                          UART1_Write_Text(txt);
                          //UART1_Write(32);
                          A=B=Cf=0;
                          //Delay_ms(1);
                          }
              TWI_Stop();
              Delay_ms(1);
              TWI_Close();
              Delay_ms(1);

//----------------------  DATOS DEL GYROSCOPIO  --------------------------------
              TWI_Start();               // issue TWI start signal
              TWI_Write(WRITE_ITG);      // send byte via TWI (device address + W)
              TWI_Write(GYRO_X1);
              TWI_Start();                    // issue TWI start signal
              TWI_Write(READ_ITG);          // send byte via TWI (device address + W)

                     for(k=0;k<3;k++)
                         {
                          A=TWI_Read(1);
                          B=TWI_Read(1);
                          //UART1_Write(A2);
                          //UART1_Write(B2);
                          Cf=(A*0x100+B);
                          //if(Cf < 0.0001)
                                //Cf = 0.0f;
                          IntToStr(Cf, txt);
                          UART1_Write(32);
                          UART1_Write_Text(txt);
                          A=B=Cf=0;
                          //Delay_ms(1);
                          }
              TWI_Stop();
              Delay_ms(1);
              TWI_Close();
              Delay_ms(1);
             }

       }

 }
}