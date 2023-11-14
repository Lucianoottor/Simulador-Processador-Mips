#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Instrucoes
#define instrucao_R 0
#define instrucao_J 2
#define instrucao_I 8

// OP-codes
// Instruçoes I
#define ADDI_OPCODE 8
#define SUBI_OPCODE 8
#define ANDI_OPCODE 12
#define ORI_OPCODE 13
#define LW_OPCODE 35
#define SW_OPCODE 43

#define endereco_instrucao_aleatorio 644
#define tam_memoria 1000

int converte_binario(int bin) {
    if (bin == 0) {
        return 0;
    } else {
        return (bin % 2) + 10 * converte_binario(bin / 2);
    }
}

char unidade_controle(int bin){
    if(bin == 0){
        return 'R';
    }
    else if(bin <= 101){
        return 'J';
    }
    else{
        return 'I';
    }
}

int adder(int valor_1, int valor_2){
    return valor_1 + valor_2;
}

int program_counter(int endereço_instrucao, int fim_operacao){
    if(fim_operacao == 0){
        return endereço_instrucao;
    }
    else{
        return adder(endereço_instrucao, 4);
    }
}

int ULA(int op_code, int operando_1, int operando_2){
    switch (op_code) {
        case 0:
            return operando_1 + operando_2;
        case 1: 
            return operando_1 - operando_2;
        case 2:
            return operando_1 * operando_2;
        case 3:
            return operando_1 / operando_2; 
        case 4:
            return operando_1 | operando_2; 
        case 5:
            return operando_1 & operando_2;
        default: 
            printf("Operação inválida!\n");
            return -1;
    }
    
}

int banco_de_registradores(int registrador, int valor, int registradores[]){
    registradores[registrador] = valor;
    return registradores[registrador];
}

int memoria(int posicao, int valor){
    static int memoria_vet[tam_memoria]; 

    if (posicao >= 0 && posicao < tam_memoria) {
        memoria_vet[posicao] = valor;
        return memoria_vet[posicao];
    } else {
        printf("Estouro de memória!\n");
        return -1;
    }
}

int tipo_registrador(int registrador, char tipo_registrador){
        int num_registrador = registrador;
        switch (tipo_registrador) {
        case 't':
            num_registrador += 8;  
            break;
        case 'a':
            num_registrador += 4; 
            break;
        default:
            break;
    }
    return num_registrador;
}

