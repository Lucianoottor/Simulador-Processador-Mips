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
#define ANDI_OPCODE 12
#define ORI_OPCODE 13
#define XORI_OPCODE 14
#define LW_OPCODE 35
#define SW_OPCODE 43

// Instrucoes R: OP-Code, shamt e funct
#define ADD_Funct 32
#define SUB_Funct 34
#define AND_Funct 36
#define OR_Funct 37
#define XOR_Funct 38


// Memoria
#define endereco_instrucao_aleatorio 0
#define tam_memoria 10000

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
        case 8:
        case 32:
        case 35:
            return operando_1 + operando_2;
        case 34: 
            return operando_1 - operando_2;
        case 2:
            return operando_1 * operando_2;
        case 3:
            return operando_1 / operando_2; 
        case 13:
        case 37:
            return operando_1 | operando_2; 
        case 12:
        case 36:
            return operando_1 & operando_2;
        case 14:
        case 38:
            return operando_1 ^ operando_2;
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
        switch (tipo_registrador)
        {
        case 's':
            num_registrador +=16;
            break;
        case 't':
            if(registrador == 8){
                num_registrador = 24;
            }
            else if(registrador == 9){
                num_registrador = 25;
            }
            else{
            num_registrador += 8;  
            }
        break;
        case 'a':
            num_registrador += 4; 
        break;
        case 'v':
            num_registrador += 2;
        break;
        case 'z':
                num_registrador = 0;
        break;
    }
    return num_registrador;
}

