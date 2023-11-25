#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Instrucao{
    int opcode;
    int rs;
    int rt;
    int rd;
    int shamt;
    int funct;
    int imm;
    char endereço[26];
};

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
#define tam_memoria 10000

int funcaoOPcode(char *input) { // Retorne OP-Code ou Funct dependendo do input do usuário
    if (strcmp(input, "ADDI") == 0) {
        return ADDI_OPCODE;
    } else if (strcmp(input, "ANDI") == 0) {
        return ANDI_OPCODE;
    } else if (strcmp(input, "ORI") == 0) {
        return ORI_OPCODE;
    } else if (strcmp(input, "XORI") == 0) {
        return XORI_OPCODE;
    } else if (strcmp(input, "LW") == 0) {
        return LW_OPCODE;
    } else if (strcmp(input, "SW") == 0) {
        return SW_OPCODE;
    } 
    else if (strcmp(input, "ADD") == 0) {
        return ADD_Funct;  
    } else if (strcmp(input, "SUB") == 0) {
        return SUB_Funct;  
    } else if (strcmp(input, "AND") == 0) {
        return AND_Funct; 
    } else if (strcmp(input, "OR") == 0) {
        return OR_Funct;  
    } else if (strcmp(input, "XOR") == 0) {
        return XOR_Funct;  
    } else if(strcmp(input, "J") == 0) {
        return instrucao_J;
    }   else {
        printf("OP-Code inválido: %s\n", input);
        return -1; 
    }
}

int converte_binario(int bin) { // Retorna um valor binário
    if (bin == 0) {
        return 0;
    } else {
        return (bin % 2) + 10 * converte_binario(bin / 2);
    }
}

void preencheInstrucao(int opcode, int rs, int rt, int rd, int shamt, int funct, int imm, int endereco, struct Instrucao *instrucao){ // Preenche a instruçao com seus valores
    instrucao->opcode = opcode;
    instrucao->rs = rs;
    instrucao->rt = rt;
    instrucao->rd = rd;
    instrucao->shamt = shamt;
    instrucao->funct = funct;
    instrucao->imm = imm;
}

void preencheInstrucaoBinario(struct Instrucao *instrucao_binario, struct Instrucao *instrucao){ // Cria um novo struct e converte a instrucao para binario
    instrucao_binario->opcode = converte_binario(instrucao->opcode);
    instrucao_binario->rs = converte_binario(instrucao->rs);
    instrucao_binario->rt = converte_binario(instrucao->rt);
    instrucao_binario->rd = converte_binario(instrucao->rd);
    instrucao_binario->shamt = converte_binario(instrucao->shamt);
    instrucao_binario->funct = converte_binario(instrucao->funct);
    instrucao_binario->imm = converte_binario(instrucao->imm);
}

int unidade_controle(struct Instrucao *instrucao){ // Concede comandos à ULA
    int instrucao_decodificada = converte_binario(instrucao->opcode);
    if(instrucao_decodificada == 0){
        return instrucao->funct;
    }
    else{
        return instrucao->opcode;
    }
    return -1;
}

int adder(int valor_1, int valor_2){
    valor_1 += valor_2;
    return valor_1;
}

int program_counter(int endereço_instrucao){
    return endereço_instrucao;
}

