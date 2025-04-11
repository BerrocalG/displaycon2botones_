//codigoprueba tareaq
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

    DDRB &= ~(0x10);         // botón para restar
    PORTB |= (0x10);         
    DDRB &= ~(0x20);         // botón para sumar
    PORTB |= (0x20); 
    DDRD &= ~(0x02);         // botón para ENTER
    PORTD |= (0x02);        

    uint8_t unidades = 0;    
    uint8_t decenas = 0;     
    uint8_t guardadod = 0;    
    uint8_t guardadou =0 ;
    uint8_t mate=0;

    char finalu=0;
    char finald=0;
    char resultadou=0;
    char resultadod=0;


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
            mate=1;
        }
        //para suma

        if (!(PINB & 0x10)) {
            _delay_ms(50);
            while (!(PINB & 0x10));
            _delay_ms(50);

            // para guardarlos numeros actuales
            guardadou = unidades;
            guardadod = decenas;

            // Resetear display
            unidades = 0;
            decenas = 0;
            mate=2; 
        }

        if (!(PIND & 0x02)) { //ENTER
            _delay_ms(50);

            while (!(PIND & 0x02));
            _delay_ms(50);

            // para guardarlos numeros actuales
            unidades=0;
            decenas=0;

    

          if (!(PINB & 0x10)&& (mate==1)) { // resta

            finalu= unidades;
            finald= decenas;
            resultadou= (guardadou-finalu);
            resultadod= (guardadod-finald);

            }

         if (!(PINB & 0x20)&& (mate==2)) { // sumar

            finalu= unidades;
            finald= decenas;
            resultadou= (guardadou+finalu);
            resultadod= (guardadod+finald);
            
            }

            if (resultadou<0){
            resultadou=0;
            }
            if (resultadou>9){
            resultadou=9;
            }
             if (resultadod<0){
            resultadod=0;
            }
             if (resultadod>9){
            resultadod=9;
             }
        
         unidades=resultadou;
         decenas=resultadod;
         mate=0;
        }

        PORTD = (PORTD & 0x0F) | (decenas << 4);   
        PORTB = (PORTB & 0xF0) | (unidades & 0x0F); 
    }
}






/*
//codigo del motor
#define F_CPU 16000000UL  
#include <avr/io.h>  
#include <util/delay.h> 

int main(void) {
    DDRD |= 0xC0; // PD6 y PD7 salida (motor 1)
    PORTD &= ~0xC0;

    DDRD |= 0x0C; // PD2 y PD3 salida (motor 2)
    PORTD &= ~0x0C;

    DDRB &= ~0x02; // PB1 como entrada (botón 1)
    PORTB |= 0x02; // pull-up para botón 1

    DDRB &= ~0x01; // PB0 como entrada (botón 2)
    PORTB |= 0x01; // pull-up para botón 2

    DDRD &= ~0x20; // PD5 como entrada (botón 3)
    PORTD |= 0x20; // pull-up para botón 3

    char A = 0;
    char B = 0;
    char C = 0;
    char D = 0;
    char E = 0;
    char F = 0;

    while (1) {
        // Primera condición gira motor 1 apaga motor 2 botnon2+boton3
        if (!(PINB & 0x02) && !(PINB & 0x01)) {
            _delay_ms(100);
            if (A == 0) {
                PORTD &= ~0x0C;     // Apaga motor 2
                PORTD &= ~0xC0;     // Apaga motor 1
                _delay_ms(100);
                PORTD |= 0x80;      // Enciende PD6 (motor 1)
                PORTD &= ~0x40;     // Apaga PD7
                A = 1;
                B = 0;              // corta la otra condición
                C = 0;
                D = 0;
                E = 0;
                F = 0;

            }
        }
        else{ //si solo presiono el b2  se ejecuta lo anterior que va actvar ambos motoresm1 isquierda m2 derecha
            if (!(PINB & 0x02)) {
                _delay_ms(100);
                if (E == 0) {
    
                PORTD&=~(0X0C); 
                PORTD&=~(0XC0);
                _delay_ms(100); //abra un delay
                PORTD|=(0X40); //
                PORTD|=(0X08);//el pin4 en 1
                PORTD &= ~0x80;
                PORTD &= ~0x04;
    
                    B = 0;
                    C = 0;
                    D = 0;
                    A = 0;
                    E = 1;
                    F = 0;

    
                }
        }

        // Segunda condición  gira motor 2 apaga motor 1 boton1+boton2
        if (!(PINB & 0x01) && !(PIND & 0x20)) {
            _delay_ms(100);
            if (B == 0) {
                PORTD &= ~0x0C;     // Apaga motor 2
                PORTD &= ~0xC0;     // Apaga motor 1
                _delay_ms(100);
                PORTD |= 0x04;      // Enciende PD2 (motor 2)
                PORTD &= ~0x08;     // apaga PD3
                B = 1;
                C = 0;
                D = 0;
                E = 0;
                F = 0;
                A = 0;              // corta la otra condición
            }
        }
        
        else{ //si solo presiono el b1  van los dos hacia adedlante
            if (!(PINB & 0x01)) {
                _delay_ms(100);

                if (F == 0) {
    
                PORTD&=~(0X0C); 
                PORTD&=~(0XC0);
                _delay_ms(100); //abra un delay
                PORTD|=(0X08); // ambos
                PORTD|=(0X80);//

    
                    B = 0;
                    C = 0;
                    D = 0;
                    A = 0;
                    E = 0;
                    F = 1;
                }
            }
        }
    
        //giro corto 1 m1 derecha m2 izquierda
        if (!(PINB & 0x02) && !(PIND & 0x20)) {
            _delay_ms(100);
            if (D == 0) {
                PORTD&=~(0X0C); 
                PORTD&=~(0XC0);
                _delay_ms(100); //abra un delay
                PORTD|=(0X80); //
                PORTD|=(0X04);//el pin4 en 1
                
                B = 0;
                C = 0;
                D = 1;
                A = 0; 
                E = 0;
                F = 0;

            }
        } 
        else{ //APAGADO AMBOS MOTORES
            if (!(PIND & 0x20)) {
                _delay_ms(100);

                if (C == 0) {
    
                PORTD&=~(0X0C); 
                PORTD&=~(0XC0);
                _delay_ms(100); //abra un delay
                PORTD&=~(0X0C); 
                PORTD&=~(0XC0);

    
                    B = 0;
                    C = 1;
                    D = 0;
                    A = 0;
                    E = 0;
                    F = 0;
                }
            }
        }
          

    }
}
}

*/


/*

//display ascendente descendente

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