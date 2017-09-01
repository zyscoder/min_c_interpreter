#ifndef global_variable_hpp
#define global_variable_hpp

#include "lexical_analysis.hpp"

extern int token = 0, line = 0;
extern long token_val = 0;
extern double ftoken_val = 0;

extern char *src = NULL, *old_src = NULL, *data = NULL;


#endif /* global_variable_hpp */
