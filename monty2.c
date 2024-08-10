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
