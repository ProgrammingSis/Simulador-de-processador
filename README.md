# Um simulador de processador em C.

É possível fazer algumas operações típicas de um processador simples a partir de codigos em hexadecimal em um arquivo chamado "teste.txt". Para facilitar o processo de compilação e teste do código, o arquivo makefile faz comandos automáticos partindo de comandos mais curtos no terminal.

## O arquivo Makefile pode ser usado no terminal com o comando:

> make run
## Para compilar, basta usar o comando:
> make build

## Que comandos o simulador de processador pode realizar?
- Operações aritméticas
  - Adição 
  - Subtração
    
- Operações lógicas:
  - AND
  - OR
  - XOR
  - NOT
    
- Operações especiais:
  - Deixar o registrador chamado de "acumulador" preenchido com 0s.
  - Deixar o acumulador preenchido com "1111"
  - JUMP
  - RETURN (faz com que ele retorne à próxima instrução que seria executada antes do salto)
  - HALT (faz o programa parar)
