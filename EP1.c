#include "driverEP1.h"
#include <inttypes.h>
#include <stdbool.h>

typedef enum opcode_t {
	NO_OP = 0b0000,
	LOAD_A = 0b0001,
	STORE_A = 0b0010,
	JUMP = 0b0011,
	JUMP_NZ = 0b0100,
	RETURN = 0b0101,
	ARIT = 0b0110,
	HALT = 0b1111
} Opcode;

typedef enum opArit{//poderia colocar como numeros em base decimal em vez dos binarios
	SET_OP_DEST_NULO = 0b0000,
	SET_OP_DEST_FFFF = 0b0001,
	NOT = 0b0010,
	AND = 0b0011,
	OR = 0b0100,
	XOR = 0b0101,
	ADD = 0b0110,
	SUB = 0b0111
} OperacaoArit;

///@param REG_A é uma codificação para que você saiba qual registrador será usado, não é um endereço 
typedef enum qRegistrador{//poderia colocar como numeros em base decimal em vez dos binarios
	REG_A = 0,
	REG_B = 1,
	REG_C = 2,
	REG_D = 3,
	REG_R = 6,
	REG_PSW = 7
} QualRegistrador;

unsigned short int ri = 0; //conteudo de memoria na posicao pc
 
    //Registradores propriamente ditos, incializados com 0
	unsigned short int pc = 0; 
	unsigned short int a = 0;
	unsigned short int b = 0;
	unsigned short int c = 0;
	unsigned short int d = 0;
	unsigned short int r = 0;
	unsigned short int psw = 0;

 unsigned short int* qualOperador(unsigned short int operando);

int processa(short int* M, int memSize) {
	unsigned short int* memory = (unsigned short int*)M;

	// Definição dos registradores
	
	

	// Começa a executar a partir da instrução na posição 0 da memória
	pc = 0;
	while(1) {
		ri = memory[pc];
		
		// Extrai o opcode da instrução (os 4 bits mais significantes)
		                                          
		unsigned int opcode = (ri & 0xF000) >> 12; 
		unsigned int argument = (ri & 0x0fff);    

		printf("Ensine-me a fazer algo com %hx\n", ri);
		
		/*NOP*/
		if (opcode == NO_OP) {}

		// Sai do loop se a instrução for HALT
		if (opcode == HALT) break;

		//carrega o conteudo da memoria na posicao argument e o armazena no registrador "a"
		if (opcode == LOAD_A){

			a = memory[argument];
		}

		//carrega o conteudo do acumulador na posicao de memoria indicada por argument
		if(opcode == STORE_A){
			memory[argument] = a;
		}

		if(opcode == JUMP){
			r = pc + 1;
			pc = argument;
		}

		if(opcode == JUMP_NZ){
			if(a != 0){
				r = pc + 1;
				pc = argument;
			}
		}

		if(opcode == RETURN){
			unsigned int aux = r;
			r = pc + 1;
			pc = aux;
		}

		if(opcode == ARIT){
			/*O sinal >> move casas para a direita e ignora o que passar do espaço de memoria.
			  Nesse caso, são 6 casas ignoradas para ter o numero certo nas comparações tipoOperação,
			que contém apenas 3 bits. A máscara de bits seleciona esses 3 bits e "zera" o resto, que é retirado
			da variável com o ">>" que move os bits não zerados para a direita. 

			Esses numeros representam qual opção de cada coisa sera selecionada (exemplo: add, and, or, XOR, ETC.)*/
			unsigned short int tipoOperacao = (ri & 0xe00) >> 9;
			unsigned short int destinoOperacao = (ri & 0b0000000111000000) >> 6;
			unsigned short int operando1 = (ri & 0b0000000000111000) >> 3;
			unsigned short int operando2 = (ri & 0b0000000000000111);

			unsigned short int* regDestino; // aqui temos um ponteiro para o destino

			//sequencia de condicões para determinar o endereco destino correto

			regDestino = qualOperador(destinoOperacao);

			
			unsigned short int* regOperador1 =  qualOperador(operando1);
			unsigned short int* regOperador2 =  qualOperador(operando2);

			//abaixo estão as condicoes que verifica qual eh a operacao pedida

			// set destino para 0
			if(tipoOperacao == SET_OP_DEST_NULO){
				*regDestino = 0x0000; 
			}

			 //set destino para ffff
			if(tipoOperacao == SET_OP_DEST_FFFF){
				*regDestino = 0xffff;
			}

			if(tipoOperacao == AND){
				*regDestino = (*regOperador1 & *regOperador2);
			}

			if(tipoOperacao == OR){
				*regDestino = (*regOperador1 | *regOperador2);
			}
			if(tipoOperacao == XOR){
				*regDestino = (*regOperador1 ^ *regOperador2);

			}
			if(tipoOperacao == NOT){
				//para inverter com o NOT em nível de bit, foi usado "~"
				*regDestino = ~(*regOperador1); 
			}
			 
			if(tipoOperacao == ADD){
				*regDestino = *regOperador1 + *regOperador2;
			}
			
		}

		pc++;

		// Volta o PC para posicao 0 se ele passar do limite da memóia
		if (pc >= memSize) pc = 0;		
	}

	return 0;
}

unsigned short int* qualOperador(unsigned short int operando){
	unsigned short int* regOperador = NULL;

	if(operando == REG_A){
		regOperador = &a;
	}
	if(operando == REG_B){
		regOperador = &b;
	}
	if(operando == REG_C){
		regOperador = &c;
	}
	if(operando == REG_D){
		regOperador = &d;
	}
	if(operando == REG_R){
		regOperador = &r;
	}
	if(operando == REG_PSW){
		regOperador = &psw;
	}

	return regOperador;
 }
