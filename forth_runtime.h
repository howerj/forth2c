/* Modified from <http://yosefk.com/blog/c-as-an-intermediate-language.html> */
#ifndef FORTH_RUNTIME_H
#define FORTH_RUNTIME_H
#include <stdio.h>
#include <assert.h>
#include <stdint.h>

typedef intptr_t DATA;

#ifndef FORTH_SIZE
#define FORTH_SIZE (4096u)
#endif

#ifndef FORTH_ENTRY_POINT
#define FORTH_ENTRY_POINT cold
#endif

struct forth { DATA *stack; size_t max; FILE *in, *out; };
typedef struct forth FORTH;

DATA *FORTH_ENTRY_POINT(FORTH *F, DATA *S);

static inline DATA *CHK(FORTH *F, DATA *S) { assert(F && S && S <= (F->stack + F->max) && S >= F->stack); return S; }

#define OP2(F, S, op) (S[1] = S[1] op S[0], CHK(F, S+1))
#define LABEL() _ ## __LINE__

static inline DATA *PUSH(FORTH *F, DATA *S, DATA item)  { CHK(F,--S); *S = item; return CHK(F,S); }
static inline DATA *LOAD(FORTH *F, DATA *S)   { CHK(F,S); DATA V = S[0]; S[0] = *(DATA*)V; return CHK(F,S); }
static inline DATA *STORE(FORTH *F, DATA *S)  { CHK(F,S+2); *(DATA*)S[0] = S[1]; return CHK(F,S+2); }
static inline DATA *cLOAD(FORTH *F, DATA *S)  { CHK(F,S); DATA V = S[0]; S[0] = *(char*)V; return CHK(F,S); }
static inline DATA *cSTORE(FORTH *F, DATA *S) { CHK(F,S+2); *(char*)S[0] = S[1]; return CHK(F,S+2); }
static inline DATA *drop(FORTH *F, DATA *S)   { return CHK(F, S+1); }
static inline DATA *dup(FORTH *F, DATA *S)    { CHK(F,--S); S[0]=S[1]; return CHK(F,S); }
static inline DATA *swap(FORTH *F, DATA *S)   { CHK(F,S+2); DATA V = S[0]; S[0] = S[1]; S[1] = V; return CHK(F,S); } 
static inline DATA *tuck(FORTH *F, DATA *S)   { CHK(F,--S); S[0]=S[1]; S[1]=S[2]; S[2]=S[0]; return CHK(F,S); }
static inline DATA *over(FORTH *F, DATA *S)   { CHK(F,--S); S[0]=S[2]; return CHK(F,S); }
static inline DATA *key(FORTH *F, DATA *S)    { CHK(F,--S); *S = fgetc(F->in); return CHK(F,S); }
static inline DATA *emit(FORTH *F, DATA *S)   { (void)fputc(S[0], F->out); return CHK(F,S+1); }
static inline DATA *depth(FORTH *F, DATA *S)  { return PUSH(F, S, (DATA)(&F->stack[F->max] - S)); }

int FORTH_MAIN(int argc, char **argv, DATA here) {
	static DATA stack[FORTH_SIZE];
	FORTH F = { .stack = stack, .max = FORTH_SIZE, }; 
	F.stack[0] = (DATA)&stack[0];
	F.stack[1] = (DATA)(&stack[0] + FORTH_SIZE);
	F.stack[2] = (DATA)argc;
	F.stack[3] = (DATA)argv;
	F.stack[4] = here + (DATA)F.stack;
	F.in  = stdin; 
	F.out = stdout; 
	return *(FORTH_ENTRY_POINT(&F, F.stack+F.max)); 
}

#endif