int ULA(int op_code, int operando_1, int operando_2){
    switch (op_code) {
        case 8:
        case 32:
        case 35:
        case 43:
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

int banco_de_registradores(char *registrador, int *registradores) {
    if (strcmp(registrador, "zero") == 0) {
        return registradores[0];
    } 
    else if(strcmp(registrador, "at") == 0){
        return registradores[1];
    }
    else if(strncmp(registrador, "v", 1) == 0){
        int index;
        sscanf(registrador, "v%d", &index);
        if(index >= 0 && index<=1){
            return registradores[2+index];
        }
    }
    else if(strncmp(registrador, "a", 1) == 0){
        int index;
        sscanf(registrador, "a%d", &index);
        if(index >= 0 && index<=3){
            return registradores[4+index];
        }
    }
    else if (strncmp(registrador, "t", 1) == 0) {
        int index;
        sscanf(registrador, "t%d", &index);
        if (index >= 0 && index <= 7) {
            return registradores[8 + index];
        } 
        else if(index == 8 && index == 9){
            return registradores[16 + index];
        }
        else {
            printf("Registrador inválido: %s\n", registrador);
            return -1;
        }
    } else if (strncmp(registrador, "s", 1) == 0) {
        int index;
        sscanf(registrador, "s%d", &index);
        if (index >= 0 && index <= 7) {
            return registradores[16 + index];
        } else {
            printf("Registrador inválido: %s\n", registrador);
            return -1;
        }
    } else if (strncmp(registrador, "k", 1) == 0) {
        int index;
        sscanf(registrador, "k%d", &index);
        if(index == 0 && index == 1){
            return registrador[26 + index];
        }
    } else if (strcmp(registrador, "gp") == 0) {
        return registradores[28]; 
    } else if (strcmp(registrador, "sp") == 0) {
        return registradores[29];
    } else if (strcmp(registrador, "fp") == 0) {
        return registradores[30]; 
    } else if (strcmp(registrador, "ra") == 0) {
        return registradores[31];
    } else {
        printf("Registrador inválido: %s\n", registrador);
        return -1;
    }
}

void write_registrador(int registrador, int valor, int *registradores){
    registradores[registrador] = valor;
}

int read_memoria(int endereco, int *vetor_memoria){
    if (endereco < 0 || endereco >= tam_memoria) {
        printf("Erro de leitura: endereço de memória inválido %d\n", endereco);
        return -1;
    }

    return vetor_memoria[endereco];
}

void write_memoria(int endereco, int valor, int *vetor_memoria){
    if (endereco < 0 || endereco >= tam_memoria) {
        printf("Erro de escrita: endereço de memória inválido %d\n", endereco);
        return;
    }

    vetor_memoria[endereco] = valor;
}

void InstrucaoR(int opcode, char *input_mips, char *RD, char *RS, char *RT, int shamt, int funct, int *registradores, int *valores_memoria, int endereco_instrucao_aleatorio){
    
    struct Instrucao instrucao;
    struct Instrucao instrucao_binario;
    write_memoria(endereco_instrucao_aleatorio, 0, valores_memoria);
    preencheInstrucao(opcode, banco_de_registradores(RS, registradores), banco_de_registradores(RT, registradores), banco_de_registradores(RD, registradores), shamt, funct, 0, 0, &instrucao);
    preencheInstrucaoBinario(&instrucao_binario, &instrucao);
    int resultado, comando;

    switch (funct)
    {
    case ADD_Funct:
    case AND_Funct:
    case OR_Funct:
    case XOR_Funct:
    case SUB_Funct:
        // Decode
        printf("\n=== Decode ===\n");
        comando = unidade_controle(&instrucao);
        printf("\nOP-Code | $rs | $rt | $rd | shamt | funct\n");
        printf("%06d | %05d | %05d | %05d | %05d | %06d\n", instrucao_binario.opcode,
                                                            instrucao_binario.rs,
                                                            instrucao_binario.rt,
                                                            instrucao_binario.rd,
                                                            instrucao_binario.shamt,
                                                            instrucao_binario.funct); 
        printf("\nValores decodificados:\n");
        printf("OP: %d\n", instrucao.opcode);
        printf("RS: $%s = %d\n", RS, banco_de_registradores(RS, registradores));
        printf("RT: $%s = %d\n", RT, banco_de_registradores(RT, registradores));
        printf("RD: $%s = %d\n", RD, banco_de_registradores(RD, registradores));
        printf("Shamt: %d\n", instrucao.shamt);
        printf("Funct: %d\n", instrucao.funct);

        // Execução
        printf("\n=== Etapa 3 - Execução (%s) ===\n", input_mips);
        resultado = ULA(comando, banco_de_registradores(RS, registradores), banco_de_registradores(RT, registradores));
        write_registrador(banco_de_registradores(RD, registradores), resultado, registradores);

        // Print de valores
        printf("Valor atual do registrador:\n");
        printf("$%s = %d\n", RD, banco_de_registradores(RD, registradores));
    }
}

void InstrucaoI(int opcode, char *input_mips, char *RD, char *RS, int imm, int *registradores, int *valores_memoria, int endereco_instrucao_aleatorio){

struct Instrucao instrucao;
struct Instrucao instrucao_binario;
int resultado;

write_memoria(endereco_instrucao_aleatorio, 0, valores_memoria);
preencheInstrucao(opcode, banco_de_registradores(RS, registradores), 0, banco_de_registradores(RD, registradores), 0, 0, imm, endereco_instrucao_aleatorio, &instrucao);
preencheInstrucaoBinario(&instrucao_binario, &instrucao);
    switch (opcode)
    {

    case ADDI_OPCODE:
    case ORI_OPCODE:
    case XORI_OPCODE:
    case ANDI_OPCODE:

        // Fetch
        printf("\n=== Etapa 1 - Fetch ===\n");
        endereco_instrucao_aleatorio = program_counter(endereco_instrucao_aleatorio);
        printf("PC recebe instrução armazenada na memória.\n");
        printf("PC = %d\n", endereco_instrucao_aleatorio);

        // Etapa de Decode
        printf("\n=== Etapa 2 - Decode ===\n");
        int comando_unidade_controle_I = unidade_controle(&instrucao);
        // Print valores decodificados
        printf("\nOP-Code | $rs | $rd | Imm\n");
        printf("%06d | %05d | %05d | %016d\n",  instrucao_binario.opcode,
                                                instrucao_binario.rs,
                                                instrucao_binario.rd,
                                                instrucao_binario.imm);
        printf("\nValores decodificados:\n");
        printf("Instrução tipo I\n");
        printf("OP: %d\n", opcode);
        printf("RS: $%s = %d\n", RS, registradores[banco_de_registradores(RS, registradores)]);
        printf("RD: $%s = %d\n", RD, registradores[banco_de_registradores(RD, registradores)]);
        printf("Imediato: %d\n", imm);

        // Execução
        printf("\n=== Etapa 3 - Execução (%s) ===\n", input_mips);
   
        resultado = ULA(comando_unidade_controle_I, registradores[banco_de_registradores(RS, registradores)], imm);
        printf("Operação realizada!\nResultado da operação = %d\n", resultado);


        // Print de valores
        printf("\n=== Etapa 4 - Write Back ===\n");
        write_registrador(banco_de_registradores(RD, registradores), resultado, registradores);
        printf("Valor atual do registrador:\n");
        printf("$%s = %d\n", RD, registradores[banco_de_registradores(RD, registradores)]);

        // Program-Counter
        printf("\n=== Program-Counter ===\n", input_mips);

        // Atualizar pc
        endereco_instrucao_aleatorio = adder(endereco_instrucao_aleatorio, 4);
        printf("PC atualizado!\nPC = %d\n", endereco_instrucao_aleatorio);
        break;

    case SW_OPCODE:

        // Fetch
        printf("\n=== Etapa 1 - Fetch ===\n");
        endereco_instrucao_aleatorio = program_counter(endereco_instrucao_aleatorio);
        printf("PC recebe instrução armazenada na memória.\n");
        printf("PC = %d\n", endereco_instrucao_aleatorio);

        // Etapa de Decode
        printf("\n=== Etapa 2 - Decode ===\n");
        int comando_unidade_controle_SW = unidade_controle(&instrucao);

        // Print valores decodificados
        printf("\nOP-Code | $rs | $rd | Imm\n");
        printf("%06d | %05d | %05d | %016d\n", instrucao_binario.opcode,
            instrucao_binario.rs,
            instrucao_binario.rd,
            instrucao_binario.imm);
        printf("\nValores decodificados:\n");
        printf("Instrução tipo I\n");
        printf("OP: %d\n", opcode);
        printf("RS: $%s = %d\n", RS, registradores[banco_de_registradores(RS, registradores)]);
        printf("RD: $%s = %d\n", RD, registradores[banco_de_registradores(RD, registradores)]);
        printf("Offset: %d\n", imm);

       // Execução
        printf("\n=== Etapa 3 - Execução (%s) ===\n", input_mips);

        // Calcula o endereço de memória para leitura
        int endereco_leitura_sw = ULA(comando_unidade_controle_SW, banco_de_registradores(RS, registradores), imm);

        // Print do endereço de memória para leitura
        printf("Endereço de memória para leitura: %d\n", endereco_leitura_sw);

        // Leitura da memória
        write_memoria(endereco_leitura_sw, registradores[endereco_leitura_sw], valores_memoria);
        int dado_lido_sw = read_memoria(endereco_leitura_sw, valores_memoria);

        // Print do dado lido
        printf("Dado lido da memória: %d\n", dado_lido_sw);

        // Write Back
        printf("\n=== Etapa 4 - Write Back ===\n");

        // Escreve o dado lido no registrador RD
        write_registrador(banco_de_registradores(RD, registradores), dado_lido_sw, registradores);

        // Print do valor atual do registrador
        printf("Valor atual do registrador $%s: %d\n", RD, registradores[banco_de_registradores(RD, registradores)]);
        // Program-Counter
        printf("\n=== Program-Counter ===\n", input_mips);

        // Atualizar pc
        endereco_instrucao_aleatorio = adder(endereco_instrucao_aleatorio, 4);
        printf("PC atualizado!\nPC = %d\n", endereco_instrucao_aleatorio);
        break;

    case LW_OPCODE:
        //Fetch
        printf("\n=== Etapa 1 - Fetch ===\n");
        int program_counter_ = program_counter(endereco_instrucao_aleatorio);
        printf("PC recebe instrução armazenada na memória.\n");
        printf("PC = %d\n", program_counter_);

        // Etapa de Decode
        printf("\n=== Etapa 2 - Decode ===\n");
        int comando_unidade_controle_LW = unidade_controle(&instrucao);

        // Print valores decodificados
        printf("\nOP-Code | $rs | $rd | Imm\n");
        printf("%06d | %05d | %05d | %016d\n", instrucao_binario.opcode,
            instrucao_binario.rs,
            instrucao_binario.rd,
            instrucao_binario.imm);
        printf("\nValores decodificados:\n");
        printf("Instrução tipo I\n");
        printf("OP: %d\n", opcode);
        printf("RS: $%s = %d\n", RS, registradores[banco_de_registradores(RS, registradores)]);
        printf("RD: $%s = %d\n", RD, registradores[banco_de_registradores(RD, registradores)]);
        printf("Offset: %d\n", imm);

        // Execução
        printf("\n=== Etapa 3 - Execução (%s) ===\n", input_mips);

        // Calcula o endereço de memória para leitura
        int endereco_leitura_lw = ULA(comando_unidade_controle_LW, banco_de_registradores(RS, registradores), imm);

        // Print do endereço de memória para leitura
        printf("Endereço de memória para leitura: %d\n", endereco_leitura_lw);

        // Leitura da memória
        write_memoria(endereco_leitura_lw, registradores[endereco_leitura_lw], valores_memoria);
        int dado_lido_lw = read_memoria(endereco_leitura_lw, valores_memoria);

        // Print do dado lido
        printf("Dado lido da memória: %d\n", dado_lido_lw);

        // Write Back
        printf("\n=== Etapa 4 - Write Back ===\n");

        // Escreve o dado lido no registrador RD
        write_registrador(banco_de_registradores(RD, registradores), dado_lido_lw, registradores);

        // Print do valor atual do registrador
        printf("Valor atual do registrador $%s: %d\n", RD, registradores[banco_de_registradores(RD, registradores)]);
        break;
        // Program-counter
        printf("\n=== Program-Counter ===\n", input_mips);

        // Atualizar pc
        endereco_instrucao_aleatorio = adder(endereco_instrucao_aleatorio, 4);
        printf("PC atualizado!\nPC = %d\n", endereco_instrucao_aleatorio);
    }
}

void InstrucaoJ(int opcode, char *input_mips, int endereco_destino, int *endereco_instrucao_aleatorio){

    struct Instrucao instrucao;
    struct Instrucao instrucao_binario;
    int resultado;
    preencheInstrucao(instrucao_J, 0, 0, 0, 0, 0, 0, endereco_instrucao_aleatorio, &instrucao);
    preencheInstrucaoBinario(&instrucao_binario, &instrucao);

    //Fetch
    printf("\n=== Etapa 1 - Fetch ===\n");
    int program_counter_ = program_counter(*endereco_instrucao_aleatorio);
    printf("PC recebe instrução armazenada na memória.\n");
    printf("PC = %d\n", program_counter_);
    
    // Decode
    printf("\n=== Etapa 2 - Decode ===\n");
    printf("OP-Code | Endereço\n");
    printf("%06d | %08d\n", instrucao_binario.opcode, instrucao_binario.endereço);
    printf("Instrução tipo J\n");
    printf("OP: %d\n", opcode);
    printf("Endereço de destino: %d\n", endereco_destino);

    // Executar
    printf("\n=== Etapa 3 - Executar (%s) ===\n", input_mips);

    // Atualizar pc
    *endereco_instrucao_aleatorio = endereco_destino;
    printf("PC atualizado!\nPC = %d\n", *endereco_instrucao_aleatorio);

}

int main(void){

    int endereco_instrucao_aleatorio = 0;

    // Declarando registradores e variáveis necessárias
    int registradores[32];
    for(int i=0;i<32;i++){
        registradores[i] = i; // Valor aleatório para testar execução dos códigos
    }
    int memoria_vet[tam_memoria] = {0};
    int program_counter_;

    // Inputs
    char input_mips[100];
    char instrucao_mips[100];

while (1) {
    printf("\nInsira o comando MIPS. Ex.: ADDI $t0, $t1, 4.\n"
           "Digite 'fim' para encerrar o programa.\n\nMips32: ");
    if (fgets(input_mips, sizeof(input_mips), stdin) == NULL) {
        printf("Erro ao ler a entrada. Encerrando programa.\n");
        return 1;
    }
    if (strlen(input_mips) >= 1 && strcmp(input_mips, "fim\n") == 0) {
        printf("Encerrando programa...");
        return 0;
    }

    size_t len = strlen(input_mips);
    if (len > 0 && input_mips[len - 1] == '\n') {
        input_mips[len - 1] = '\0';
    }

    // Pegando a instrução
    char input_temp[100];
    strcpy(input_temp, input_mips);
    char *token = strtok(input_temp, " \t\n");
    if (token != NULL) {
    sscanf(token, "%s", instrucao_mips);

        if (strcmp(instrucao_mips, "ADD") == 0 || strcmp(instrucao_mips, "SUB") == 0 ||
            strcmp(instrucao_mips, "AND") == 0 || strcmp(instrucao_mips, "OR") == 0 ||
            strcmp(instrucao_mips, "XOR") == 0) {
            // Instrução do tipo R
            char RD[10], RS[10], RT[10];
            if (sscanf(input_mips, "%*s $%[^,], $%[^,], $%[^,]", RD, RS, RT) == 3) {
                // Processar instrução do tipo R
                InstrucaoR(instrucao_R, instrucao_mips, RD, RS, RT, 0, funcaoOPcode(instrucao_mips), registradores, memoria_vet, endereco_instrucao_aleatorio);
            } else {
                printf("Formato inválido para instrução do tipo R.\n");
            }
        } 
        
        // Instrucoes tipo I
        else if (strcmp(instrucao_mips, "ADDI") == 0 || strcmp(instrucao_mips, "ORI") == 0 ||
                   strcmp(instrucao_mips, "XORI") == 0 || strcmp(instrucao_mips, "ANDI") == 0) {
            // Instrução do tipo I
            char RD[10], RS[10];
            int imm;
            if (sscanf(input_mips, "%*s $%[^,], $%[^,], %d", RD, RS, &imm) == 3) {
                // Processar instrução do tipo I
                InstrucaoI(funcaoOPcode(instrucao_mips), instrucao_mips, RD, RS, imm, registradores, memoria_vet, endereco_instrucao_aleatorio);
            } else {
                printf("Formato inválido para instrução do tipo I.\n");
            }
        }

        // Instrucoes Load/Store
        else if (strcmp(instrucao_mips, "SW") == 0) {

            // Instrução do tipo I Store
            char RD[10], RS[10];
            int imm;
            if (sscanf(input_mips, "%*s $%[^,], %d($%[^,])", RS, &imm, RD) == 3) {

            // Remover )
            char *token = strtok(RD, ")");
            while (token != NULL) {
                token = strtok(NULL, ")");
            }

                // Processar instrução do tipo I (Load/Store)
                InstrucaoI(funcaoOPcode(instrucao_mips), instrucao_mips, RD, RS, imm, registradores, memoria_vet, endereco_instrucao_aleatorio);
            } else {
                printf("Formato inválido para instrução do tipo I (Load/Store).\n");
            }
        } 
        else if (strcmp(instrucao_mips, "LW") == 0) {

            // Instrução do tipo I Load
            char RD[10], RS[10];
            int imm;
            if (sscanf(input_mips, "%*s $%[^,], %d($%[^,])", RD, &imm, RS) == 3) {

            // Remover )
            char *token = strtok(RS, ")");
            while (token != NULL) {
                token = strtok(NULL, ")");
            }

                // Processar instrução do tipo I (Load/Store)
                InstrucaoI(funcaoOPcode(instrucao_mips), instrucao_mips, RD, RS, imm, registradores, memoria_vet, endereco_instrucao_aleatorio);
            } else {
                printf("Formato inválido para instrução do tipo I (Load/Store).\n");
            }
        } 


        // Instruçoes J
        else if (strcmp(instrucao_mips, "J") == 0) {
            int salto;
            if (sscanf(input_mips, "%*s %d", &salto) == 1) {
                InstrucaoJ(instrucao_J, instrucao_mips, salto, &endereco_instrucao_aleatorio);
            } else {
                printf("Formato inválido para instrução do tipo J.\n");
            }
        } 
        
         else {
            printf("Instrução inválida: %s\n", instrucao_mips);
        }
    }
}
}

    
