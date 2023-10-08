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
#use delay(clock=20000000)

#byte TRISC = 0x87
#byte PORTC = 0x07

void spi_write_slave1(int8 data)
{    
   output_low(PIN_C1);
   spi_write(data);
   delay_ms(100);
   output_high(PIN_C1);
   delay_ms(100);
}


void spi_write_slave2(int8 data)
{
   output_low(PIN_C2);
   spi_write(data);
   delay_ms(100);
   output_high(PIN_C2);
   delay_ms(100);
}


void main()
{
     TRISC=0;
     setup_spi(SPI_MASTER |SPI_L_TO_H | SPI_CLK_DIV_16  );
     delay_ms(100);
     output_high(PIN_C1);
     output_high(PIN_C2);
     int8 data1 = 0b01111111;
     int8 data2 = 0b00000011;
     
    
   while(TRUE)
   {
    
     spi_write_slave1(data1);  
     data1 = data1 +1 ;
   
     spi_write_slave2(data2);
     data2 = data2 + 1;
     
     if (data1==255) data1=0;
     else if (data2==255) data2=0;
     delay_ms(100);
     
   }

}
