

#include <stdio.h>
#include <conio.h>
#include <unistd.h>
#include <EasyPIO.h>

int menu(void) ;
void autof(void) ;
void dips_binary(int) ;
void not_yet(void) ;
void not_yet(void) ;
void choquef(void) ;

void main (void){
    int choice ;

    for( ; ; ){
        choice = menu() ;
        switch(choice){
            case 1: 
               autof() ;
            break;
            case 2: 
               choque() ;
            break;
            case 3: 
               not_yet() ;
            break;
            case 4: 
               not_yet() ;
            break;
            case 5: 
               return ;
            break;
        }
    }
}

int menu(void){
    int opc ;
    do{
        printf("\nMENU\n");
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

void Autofantastico(){
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
            delay(tiempo);
            if(press_key() == 0){
                echo();
                endwin();
                return;
            } 
            
        };
    };
};

void choquef(void) {
    printf("\nMostrando choque:\n");
    char a;
    unsigned char tabla[7] = {0x81, 0x42, 0x24, 0x18, 0x18, 0x24, 0x81}
    for(int i=0; i<7; i++){
        dips_binary(tabla[i]) ;
        leds(-tabla[i]);
        delayMillis(300) ;
    }
}

void disp_binary(int i){
    int t ;
    for(t=128, t>0; t=t/2){
        if(i&t) printf ("*") //chequear si es *
    } else printf("_") ;
    printf("\n") ;
}