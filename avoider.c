#include <mega16.h>
#include <delay.h>
#define s PORTC.0
#define ADC_VREF_TYPE 0x60

// Read the 8 most significant bits
// of the AD conversion result

unsigned char read_adc(unsigned char adc_input)
{
    ADMUX=adc_input | (ADC_VREF_TYPE & 0xff);
    // Delay needed for the stabilization of the ADC input voltage
    delay_us(10);
    // Start the AD conversion
    ADCSRA|=0x40;
    // Wait for the AD conversion to complete
    while ((ADCSRA & 0x10)==0);
    ADCSRA|=0x10;
    return ADCH;
}

// Declare your global variables here
int i;

unsigned char jarak(unsigned char x)
{
    if (read_adc(x)<21) return 80;
    else return (1560/read_adc(x)-2);
}

void p0()
{   
    for (i=0;i<47;i++)
    {   s =1;
        delay_us(1300);
        s=0;
        delay_ms(15);
    }
}

void p90()
{   
    for (i=0;i<47;i++)
    {   s =1;
        delay_us(3250);
        s=0;
        delay_ms(15);                                                                                         
    }
}   

void p180()
{   
    for (i=0;i<47;i++)    // PORTB  xxxx 01 01 = maju; = PORTB = 0x05;
    {   s =1;             // PORTB xxxx 00 00 = stop;
        delay_us(5200); 
        s=0;
        delay_ms(15) ;
    }
}

void go()
{   
    PORTD = 0x05;                                                                                   
    OCR1A = 250;
    OCR1B = 255;
}

void stop()
{   
    PORTD = 0x00;
}

/*void maju()
{   OCR1A = OCR1B = 254;
                
    // delay_ms();     
}*/

void kanan()                 //kiri kanan
{   
    PORTD = 0x04;            //xxxx 10 00
    //OCR1A =  250;
    //OCR1B =  200   ;            
    delay_ms(1050);   
}

void kiri()
{   PORTD = 0x01;            // xx 00 01   
 //   OCR1A =  200   ;
//    OCR1B =  250   ;            
     delay_ms(1050);
}

void main(void)
{
    // Declare your local variables here
    unsigned char a;
    
    // Input/Output Ports initialization
    // Port A initialization
    // Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
    // State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
    PORTA=0x00;
    DDRA=0x00;              
    
    // Port B initialization
    // Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
    // State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
    PORTB=0x05;
    DDRB=0xff;              
    
    // Port C initialization
    // Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=Out 
    // State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=0 
    PORTC=0x00;
    DDRC=0xf1;
    
    // Port D initialization    
    // Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
    // State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
    PORTD=0x00;
    DDRD=0xFF;

    // Timer/Counter 0 initialization
    // Clock source: System Clock
    // Clock value: Timer 0 Stopped
    // Mode: Normal top=FFh
    // OC0 output: Disconnected
    TCCR0=0x00;
    TCNT0=0x00;
    OCR0=0x00;
    
    // Timer/Counter 1 initialization
    // Clock source: System Clock
    // Clock value: 16000.000 kHz
    // Mode: Fast PWM top=0x00FF
    // OC1A output: Non-Inv.
    // OC1B output: Non-Inv.
    // Noise Canceler: Off
    // Input Capture on Falling Edge
    // Timer1 Overflow Interrupt: Off
    // Input Capture Interrupt: Off
    // Compare A Match Interrupt: Off
    // Compare B Match Interrupt: Off
    TCCR1A=0xA1;
    TCCR1B=0x09;
    TCNT1H=0x00;
    TCNT1L=0x00;
    ICR1H=0x00;
    ICR1L=0x00;
    OCR1AH=0x00;
    OCR1AL=0x00;
    OCR1BH=0x00;
    OCR1BL=0x00;
    
    // Timer/Counter 2 initialization
    // Clock source: System Clock
    // Clock value: Timer2 Stopped
    // Mode: Normal top=FFh
    // OC2 output: Disconnected
    ASSR=0x00;
    TCCR2=0x00;
    TCNT2=0x00;
    OCR2=0x00;
    
    // External Interrupt(s) initialization
    // INT0: Off
    // INT1: Off
    // INT2: Off
    MCUCR=0x00;
    MCUCSR=0x00;
    
    // Timer(s)/Counter(s) Interrupt(s) initialization
    TIMSK=0x00;
    
    // Analog Comparator initialization
    // Analog Comparator: Off
    // Analog Comparator Input Capture by Timer/Counter 1: Off
    ACSR=0x80;
    SFIOR=0x00;
    
    // ADC initialization
    // ADC Clock frequency: 1000.000 kHz
    // ADC Voltage Reference: AVCC pin
    // ADC Auto Trigger Source: None
    // Only the 8 most significant bits of
    
    // the AD conversion result are used
    ADMUX=ADC_VREF_TYPE & 0xff;
    ADCSRA=0x83;
    OCR1A =255;
    OCR1B = 250;
    
    while (1){
    
        // Place your code here    
        p90();
        a = jarak(0);
        if(a<35) // awal        
        {   
            stop();
            p180();
            //delay_ms(10);
            a = jarak(0);
            
            if(a<35){ 
                p0();
                a= jarak(0);
                if(a>35){  
                    kanan();
                  //  delay_ms(100);
                 // p90();
                } 
            }
            else
            {  
                kiri();
                // delay_ms(100);              
            }              
        }
        
        else{
            go();
        }
                                                                                        
      delay_ms(10);   // tutup 1   
    }    
}      
                   




   

