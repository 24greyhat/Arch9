#include "include/arch9.h"



Arch9 init_arch9(inst_t* program, int size)
{
  return (Arch9){
    .program = program,
    .ip = 0,
    .mp = 0,
    .fr = zero_f,
    .r1 = 0,
    .r2 = 0,
    .r3 = 0,
    .r4 = 0,
    .r5 = 0,
    .r6 = 0,
    .r7 = 0,
    .r8 = 0,
    .r9 = 0,
    .r10 = 0
  };
}


void writeToReg(Arch9* arch, int reg, mem_t data)
{
 switch(reg)
  {
    case R1:
      arch->r1 = data;
      break;

    case R2:
      arch->r2 = data;
      break;

    case R3:
      arch->r3 = data;
      break;

    case R4:
      arch->r4 = data;
      break;

    case R5:
      arch->r5 = data;
      break;

    case R6:
      arch->r6 = data;
      break;

    case R7:
      arch->r7 = data;
      break;

    case R8:
      arch->r8 = data;
      break;

    case R9:
      arch->r9 = data;
      break;

    case R10:
      arch->r10 = data;
      break;

    default:
      break;

  };


};



mem_t readFromReg(Arch9* arch, int reg)
{
  switch(reg)
  {
    case R1:
      return arch->r1;

    case R2:
      return arch->r2;

    case R3:
      return arch->r3;

    case R4:
      return arch->r4;

    case R5:
      return arch->r5;


    case R6:
      return arch->r6;


    case R7:
      return arch->r7;

    case R8:
      return arch->r8;

    case R9:
      return arch->r9;

    case R10:
      return arch->r10;

    default:
        printf("TRAP:\n\tUnknown register: (R%d)\n", reg);
        arch->fr=trap_f;
      return 0;

  };

};


void interrupt(Arch9* arch)
{
  switch(arch->program[arch->ip].dest)
  {
    case 0:
      printf("%c", (char)readFromReg(arch, arch->program[arch->ip].src));
      break;
      

    default:
        printf("TRAP:\n\tUnknown interrupt: (%lld)\n", arch->program[arch->ip].dest);
        arch->fr=trap_f;
      break;
  }
};


void inc_dec(Arch9* arch, int reg, int increment)
{
  if(increment)
    switch(reg)
    {
      case R1:
        arch->r1+=1;
        break;

      case R2:
        arch->r2+=1;
        break;

      case R3:
        arch->r3+=1;
        break;

      case R4:
        arch->r4+=1;
        break;

      case R5:
        arch->r5+=1;
        break;


      case R6:
        arch->r6+=1;
        break;


      case R7:
        arch->r7+=1;
        break;

      case R8:
        arch->r8+=1;
        break;

      case R9:
        arch->r9+=1;
        break;

      case R10:
        arch->r10+=1;
        break;

      default:
          printf("TRAP:\n\tUnknown register: (R%d)\n", reg);
          arch->fr=trap_f;
        break;
    }

  else
    switch(reg)
      {
        case R1:
          arch->r1-=1;
          break;

        case R2:
          arch->r2-=1;
          break;

        case R3:
          arch->r3-=1;
          break;

        case R4:
          arch->r4-=1;
          break;

        case R5:
          arch->r5-=1;
          break;


        case R6:
          arch->r6-=1;
          break;


        case R7:
          arch->r7-=1;
          break;

        case R8:
          arch->r8-=1;
          break;

        case R9:
          arch->r9-=1;
          break;

        case R10:
          arch->r10-=1;
          break;

        default:
            printf("TRAP:\n\tUnknown register: (R%d)\n", reg);
            arch->fr=trap_f;
          break;
      }
};



void arch9_run(Arch9* arch, int debug)
{
  while(arch->fr==zero_f)
  {
    switch(arch->program[arch->ip].op)
    {
      case STORE_i:
        if(debug) puts("STORE\n");
        arch->memory[arch->mp++] = arch->program[arch->ip].dest;
        arch->ip++;
        break;

      case INT_i:
        if(debug) puts("INT\n");
        interrupt(arch);
        arch->ip++;
        break;

      case LOAD_i:
        if(debug) puts("LOAD\n");
        writeToReg(arch, arch->program[arch->ip].dest, arch->memory[--arch->mp]);
        arch->ip++;
        break;

      case HLT_i:
        if(debug) puts("HLT\n");
        arch->fr = hlt_f;
        arch->ip++;
        break;

      case MOV_i:
        if(debug) puts("MOV\n");
        writeToReg(arch, arch->program[arch->ip].dest, arch->program[arch->ip].src);
        arch->ip++;
        break;

      case INC_i:
        if(debug) puts("INC\n");
        inc_dec(arch, arch->program[arch->ip].dest, 1);
        arch->ip++;
        break;

      case DEC_i:
        if(debug) puts("DEC\n");
        inc_dec(arch, arch->program[arch->ip].dest, 0);
        arch->ip++;
        break;

      case JMP_i:
        if(debug) puts("JMP\n");
        arch->ip=arch->program[arch->ip].dest;
        break;

      case SKIP_i:
        arch->ip++;
        break;

      // not implemented
      case ADD_i:
        break;

      // not implemented
      case MUL_i:
        break;

      // not implemented
      case DIV_i:
        break;

      // not implemented
      case SUB_i:
        break;

      // not implemented
      case MOD_i:
        break;

      case JMPQZ_i:
        if(debug) puts("JMPQZ\n");
        if(readFromReg(arch, arch->program[arch->ip].src) <= 0)
        {
          arch->ip=arch->program[arch->ip].dest;
        }
        else{
          arch->ip++;
        }
        break;


      case JMPNZ_i:
        if(debug) puts("JMPNZ\n");
         if(readFromReg(arch, arch->program[arch->ip].src) > 0)
         {
          arch->ip=arch->program[arch->ip].dest;
         }
         else{
          arch->ip++;
         }
        break;


      default:
        printf("TRAP:\n\tUnknown or null instruction: (%lld)\n", arch->ip);
        arch->fr = trap_f;
        break;
    }
  }

};


int main(int argc, char* argv[])
{

  inst_t* program = malloc(sizeof(inst_t)*4);

  program[0] = (inst_t){STORE_i, '\n'};  //  store '\n'
  program[1] = (inst_t){STORE_i, 'C'};  //  store 'C'
  program[2] = (inst_t){STORE_i, 'B'};  //  store 'B'
  program[3] = (inst_t){STORE_i, 'A'};  //  store 'A'

  program[4] = (inst_t){MOV_i, R2, 4}; //   mov r2, 4
  program[5] = (inst_t){LOAD_i, R1};   //   load r1
  program[6] = (inst_t){INT_i, 0, R1}; //   int 0, r1 
  program[7] = (inst_t){DEC_i, R2};    //   dec r2
  program[8] = (inst_t){JMPNZ_i, 5, R2};//  jmpqz 5, r2  ; jumping to instruction 5 if r2 not zero
  program[9] = (inst_t){HLT_i};         //  hlt


  Arch9 arch = init_arch9(program, 4);


  arch9_run(&arch, 0); // debug = 1 ; prints every instruction name


  return 0;
};
