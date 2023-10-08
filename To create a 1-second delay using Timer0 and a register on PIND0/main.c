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
#byte TRISD = 0x88
#byte PORTD = 0x08
#byte OPTION_REG = 0x81
#bit T0IF = 0x0B.2

void t0delay();
void main()
{
  TRISD=0;
  OPTION_REG=0x07;   //Prescale is assigned to Timer 0, Prescaler value = 256, Fclk = 11.0592MHz
  while(1) {
    PORTD=0xff;
    t0delay();
    PORTD=0x00;
    t0delay();
  }
}
void t0delay()          // 1 second
{
  int i;
  for(i=0;i<42;i++) {
    while(!T0IF);
    T0IF=0;
  }
}  
