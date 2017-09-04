#ifndef global_variable_h
#define global_variable_h

extern int token = 0, line = 0;
extern long token_val = 0;
extern double ftoken_val = 0;

extern char *src = NULL, *old_src = NULL;
extern void *data_ = NULL, *stack = NULL, *bp = NULL, *sp = NULL, *ax = malloc(8);

extern int *text = NULL, *old_text = NULL;
extern int *pc = NULL, cycle = 0;

extern int depth = 0;

#endif /* global_variable_h */
