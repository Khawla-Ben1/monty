#include "monty.h"

/**
 * main - Entry point for the Monty bytecode interpreter.
 * @argc: The number of command-line arguments.
 * @argv: The command-line arguments.
 *
 * Return: EXIT_SUCCESS if the program runs successfully,
 *          or EXIT_FAILURE
 *         if an error occurs
 *
 * Description: This function reads the bytecode file,
 *          processes each line,
 *          and executes the corresponding opcodes.
 */

int main(int argc, char *argv[])
{
	FILE *file;
	char line[256];
	stack_t *stack = NULL;
	unsigned int line_number = 1;

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}
	file = fopen(argv[1], "r");
	if (!file)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	while (fgets(line, sizeof(line), file))
	{
		char *opcode;
		char *line_copy = strdup(line);

		if (line_copy == NULL)
		{
			fprintf(stderr, "Error: malloc failed\n");
			exit(EXIT_FAILURE);
		}

		opcode = strtok(line_copy, " \t\n");
		if (opcode && opcode[0] != '#')
		{
			execute_opcode(opcode, &stack, line_number);
		}

		free(line_copy);
		line_number++;
	}
	fclose(file);
	free_stack(stack);
	return (EXIT_SUCCESS);
}
