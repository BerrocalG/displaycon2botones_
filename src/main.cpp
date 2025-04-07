#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void) {
    DDRD |= 0xF0;            // PD4–PD7 como salida (decenas)
    DDRB |= 0x0F;            // PB0–PB3 como salida (unidades)
    
    DDRD &= ~(0x04);     // PD3 como entrada (botón)
    PORTD |= (0x04);     // Pull-up en PD3 (botón a GND)

    uint8_t unidades = 0;
    uint8_t decenas = 0;

    while (1) {
        if (!(PIND&0X04)) {     // Si el botón está presionado
            _delay_ms(50);              // Anti-rebote

            // Esperar a que se suelte el botón
            while (!(PIND & 0x04)); //mientras el boton este precionado el numero cambiara

                if (unidades > 9) {
                    _delay_ms(50);
                    unidades = 0;
                    decenas++;
                }
                    else {
                    _delay_ms(50);

                    unidades++;
                    }
                    if (decenas > 9) {
                        _delay_ms(50);
                        decenas = 0;
                    }
                }

            // Mostrar en PD4–PD7 (decenas)
            PORTD = (PORTD & 0x0F) | (decenas << 4);
            // Mostrar en PB0–PB3 (unidades)
            PORTB = (PORTB & 0xF0) | (unidades & 0x0F);
        }
    }

