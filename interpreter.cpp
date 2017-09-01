#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>
#include <iostream>
#include<memory.h>
//#include "virtrual_machine.h"
#include "lexical_analysis.hpp"
#include "global_variable.hpp"
//#include "syntax_analysis.h"
//#include "expression_analysis.h"
using namespace std;

int main(int argc, char *argv[])
{
    argc--;
    argv++;

	int size;
	FILE *fd;

	int poolsize = 1024 * 1024 * 64;

	if ((fd = fopen(*argv, "r")) < 0)
	{
		printf("could not open(%s)\n", *argv);
		return -1;
	}
    
    // start testing part.
    
    if ((data = (char *)malloc(poolsize)) == NULL) {
        printf("failed to allocate memory for data[]\n");
        return -1;
    }
    memset(data, 0, sizeof(char) * poolsize);
    if (!(src = old_src = (char *)malloc(poolsize))) {
        printf("could not malloc(%d) for source area\n", poolsize);
        return -1;
    }
    id_list_inintialize();
    src = old_src;
    if ((size = (int)fread(src, 1, poolsize - 1, fd)) <= 0) {
		printf("read() returned %d\n", size);
		return -1;
	}
    src[size] = 0;
    fclose(fd);
    test();
    
    // end testing part
    
	return 0;
}
