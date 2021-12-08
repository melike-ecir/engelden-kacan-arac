#include <main.h>
#define echo pin_c1
#define trig pin_c0
#FUSES XT,NOWDT,NOPROTECT,PUT,NOBROWNOUT,NOLVP
#use delay(clock=4000000)


void main()
{
   float uzaklik, zaman, sol, sag;
   setup_timer_1(T1_INTERNAL|T1_DIV_BY_8);      //13,1 ms overflow
   set_tris_c(0b11111110);
   set_tris_d(0b00000000);
   output_low(trig);
   output_high(pin_d1);
   delay_ms(200);

   while(TRUE)
   {
      for(int m=0;m<25;++m)
             {
              output_high(pin_d0);
              delay_us(1500);
              output_low(pin_d0);
              delay_us(18500);
             }
             
      output_high(trig);
      delay_us(10);                       
      output_low(trig);
      while(input(echo)!=1)                     
      {}
      set_timer1(0);                         
      while(input(echo)!=0)                     
      {}
      zaman=get_timer1();
      uzaklik=zaman*4/27;
      
      
         output_low(pin_b5); //led
         
         output_high(pin_d2);
         output_low(pin_d3);
         output_high(pin_d4);
         output_low(pin_d5);
         sag=0;
         sol=0;
       if(uzaklik<25 && uzaklik>3)
      {
             output_low(pin_d2);
             output_low(pin_d3);
             output_low(pin_d4);
             output_low(pin_d5);
           
           for(int l=0;l<15;++l)    //SENSÖR SOLA
             {
              output_high(pin_d0);
              delay_us(700);
              output_low(pin_d0);
              delay_us(19200);
             }
               delay_ms(700);
               
               output_high(trig);      // SOL ÖLÇÜM
               delay_us(10);                       
               output_low(trig);
               while(input(echo)!=1)                     
               {}
               set_timer1(0);                         
               while(input(echo)!=0)                     
               {}
               zaman=get_timer1();
               sol=zaman*4/27;
               
               delay_ms(100);
             
             for(int k=0;k<15;++k)     //SENSÖR SAÐA
             {
              output_high(pin_d0);
              delay_us(2350);
              output_low(pin_d0);
              delay_us(17600);
             }
                 delay_ms(700);
                 
               output_high(trig);      //SAÐ ÖLÇÜM
               delay_us(10);                       
               output_low(trig);
               while(input(echo)!=1)                     
               {}
               set_timer1(0);                         
               while(input(echo)!=0)                     
               {}
               zaman=get_timer1();
               sag=zaman*4/27;
               
               delay_ms(100);
         
         output_high(pin_b5); //led
        
      }
               if(sol <= sag-5)
                 {
                  output_high(pin_d2);
                  output_low(pin_d3);
                  output_high(pin_d5);
                  output_low(pin_d4);
                  delay_ms(500);
                  }
      
               if(sag < sol-5)
                 {
                  output_high(pin_d3);
                  output_low(pin_d2);
                  output_high(pin_d4);
                  output_low(pin_d5);
                  delay_ms(500);
                  }
                  sag=0;
                  sol=0;
                   output_high(pin_d2);
                   output_low(pin_d3);
                   output_high(pin_d4);
                   output_low(pin_d5);
      
   }

}


