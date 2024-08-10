#include "monty.h"


/**
 * free_stack - Frees the memory allocated for the stack.
 * @stack: Pointer to the head of the stack.
 *
 * Description: This function iterates through the stack, freeing each node.
 */
void free_stack(stack_t *stack)
{
	stack_t *tmp;

	while (stack)
	{
		tmp = stack;
		stack = stack->next;
		free(tmp);
	}
}

/**
 * push - Handles the push opcode.
 * @stack: Pointer to the head of the stack.
 * @line_number: The current line number in the bytecode file.
 *
 * Description: This function pushes an integer onto the stack.
 * It parses the argument after the "push" opcode and adds it to the stack.
 * If the argument is invalid, it prints an error message and exits.
 */
void push(stack_t **stack, unsigned int line_number)
{
	stack_t *new_node;
	char *arg;
	char *endptr;
	int n;

	arg = strtok(NULL, " \t\n");
	if (arg == NULL || *arg == '\0')
	{
		fprintf(stderr, "L%u: usage: push integer\n", line_number);
		exit(EXIT_FAILURE);
	}

	n = strtol(arg, &endptr, 10);
	if (*endptr != '\0')
	{
		fprintf(stderr, "L%u: usage: push integer\n", line_number);
		exit(EXIT_FAILURE);
	}

	new_node = malloc(sizeof(stack_t));
	if (!new_node)
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}

	new_node->n = n;
	new_node->next = *stack;
	new_node->prev = NULL;
	if (*stack)
		(*stack)->prev = new_node;
	*stack = new_node;
}

/**
 * pall - Handles the pall opcode.
 * @stack: Pointer to the head of the stack.
 * @line_number: The current line number in the bytecode file.
 *
 * Description: This function prints all the values on the stack, starting
 * from the top of the stack.If the stack is empty, it does not print anything.
 */
void pall(stack_t **stack, unsigned int line_number)
{
	stack_t *current = *stack;

	(void)line_number; /* Unused parameter */

	while (current)
	{
		printf("%d\n", current->n);
		current = current->next;
	}
}

/**
 * execute_opcode - Executes the given opcode.
 * @opcode: The opcode to be executed.
 * @stack: Pointer to the head of the stack.
 * @line_number: The current line number in the bytecode file.
 *
 * Description: This function matches the opcode with the corresponding
 * function and executes it. If the opcode is not recognized, it prints
 * an error message and exits.
 */
void execute_opcode(char *opcode, stack_t **stack, unsigned int line_number)
{
	instruction_t instructions[] = {
		{"push", push},
		{"pall", pall},
		{"pint", pint},
		{"pop", pop},
		{"swap", swap},
		{"add", add},
		{"nop", nop},
		{NULL, NULL}
	};
	int i;

	for (i = 0; instructions[i].opcode; i++)
	{
		if (strcmp(opcode, instructions[i].opcode) == 0)
		{
			instructions[i].f(stack, line_number);
			return;
		}
	}

	fprintf(stderr, "L%u: unknown instruction %s\n", line_number, opcode);
	exit(EXIT_FAILURE);
}
