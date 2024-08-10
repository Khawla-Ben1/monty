#include "monty.h"


/**
 * sub - Handles the sub opcode.
 * @stack: Pointer to the head of the stack.
 * @line_number: The current line number in the bytecode file.
 *
 * Description: This function subtracts the top element from the second top element
 * of the stack. If the stack contains fewer than two elements, it prints an error message
 * and exits.
 */
void sub(stack_t **stack, unsigned int line_number)
{
	stack_t *first, *second;
	int difference;

	if (*stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%u: can't sub, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}

	first = *stack;
	second = (*stack)->next;

	difference = second->n - first->n;
	second->n = difference;

	*stack = second;
	(*stack)->prev = NULL;

	free(first);
}

/**
 * mul - Handles the mul opcode.
 * @stack: Pointer to the head of the stack.
 * @line_number: The current line number in the bytecode file.
 *
 * Description: This function multiplies the top element of the stack
 * with the second top element. If the stack contains fewer than two
 * elements, it prints an error message and exits.
 */
void mul(stack_t **stack, unsigned int line_number)
{
	stack_t *first, *second;
	int product;

	if (*stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%u: can't mul, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}

	first = *stack;
	second = (*stack)->next;

	product = second->n * first->n;
	second->n = product;

	*stack = second;
	(*stack)->prev = NULL;

	free(first);
}