void executarInstrucaoR(int opcode, int shamt, int funct, char *input_mips, int *registradores){
    int RD, RS, RT;
    char tipo_RD, tipo_RS, tipo_RT;
    int endereco, resultado;

    switch (funct)
    {
    case ADD_Funct:
    case AND_Funct:
    case OR_Funct:
    case XOR_Funct:
    case SUB_Funct:
        printf("Insira os registradores de destino e source. Ex.: $t0, $t1, $t2\n");
        getchar();
        scanf("$%c%d, $%c%d, $%c%d", &tipo_RD, &RD, &tipo_RS, &RS, &tipo_RT, &RT);

        // Fetch
        printf("\n=== Etapa 1 - Fetch ===\n");

        // Memória armazena endereço da instrução
        endereco = memoria(0, endereco_instrucao_aleatorio);
        // PC busca a instrução na memória
        printf("PC = %d\n", program_counter(endereco, 0));

        // Decode
        printf("\nOP-Code | $rs | $rt | $rd | shamt | funct\n");
        printf("%06d | %05d | %05d | %05d | %05d | %06d\n",   converte_binario(opcode),
                                                            converte_binario(tipo_registrador(RS, tipo_RS)),
                                                            converte_binario(tipo_registrador(RT, tipo_RT)),
                                                            converte_binario(tipo_registrador(RD, tipo_RD)),
                                                            converte_binario(shamt),
                                                            converte_binario(funct)); 
        printf("\nValores decodificados:\n");
        printf("OP: %d\n", instrucao_R);
        printf("RS: $%c%d = %d\n", tipo_RS, RS, tipo_registrador(RS, tipo_RS));
        printf("RT: $%c%d = %d\n", tipo_RT, RT, tipo_registrador(RT, tipo_RT));
        printf("RD: $%c%d = %d\n", tipo_RD, RD, tipo_registrador(RD, tipo_RD));
        printf("Shamt: 0\n");
        printf("Funct: %d\n", ADD_Funct);

        // Execução
        printf("\n=== Etapa 3 - Execução (%s) ===\n", input_mips);
        resultado = ULA(funct, registradores[tipo_registrador(RS, tipo_RS)], registradores[tipo_registrador(RT, tipo_RT)]);
        banco_de_registradores(tipo_registrador(RD, tipo_RD), resultado, registradores);

        // Print de valores
        printf("Valor atual do registrador:\n");
        printf("$%c%d = %d\n", tipo_RD, RD, registradores[tipo_registrador(RD, tipo_RD)]);

        // Atualizar PC
        endereco = program_counter(endereco_instrucao_aleatorio, 1);
        printf("PC atualizado!\nPC = %d\n", endereco);
    }
}
void executarInstrucaoI(int opcode, char *input_mips, int *registradores){
    int RD, RS, imediato, offset;
    int endereco, resultado;
    char tipo_RD, tipo_RS;
    switch (opcode)
    {

    case ADDI_OPCODE:
    case ORI_OPCODE:
    case XORI_OPCODE:
    case ANDI_OPCODE:
    
    printf("Insira os registradores de source e destino e o valor do imediato. Ex.: $t0, $t1, 4\n");
    getchar();
    scanf("$%c%d, $%c%d, %d", &tipo_RD, &RD, &tipo_RS, &RS, &imediato);


    // Etapa de fetch
    printf("\n=== Etapa 1 - Fetch ===\n");
    // Memória armazena endereço da instrução
    endereco = memoria(endereco_instrucao_aleatorio, endereco_instrucao_aleatorio);
    // PC busca a instrução na memória
    printf("PC = %d\n", program_counter(endereco,0));

    // Etapa de Decode
    printf("\n=== Etapa 2 - Decode ===\n");
    // Print valores decodificados
    printf("\nOP-Code | $rs | $rd | Imm\n");
    printf("%06d | %05d | %05d | %016d\n", converte_binario(opcode), converte_binario(tipo_registrador(RS, tipo_RS)), converte_binario(tipo_registrador(RD, tipo_RD)), converte_binario(imediato));
    printf("\nValores decodificados:\n");
    printf("Instrução tipo %c\n", unidade_controle(converte_binario(opcode)));
    printf("OP: %d\n", opcode);
    printf("RS: $%c%d = %d\n", tipo_RS, RS, registradores[tipo_registrador(RS, tipo_RS)]);
    printf("RD: $%c%d = %d\n", tipo_RD, RD, registradores[tipo_registrador(RD, tipo_RD)]);
    printf("Imediato: %d\n", imediato);

    // Execução
    printf("\n=== Etapa 3 - Execução (%s) ===\n", input_mips);
    resultado = ULA(opcode, registradores[tipo_registrador(RS, tipo_RS)], imediato);

    // Print de valores
    printf("\n=== Etapa 4 - Write Back ===\n");
    banco_de_registradores(tipo_registrador(RD, tipo_RD), resultado, registradores);
    printf("Valor atual do registrador:\n");
    printf("$%c%d = %d\n", tipo_RD, RD, registradores[tipo_registrador(RD, tipo_RD)]);

    printf("\n=== Atualização do Program - Counter ===\n");
    // Atualizar PC
    endereco = program_counter(endereco_instrucao_aleatorio, 1);
    printf("PC atualizado!\nPC = %d\n", endereco);
    break;

    case LW_OPCODE:
    
        printf("Insira o registrador de destino, offset e word. Ex.: $t0, 4($t1)\n");
        getchar();
        scanf("$%c%d, %d($%c%d)", &tipo_RD, &RD, &offset, &tipo_RS, &RS);

        // Fetch
        printf("\n=== Etapa 1 - Fetch ===\n");

        // Memória armazena endereço da instrução
        endereco = memoria(0, endereco_instrucao_aleatorio);
        // PC busca a instrução na memória
        printf("PC = %d\n", program_counter(endereco,0));

        // Decode
        printf("\n=== Etapa 2 - Decode ===\n");

        printf("\nOP-Code | Base | Destino | offset\n");
        printf("%06d | %05d | %05d | %016d\n",  converte_binario(opcode),
                                                converte_binario(tipo_registrador(RS, tipo_RS)),
                                                converte_binario(tipo_registrador(RD, tipo_RD)),
                                                converte_binario(offset));
        printf("\nValores decodificados:\n");
        printf("Instrução tipo %c\n", unidade_controle(converte_binario(opcode)));
        printf("OP: %d\n", opcode);
        printf("Base: $%c%d\n", tipo_RS, RS);
        printf("Destino: $%c%d\n", tipo_RD, RD);
        printf("Offset: %d\n", offset);

        // Execução
        printf("\n=== Etapa 3 - Execução (%s) ===\n", input_mips);
        
        // Calcula o endereço de memória
        endereco = registradores[RS] + offset;
        
        // Armazena o conteúdo do registrador RD na memória
        memoria(registradores[RD], endereco);

        // Atualiza o valor dos registradores
        printf("Valor dos registradores atualizado:\n");
        printf("$%c%d = %d\n", tipo_RD, RD, registradores[RD]);
        printf("$%c%d = %d\n", tipo_RS, RS, registradores[RS]);
        printf("Memória = %d\n", memoria(registradores[RD], endereco));

        // Atualizar PC
        endereco = program_counter(endereco_instrucao_aleatorio, 1);
        printf("PC atualizado!\nPC = %d\n", endereco);
    break;

    case SW_OPCODE:
        printf("Insira o registrador de destino, offset e word. Ex.: $t0, 4($t1)\n");
    getchar();
    scanf("$%c%d, %d($%c%d)", &tipo_RD, &RD, &offset, &tipo_RS, &RS);

    // Fetch
    printf("\n=== Etapa 1 - Fetch ===\n");

    // Memória armazena endereço da instrução
    endereco = memoria(0, endereco_instrucao_aleatorio);
    // PC busca a instrução na memória
    printf("PC = %d\n", program_counter(endereco,0));

    // Decode
    printf("\n=== Etapa 2 - Decode ===\n");

    printf("\nOP-Code | Base | Destino | offset\n");
    printf("%06d | %05d | %05d | %016d\n",  converte_binario(opcode),
                                            converte_binario(tipo_registrador(RS, tipo_RS)),
                                            converte_binario(tipo_registrador(RD, tipo_RD)),
                                            converte_binario(offset));
    printf("\nValores decodificados:\n");
    printf("Instrução tipo %c\n", unidade_controle(converte_binario(SW_OPCODE)));
    printf("OP: %d\n", opcode);
    printf("Base: $%c%d\n", tipo_RS, RS);
    printf("Destino: $%c%d\n", tipo_RD, RD);
    printf("Offset: %d\n", offset);

    // Execução
    printf("\n=== Etapa 3 - Execução (%s) ===\n", input_mips);
    
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
    break;
    }
}

