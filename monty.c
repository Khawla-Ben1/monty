#include "monty.h"


/* Helper function to free the stack */
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

/* Function to handle the push opcode */
void push(stack_t **stack, unsigned int line_number)
{
    stack_t *new_node;
    char *arg;
    int n;

    arg = strtok(NULL, " \t\n");
    if (arg == NULL || !isdigit(arg[0]))
    {
        fprintf(stderr, "L%u: usage: push integer\n", line_number);
        exit(EXIT_FAILURE);
    }

    n = atoi(arg);
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

/* Function to handle the pall opcode */
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

/* Function to execute an opcode */
void execute_opcode(char *opcode, stack_t **stack, unsigned int line_number)
{
    instruction_t instructions[] = {
        {"push", push},
        {"pall", pall},
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

