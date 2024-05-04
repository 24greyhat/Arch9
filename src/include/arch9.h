#ifndef __ARCH9__
#define __ARCH9__

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define ADDRESS_SPACE 500000 // 500 Kilo bytes of memory


typedef int64_t mem_t;


struct Inst_S{
  mem_t op;
  mem_t dest;
  mem_t src;
}typedef inst_t;



struct {
  mem_t memory[ADDRESS_SPACE];
  
  // to be safe instructions are loaded seperately 
  inst_t* program;

  mem_t ip; // instruction pointer (grows up)
  mem_t mp; // memory pointer
  mem_t fr; // flag register
             
  mem_t r1; // general purpose registers r1 to r10
  mem_t r2; // general purpose registers r1 to r10
  mem_t r3; // general purpose registers r1 to r10
  mem_t r4; // general purpose registers r1 to r10
  mem_t r5; // general purpose registers r1 to r10
  mem_t r6; // general purpose registers r1 to r10
  mem_t r7; // general purpose registers r1 to r10
  mem_t r8; // general purpose registers r1 to r10
  mem_t r9; // general purpose registers r1 to r10
  mem_t r10; // general purpose registers r1 to r10
}typedef Arch9;



Arch9 init_arch9(inst_t* program);
void arch9_run(Arch9* arch, int debug);



enum {
  HLT_i=100, // end program execution
  STORE_i,   // store in memory
  LOAD_i,   // load from memory
  JMP_i,   // jump to dest
  JMPNZ_i, // jump to dest if src-register is greater than zero
  JMPQZ_i,// jump to dest if src-register less than or equal to zero
  SKIP_i, // skip next instruction
  ADD_i,
  MUL_i,
  SUB_i,
  DIV_i,
  MOD_i, // %
  MOV_i,
  INC_i, // ++
  DEC_i, // --
  INT_i, // call an interrupt (built in functions)
}typedef OPS;


enum {
  R1 = 1,
  R2,
  R3,
  R4,
  R5,
  R6,
  R7,
  R8,
  R9,
  R10
}typedef REGS;


enum {
  zero_f=0,  // running fine flag (executing code)
  trap_f,   //  trap flag (error occurred)
  hlt_f    //   halt flag (stop execution)

}typedef FLAGS;




/*
 *
 
Single address architecture


# arch9 simple HELLO message

  store '\n'
  store 'H'      ; op: store, dest: 'H', src: 0
  store 'E'
  store 'L'
  store 'L'
  store 'O'

  mov r2, 6       

  load r1         ; pop item from memory and store it in r1
  int 0, r1       ; 0 = putchar intterrupt (this line prints last store)

  dec r2          ; decrement r2

  jmpnz 8, r2     ; keeps jumping to the 8th instruction until r2 is zero

  hlt             ; halt execution

 */


/*

0 = putchar
1 = getchar


*/




#endif
