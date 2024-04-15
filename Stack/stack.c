#include"stack.h"

value create(void *ptr, enum type t)
{
	if (ptr == NULL)
	{
		fprintf(stderr,"Erro: Parâmetro inválido.\n");
		exit(EXIT_FAILURE);
	}
	
	value v;
	v.val = ptr;
	v.type = t;
	return v;
}

void init_stack (stack **s, size_t n)
{
	if (n <= 0)
	{
		fprintf(stderr,"Erro: Tamanho de pilha inválido.\n");
		exit(EXIT_FAILURE);
	}
	
	*s = (stack*) malloc (sizeof(stack));
	
	if (*s == NULL) 
	{
		fprintf(stderr,"Erro: Falha durante alocação dinâmica da pilha.\n");
		exit(EXIT_FAILURE);
	} 
	
	(*s)->top = 0;
	(*s)->size = n;
	(*s)->values = (value*) malloc (sizeof(value) * n);
	
	if ((*s)->values == NULL)
	{
		fprintf(stderr,"Erro: Falha durante alocação dinâmica dos itens da pilha.\n");
		free(*s);
		exit(EXIT_FAILURE);
	}
}

void push (stack **s, value v)
{
	if (*s == NULL)
	{
		fprintf(stderr,"Erro: objeto nulo.\n");
		exit(EXIT_FAILURE);
	}
	if ((*s)->top >= (*s)->size)
	{
		printf("Full stack!\n");
		return;
	}
	(*s)->values[(*s)->top] = v;
	(*s)->top++;
}
	
value* pop (stack **s)
{
	if (*s == NULL)
	{
		fprintf(stderr,"Erro: objeto nulo.\n");
		exit(EXIT_FAILURE);
	}
	(*s)->top--;
	if ((*s)->top < 0)
	{
		printf("Empty stack!\n");
		return NULL;
	}
	return &(*s)->values[(*s)->top];
}
	
void show_stack (stack **s)
{
	if (*s == NULL || (*s)->values == NULL)
	{
		fprintf(stderr,"Erro: objeto nulo.\n");
		exit(EXIT_FAILURE);
	}
	
	printf("[ ");
	
	for (int i = 0; i < (*s)->top; i++)
	{	
		switch ((*s)->values[i].type)
		{
			case INT:
			{
				printf(" %d",(*(int*)(*s)->values[i].val));
			}
			break;
			case CHAR:
			{
				printf(" %c",39);
				printf("%c",(*(char*)(*s)->values[i].val));
				printf("%c",39);
			}	
			break;
			case FLOAT:
			{
				printf(" %.2f",(*(float*)(*s)->values[i].val));
			}
			break;
			case STRING:
			{
				char *str = (char*)(*s)->values[i].val;
				
				printf(" %c",34);
				while (str != NULL && *str != '\0')
				{
					printf("%c",*str);
					str++;	
				}
				printf("%c",34);			
			}
			break;
			case BOOL:
			{
				printf(" %c",34);
				printf("%s",(*(int*)(*s)->values[i].val) == 1 ? "True" : "False");
				printf("%c",34);			
			}
			break;
		}
		if (i + 1 < (*s)->top) printf(",");
		
	}
	printf(" ]\n\n");
}

void clear_stack (stack **s)
{
	if (*s != NULL)
	{
		if ((*s)->values != NULL) 
		{
			free((*s)->values);
		}
		free(*s);
	}
}