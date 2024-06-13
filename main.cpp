#include <stdio.h>
#include <conio.h>
#include <unistd.h>
#include "EasyPIO.h"
// #include <unistd.h> // Para usar la función usleep (en sistemas Unix/Linux)

char password[5];
char letra;
    
// ////Valor global del delay
// int tiempo = 12;


////////////////////tablas de datos //////////////////////////////////
//unsigned char TablaAf []= {0x01, 0x02, 0x04,0x08,0x10, 0x20, 0x40, 0x80};
unsigned char TablaCh []= {0x81, 0x42, 0x24, 0x18, 0x18, 0x24, 0x42, 0x81};
unsigned char TablaCa []= {0x01, 0x01 ,0x03, 0x03, 0x05, 0x05, 0x09, 0x09, 0x11,0x12,0x24,0x28,0x50,0x60,0x40,0x80};
unsigned char TP[] = {0x88, 0x48, 0x28, 0x18, 0x14, 0x12, 0x12, 0x14, 0x18,0x28,0x48,0x48, 0x28,0x18,0x14,0x14,0x18,0x28,0x28,0x18,0x18,0x18};

int menu(void) ;
int ingreso() ;
int presskey() ;
void delay(int) ;
void autof() ;
void ChoqueT(void) ;
void dips_binary(int) ;
void simulador_balizas(void) ;
void expansion_ondas(void) ;



int menu(void){
    int opc ;
    do{
        printf("\n--- MENU ---\n");
        printf("1) autof\n") ;
        printf("2) choque\n");
        printf("3) opcion 3\n");
        printf("4) opcion 4\n");
        printf("5) salir\n");
        printf("Elija su opción:\n");
        scanf("%d", &opc);
    } while (opc<1 || opc>5);
    return opc ;
}

/////////////////Comprobar Contraseña///////////////////////////
int ingreso(){	
    initscr();
    noecho();
    printw("Ingrese clave: ");
    for(int i=0; i<3;i++){
        char c;
        char temp[6];
        for(int i = 0; i < 6; i++){
            c = getch();
            temp[i] = c;
            printw("*");
        }
        printw("\r                      ");
        fflush(stdout);
    if(strcmp(temp, password)==0){
        printw("\r");
        echo();
        endwin();
        return 1; 
    }
    printw("\rPrueba de nuevo: ");
   }
    printw("\r                         ");
    printw("\r");
    fflush(stdout);
    echo();
    endwin();
    return 0;
}

int press_key() {
    cbreak();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    switch (getch()) {
        case 'a':
            return 0;
        case KEY_UP:
            if(tiempo > 0) tiempo--;
            break;
        case KEY_DOWN:
            if(tiempo < 30) tiempo++;
            break;
    }
    return 1;
    nocbreak();
}


void disp_binary(int i){
    int t ;
    for(t=128, t>0; t=t/2){
        if(i&t) printf ("*") //chequear si es *
    } else printf("_") ;
    printf("\n") ;
}

///////////////// Delay de todas las funciones 
void delay(int a){
  for(int j=0;j<a;j++)
  {
    unsigned int i = 0x2fffff; //raspberry 0x3fffff
    while(a)a--;
  };
};


////// simulaciones led 
void autof(){
  while(1){
        initscr();
        noecho();
        for(int i = 1; i<=128; i=i*2) 
        {
            output(i);
            delay(tiempo);
            if(press_key() == 0){
                echo();
                endwin();
                return;
            } 
        };
        for(int i = 64; i>0 ; i=i/2){ 
            output(i);
            delay(12);
            if(press_key() == 0){
                echo();
                endwin();
                return;
            } 
            
        };
    };
};


//   ------ Autofantastico Algoritmo
void AutofantasticoA(){
  while(1){
        initscr();
        noecho();
        for(int i = 1; i<=128; i=i*2) 
        {
            output(i);
            delay(20);
            if(press_key() == 0){
                echo();
                endwin();
                return;
            } 
        };
        for(int i = 64; i>0 ; i=i/2){ 
            output(i);
            delay(20);
            if(press_key() == 0){
                echo();
                endwin();
                return;
            } 
            
        };
    };
};


//////////// Algoritmo choque hecho por tabla 

void ChoqueT()
{
    initscr();
    noecho();
    while(1){
        for (int i = 0; i<8; i++ )
        {
            int valor = TablaCh[i];
            output(valor);
            delay(tiempo);
            if(press_key() == 0){
                echo();
                endwin();
                return;
            } 
        };
    };
};

/*

//Funcion Carrera hecha con tabla 
void choque__f()
{
    initscr();
    noecho();
    while(1){
        for (int i = 0; i<16; i++ )
        {
            int valor = TablaCa[i];
            output(valor);
            delay(15);
            if(press_key() == 0){
                echo();
                endwin();
                return;
            } 
        };
    };
};

*/

/////// balizas algoritmo

// #define DELAY 500000 // 500000 microsegundos = 0.5 segundos

// ------------------------------------

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


void simulador_balizas(int num_cycles) {
    int balizas[8] = {0, 0, 0, 0, 0, 0, 0, 0}; // Inicializar las luces de emergencia apagadas

    for (int cycle = 0; cycle < num_cycles; cycle++) {
        // Alternar luces
        // Encender luces
        balizas[0] = 1; 
        balizas[1] = 1;
        balizas[4] = 1; 
        balizas[5] = 1; 
        // Apagar luces 
        balizas[2] = 0; 
        balizas[3] = 0; 
        balizas[6] = 0; 
        balizas[7] = 0; 

        print_balizas(balizas);

        delay(10) ; // Esperar el retardo

        balizas[0] = 0; 
        balizas[1] = 0;
        balizas[4] = 0; 
        balizas[5] = 0; 
    
        balizas[2] = 1; 
        balizas[3] = 1; 
        balizas[6] = 1; 
        balizas[7] = 1; 

        print_balizas(balizas);
        delay(10); // Esperar el retardo
    }
}


//// expansion de ondas por tabla


void expansion_ondas(){

}

int main() {

    /*
    int num_cycles = 8; // Número de ciclos a ejecutar

    simulador_balizas(num_cycles);
    */

    pioInit();
    strcpy(password, "123456");


    int num_cycles = 10; // Número de ciclos a ejecutar
    int choice;
    int authenticated = 0;

    while(choice != 5){
        choice = menu() ;
        switch(choice){
            case 1: 
               autof() ;
            break;
            case 2: 
               ChoqueT() ;
            break;
            case 3: 
               simulador_balizas() ;
            break;
            case 4: 
               expansion_ondas() ;
            break;
            case 5: 
               return ;
            break;
        }
    }

    while (!authenticated) {
        authenticated = ingreso();
        if (!authenticated) {
            printf("Password no válida. Intentos restantes: %d\n", MAX_ATTEMPTS - authenticated);
        }
    }

    return 0;
}