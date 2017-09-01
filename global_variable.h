#ifndef global_variable_h
#define global_variable_h

extern int token = 0, line = 0;
extern long token_val = 0;
extern double ftoken_val = 0;

extern char *src = NULL, *old_src = NULL, *Data = NULL;

extern int *text = NULL, *old_text = NULL, *stack = NULL;
extern int *pc = NULL, *bp = NULL, *sp = NULL, ax = 0, cycle = 0;

#endif /* global_variable_h */
