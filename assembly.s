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

////////////////////////////////////


.global expansion_ondas

.data
TablaExpansiva:
    .word 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80
    .word 0x03, 0x06, 0x0C, 0x18, 0x30, 0x60, 0xC0, 0x81
    // Agregar más datos según sea necesario

.text
expansion_ondas:
    PUSH    {LR}            // Guardar el registro de enlace
    MOV     R0, #1          // Inicializar numLedsEncendidos en R0

loop_while:
    CMP     R0, #9          // Comparar numLedsEncendidos con 9
    BGE     end_function    // Si numLedsEncendidos >= 9, salir del bucle

    MOV     R1, #0          // Inicializar el índice i en R1

loop_for:
    CMP     R1, #8          // Comparar i con 8
    BGE     increment_numLeds // Si i >= 8, incrementar numLedsEncendidos

    SUB     R2, R0, #1      // numLedsEncendidos - 1
    LSL     R2, R2, #3      // Multiplicar por 8 (desplazamiento de 3 bits a la izquierda)
    ADD     R2, R2, R1      // Añadir el índice i
    LDR     R3, =TablaExpansiva
    LDR     R3, [R3, R2, LSL #2] // Cargar TablaExpansiva[numLedsEncendidos - 1][i]
    MOV     R0, R3          // Pasar el valor a R0 (argumento para print_ondas)
    BL      print_ondas     // Llamar a la función print_ondas

    MOV     R0, #100        // Cargar el valor de retardo (100) en R0
    BL      delay           // Llamar a la función delay

    ADD     R1, R1, #1      // Incrementar i
    B       loop_for        // Repetir el bucle for

increment_numLeds:
    ADD     R0, R0, #1      // Incrementar numLedsEncendidos
    B       loop_while      // Repetir el bucle while

end_function:
    POP     {LR}            // Restaurar el registro de enlace
    MOV     PC, LR          // Retornar de la función

print_ondas:
    // Placeholder para la función print_ondas
    MOV     PC, LR          // Retornar de la función

delay:
    // Placeholder para la función delay
    // Usamos R0 como el argumento del retardo
    MOV     PC, LR          // Retornar de la función