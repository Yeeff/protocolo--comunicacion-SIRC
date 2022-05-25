#include <avr/io.h>
#include <util/delay.h>

void main(void)
{   int i,j,x=0b11111111,f=9;  
 
    //DDRB&=~(1<<3);//pin b0 como entrada
	//PORTB|=(1<<3);//acticar resistencia pull up
    DDRB|= (1<<4);//pin b3 como salida
	PORTB&=~(1<<4);//inicia apagado

    while (1)
	{ //if(TCNT0>255){PORTB|=(1<<4);} 
      //if((PINB&(1<<3))==0){ 
	         for(i=0;i<103;i++){//2410 en total, si es mayor q 9 es verdadero y si es mayor que 115, sera verdadero y negado, sandra del bucle
			 PORTB|=(1<<4);
	         _delay_us(f);
	         PORTB&=~(1<<4);       
	         _delay_us(f); 
			 } 
	         _delay_us(600);
			 
			 for(i=0;i<8;i++)
	         { if((x&(1<<i))==0){
	              for(j=0;j<26;j++){//600 micros en total
			         PORTB|=(1<<4);
	                 _delay_us(f);
	                 PORTB&=~(1<<4);       
	                 _delay_us(f);
			      }
	               _delay_us(600);  
	            }
	            else{
		            for(j=0;j<48;j++){//1200 micros en total
			        PORTB|=(1<<4);
	                _delay_us(f);
	                PORTB&=~(1<<4);       
	                _delay_us(f);
			        }
				    _delay_us(600);
		        }
	         }
			 
			 
			 _delay_ms(2);
			 
		//}	 
    }	
}

