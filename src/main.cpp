#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void) {
    DDRD |= 0xF0;            // PD4–PD7 como salida (decenas)
    DDRB |= 0x0F;            // PB0–PB3 como salida (unidades)
    
    DDRD &= ~(0x04);     //  boton para subir
    PORTD |= (0x04);     // Pull-up en PD3 (botón a GND)
    
    DDRD &= ~(0x08);     // boton para bajar
    PORTD |= (0x08);     // Pull-up en PD4 (botón a GND)

    uint8_t unidades = 0; //declaramos la variable entero sin signo para poder contar en unidades
    uint8_t decenas = 0; //declaramos las variables para descenas inia en 0 el valor

    while (1) { //base programa

        
        //para el boton que sube numero de 1 en 1

        if (!(PIND&0X04)) {     // Si el botón está presionado
            _delay_ms(50);              // Anti-rebote

            // Esperar a que se suelte el botón
            while (!(PIND & 0x04)); //mientras el boton este precionado el numero cambiara
                _delay_ms(50);              // Anti-rebote

                if (unidades >= 9) {
                    unidades = 0;
                    decenas++; //sube en una unidad
                }
                    else {
                    unidades++; //sube en una unidad

                    }
                    if (decenas > 9) {
                        decenas = 0; // Asegurarse que las decenas no superen 9
                    }
                }

            //para que retroceda pd3

            if (!(PIND & 0x08)) {     // Si el botón en PD3 está presionado
                _delay_ms(50);              // Anti-rebote
    
                // Esperar a que se suelte el botón
                while (!(PIND & 0x08)); // Esperar a que se suelte el botón
                _delay_ms(50);

                if (!(unidades == 0 && decenas == 0)) { // esto es para que se quede firme en 00 y no de vuelta el de unidad

                    if (unidades == 0) {
                        unidades = 9;    // Si las unidades están en 0, reiniciar a 9
                        
                        if (decenas > 0) {
                            decenas--;   // Decrementa las decenas si son mayores que 0
                        }
                    } else {
                        unidades--;     // disminuye la unidad
                    }
        
                    if (decenas > 9) {
                        decenas = 0;    // Asegurarse que las decenas no superen 9
                    }

                }
            }
            // Mostrar en PD4–PD7 (decenas) y en PB0–PB3 (unidades)
        PORTD = (PORTD & 0x0F) | (decenas << 4);   // Actualizar decenas en PD4–PD7
        PORTB = (PORTB & 0xF0) | (unidades & 0x0F); // Actualizar unidades en PB0–PB3
       
        }
    }