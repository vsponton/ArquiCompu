#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ncurses.h>
#include "EasyPIO.h"  // Asegúrate de tener esta librería para controlar los GPIO

char password[6];
char letra;

// Tabla de datos
unsigned char TablaCh[] = {0x81, 0x42, 0x24, 0x18, 0x18, 0x24, 0x42, 0x81};

// Tabla para patrones de expansión de onda
unsigned char TablaExpansiva[8][8] = {
    {0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},  // 1 LED
    {0x03, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},  // 2 LEDs
    {0x07, 0x06, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00},  // 3 LEDs
    {0x0F, 0x0E, 0x0C, 0x08, 0x00, 0x00, 0x00, 0x00},  // 4 LEDs
    {0x1F, 0x1E, 0x1C, 0x18, 0x10, 0x00, 0x00, 0x00},  // 5 LEDs
    {0x3F, 0x3E, 0x3C, 0x38, 0x30, 0x20, 0x00, 0x00},  // 6 LEDs
    {0x7F, 0x7E, 0x7C, 0x78, 0x70, 0x60, 0x40, 0x00},  // 7 LEDs
    {0xFF, 0xFE, 0xFC, 0xF8, 0xF0, 0xE0, 0xC0, 0x80}   // 8 LEDs
};

// Prototipos de funciones
int menu(void);
int ingreso(void);
int presskey(void);
void delay(int);
void disp_binary(int);
void autof(void);
void ChoqueT(void);
void simulador_balizas(void);
void expansion_ondas(void);

// Variable global para controlar la velocidad
int speed = 10;

int menu(void) {
    int opc = 0;
    while (opc < 1 || opc > 5) {
        printf("\n--- MENU ---\n");
        printf("1) Auto fantástico\n");
        printf("2) Choque\n");
        printf("3) Simulador de balizas\n");
        printf("4) Expansión de ondas\n");
        printf("5) Salir\n");
        printf("Elija su opción: ");
        scanf("%d", &opc);
        if (opc < 1 || opc > 5) {
            printf("!!!Opcion incorrecta!!!");
        }
    }
    return opc;
}

int ingreso(void) {
    
    printf("Ingrese clave: ");
    int i = 0;
    
    while (i < 4 && (letra = getchar()) != '\n' ) {
        password[i++]  = letra ;
        char temp[6] = {0};
            printf("*");
    }
    password[i] = '\0';
    printf("\n") ;
    
    return strcmp(password,"12345") == 0 ;
}

int presskey(void) {

    char ch = getchar();
    if (ch == 'a') {
        return 0;
    } else if (ch == 'u') {
        speed = (speed > 1) ? speed - 1 : speed; // Aumentar velocidad
    } else if (ch == 'd') {
        speed++; // Disminuir velocidad
    }
    getchar();
    return 1;
}

void delay(int a) {
    for (int j = 0; j < a; j++) {
        unsigned int i = 0x2fffff; // Ajusta según sea necesario para el tiempo de retardo deseado
        while (i) i--;
    }
}

void disp_binary(int i) {
    for (int t = 128; t > 0; t = t / 2) {
        if (i & t) {
            printf("*");
        } else {
            printf("_");
        }
    }
    printf("\n");
}

void autof(void) {
    while (1) {
        
        for (int i = 1; i <= 128; i = i * 2) {
            //output(i);
            delay(speed);
             printf("Light pattern: %d\n", i);
            if (presskey() == 0) {
                return;
            }
        }
        for (int i = 64; i > 0; i = i / 2) {
            //output(i);
            
            delay(speed);
            printf("Light pattern: %d\n", i);
            if (presskey() == 0) {
                return;
            }
        }
    }
}

void ChoqueT(void) {
   
    while (1) {
        for (int i = 0; i < 8; i++) {
            int valor = TablaCh[i];
            //output(valor);
            printf("Light pattern: %d\n", valor);
            delay(speed);
            if (presskey() == 0) {
                return;
            }
        }
    }
}

void print_balizas(int balizas[]) {
    for (int i = 0; i < 8; i++) {
        if (balizas[i]) {
            printf("● ");
        } else {
            printf("○ ");
        }
    }
    printf("\n");
}

void simulador_balizas(void) {
    int num_cycles = 10;  // Número de ciclos a ejecutar
    int balizas[8] = {0, 0, 0, 0, 0, 0, 0, 0}; // Inicializar las luces de emergencia apagadas

    for (int cycle = 0; cycle < num_cycles; cycle++) {
        // Encender luces
        balizas[0] = 1; 
        balizas[1] = 1;
        balizas[4] = 1; 
        balizas[5] = 1; 
        balizas[2] = 0; 
        balizas[3] = 0; 
        balizas[6] = 0; 
        balizas[7] = 0; 

        print_balizas(balizas);
        delay(speed); // Esperar el retardo

        // Alternar a otro estado
        balizas[0] = 0; 
        balizas[1] = 0;
        balizas[4] = 0; 
        balizas[5] = 0; 
        balizas[2] = 1; 
        balizas[3] = 1; 
        balizas[6] = 1; 
        balizas[7] = 1; 

        print_balizas(balizas);
        delay(speed); // Esperar el retardo
    }
}

void print_ondas(unsigned char onda) {
    for (int i = 0; i < 8; i++) {
        if (onda & (1 << i)) {
            printf("● ");
        } else {
            printf("○ ");
        }
    }
    printf("\n");
}

void expansion_ondas(void) {
    int numLedsEncendidos = 1;
    while (numLedsEncendidos <= 8) {
        for (int i = 0; i < 8; i++) {
            print_ondas(TablaExpansiva[numLedsEncendidos - 1][i]);
            delay(speed);  // Ajusta el tiempo de acuerdo a tus necesidades
        }
        numLedsEncendidos++;
    }
}

int main(void) {
    pioInit();
    strcpy(password, "12345");

    int opc = 0;

    while (opc != 5) {
        opc = menu(); // Agregado para actualizar opc desde el menú
        if (ingreso()) {
            switch (opc) {
                case 1:
                    autof();
                    break;
                case 2:
                    ChoqueT();
                    break;
                case 3:
                    simulador_balizas();
                    break;
                case 4:
                    expansion_ondas();
                    break;
                case 5:
                    return 0;
            }
        } else {
            printf("Password no válida. Aborting...\n");
            return 1;
        }
    }
    return 0;
}
