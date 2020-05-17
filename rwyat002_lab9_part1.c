/*	Author: lab
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#include "timer.h"
#endif


void set_PWM(double frequency){
static double current_frequency;
if(frequency != current_frequency){
if(!frequency) {TCCR3B &= 0x08;}
else{TCCR3B |= 0x03;}
if(frequency < 0.954){OCR3A = 0xFFFF;}
else if(frequency > 31250){OCR3A = 0x0000;}
else {OCR3A = (short)(8000000 / (128 * frequency)) - 1;}

TCNT3 = 0;
current_frequency = frequency;
}

}

void PWM_on() {
TCCR3A = (1 << COM3A0);
TCCR3B = (1 << WGM32) | (1 << CS31)| (1 << CS30);
set_PWM(0);

}

void PWM_off(){
TCCR3A = 0x00;
TCCR3B = 0x00;
}


enum States{Start,stateC,stateD,stateE,stateBase}state;
void Tick(){
switch(state){
	case Start:
		state = stateBase;
	break;
	case stateC:
		//if((~PINA & 0x07) == 0x00)
		//	state = stateBase;
		 if((~PINA & 0x07)  == 0x01)
			state = stateC;
		else if((~PINA & 0x07)  == 0x02)
			state = stateD;
		else if((~PINA & 0x07)  == 0x04)
			state = stateE;
		 else 
			 state = stateBase;
	break;
	case stateD:
	        //if((~PINA & 0x07)  == 0x00)
                 //       state = stateBase;
                 if((~PINA & 0x07)  == 0x01)
                        state = stateC;
                else if((~PINA & 0x07)  == 0x02)
                        state = stateD;
                else if((~PINA & 0x07)  == 0x04)
                        state = stateE;
		else
			state = stateBase;
	break;
	case stateE:
                //if((~PINA & 0x07)  == 0x00)
                 //       state = stateBase;
                 if((~PINA & 0x07)  == 0x01)
                        state = stateC;
                else if((~PINA & 0x07)  == 0x02)
                        state = stateD;
                else if((~PINA & 0x07)  == 0x04)
                        state = stateE;
		else
			state = stateBase;
	break;
	case stateBase:
	        //if((~PINA & 0x07)  == 0x00)
                //        state = stateBase;
                 if((~PINA & 0x07)  == 0x01)
                        state = stateC;
                else if((~PINA & 0x07)  == 0x02)
                        state = stateD;
                else if((~PINA & 0x07)  == 0x04)
                        state = stateE;
		else 
			state = stateBase;
	break;


}
switch(state){
        case Start:
        break;
        case stateC:
		set_PWM(261.63);
        break;
        case stateD:
		set_PWM(293.66);
        break;
        case stateE:
		set_PWM(329.63);
        break;
        case stateBase:
		set_PWM(0);
        break;




}


}






int main(void) {
    /* Insert DDR and PORT initializations */
	DDRB = 0x40; PORTB = 0xBF; 
    /* Insert your solution below */
	DDRA = 0x00; PORTA = 0xFF;
	TimerSet(250);
	TimerOn();
	PWM_on();
	state = Start;

    while (1) {
	Tick();
	while(!TimerFlag){}
	TimerFlag = 0;
    }
    return 1;
}