int main(void){

    // Declarando registradores
    int registradores[32];
    for(int i=0;i<32;i++){
        registradores[i] = i; // Valor aleatório para testar execução dos códigos
    }
    registradores[0] = 0;

    // Inputs
    system("clear");
    char input_mips[10];
    printf("Insira o comando MIPS: \n");
    scanf("%s", input_mips);
    printf("===========================\n");

    // Instruções tipo I
    // Função ADDI
    if(strcmp(input_mips, "ADDI") == 0){
        executarInstrucaoI(ADDI_OPCODE, input_mips, registradores);
    }
    // Funcao ORI
    else if(strcmp(input_mips, "ORI") == 0){
        executarInstrucaoI(ORI_OPCODE, input_mips, registradores);
    }
    // Funcao XORI
    else if(strcmp(input_mips, "XORI") == 0){
        executarInstrucaoI(XORI_OPCODE, input_mips, registradores);
    }
    // Funcao ANDI
    else if(strcmp(input_mips, "ANDI") == 0){
        executarInstrucaoI(ANDI_OPCODE, input_mips, registradores);
    }
    // Funcao LW
    else if(strcmp(input_mips, "LW") == 0){
        executarInstrucaoI(LW_OPCODE, input_mips, registradores);
    }
    // Funcao SW
    else if(strcmp(input_mips, "SW") == 0){
        executarInstrucaoI(SW_OPCODE, input_mips, registradores);
}

    
    // Instruções tipo R
    // Funçao ADD
    else if (strcmp(input_mips, "ADD") == 0) {
        executarInstrucaoR(instrucao_R, 0, ADD_Funct, input_mips, registradores);
    }
    // Funçao SUB
    else if (strcmp(input_mips, "SUB") == 0) {
        executarInstrucaoR(instrucao_R, 0, SUB_Funct, input_mips, registradores);
    }
    // Funçao AND
    else if(strcmp(input_mips, "AND") == 0){
        executarInstrucaoR(instrucao_R, 0, AND_Funct, input_mips, registradores);
    }
    // Funçao OR
    else if (strcmp(input_mips, "OR") == 0) {
        executarInstrucaoR(instrucao_R, 0, OR_Funct, input_mips, registradores);
    }
    // Função XOR
    else if (strcmp(input_mips, "XOR") == 0) {
        executarInstrucaoR(instrucao_R, 0, XOR_Funct, input_mips, registradores);
    }
    // Função J
    else if(strcmp(input_mips, "J") == 0){
        int salto;
        printf("Insira o valor de salto: \n");
        scanf("%d", &salto);

         // Fetch
        printf("\n=== Etapa 1 - Fetch ===\n");
        // Memória armazena endereço da instrução
        int endereco = memoria(0, endereco_instrucao_aleatorio);
        // PC busca a instrução na memória
        printf("PC = %d\n", program_counter(endereco, 0));

        // Decode
        printf("\n=== Etapa 2 - Decode ===\n");
        printf("OP-Code | Endereço\n");
        printf("%06d | %026d\n", converte_binario(instrucao_J), converte_binario(endereco));
        printf("OP-Code: %d\n", instrucao_J);
        printf("Endereço: %d\n", endereco);

        printf("\n=== Etapa 3 - Execução (J) ===\n");
        endereco = memoria(salto, salto);
        printf("Program-Counter: %d", program_counter(endereco,0));
    }
}




    
