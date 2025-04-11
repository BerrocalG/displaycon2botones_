
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void) {
    DDRD |= 0xF0;            // PD4–PD7 como salida (decenas)
    DDRB |= 0x0F;            // PB0–PB3 como salida (unidades)
    
    DDRD &= ~(0x04);         // botón para subir
    PORTD |= (0x04);         
    DDRD &= ~(0x08);         // botón para bajar
    PORTD |= (0x08);         
    DDRB &= ~(0x20);         // botón para bajar
    PORTB |= (0x20); 

    uint8_t unidades = 0;    
    uint8_t decenas = 0;  
    
    uint8_t guardadou=0;
    uint8_t guardadod=0;

    PORTD &= 0x0F;           
    PORTB &= 0xF0;           

    while (1) {  // Bucle principal del programa

        // Si el botón para subir está presionado
        if (!(PIND & 0x04)) {
            _delay_ms(50);  // Anti-rebote

            // Espera hasta que se suelte el botón
            while (!(PIND & 0x04)); 
            _delay_ms(50);  // Anti-rebote

            // Incrementar solo si no estamos en 99
            if (decenas == 9 && unidades == 9) { // el valor se mantiene en 99 si ya está en ese valor
            } else {
                if (unidades >= 9) {
                    unidades = 0;
                    decenas++;  
                } else {
                    unidades++;  
                }
            }

            if (decenas > 9) {
                decenas = 9;
            }
        }

        // Si el botón para bajar está presionado
        if (!(PIND & 0x08)) {
            _delay_ms(50);  // anti-rebote

            // espera hasta que se suelte el botón
            while (!(PIND & 0x08)); 
            _delay_ms(50);  // annti-rebote

            if (!(unidades == 0 && decenas == 0)) {  // paraevitar decrecer cuando este en 00
                if (unidades == 0) {
                    unidades = 9;  
                    if (decenas > 0) {
                        decenas--;  
                    }
                } else {
                    unidades--;  
                }
            }
        }

         // Botón de resta (PD3)
         if (!(PINB & 0x20)) {
            _delay_ms(50);
            while (!(PINB & 0x20));
            _delay_ms(50);

            // para guardarlos numeros actuales
            guardadou = unidades;
            guardadod = decenas;

            // Resetear display
            unidades = 0;
            decenas = 0;
        }

        PORTD = (PORTD & 0x0F) | (decenas << 4);   
        PORTB = (PORTB & 0xF0) | (unidades & 0x0F); 
    }
}

//display ascendente descendente
/*
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void) {
    DDRD |= 0xF0;            // PD4–PD7 como salida (decenas)
    DDRB |= 0x0F;            // PB0–PB3 como salida (unidades)
    
    DDRD &= ~(0x04);         // botón para subir
    PORTD |= (0x04);         
    DDRD &= ~(0x08);         // botón para bajar
    PORTD |= (0x08);          

    uint8_t unidades = 0;    
    uint8_t decenas = 0;     

    PORTD &= 0x0F;           
    PORTB &= 0xF0;           

    while (1) {  // Bucle principal del programa

        // Si el botón para subir está presionado
        if (!(PIND & 0x04)) {
            _delay_ms(50);  // Anti-rebote

            // Espera hasta que se suelte el botón
            while (!(PIND & 0x04)); 
            _delay_ms(50);  // Anti-rebote

            // Incrementar solo si no estamos en 99
            if (decenas == 9 && unidades == 9) { // el valor se mantiene en 99 si ya está en ese valor
            } else {
                if (unidades >= 9) {
                    unidades = 0;
                    decenas++;  
                } else {
                    unidades++;  
                }
            }

            if (decenas > 9) {
                decenas = 9;
            }
        }

        // Si el botón para bajar está presionado
        if (!(PIND & 0x08)) {
            _delay_ms(50);  // anti-rebote

            // espera hasta que se suelte el botón
            while (!(PIND & 0x08)); 
            _delay_ms(50);  // annti-rebote

            if (!(unidades == 0 && decenas == 0)) {  // paraevitar decrecer cuando este en 00
                if (unidades == 0) {
                    unidades = 9;  
                    if (decenas > 0) {
                        decenas--;  
                    }
                } else {
                    unidades--;  
                }
            }
        }

        PORTD = (PORTD & 0x0F) | (decenas << 4);   
        PORTB = (PORTB & 0xF0) | (unidades & 0x0F); 
    }
}
*/

