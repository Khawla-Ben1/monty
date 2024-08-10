#include "monty.h"

/**
 * pint - Handles the pint opcode.
 * @stack: Pointer to the head of the stack.
 * @line_number: The current line number in the bytecode file.
 *
 * Description: This function prints the value at the top of the stack.
 * If the stack is empty, it prints an error message and exits.
 */
void pint(stack_t **stack, unsigned int line_number)
{
	if (*stack == NULL)
	{
		fprintf(stderr, "L%u: can't pint, stack empty\n", line_number);
		exit(EXIT_FAILURE);
	}
	printf("%d\n", (*stack)->n);
}

/**
 * pop - Handles the pop opcode.
 * @stack: Pointer to the head of the stack.
 * @line_number: The current line number in the bytecode file.
 *
 * Description: This function removes the top element of the stack.
 * If the stack is empty, it prints an error message and exits.
 */
void pop(stack_t **stack, unsigned int line_number)
{
	stack_t *temp;

	if (*stack == NULL)
	{
		fprintf(stderr, "L%u: can't pop an empty stack\n", line_number);
		exit(EXIT_FAILURE);
	}

	temp = *stack;
	*stack = (*stack)->next;
	if (*stack)
		(*stack)->prev = NULL;

	free(temp);
}

/**
 * swap - Handles the swap opcode.
 * @stack: Pointer to the head of the stack.
 * @line_number: The current line number in the bytecode file.
 *
 * Description: This function swaps the top two elements of the stack.
 * If the stack contains fewer than two elements, it prints an error message
 * and exits.
 */
void swap(stack_t **stack, unsigned int line_number)
{
	stack_t *first, *second;

	if (*stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%u: can't swap, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}
	first = *stack;
	second = (*stack)->next;
	first->next = second->next;
	if (second->next)
		second->next->prev = first;
	
	second->next = first;
	second->prev = NULL;
	first->prev = second;
	*stack = second;
}

/**
 * add - Handles the add opcode.
 * @stack: Pointer to the head of the stack.
 * @line_number: The current line number in the bytecode file.
 *
 * Description: This function adds the top two elements of the stack.
 * If the stack contains fewer than two elements, it prints an error message
 * and exits.
 */
void add(stack_t **stack, unsigned int line_number)
{
	stack_t *first, *second;
	int sum;

	if (*stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%u: can't add, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}

	first = *stack;
	second = (*stack)->next;

	sum = first->n + second->n;
	second->n = sum;

	*stack = second;
	(*stack)->prev = NULL;

	free(first);
}

/**
 * nop - Handles the nop opcode.
 * @stack: Pointer to the head of the stack.
 * @line_number: The current line number in the bytecode file.
 *
 * Description: This function does nothing. It is used to maintain
 * the structure of the interpreter and handle no-operation commands.
 */
void nop(stack_t **stack, unsigned int line_number)
{
	(void)stack;
	(void)line_number;
}
