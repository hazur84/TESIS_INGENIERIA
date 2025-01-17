/*
    5-18-10
    Copyright Spark Fun Electronics© 2010
    Nathan Seidle
	
	Example I2C to control the ADXL345
	
	Designed to run on an Arduino using the standard serial bootloader.
	This is not written in Arduino, this is a C example.
	
	Things to know: SDO pin must be tied high for address 0x1D or low for address 0x53. 
	It cannot be left floating.
	
	The only register you have to write to, to get the ADXL345 to start outputting data
	is 0x2D, the POWER_CTL register. You have to set bit 3 (MEASURE).
	
	Don't forget to enable or add pullups to SDA/SCL. This firmware uses the internal
	pullups. Should work fine without them.
	
	SCL is Analog pin 5 (aka PC5)
	SDA is Analog pin 4 (aka PC4)
*/

#include <stdio.h>
#include <avr/io.h>
#include "i2c.h" //Needed  for I2C sensors

#define ADXL345_W	0b00111010
#define ADXL345_R	0b00111011

#define FALSE	0
#define TRUE	-1

#define FOSC 16000000 //16MHz external osc

#define SERIAL_BAUD 9600
#define SERIAL_MYUBRR (((((FOSC * 10) / (16L * SERIAL_BAUD)) + 5) / 10) - 1)

//Function definitions
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
void ioinit(void);
void delay_ms(uint16_t x);
void delay_us(uint16_t x);
int uart_putchar(char c, FILE *stream);

int16_t read_adxl345(char reg_adr);
void init_adxl345(void);
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

//Global variables
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
static FILE mystdout = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

int main (void)
{
	int16_t x, y, z;

    ioinit(); //Boot up defaults

	i2cInit(); //Get the I2C bus ready

	printf("ADXL345 Example\n");

	init_adxl345(); //Write to 0x2D power ctl - we have to set bit D3 to start measurment
	
	while(1)
	{
		x = read_adxl345(0x32);
		y = read_adxl345(0x34);
		z = read_adxl345(0x36);

		printf("x=%04d, y=%04d, z=%04d\n", x, y, z);

		if ((UCSR0A & _BV(RXC0))) //Check for incoming RX characters
			if(UDR0 == 'x') break;
			
		//delay_ms(100);
	}
	
	printf("You've gone too far!");
	while(1);

    return(0);
}


void ioinit(void)
{
	
	//1 = output, 0 = input 
    //DDRB = 0b11111111;
    //DDRC = 0b11111110;
    //DDRD = 0b11111111;

	PORTC = 0b00110000; //pullups on the I2C bus
	
    //Setup USART baud rate
    UBRR0H = SERIAL_MYUBRR >> 8;
    UBRR0L = SERIAL_MYUBRR;
    UCSR0B = (1<<RXEN0)|(1<<TXEN0); //No receive interrupt
	UCSR0A ^= (1<<U2X0); //This clears the double speed UART transmission that may be set by the Arduino bootloader

    stdout = &mystdout; //Required for printf init

    //Init Timer0 for delay_us
	TCCR0B = (1<<CS01); //Set Prescaler to clk/8 : 1click = 0.5us(assume we are running at external 16MHz). CS01=1 
}


int16_t read_adxl345(char reg_adr)
{		
	char lsb, msb;

	i2cSendStart();
	i2cWaitForComplete();
	
	i2cSendByte(ADXL345_W);	// write to this I2C address, R/*W cleared
	i2cWaitForComplete();
	
	i2cSendByte(reg_adr);	//Read from a given address
	i2cWaitForComplete();
	
	i2cSendStart();
	
	i2cSendByte(ADXL345_R); // read from this I2C address, R/*W Set
	i2cWaitForComplete();
	
	i2cReceiveByte(TRUE);
	i2cWaitForComplete();
	lsb = i2cGetReceivedByte(); //Read the LSB data
	i2cWaitForComplete();

	i2cReceiveByte(FALSE);
	i2cWaitForComplete();
	msb = i2cGetReceivedByte(); //Read the MSB data
	i2cWaitForComplete();
	
	i2cSendStop();
	
	return( (msb<<8) | lsb);
}

//Setup ADXL345 for constant measurement mode
void init_adxl345(void)
{
	i2cSendStart();
	i2cWaitForComplete();

	i2cSendByte(ADXL345_W); //write to ADXL345
	i2cWaitForComplete();

	i2cSendByte(0x2D); //Write to Power CTL register
	i2cWaitForComplete();

	i2cSendByte( (1<<3) ); //Set the measure bit on D3
	i2cWaitForComplete();

	i2cSendStop();
}

//General short delays
void delay_ms(uint16_t x)
{
	for (; x > 0 ; x--)
	{
		delay_us(250);
		delay_us(250);
		delay_us(250);
		delay_us(250);
	}
}

//General short delays
void delay_us(uint16_t x)
{
	x *= 2; //Runs at 16MHz instead of normal 8MHz

	while(x > 256)
	{
		TIFR0 = (1<<TOV0); //Clear any interrupt flags on Timer2
		TCNT0 = 0; //256 - 125 = 131 : Preload timer 2 for x clicks. Should be 1us per click
		while( (TIFR0 & (1<<TOV0)) == 0);
		
		x -= 256;
	}

	TIFR0 = (1<<TOV0); //Clear any interrupt flags on Timer2
	TCNT0 = 256 - x; //256 - 125 = 131 : Preload timer 2 for x clicks. Should be 1us per click
	while( (TIFR0 & (1<<TOV0)) == 0);
}

int uart_putchar(char c, FILE *stream)
{
    if (c == '\n') uart_putchar('\r', stream);
  
    loop_until_bit_is_set(UCSR0A, UDRE0);
    UDR0 = c;

    return 0;
}
