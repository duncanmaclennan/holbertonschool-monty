#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct stack_s
{
	int n;
	struct stack_s *prev;
	struct stack_s *next;
} stack_t;

typedef struct instruction_s
{
	char *opcode;
	void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;

void push(stack_t **stack, unsigned int line_number, const char *n_str);
void pall(stack_t **stack, unsigned int line_number);
int is_valid_integer(const char *str);
void free_stack(stack_t **stack);
void handle_line(char *line, stack_t **stack, unsigned int line_number);
void pint(stack_t **stack, unsigned int line_number);
