#include "monty.h"

/**
 * stack_pstr - Handles the pstr opcode.
 * @stack: Pointer to the head of the stack.
 * @line_number: The current line number in the bytecode file.
 *
 * Description: This function prints the string starting from the top of
 * the stack. The string ends when a 0, a non-printable ASCII value, or
 * the end of the stack is encountered. If the stack is empty, only a new
 * line is printed.
 */
void stack_pstr(stack_t **stack, unsigned int line_number)
{
	stack_t *current = *stack;

	(void)line_number;  // Suppress unused parameter warning

	if (current == NULL)
	{
		printf("\n");
		return;
	}

	while (current != NULL)
	{
		if (current->n == 0 || current->n < 32 || current->n > 126)
			break;

		printf("%c", current->n);
		current = current->next;
	}

	printf("\n");
}

/**
 * stack_rotl - Handles the rotl opcode.
 * @stack: Pointer to the head of the stack.
 * @line_number: The current line number in the bytecode file.
 *
 * Description: This function rotates the stack such that the top element
 * becomes the bottom element and all other elements shift up by one position.
 */
void stack_rotl(stack_t **stack, unsigned int line_number)
{
	stack_t *current = *stack;
	stack_t *top;
	stack_t *bottom;

	(void)line_number;
	if (current == NULL || current->next == NULL)
		return;
	bottom = current;
	while (bottom->next != NULL)
		bottom = bottom->next;
	top = *stack;
	*stack = top->next;
	(*stack)->prev = NULL;
	bottom->next = top;
	top->prev = bottom;
	top->next = NULL;
}


/**
 * stack_rotr - Handles the rotr opcode.
 * @stack: Pointer to the head of the stack.
 * @line_number: The current line number in the bytecode file.
 *
 * Description: This function rotates the stack such that the last element
 * becomes the top element, and all other elements shift down by one position.
 */
void stack_rotr(stack_t **stack, unsigned int line_number)
{
	stack_t *current = *stack;
	stack_t *bottom;

	(void)line_number;

	if (current == NULL || current->next == NULL)
		return;
	bottom = current;
	while (bottom->next != NULL)
		bottom = bottom->next;
	if (bottom == *stack)
		return;
	bottom->prev->next = NULL;
	bottom->prev = NULL;
	bottom->next = *stack;
	(*stack)->prev = bottom;
	*stack = bottom;
}
