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

int processa(short int* M, int memSize) {
	unsigned short int* memory = (unsigned short int*)M;

	// Definição dos registradores
	unsigned short int ri = 0; //conteudo de memoria na posicao pc
	unsigned short int pc = 0; 
	unsigned short int a = 0;
	unsigned short int b = 0;
	unsigned short int c = 0;
	unsigned short int d = 0;
	unsigned short int r = 0;
	unsigned short int psw = 0;

	// Começa a executar a partir da instrução na posição 0 da memória
	pc = 0;
	while(true) {
		ri = memory[pc];
		
		// Extrai o opcode da instrução (os 4 bits mais significantes)
		unsigned int opcode = (ri & 0xF000) >> 12;

		if (opcode == 0b0000) {/*NOP*/		}

		// Sai do loop se a instrução for HALT
		if (opcode == 0b1111) break;

		printf ("Ensine-me a fazer algo com %hx\n", ri);
		
		pc++;
		
		// Volta o PC para 0 se ele passar do limite da memóia
		if (pc >= memSize) pc = 0;

		
	};

	return 0;
}
