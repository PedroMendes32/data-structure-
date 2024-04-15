#ifndef STACK_H
#define STACK_H
#include<stdio.h>
#include<stdlib.h>

enum type
{
	INT,CHAR,FLOAT,STRING,BOOL	
};

struct value
{
	void *val;
	enum type type;	
};
typedef struct value value;

struct stack
{
	int top;
	int size;
	value *values;	
};
typedef struct stack stack;

value create(void *ptr, enum type t);
void init_stack (stack **s, int n);
void push (stack **s, value v);
value* pop (stack **s);
void show_stack (stack **s);

#endif