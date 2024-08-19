### Functions to be Used

**1. readline**
```
char *readline(const char *prompt)
```
**Purpose:** It reads a line of text from the user input, typically from the terminal and returns a pointer to a dynamically allocated string containing that line. It does not modify or transform the input but simply returns it as-is.\
**Parameters:**\
prompt: A string that is displayed to the user before input is taken.\
**Returns:**\
-A pointer to the line read from input, which is allocated dynamically (you need to free it).\
-NULL if an error occurs or EOF is reached.\
**Basic use of readline**
compile with flag -lreadline
``` c
#include <readline/readline.h>

int main(int argc, char **argv, char **envp)
{
	char *input;
	input = readline("minishell:");
	if (input != NULL)
	{
		//process it here
		free(input);
	}
}
```
This will be used to make a prompt, waiting for commands.\
For multiple lines, we will put it in  an infinite loop.\