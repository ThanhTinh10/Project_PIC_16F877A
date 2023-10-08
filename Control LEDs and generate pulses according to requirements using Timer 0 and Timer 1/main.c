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
int1 TTD2;
int count;
#int_timer0
void interrupt_timer0()
{
set_timer0(6);
++count;
if(count == 157 &&  TTD2 == TRUE )
{
count=0;
output_high(PIN_D3);
output_low(PIN_D2);
TTD2 = FALSE;
}
else if(count == 157 &&  TTD2 == FALSE )
{
count=0;
output_high(PIN_D2);
output_low(PIN_D3);
TTD2 = TRUE;
}
}



void main()
{  

   int1  TTD1;
  
   TRISD=0; 
   enable_interrupts(global);
   enable_interrupts(int_timer0);
   setup_timer_0 (RTCC_INTERNAL|RTCC_DIV_128);
   setup_timer_1( T1_INTERNAL| T1_DIV_BY_1 );
   
   set_timer0(0);
   set_timer1(0);
   output_high(PIN_D0);
   output_high(PIN_D1);
   count = 0;
   TTD1= TRUE;
 

   while(TRUE)
   {
      
     if(get_timer1()>5000 & TTD1==TRUE)
     {
         set_timer1(0);
         output_low(PIN_D1);
         TTD1=FALSE;
    
     }
     else if(get_timer1()>10000 & TTD1==FALSE)
     {
         set_timer1(0);
         output_high(PIN_D1);
         TTD1=TRUE;
   
     }
  
}
}
