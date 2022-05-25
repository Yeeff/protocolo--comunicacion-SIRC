#include <avr/io.h>
#include <util/delay.h>

void main (void){

unsigned int x=0,y=0,data=0,con=0, estadoAnt=1, estado=0;

DDRB|=(1<<3);//PIN D4 COMO SALIDA

DDRB&=~(1<<2);// The b2 pin set as entry swich
PORTB|=(1<<2);// Resistor pull up actived

DDRB&=~(1<<4);// The b4 pin set as IF entry 
PORTB|=(1<<4);// Resistor pull up actived

   while(1)
   {  
      if((PINB&(1<<4))==0  && (x==0)) // If is a low detected...
	  {  
	     TCCR0B=0B00000011;// Set register. 
         TCNT0=0; // The timer start on zero.
		 while(y==0) //bucle, signal of  2400Us                                   
		 {             //Timer start
		   
		   if ((PINB&(1<<4))!=0 && (x==0)){x=1;}//If a High is detected, set x.
		   
           if((PINB&(1<<4))==0 && (x==1)){y=1;x=0;}// If now it's low and it was high get out of bluclel and x=0.
               	
           if(TCNT0>40)
		   {   
               TCNT0=0;     // Start timer 1000Us
               while(y==0)
               {    
                   if((PINB&(1<<4))!=0 && (x==0)){x=1;}//If a High is detected, set x.
                   if((PINB&(1<<4))==0 && x==1)     
			       {   
                       x=0;
                       TCNT0=0; // empieza timer 900
                       while(y==0)
				       {  //PORTB|=(1<<0);//--------------------------------------0
					      if((PINB&(1<<4))!=0 && (x==0)){x=1;}
						  if((PINB&(1<<4))==0 && (x==1)){y=1;}
						  if(TCNT0>=15)
						  {   //PORTB|=(1<<1);//----------------------------------1
						      if((PINB&(1<<4))==0)
					          {  
                                 data=(data<<1);
                                 data|=(1<<0);
							     con++;
								 TCNT0=0;
						         break;
						      }
						      else
					          {  
							     data=(data<<1);
                                 con++;
                                 TCNT0=0;  
                                 break;
						      }
						    }  
					    } 
					} 
                    if(TCNT0>17){
					   //PORTB =con;
					   y=1;
					   data=0;
                       con=0;
                       x=0;    
					}
			        if(con==8){
					   
					   if(data==0b11111111){PORTB^=(1<<3);}
					   y=1;
					   data=0;
					   con=0;
					   x=0;
					}
					
               } 
		   }								 		 					 	  	 
	    }
      }
	  
	  if(y==1){y=0;x=0;_delay_ms(100);}
	  
	  estado=PINB&(1<<2);
	  if(estado != estadoAnt){
		 PORTB^=(1<<3);
		 estadoAnt=estado;
		 _delay_ms(500);
	  } 
	  
	} 
}


