#include "monty.h"

/**
* main - function for monty code interpreter
* @argc: argument count
* @argv: argument value
*
* Return : exit success
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