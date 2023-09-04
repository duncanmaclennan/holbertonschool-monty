#include "monty.h"

void push(stack_t **stack, unsigned int line_number, const char *n_str)
{
	stack_t *new_node;

	if (n_str == NULL || (atoi(n_str) == 0 && strcmp(n_str, "0") != 0))

	{
		fprintf(stderr, "L%d: usage: push integer\n", line_number);
		exit(EXIT_FAILURE);
	}

	int num = atoi(n_str);

	new_node = malloc(sizeof(stack_t));
	if (new_node == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}

	new_node->n = num;
	new_node->prev = NULL;
	new_node->next = *stack;

	if (*stack != NULL)
	{
		(*stack)->prev = new_node;
	}

	*stack = new_node;
}

void pall(stack_t **stack, unsigned int line_number)
{
	stack_t *current = *stack;

	(void)line_number;

	while (current != NULL)
	{
		printf("%d\n", current->n);
		current = current->next;
	}
}

void free_stack(stack_t **stack)
{
    stack_t *current_node;
    stack_t *next_node;

    current_node = *stack;
    while (current_node != NULL)
    {
        next_node = current_node->next;
        free(current_node);
        current_node = next_node;
    }
    *stack = NULL;
}

int main(int argc, char **argv)
{
	FILE *fp;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	unsigned int line_number = 0;
	stack_t *stack = NULL;

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}

	fp = fopen(argv[1], "r");
	if (fp == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	while ((read = getline(&line, &len, fp)) != -1)
	{
		char *opcode;
		char *argument;

		line_number++;
		opcode = strtok(line, " \t\r\n");
		if (opcode == NULL || opcode[0] == '#')
			continue;

		argument = strtok(NULL, " \t\r\n");

		if (strcmp(opcode, "push") == 0)
		{
			push(&stack, line_number, argument);
		}
		else if (strcmp(opcode, "pall") == 0)
		{
			pall(&stack, line_number);
		}
		else
		{
			fprintf(stderr, "L%d: unknown instruction %s\n", line_number, opcode);
			exit(EXIT_FAILURE);
		}
	}

	fclose(fp);
	if (line)
		free(line);

	free_stack(&stack);

	return 0;
}
