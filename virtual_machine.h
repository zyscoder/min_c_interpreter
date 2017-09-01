#pragma once

#ifndef _VIRTUAL_MACHINE_H_
#define _VIRTUAL_MACHINE_H_

#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>
#include<memory.h>

#include "global_variable.h"

enum {
	IMM, LC, LI, SC, SI, PUSH, JMP, JZ, JNZ, CALL, ENT, ADJ, LEV, LEA,
	OR, AND, NOT, EQ, NE, LT, LE, GT, GE, ADD, SUB, MUL, DIV, MOD,
	EXIT, INI, INR, INS, OUTI, OUTR, OUTS, ASSIGN, 
};

int eval()
{
	int op, *tmp;
	while (true)
	{
		op = *pc++;
		if (op == '\0')break;

		/* MOV */
		if (op == IMM) { ax = *pc++; }
		else if (op == LC) { ax = *(char *)ax; }
		else if (op == LI) { ax = *(int *)ax; }
		else if (op == SC) { ax = *(char *)*sp++ = ax; }
		else if (op == SI) { *(int *)*sp++ = ax; }
		
		/*PUSH*/
		else if (op == PUSH) { *--sp = ax; }

		/* JMP */
		else if (op == JMP) { pc = (int *)*pc; }

		/* JZ/JNZ */
		else if (op == JZ) { pc = (ax)? pc + 1 : (int *)*pc; }
		else if (op == JNZ) { pc = (!ax) ? pc + 1 : (int *)*pc; }

		/* CALL */
		else if (op == CALL) { *--sp = (int)(pc + 1); pc = (int *)*pc; }

		/* ENT */
		else if (op == ENT) { *--sp = (int)bp; bp = sp; sp = sp - *pc++; } //? ? ?

		/* ADJ */
		else if (op == ADJ) { sp = sp + *pc++; }

		/* LEV */
		else if (op == LEV) { sp = bp; bp = (int *)*sp++; pc = (int *)*sp++; }

		/* LEA */
		else if (op == LEA) { ax = (int)(bp + *pc++); }

		/* 运算符指令集 */
		else if (op == OUTR) ax = *sp++ | ax;
		else if (op == AND) ax = *sp++ & ax;
		else if (op == NOT) ax = ~ax;
		else if (op == ASSIGN) *pc++ = ax;

		else if (op == EQ) ax = *sp++ == ax;
		else if (op == NE) ax = *sp++ != ax;
		else if (op == LT) ax = *sp++ < ax;
		else if (op == LE) ax = *sp++ <= ax;
		else if (op == GT) ax = *sp++ > ax;
		else if (op == GE) ax = *sp++ >= ax;
		else if (op == ADD) ax = *sp++ + ax;
		else if (op == SUB) ax = *sp++ - ax;
		else if (op == MUL) ax = *sp++ * ax;
		else if (op == DIV) ax = *sp++ / ax;
		else if (op == MOD) ax = *sp++ % ax;

		/* 内置函数 */
		else if (op == EXIT) { printf("exit(%d)", *sp); return *sp; }
		else if (op == OUTI) printf("%d", *pc++);
		else if (op == OUTR)printf("%lf", *pc++);
		else if (op == OUTS)printf("%s", *pc++);
		else if (op == INI)scanf("%d", (int *)ax);
		else if (op == INR)scanf("%lf", (double *)ax);
		else if (op == INS)scanf("%s", (char *)ax);

	}

	return 0;
}

#endif