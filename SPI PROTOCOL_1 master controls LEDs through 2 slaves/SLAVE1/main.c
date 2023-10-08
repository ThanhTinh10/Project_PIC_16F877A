#include <16F877A.h>
#device adc=8

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES HS                       //High speed Osc (> 4mhz for PCM/PCH) (>10mhz for PCD)
#FUSES NOPUT                    //No Power Up Timer
#FUSES NOPROTECT                //Code not protected from reading
#FUSES NODEBUG                  //No Debug mode for ICD
#FUSES NOBROWNOUT               //No brownout reset
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NOCPD                    //No EE protection
#FUSES NOWRT                    //Program memory not write protected
#FUSES RESERVED                 //Used to set the reserved FUSE bits
//#use delay(clock=20000000)
//#define CS_PIN PIN_A5
//#bit CS_PIN = 0x06.1
#byte TRISD = 0x88
#byte PORTD = 0x08
#byte TRISA = 0x85

void main()
{   
    TRISD = 0;
    PORTD=0;
    TRISA=1;
    setup_spi(SPI_SLAVE | SPI_L_TO_H   | SPI_CLK_DIV_16 );
    int8 data2;
  while(TRUE)
     {    
     data2= spi_read(); 
     if(input(PIN_A5) == 0) 
        PORTD= data2;
    }

}