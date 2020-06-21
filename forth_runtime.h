/* Modified from <http://yosefk.com/blog/c-as-an-intermediate-language.html> */
#ifndef FORTH_RUNTIME_H
#define FORTH_RUNTIME_H
#include <stdio.h>
#include <assert.h>
#include <stdint.h>

#ifndef FORTH_ENTRY_POINT
#define FORTH_ENTRY_POINT cold
#endif

typedef intptr_t DATA;
typedef struct forth FORTH;
struct forth { DATA *stack, *R; size_t max; FILE *in, *out; };

DATA *FORTH_ENTRY_POINT(FORTH *F, DATA *S);

static inline DATA *CHK(FORTH *F, DATA *S) { assert(F && S && S <= (F->stack + F->max) && S >= F->stack); return S; }

#define OP1(F, S, op) (S[0] = op S[0], CHK(F, S))
#define OP2(F, S, op) (S[1] = S[1] op S[0], CHK(F, S+1))

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
static inline DATA *sp(FORTH *F, DATA *S)     { return PUSH(F, S, (DATA)S); }

static inline FORTH *FORTH_INIT(FORTH *F, DATA start, DATA *stack, DATA elements) {
	assert(F && stack);
	*F = (FORTH){ .stack = stack, .R = &stack[elements/2], .max = elements, .in = stdin, .out = stdout };
	stack[0] = start    * sizeof (DATA);
	stack[1] = elements * sizeof (DATA);
	stack[2] = (DATA)&F->R;
	return F;
}

#endif
