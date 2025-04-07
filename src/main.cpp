//codigo base para display con 2 botones tarea 1 sem 3.___
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void) {
    // Configurar pines D4-D7 y B8-B12 como salida
    DDRD |= 0xF0; // Configura PD4-PD7 como salida
    DDRB |= 0x0F; // Configura PB0-PB4 (pines 8-12) como salida

    DDRD &= ~(0x0C);  // Configura PD2 y PD3 como entrada para pulsadores
    PORTD |= 0x0C;


    while (1) {
        for (uint8_t decenas = 0; decenas < 10; decenas++) { // Decenas (0-9)
            for (uint8_t unidad = 0; unidad < 10; unidad++) { // Unidades (0-9)
                PORTD = (PORTD & 0x0F) | (decenas << 4); // PD4-PD7 = decenas
                PORTB = (PORTB & 0xE0) | (unidad & 0x0F); // PB0-PB4 = unidades
                _delay_ms(500);
            }
        }
    }
}