#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define endereco_instrucao_aleatorio 0
#define tam_memoria 1000

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
        default: 
            printf("Operação inválida!\n");
            return -1;
    }
    
}
void banco_de_registradores(int registrador, int valor, int registradores[]){
    registradores[registrador] = valor;
}


int memoria(int *endereco){
    static int memoria_vet[tam_memoria]; 

    if (endereco >= 0 && endereco < tam_memoria) {
        return memoria_vet[*endereco];
    } else {
        printf("Estouro de memória!\n");
        return -1;
    }
}

int main(void){

    do{
    // Declarando registradores
    int registradores[32] = {0};

    // Inputs
    system("clear");
    char input_mips[10];
    printf("Insira o comando MIPS: \n");
    scanf("%s", input_mips);
    printf("===========================\n");
    if(strcmp(input_mips, "MOV") == 0){
        printf("oi");
    }
    // Função ADDI - adição com imediato
    else if(strcmp(input_mips, "ADDI") == 0){

        int input_1, input_2;
        char tipo_registrador;
        printf("Insira o número do registrador e um número inteiro. Ex.: $s0, 4\n");
        getchar();
        scanf("$%c%d, %d", &tipo_registrador, &input_1, &input_2);

        // Etapa de fetch
        printf("Program Counter recebe endereço da instrução armazenado na memória.\n");

        // Decodificação da instrução
        int RS = tipo_registrador - 'a';
        int RT = input_1;
        int imediato = input_2;

        // Print valores decodificados
        printf("\nValores decodificados:\n");
        printf("RS: $%c%d\n", tipo_registrador, RS);
        printf("RT: $t%d\n", RT);
        printf("Imediato: %d\n", imediato);

        // Execução
        int resultado = adder(registradores[RS], imediato);
        banco_de_registradores(RT, resultado, registradores);

        // Print de valores
        printf("\nValor atual do registrador:\n");
        printf("$%c%d = %d\n", tipo_registrador, input_1, registradores[input_1]);
        

        // Atualizar PC
        int endereco = program_counter(endereco_instrucao_aleatorio, 1);
        printf("\nPC atualizado, valor PC = %d\n", endereco);
    }
    /*else if(strcmp(input_mips, "ADD") == 0){

    }
    else if(strcmp(input_mips, "SUBI") == 0){

    }
    else if(strcmp(input_mips, "SUB") == 0){

    }*/
    }while(!EOF);
    

}