int main(void){

    // Declarando registradores
    int registradores[32];
    for(int i=0;i<32;i++){
        registradores[i] = i+1; // Valor aleatório para testar execução dos códigos
    }

    // Inputs
    system("clear");
    char input_mips[10];
    printf("Insira o comando MIPS: \n");
    scanf("%s", input_mips);
    printf("===========================\n");
    if(strcmp(input_mips, "MOV") == 0){
        printf("oi");
    }

    // Instruções tipo I
    // Função ADDI
    else if(strcmp(input_mips, "ADDI") == 0){

        int RD, RS, imediato;
        char tipo_RD, tipo_RS;
        printf("Insira os registradores de source e destino e o valor do imediato. Ex.: $t0, $t1, 4\n");
        getchar();
        scanf("$%c%d, $%c%d, %d", &tipo_RD, &RD, &tipo_RS, &RS, &imediato);


        // Etapa de fetch
        printf("\n=== Etapa 1 - Fetch ===\n");

        // Memória armazena endereço da instrução
        int endereco = memoria(0, endereco_instrucao_aleatorio);
        // PC busca a instrução na memória
        printf("PC = %d\n", program_counter(endereco,0));

        // Etapa de Decode
        printf("\n=== Etapa 2 - Decode ===\n");
        // Print valores decodificados
        printf("OP-Code | $rs | $rd | Imm\n");
        printf("%06d | %05d | %05d | %016d\n", converte_binario(ADDI_OPCODE), converte_binario(tipo_registrador(RS, tipo_RS)), converte_binario(tipo_registrador(RD, tipo_RD)), converte_binario(imediato));
        printf("\nValores decodificados:\n");
        printf("Instrução tipo %c\n", unidade_controle(converte_binario(ADDI_OPCODE)));
        printf("OP: %d\n", ADDI_OPCODE);
        printf("RS: $%c%d\n", tipo_RS, RS);
        printf("RD: $%c%d\n", tipo_RD, RD);
        printf("Imediato: %d\n", imediato);

        // Execução
        printf("\n=== Etapa 3 - Execução (ADDI) ===\n");
        int resultado = ULA(0, registradores[RS], imediato);
        banco_de_registradores(RD, resultado, registradores);

        // Print de valores
        printf("Valor atual do registrador:\n");
        printf("$%c%d = %d\n", tipo_RD, RD, registradores[RD]);
        

        // Atualizar PC
        endereco = program_counter(endereco_instrucao_aleatorio, 1);
        printf("PC atualizado!\nPC = %d\n", endereco);
    }
    // Funcao SUBI
    else if(strcmp(input_mips, "SUBI") == 0){

        int RD, RS, imediato;
        char tipo_RD, tipo_RS;
        printf("Insira os registradores de source e destino e o valor do imediato. Ex.: $t0, $t1, 4\n");
        getchar();
        scanf("$%c%d, $%c%d, %d", &tipo_RD, &RD, &tipo_RS, &RS, &imediato);


        // Etapa de fetch
        printf("\n=== Etapa 1 - Fetch ===\n");

        // Memória armazena endereço da instrução
        int endereco = memoria(0, endereco_instrucao_aleatorio);
        // PC busca a instrução na memória
        printf("PC = %d\n", program_counter(endereco,0));

        // Etapa de Decode
        printf("\n=== Etapa 2 - Decode ===\n");
        // Print valores decodificados
        printf("OP-Code | $rs | $rd | Imm\n");
        printf("%06d | %05d | %05d | %016d\n", converte_binario(SUBI_OPCODE), converte_binario(tipo_registrador(RS, tipo_RS)), converte_binario(tipo_registrador(RD, tipo_RD)), converte_binario(imediato));
        printf("\nValores decodificados:\n");
        printf("Instrução tipo %c\n", unidade_controle(converte_binario(SUBI_OPCODE)));
        printf("OP: %d\n", SUBI_OPCODE);
        printf("RS: $%c%d\n", tipo_RS, RS);
        printf("RD: $%c%d\n", tipo_RD, RD);
        printf("Imediato: %d\n", imediato);

        // Execução
        printf("\n=== Etapa 3 - Execução (SUBI) ===\n");
        int resultado = ULA(1, registradores[RS], imediato);
        banco_de_registradores(RD, resultado, registradores);

        // Print de valores
        printf("Valor atual do registrador:\n");
        printf("$%c%d = %d\n", tipo_RD, RD, registradores[RD]);
        

        // Atualizar PC
        endereco = program_counter(endereco_instrucao_aleatorio, 1);
        printf("PC atualizado!\nPC = %d\n", endereco);

    }
    // Funcao ORI
    else if(strcmp(input_mips, "ORI") == 0){

    int RD, RS, imediato;
    char tipo_RD, tipo_RS;
    printf("Insira os registradores de source e destino e o valor do imediato. Ex.: $t0, $t1, 4\n");
    getchar();
    scanf("$%c%d, $%c%d, %d", &tipo_RD, &RD, &tipo_RS, &RS, &imediato);
    // Fetch
        printf("\n=== Etapa 1 - Fetch ===\n");

    // Memória armazena endereço da instrução
    int endereco = memoria(0, endereco_instrucao_aleatorio);
    // PC busca a instrução na memória
    printf("PC = %d\n", program_counter(endereco,0));

    // Decode
    printf("\n=== Etapa 2 - Decode ===\n");

    printf("OP-Code | $rs | $rd | Imm\n");
    printf("%06d | %05d | %05d | %016d\n",  converte_binario(ORI_OPCODE),
                                            converte_binario(tipo_registrador(RS, tipo_RS)),
                                            converte_binario(tipo_registrador(RD, tipo_RD)),
                                            converte_binario(imediato));
    printf("\nValores decodificados:\n");
    printf("Instrução tipo %c\n", unidade_controle(converte_binario(ORI_OPCODE)));
    printf("OP: %d\n", ORI_OPCODE);
    printf("RS: $%c%d\n", tipo_RS, RS);
    printf("RD: $%c%d\n", tipo_RD, RD);
    printf("Imediato: %d\n", imediato);

    // Execuçao
    printf("\n=== Etapa 3 - Execução (ORI) ===\n");
    int resultado = ULA(4, registradores[RS], imediato);
    banco_de_registradores(RD, resultado, registradores);

 
    printf("Valor dos registradores:\n");
    printf("$%c%d = %d\n", tipo_RD, RD, registradores[RD]);

    
    endereco = program_counter(endereco_instrucao_aleatorio, 1);
    printf("PC atualizado!\nPC = %d\n", endereco);
}
    // Funcao ANDI
    else if(strcmp(input_mips, "ANDI") == 0){

    int RD, RS, imediato;
    char tipo_RD, tipo_RS;
    printf("Insira os registradores de source e destino e o valor do imediato. Ex.: $t0, $t1, 4\n");
    getchar();
    scanf("$%c%d, $%c%d, %d", &tipo_RD, &RD, &tipo_RS, &RS, &imediato);
    // Fetch
    printf("\n=== Etapa 1 - Fetch ===\n");

    // Memória armazena endereço da instrução
    int endereco = memoria(0, endereco_instrucao_aleatorio);
    // PC busca a instrução na memória
    printf("PC = %d\n", program_counter(endereco,0));

    // Decode
    printf("\n=== Etapa 2 - Decode ===\n");

    printf("OP-Code | $rs | $rd | Imm\n");
    printf("%06d | %05d | %05d | %016d\n",  converte_binario(ANDI_OPCODE),
                                            converte_binario(tipo_registrador(RS, tipo_RS)),
                                            converte_binario(tipo_registrador(RD, tipo_RD)),
                                            converte_binario(imediato));
    printf("\nValores decodificados:\n");
    printf("Instrução tipo %c\n", unidade_controle(converte_binario(ANDI_OPCODE)));
    printf("OP: %d\n", ANDI_OPCODE);
    printf("RS: $%c%d\n", tipo_RS, RS);
    printf("RD: $%c%d\n", tipo_RD, RD);
    printf("Imediato: %d\n", imediato);

    // Execuçao
    printf("\n=== Etapa 3 - Execução (ANDI) ===\n");
    int resultado = ULA(5, registradores[RS], imediato);
    banco_de_registradores(RD, resultado, registradores);

 
    printf("Valor dos registradores:\n");
    printf("$%c%d = %d\n", tipo_RD, RD, registradores[RD]);

    
    endereco = program_counter(endereco_instrucao_aleatorio, 1);
    printf("PC atualizado!\nPC = %d\n", endereco);
}
// Funcao LW
else if(strcmp(input_mips, "LW") == 0){
    int RD, offset, RS;
    char tipo_RD, tipo_RS;
    printf("Insira o registrador de destino, offset e word. Ex.: $t0, 4($t1)\n");
    getchar();
    scanf("$%c%d, %d($%c%d)", &tipo_RD, &RD, &offset, &tipo_RS, &RS);

    // Fetch
    printf("\n=== Etapa 1 - Fetch ===\n");

    // Memória armazena endereço da instrução
    int endereco = memoria(0, endereco_instrucao_aleatorio);
    // PC busca a instrução na memória
    printf("PC = %d\n", program_counter(endereco,0));

    // Decode
    printf("\n=== Etapa 2 - Decode ===\n");

    printf("OP-Code | Base | Destino | offset\n");
    printf("%06d | %05d | %05d | %016d\n",  converte_binario(LW_OPCODE),
                                            converte_binario(tipo_registrador(RS, tipo_RS)),
                                            converte_binario(tipo_registrador(RD, tipo_RD)),
                                            converte_binario(offset));
    printf("\nValores decodificados:\n");
    printf("Instrução tipo %c\n", unidade_controle(converte_binario(LW_OPCODE)));
    printf("OP: %d\n", LW_OPCODE);
    printf("Base: $%c%d\n", tipo_RS, RS);
    printf("Destino: $%c%d\n", tipo_RD, RD);
    printf("Offset: %d\n", offset);

    // Execução
    printf("\n=== Etapa 3 - Execução (LW) ===\n");
    
    // Calcula o endereço de memória
    int endereco_memoria = registradores[RS] + offset;
    
    // Carrega o valor da memória para o registrador RD
    banco_de_registradores(RD, memoria(1, endereco_memoria), registradores);

    // Print de valores
    printf("Valor dos registradores:\n");
    printf("$%c%d = %d\n", tipo_RD, RD, registradores[RD]);
    printf("$%c%d = %d\n", tipo_RS, RS, registradores[RS]);
    
    // Atualizar PC
    endereco = program_counter(endereco_instrucao_aleatorio, 1);
    printf("PC atualizado!\nPC = %d\n", endereco);
}
// Funcao SW
else if(strcmp(input_mips, "SW") == 0){

    int RD, offset, RS;
    char tipo_RD, tipo_RS;
    printf("Insira o registrador de destino, offset e word. Ex.: $t0, 4($t1)\n");
    getchar();
    scanf("$%c%d, %d($%c%d)", &tipo_RD, &RD, &offset, &tipo_RS, &RS);

    // Fetch
    printf("\n=== Etapa 1 - Fetch ===\n");

    // Memória armazena endereço da instrução
    int endereco = memoria(0, endereco_instrucao_aleatorio);
    // PC busca a instrução na memória
    printf("PC = %d\n", program_counter(endereco,0));

    // Decode
    printf("\n=== Etapa 2 - Decode ===\n");

    printf("OP-Code | Base | Destino | offset\n");
    printf("%06d | %05d | %05d | %016d\n",  converte_binario(SW_OPCODE),
                                            converte_binario(tipo_registrador(RS, tipo_RS)),
                                            converte_binario(tipo_registrador(RD, tipo_RD)),
                                            converte_binario(offset));
    printf("\nValores decodificados:\n");
    printf("Instrução tipo %c\n", unidade_controle(converte_binario(SW_OPCODE)));
    printf("OP: %d\n", SW_OPCODE);
    printf("Base: $%c%d\n", tipo_RS, RS);
    printf("Destino: $%c%d\n", tipo_RD, RD);
    printf("Offset: %d\n", offset);

    // Execução
    printf("\n=== Etapa 3 - Execução (SW) ===\n");
    
    // Calcula o endereço de memória
    int endereco_memoria = registradores[RS] + offset;
    
    // Armazena o conteúdo do registrador RD na memória
    memoria(registradores[RD], endereco_memoria);

    // Atualiza o valor dos registradores
    printf("Valor dos registradores atualizado:\n");
    printf("$%c%d = %d\n", tipo_RD, RD, registradores[RD]);
    printf("$%c%d = %d\n", tipo_RS, RS, registradores[RS]);
    printf("Memória = %d\n", memoria(registradores[RD], endereco_memoria));

    // Atualizar PC
    endereco = program_counter(endereco_instrucao_aleatorio, 1);
    printf("PC atualizado!\nPC = %d\n", endereco);
}

    
    // Instruções tipo R
    // Funçao ADD
    else if (strcmp(input_mips, "ADD") == 0) {
        int RD, RS, RT;
        char tipo_RD, tipo_RS, tipo_RT;
        printf("Insira os registradores de destino e source. Ex.: $t0, $t1, $t2\n");
        getchar();
        scanf("$%c%d, $%c%d, $%c%d", &tipo_RD, &RD, &tipo_RS, &RS, &tipo_RT, &RT);

        // Fetch
        printf("\n=== Etapa 1 - Fetch ===\n");

        // Memória armazena endereço da instrução
        int endereco = memoria(0, endereco_instrucao_aleatorio);
        // PC busca a instrução na memória
        printf("PC = %d\n", program_counter(endereco, 0));

        // Decode
        printf("\n=== Etapa 2 - Decode ===\n");

        printf("OP-Code | $rs | $rt | $rd\n");
        printf("%06d | %05d | %05d | %016d\n", converte_binario(instrucao_R),
               converte_binario(tipo_registrador(RS, tipo_RS)),
               converte_binario(tipo_registrador(RT, tipo_RT)),
               converte_binario(tipo_registrador(RD, tipo_RD)));
        printf("\nValores decodificados:\n");
        printf("OP: %d\n", instrucao_R);
        printf("RS: $%c%d\n", tipo_RS, RS);
        printf("RT: $%c%d\n", tipo_RT, RT);
        printf("RD: $%c%d\n", tipo_RD, RD);

        // Execução
        printf("\n=== Etapa 3 - Execução (ADD) ===\n");
        int resultado = ULA(0, registradores[RS], registradores[RT]);
        banco_de_registradores(RD, resultado, registradores);

        // Print de valores
        printf("Valor atual do registrador:\n");
        printf("$%c%d = %d\n", tipo_RD, RD, registradores[RD]);

        // Atualizar PC
        endereco = program_counter(endereco_instrucao_aleatorio, 1);
        printf("PC atualizado!\nPC = %d\n", endereco);
    }
    // Funçao SUB
    else if (strcmp(input_mips, "SUB") == 0) {
        int RD, RS, RT;
        char tipo_RD, tipo_RS, tipo_RT;
        printf("Insira os registradores de destino e source. Ex.: $t0, $t1, $t2\n");
        getchar();
        scanf("$%c%d, $%c%d, $%c%d", &tipo_RD, &RD, &tipo_RS, &RS, &tipo_RT, &RT);

        // Fetch
        printf("\n=== Etapa 1 - Fetch ===\n");

        // Memória armazena endereço da instrução
        int endereco = memoria(0, endereco_instrucao_aleatorio);
        // PC busca a instrução na memória
        printf("PC = %d\n", program_counter(endereco, 0));

        // Decode
        printf("\n=== Etapa 2 - Decode ===\n");

        printf("OP-Code | $rs | $rt | $rd\n");
        printf("%06d | %05d | %05d | %016d\n", converte_binario(instrucao_R),
               converte_binario(tipo_registrador(RS, tipo_RS)),
               converte_binario(tipo_registrador(RT, tipo_RT)),
               converte_binario(tipo_registrador(RD, tipo_RD)));
        printf("\nValores decodificados:\n");
        printf("OP: %d\n", instrucao_R);
        printf("RS: $%c%d\n", tipo_RS, RS);
        printf("RT: $%c%d\n", tipo_RT, RT);
        printf("RD: $%c%d\n", tipo_RD, RD);

        // Execução
        printf("\n=== Etapa 3 - Execução (SUB) ===\n");
        int resultado = ULA(1, registradores[RS], registradores[RT]);
        banco_de_registradores(RD, resultado, registradores);

        // Print de valores
        printf("Valor atual do registrador:\n");
        printf("$%c%d = %d\n", tipo_RD, RD, registradores[RD]);

        // Atualizar PC
        endereco = program_counter(endereco_instrucao_aleatorio, 1);
        printf("PC atualizado!\nPC = %d\n", endereco);
    }
  
}

    
