/*
** This file has been pre-processed with DynASM.
** https://luajit.org/dynasm.html
** DynASM version 1.3.0, DynASM x64 version 1.3.0
** DO NOT EDIT! The original file is in "./example/mandelbrot.c".
*/

#line 1 "./example/mandelbrot.c"
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>

#include "luajit-2.0/dynasm/dasm_proto.h"
#include "luajit-2.0/dynasm/dasm_x86.h"

static void* link_and_encode(dasm_State** d) {
  size_t sz;
  void* buf;
  dasm_link(d, &sz);
  buf = mmap(0, sz, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  dasm_encode(d, buf);
  mprotect(buf, sz, PROT_READ | PROT_EXEC);
  return buf;
}

#define TAPE_SIZE 30000
#define MAX_NESTING 100

typedef struct bf_state {
  unsigned char* tape;
  unsigned char (*get_ch)(struct bf_state*);
  void (*put_ch)(struct bf_state*, unsigned char);
} bf_state_t;

#define bad_program(s) exit(fprintf(stderr, "bad program near %.16s: %s\n", program, s))

static void (*bf_compile(const char* program))(bf_state_t*) {
  unsigned loops[MAX_NESTING];
  int nloops = 0;
  int n;
  dasm_State* d;
  unsigned npc = 8;
  unsigned nextpc = 0;

  //|.arch x64
#if DASM_VERSION != 10300
#error "Version mismatch between DynASM and included encoding engine"
#endif
#line 37 "./example/mandelbrot.c"
  //|.section code
#define DASM_SECTION_CODE 0
#define DASM_MAXSECTION 1
#line 38 "./example/mandelbrot.c"
  dasm_init(&d, DASM_MAXSECTION);

  //|.globals lbl_
  enum { lbl_bf_main, lbl__MAX };
#line 41 "./example/mandelbrot.c"
  void* labels[lbl__MAX];
  dasm_setupglobal(&d, labels, lbl__MAX);

  //|.actionlist bf_actions
  static const unsigned char bf_actions[142] = {254, 0,   248, 10,  83,  65,  84,  65,  85,  65,  86,  80,  73,  137, 252, 252, 73,  139, 156, 253, 36,  233, 76,  141, 107, 252, 255, 76,  141,
                                                179, 233, 255, 72,  129, 252, 235, 239, 76,  57,  252, 235, 15,  135, 244, 247, 72,  129, 195, 239, 248, 1,   255, 72,  129, 195, 239, 76,  57,
                                                252, 243, 15,  134, 244, 247, 72,  129, 252, 235, 239, 248, 1,   255, 128, 3,   235, 255, 128, 43,  235, 255, 76,  137, 231, 65,  252, 255, 148,
                                                253, 36,  233, 136, 3,   255, 72,  15,  182, 3,   76,  137, 231, 72,  137, 198, 65,  252, 255, 148, 253, 36,  233, 255, 49,  192, 136, 3,   255,
                                                128, 59,  0,   15,  132, 245, 249, 255, 128, 59,  0,   15,  133, 245, 249, 255, 88,  65,  94,  65,  93,  65,  92,  91,  195, 255};

#line 45 "./example/mandelbrot.c"
  dasm_setup(&d, bf_actions);
  dasm_growpc(&d, npc);
  //|.define aPtr, rbx
  //|.define aState, r12
  //|.define aTapeBegin, r13
  //|.define aTapeEnd, r14
  //|.define rArg1, rdi
  //|.define rArg2, rsi
  //|.macro prepcall1, arg1
  //| mov rArg1, arg1
  //|.endmacro
  //|.macro prepcall2, arg1, arg2
  //| mov rArg1, arg1
  //| mov rArg2, arg2
  //|.endmacro
  //|.define postcall, .nop
  //|.macro prologue
  //| push aPtr
  //| push aState
  //| push aTapeBegin
  //| push aTapeEnd
  //| push rax
  //| mov aState, rArg1
  //|.endmacro
  //|.macro epilogue
  //| pop rax
  //| pop aTapeEnd
  //| pop aTapeBegin
  //| pop aState
  //| pop aPtr
  //| ret
  //|.endmacro

  //|.type state, bf_state_t, aState
#define Dt1(_V) (int)(ptrdiff_t) & (((bf_state_t*)0)_V)
#line 79 "./example/mandelbrot.c"

  dasm_State** Dst = &d;
  //|.code
  dasm_put(Dst, 0);
#line 82 "./example/mandelbrot.c"
  //|->bf_main:
  //| prologue
  //| mov aPtr, state->tape
  //| lea aTapeBegin, [aPtr-1]
  //| lea aTapeEnd, [aPtr+TAPE_SIZE-1]
  dasm_put(Dst, 2, Dt1(->tape), TAPE_SIZE - 1);
#line 87 "./example/mandelbrot.c"
  for (;;) {
    switch (*program++) {
      case '<':
        for (n = 1; *program == '<'; ++n, ++program)
          ;
        //| sub aPtr, n%TAPE_SIZE
        //| cmp aPtr, aTapeBegin
        //| ja >1
        //| add aPtr, TAPE_SIZE
        //|1:
        dasm_put(Dst, 32, n % TAPE_SIZE, TAPE_SIZE);
#line 96 "./example/mandelbrot.c"
        break;
      case '>':
        for (n = 1; *program == '>'; ++n, ++program)
          ;
        //| add aPtr, n%TAPE_SIZE
        //| cmp aPtr, aTapeEnd
        //| jbe >1
        //| sub aPtr, TAPE_SIZE
        //|1:
        dasm_put(Dst, 52, n % TAPE_SIZE, TAPE_SIZE);
#line 104 "./example/mandelbrot.c"
        break;
      case '+':
        for (n = 1; *program == '+'; ++n, ++program)
          ;
        //| add byte [aPtr], n
        dasm_put(Dst, 72, n);
#line 108 "./example/mandelbrot.c"
        break;
      case '-':
        for (n = 1; *program == '-'; ++n, ++program)
          ;
        //| sub byte [aPtr], n
        dasm_put(Dst, 76, n);
#line 112 "./example/mandelbrot.c"
        break;
      case ',':
        //| prepcall1 aState
        //| call aword state->get_ch
        //| postcall 1
        //| mov byte [aPtr], al
        dasm_put(Dst, 80, Dt1(->get_ch));
#line 118 "./example/mandelbrot.c"
        break;
      case '.':
        //| movzx r0, byte [aPtr]
        //| prepcall2 aState, r0
        //| call aword state->put_ch
        //| postcall 2
        dasm_put(Dst, 93, Dt1(->put_ch));
#line 124 "./example/mandelbrot.c"
        break;
      case '[':
        if (nloops == MAX_NESTING) {
          bad_program("Nesting too deep");
        }
        if (program[0] == '-' && program[1] == ']') {
          program += 2;
          //| xor eax, eax
          //| mov byte [aPtr], al
          dasm_put(Dst, 111);
#line 133 "./example/mandelbrot.c"
        } else {
          if (nextpc == npc) {
            npc *= 2;
            dasm_growpc(&d, npc);
          }
          //| cmp byte [aPtr], 0
          //| jz =>nextpc+1
          //|=>nextpc:
          dasm_put(Dst, 116, nextpc + 1, nextpc);
#line 141 "./example/mandelbrot.c"
          loops[nloops++] = nextpc;
          nextpc += 2;
        }
        break;
      case ']':
        if (nloops == 0) {
          bad_program("] without matching [");
        }
        --nloops;
        //| cmp byte [aPtr], 0
        //| jnz =>loops[nloops]
        //|=>loops[nloops]+1:
        dasm_put(Dst, 124, loops[nloops], loops[nloops] + 1);
#line 153 "./example/mandelbrot.c"
        break;
      case 0:
        if (nloops != 0) {
          program = "<EOF>", bad_program("[ without matching ]");
        }
        //| epilogue
        dasm_put(Dst, 132);
#line 159 "./example/mandelbrot.c"
        link_and_encode(&d);
        dasm_free(&d);
        return (void (*)(bf_state_t*))labels[lbl_bf_main];
    }
  }
}

static void bf_putchar(bf_state_t* s, unsigned char c) { putchar((int)c); }

static unsigned char bf_getchar(bf_state_t* s) { return (unsigned char)getchar(); }

/**
 * brainfxxkを実行する
 *
 * @param[in] (program) bfファイルのバイト列
 */
static void bf_run(const char* program) {
  bf_state_t state;
  unsigned char tape[TAPE_SIZE] = {0};
  state.tape = tape;
  state.get_ch = bf_getchar;
  state.put_ch = bf_putchar;
  bf_compile(program)(&state);
}

int main(int argc, char** argv) {
  if (argc == 2) {
    long sz;
    char* program;
    FILE* f = fopen(argv[1], "r");
    if (!f) {
      fprintf(stderr, "Cannot open %s\n", argv[1]);
      return 1;
    }
    fseek(f, 0, SEEK_END);
    sz = ftell(f);
    program = (char*)malloc(sz + 1);
    fseek(f, 0, SEEK_SET);
    program[fread(program, 1, sz, f)] = 0;
    fclose(f);
    bf_run(program);
    return 0;
  } else {
    fprintf(stderr, "Usage: %s INFILE.bf\n", argv[0]);
    return 1;
  }
}
