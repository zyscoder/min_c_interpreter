#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>
#include<memory.h>

#include "global_variable.h"
#include "virtual_machine.h"
#include "lexical_analysis.h"
#include "syntax_analysis.h"
#include "expression_analysis.h"

#define debug

int main(int argc, char *argv[])
{
    	argc--;
    	argv++;

	int poolsize = 32 * 1024 * 1024;

	if (!(text = old_text = (int *)malloc(poolsize)))
	{
		printf("could not malloc(%d) for text area\n", poolsize);
		return -1;
	}
	if (!(data_ = (char *)malloc(poolsize)))
	{
		printf("could not malloc(%d) for data area\n", poolsize);
		return -1;
	}
	if (!(stack = (int *)malloc(poolsize)))
	{
		printf("could not malloc(%d) for stack area\n", poolsize);
		return -1;
	}
	if (!(src = old_src = (char *)malloc(poolsize)))
	{
		printf("could not malloc(%d) for source area\n", poolsize);
		return -1;
	}
	if (!(ed = (identifier **)malloc(poolsize * sizeof(identifier *)))) {
		printf("could not malloc(%d) for fucking area\n", poolsize * sizeof(identifier *));
		return -1;
	}

	memset(text, 0, poolsize);
	memset(data_, 0, poolsize);
	memset(stack, 0, poolsize);

	id_list_inintialize();
	src = old_src;

	int file_size;
	FILE *fd;	

	if ((fd = fopen(*argv, "r")) < 0)
	{
		printf("could not open(%s)\n", *argv);
		return -1;
	}
	if ((file_size = fread(src, 1, poolsize - 1, fd)) <= 0)
	{
		printf("read() returned %d\n", file_size);
		return -1;
	}
	
	#ifdef debug
	printf("the total size of the src is: %d\n\n", file_size);
	#endif

	src[file_size] = 0;
	fclose(fd);

	#ifdef debug
	test();
	#endif
	
	bp = sp = (int *)(stack + poolsize);
	ax = 0;

	return 0;
}