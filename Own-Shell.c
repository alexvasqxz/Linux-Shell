// 
//  Gustavo_shell.c
//  
//  This program written in C when run on terminal
//  creates an own shell that reads the input specified
//  by the user and executes a process using the fork()
//  system call each time a new command line "process
//   is called
//
//   Created on 9/13/20
//   Copyright © 2020 Gustavo Vasquez. All rights reserved
//
//           ___________________________________
//          |                                   |
//          |              WELCOME              |
//          |               TO MY               |
//          |                OWN                |
//          |               SHELL               |
//          |                                   |
//          |          -Gustavo Vasquez         |
//          |      - USE AT YOUR OWN RISK       |
//          |___________________________________|

  
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define BUFFSIZE 1024
#define TOKSIZE 64
#define LINEDELIMITER " \t\r\n\a"

/*///////////////////////////////////////////////////
// readCommandLine
// This function reads the line that is entered by 
// the user as an input
//
// Parameters: None
//
// Return: A string entered by the user in the 
// command line
*////////////////////////////////////////////////////
char *readCommandLine()
{
	int bufsize = BUFFSIZE;
	int pos = 0;
	char *buffer = malloc(sizeof(char) * bufsize);
	int c;
	
	if (!buffer){
		fprintf(stderr, "An error has ocurred :( \n");
		exit(EXIT_FAILURE);
	}
	
	while(1){
		c = getchar();
		
		if (c == EOF || c == '\n'){
			buffer[pos] = '\0';
			return buffer;
		}
		else{
			buffer[pos] = c;
		}
		
		pos++;
		
		if (pos >= bufsize){
			bufsize += BUFFSIZE;
			buffer = realloc(buffer, bufsize);
			if (!buffer){
				fprintf(stderr, "An error has ocurred :( \n");
				exit(EXIT_FAILURE);
			}
		}
	}
}

/*///////////////////////////////////////////////////
// parseLine
// This function takes the line that was previosuly
// read and splits it
//
// Parameters: A string obtainer previously from the
// readCommandLine function
//
// Return: An array of strings, hence, the splitted
// string
*////////////////////////////////////////////////////
char **parseLine(char *line)
{
	int size = TOKSIZE;
	int pos = 0;
	char **tokens = malloc(size * sizeof(char*));
	char *token;
	
	if(!tokens){
		fprintf(stderr, "An error has ocurred :( \n");
		exit(EXIT_FAILURE);
	}
	
	token = strtok(line, LINEDELIMITER);
	while(token != NULL){
		tokens[pos] = token;
		pos++;
		
		if(pos>=size){
			size += TOKSIZE;
			tokens = realloc(tokens, size * sizeof(char*));
			
			if(!tokens){
				fprintf(stderr, "An error has ocurred :( \n");
				exit(EXIT_FAILURE);
			}
		}
		
		token = strtok(NULL, LINEDELIMITER);
	}
	
	tokens[pos] = NULL;
	return tokens;
}

/*///////////////////////////////////////////////////
// childProcess
// This function creates a child process using the 
// fork() system call, then if the forking is succesful
// it executes the process that the user typed in
// the command line
//
// Parameters: An array of strings obtained in the
// the previous function (parseLine)
//
// Return: An integer value wether the process
// was succesful or not
*////////////////////////////////////////////////////
int childProcess(char **args)
{
	pid_t pid, wpid;
	int status;
	
	pid = fork();
	
	if (pid == 0){
		// We are in the child process
		if(execvp(args[0], args) == -1){
			perror("lsh");
		}
		exit(EXIT_FAILURE);
		
	}
	else if (pid < 0){
		// Error while forking
		perror("lsh");
	}
	else{
		// We are inside the parent process pid > 0
		
		do{
			wpid = waitpid(pid, &status, WUNTRACED);
		}
		while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	
	return 1;
}

/*///////////////////////////////////////////////////
// exeCommands
// This function has "extra" functions that can be 
// useful in the created shell
//
// Parameters: An array of strings obtained in the
// parseLine function
//
// Return: An integer value wether there was a
// process executed or not
*////////////////////////////////////////////////////
int exeCommands(char** args)
{
	int Number = 2, i, switchArg = 0;
	char* commList[Number];
	char* user;

	commList[0] = "exit";
	commList[1] = "hello";

	for (i = 0; i < Number; i++){
		if(strcmp(args[0], commList[i]) == 0){
			switchArg = i+1;
			break;
		}
	}
	
	switch(switchArg){
		case 1:
			printf("\n Come back soon! Goodbye \n");
			exit(0);
		case 2:
			user = getenv("USER");
			printf("\n Hello %s! \n You should know this is no place for Newbies to play around, be careful \n", user);
			return 1;
		default:
			break;
	}
	return 0;
}

/*///////////////////////////////////////////////////
// execute
// This function executes the process typed in the
// command line calling the childProcess function
//
// Parameters: An array of strings
//
// Return: An integer value obtained by calling the
// childProcess function
*////////////////////////////////////////////////////
int execute(char **args)
{
	
	if(args[0] == NULL){
		return 1;
	}
	
	return childProcess(args);
}

/*///////////////////////////////////////////////////
// init_shell
// This function calls all the other functions as 
// long as the user keeps typing on the command line
//
// Parameters: None
//
// Return: Nothing, this is a void function
*////////////////////////////////////////////////////
void init_shell()
{
	char *line;
	char **args;
	int status;
	
	do {
		printf("Gus' Shell >>> ");
		line = readCommandLine();
		args = parseLine(line);
		status = execute(args);
		
		free(line);
		free(args);
	}
	while (status);
}

int main(int argc, char **argv){
	printf("\nHello there:) Welcome to my own shell, have fun! \n");
	init_shell();
	
	return EXIT_SUCCESS;
}
			
	

