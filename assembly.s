
////////// BALIZAS

.global simulador_balizas

.equ NUM_CYCLES, 10

.text
simulador_balizas:
    PUSH    {LR}            // Guardar el registro de enlace
    MOV     R0, #NUM_CYCLES // Cargar el número de ciclos en R0
    MOV     R1, #0          // Inicializar el contador de ciclos en R1

init_balizas:
    MOV     R2, #0          // Inicializar el array de balizas en R2
    PUSH    {R2, R2, R2, R2} // Poner 4 ceros en la pila (R2 contiene 0)
    PUSH    {R2, R2, R2, R2} // Poner otros 4 ceros en la pila (R2 contiene 0)

loop_start:
    // Estado 1 de balizas: 0b00110011 (0x33)
    LDR     R2, =0x33
    STR     R2, [SP]
    BL      print_balizas   // Llamar a la función print_balizas
    BL      delay           // Llamar a la función delay

    // Estado 2 de balizas: 0b11001100 (0xCC)
    LDR     R2, =0xCC
    STR     R2, [SP]
    BL      print_balizas   // Llamar a la función print_balizas
    BL      delay           // Llamar a la función delay

    ADD     R1, R1, #1      // Incrementar el contador de ciclos
    CMP     R1, R0          // Comparar el contador de ciclos con NUM_CYCLES
    BLT     loop_start      // Si el contador de ciclos < NUM_CYCLES, repetir el bucle

    ADD     SP, SP, #32     // Limpiar la pila
    POP     {LR}            // Restaurar el registro de enlace
    MOV     PC, LR          // Retornar de la función

print_balizas:
    // Placeholder para la función print_balizas
    MOV     PC, LR          // Retornar de la función

delay:
    // Placeholder para la función delay
    MOV     R0, #10         // Cargar el valor de retardo (10) en R0
    MOV     PC, LR          // Retornar de la función