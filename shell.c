#include "shell.h"
/**
 * main - initialize the variables of the program
 * @argc: number of values received from the command line
 * @argv: values received from the command line
 * @env: number of values received from the command line
 * Return: zero on succes.
 */
int main(int ac, char **argv){

	/*Shell prompt*/

	char *prmpt = "(ShellPrmpt$)";
    	char *bufptr = NULL;char *bufptr_cpy = NULL;   /*line pointer*/
	char *complt_command = NULL, *cpy_command = NULL;
	size_t bufsize = 0;
	ssize_t inp_chars; /*Number of chars entered as an input by user*/
	const char *delim = " \n";
	int n_tokens = 0; /*number of tokens*/
	char *token;
	int i;

	/*initilizing Void vars*/

	(void)ac;

	/*add infinite loop to the shell to prevent exit*/

	while(1){
	/*Read command line from user*/

        printf("%s", prmpt);
        inp_chars = getline(&bufptr, &bufsize, stdin);

	/*Prevent CTRL+D user entry*/
	if(inp_chars == -1){
		printf("Quitting shell....\n");
		return (-1);
	}

	/*Space allocation for a copy of the input line*/

	bufptr_cpy = malloc(sizeof(char) *inp_chars);
	if (bufptr_cpy== NULL){
		perror("tsh: memory allocation error");
		return(-1);
	}

	/* Copy buffer line pointer(bufptr) to bufptr_cpy */

	strcpy(bufptr_cpy, bufptr);

	/*Token calculation*/

	token = strtok(bufptr, delim);

	while (token != NULL ){
		n_tokens++;
		token = strtok(NULL, delim);
	}

	n_tokens++;


	/* Allocating space to hold the array of strings */

	argv = malloc(sizeof(char *) * n_tokens);

	/*Storing each token in the argv array*/

	token = strtok(bufptr, delim);

	for(i=0; token != NULL; i++){
		argv[i] = malloc(sizeof(char) * strlen(token));
		strcpy(argv[i], token);

		token = strtok(NULL, delim);
	}
	argv[i] = NULL;

	/* execute the commands with execve */

	execmd(argv);

 	/*printf("%s\n", bufptr);*/

	/* free up allocated memry */

        free(bufptr);
		free(bufptr_cpy);
	}
	return (0);
}
