/* $begin shellmain */
#include "csapp.h"
#define MAXARGS   128

#define READ_END 0
#define WRITE_END 1

/* Function prototypes */
void eval(char* cmdline);
int parseline(char* buf, char** argv);
int builtin_command(char** argv);
int changeDirectory(char* args[]);
int calcPipeNum(char* buf);
void evalOnePipe(char* cmdline);
void evalTwoPipe(char* cmdline);
int ARGC;


int changeDirectory(char* args[]) {
	if (args[1] == NULL) {
		int res = chdir(getenv("HOME"));
		return 1;
	}
	else {
		if (chdir(args[1]) == -1) {
			printf(" Enable to move directory : %s\n", args[1]);
			return -1;
		}
		return 0;
	}
}



int main()
{

	char cmdline[MAXLINE];

	while (1) {
		printf("\n");
		memset(cmdline,'\0',sizeof(cmdline));
		printf("MyShell > ");
		Fgets(cmdline, MAXLINE, stdin);
		if (feof(stdin))
			exit(0);
		if (calcPipeNum(cmdline) == 0){
			printf("\n");
			eval(cmdline);
		}
		else if (calcPipeNum(cmdline) == 1){
			printf("\n");
			evalOnePipe(cmdline);
		}
		else if (calcPipeNum(cmdline) == 2){
			printf("\n");
			evalTwoPipe(cmdline);
		}
	}
}
/* $end shellmain */

/* $begin eval */
/* eval - Evaluate a command line */

int calcPipeNum(char* buf) {
	int i = 0, count = 0;
	for (i = 0; i < strlen(buf); i++) {
		if (buf[i] == '|') {
			count++;
		}
	}
	//printf("pipeNum : %d\n", count);
	return count;
}

void evalTwoPipe(char* cmdline) {
	char* argv[MAXARGS]; /* Argument list execve() */
	char buf[MAXLINE];   /* Holds modified command line */
	int bg;              /* Should the job run in bg or fg? */
	pid_t pid;           /* Process id */

	char buf_copy[MAXLINE];
	strcpy(buf_copy, cmdline);


	strcpy(buf, cmdline);
	bg = parseline(buf, argv);
	if (argv[0] == NULL)
		return;   /* Ignore empty lines */


	if (!builtin_command(argv)) {

		printf("Two pipe\n");
		/*
		TODO :
		parse the first args, second args
		Then, we can input them into pipe
		*/

		// hey, we already have *argv[] s, so we can use this

		// we found the index of '|' in argv[] s 

		int pipeIdx1 = 0, pipeIdx2 = 0;
		for (int i = 0; i < ARGC; i++) {
			if (!strcmp(argv[i], "|")) {
				pipeIdx1 = i;
				break;
			}
		}
		//printf("PipeIdx1 : %d\n", pipeIdx1);

		for (int i = pipeIdx1 + 1; i < ARGC; i++) {
			if (!strcmp(argv[i], "|"))
				pipeIdx2 = i;
		}
		//printf("PipeIdx2 : %d\n", pipeIdx2);


		char** firstArgv = (char**)malloc(sizeof(char*) * 16);
		for (int i = 0; i < 16; i++)
			firstArgv[i] = (char*)malloc(sizeof(char) * 32);


		char** secondArgv = (char**)malloc(sizeof(char*) * 16);
		for (int j = 0; j < 16; j++)
			secondArgv[j] = (char*)malloc(sizeof(char) * 32);

		char** thirdArgv = (char**)malloc(sizeof(char*) * 16);
		for (int l = 0; l < 16; l++)
			thirdArgv[l] = (char*)malloc(sizeof(char) * 32);


		for (int i = 0; i < 16; i++)
			memset(firstArgv[i], 0, sizeof(firstArgv[i]));
		for (int j = 0; j < 16; j++)
			memset(secondArgv[j], 0, sizeof(secondArgv[j]));
		for (int k = 0; k < 16; k++)
			memset(thirdArgv[k], 0, sizeof(thirdArgv[k]));


		// let's copy the firstArgv, before the pipeIdx

		for (int i = 0; i < pipeIdx1; i++) {
			strcpy(firstArgv[i], argv[i]);
		}


		// let's copy the secondArgv, after the pipeIdx
		for (int j = pipeIdx1 + 1; j < pipeIdx2; j++) {
			strcpy(secondArgv[j - pipeIdx1 - 1], argv[j]);
		}


		// let's copy the thirdArgv, after the pipeIdx2
		for (int k = pipeIdx2 + 1; k < ARGC; k++) {
			strcpy(thirdArgv[k - pipeIdx2 - 1], argv[k]);
		}

		// so, firstArgv's length equal pipeIdx
		// second Argv's length equal pipeIdx2-pipeIdx-1
		// third Argv's length equal ARGC-pipeIdx2-1
		int firstLen = pipeIdx1;
		int secondLen = pipeIdx2 - pipeIdx1 - 1;
		int thirdLen = ARGC - pipeIdx2 - 1;

		//printf("length of first : %d\n", firstLen);
		//printf("length of second : %d\n", secondLen);
		//printf("length of third : %d\n", thirdLen);

		/*
		for(int i=0;i<16;i++){
			if(firstArgv[i]!=NULL)
				printf("firstArgv[%d] : %s\n",i,firstArgv[i]);
			else
				printf("firstArgv[%d] : NULL\n",i);
		}
		for(int j=0;j<16;j++){
			if(secondArgv[j]!=NULL)
				printf("secondArgv[%d] : %s\n",j,secondArgv[j]);
			else
				printf("secondArgv[%d] : NULL\n",j);
		}
		*/
		char** prog1 = (char**)malloc(sizeof(char*) * (firstLen + 1));
		for (int i = 0; i < firstLen + 1; i++)
			prog1[i] = (char*)malloc(sizeof(char) * 16);
		for (int i = 0; i < firstLen + 1; i++)
			memset(prog1[i], 0, sizeof(prog1[i]));

		char** prog2 = (char**)malloc(sizeof(char*) * (secondLen + 1));
		for (int j = 0; j < secondLen + 1; j++)
			prog2[j] = (char*)malloc(sizeof(char) * 16);
		for (int j = 0; j < secondLen + 1; j++)
			memset(prog2[j], 0, sizeof(prog2[j]));

		char** prog3 = (char**)malloc(sizeof(char*) * (thirdLen + 1));
		for (int k = 0; k < thirdLen + 1; k++)
			prog3[k] = (char*)malloc(sizeof(char) * 16);
		for (int k = 0; k < thirdLen + 1; k++)
			memset(prog3[k], 0, sizeof(prog2[k]));



		for (int i = 0; i < firstLen; i++)
			strcpy(prog1[i], firstArgv[i]);
		for (int j = 0; j < secondLen; j++)
			strcpy(prog2[j], secondArgv[j]);
		for (int k = 0; k < thirdLen; k++)
			strcpy(prog3[k], thirdArgv[k]);

		prog1[firstLen] = NULL;
		prog2[secondLen] = NULL;
		prog3[thirdLen] = NULL;

		/*
			for(int i=0;i<firstLen+1;i++){
				if(prog1[i]!=NULL)
					printf("prog1[%d] : %s\n",i,prog1[i]);
				else
					printf("prog1[%d] : NULL\n",i);
			}

			for(int j=0;j<secondLen+1;j++){
				if(prog2[j]!=NULL)
					printf("prog2[%d] : %s\n",j,prog2[j]);
				else
					printf("prog2[%d] : NULL\n",j);

			for (int k = 0; k < thirdLen + 1; k++) {
				if (prog3[k] != NULL)
					printf("prog3[%d] : %s\n", k, prog3[k]);
				else
					printf("prog3[%d] : NULL\n", k);
		}
		*/


		int fd1[2];
		int fd2[2];
		pipe(fd1);
		pipe(fd2);


		if (Fork() == 0) {
			//printf("First argv\n");
			//close(STDOUT_FILENO);
			dup2(fd1[1], 1);
			close(fd1[0]);
			close(fd1[1]);
			close(fd2[0]);
			close(fd2[1]);
			//execvp(firstArgv[0],firstArgv);
			execvp(prog1[0], prog1);
			perror("exec of first failed\n");
			exit(1);
		}

		if (Fork() == 0) {
			//printf("Second argv\n");
			//close(STDIN_FILENO);
			dup2(fd1[0], 0);
			dup2(fd2[1], 1);
			close(fd1[0]);
			close(fd1[1]);
			close(fd2[0]);
			close(fd2[1]);

			//execvp(secondArgv[0],secondArgv);
			execvp(prog2[0], prog2);
			perror("exec of second failed\n");
			exit(1);
		}


		if (Fork() == 0) {
			//printf("Third argv\n");
			dup2(fd2[0], 0);
			close(fd1[0]);
			close(fd1[1]);
			close(fd2[0]);
			close(fd2[1]);

			execvp(prog3[0], prog3);
			perror("exec of third failed\n");
			exit(1);
		}


		close(fd1[0]);
		close(fd1[1]);
		close(fd2[0]);
		close(fd2[1]);
		/* Parent waits for foreground job to terminate */
		if (!bg) {
			int status;
			if (waitpid(pid, &status, 0) < 0)
				unix_error("waitfg: waitpid error");
		}
		else
			printf("%d %s", pid, cmdline);

	} // end of builtin

	return;
}


void evalOnePipe(char* cmdline) {
	char* argv[MAXARGS]; /* Argument list execve() */
	char buf[MAXLINE];   /* Holds modified command line */
	int bg;              /* Should the job run in bg or fg? */
	pid_t pid;           /* Process id */

	char buf_copy[MAXLINE];
	strcpy(buf_copy, cmdline);



	strcpy(buf, cmdline);
	bg = parseline(buf, argv);
	if (argv[0] == NULL)
		return;   /* Ignore empty lines */


	if (!builtin_command(argv)) {

		//printf("One pipe\n");
		/*
		TODO :
		parse the first args, second args
		Then, we can input them into pipe
		*/

		// hey, we already have *argv[] s, so we can use this

		// we found the index of '|' in argv[] s 

		int pipeIdx = 0;
		for (int i = 0; i < ARGC; i++) {
			if (!strcmp(argv[i], "|"))
				pipeIdx = i;
		}
		//printf("PipeIdx : %d\n", pipeIdx);

		char** firstArgv = (char**)malloc(sizeof(char*) * 16);
		for (int i = 0; i < 16; i++)
			firstArgv[i] = (char*)malloc(sizeof(char) * 32);


		char** secondArgv = (char**)malloc(sizeof(char*) * 16);
		for (int j = 0; j < 16; j++)
			secondArgv[j] = (char*)malloc(sizeof(char) * 32);

		for (int i = 0; i < 16; i++)
			memset(firstArgv[i], 0, sizeof(firstArgv[i]));
		for (int j = 0; j < 16; j++)
			memset(secondArgv[j], 0, sizeof(secondArgv[j]));


		// let's copy the firstArgv, before the pipeIdx

		for (int i = 0; i < pipeIdx; i++) {
			strcpy(firstArgv[i], argv[i]);
		}


		// let's copy the secondArgv, after the pipeIdx

		for (int j = pipeIdx + 1; j < ARGC; j++) {
			strcpy(secondArgv[j - pipeIdx - 1], argv[j]);
		}


		// so, firstArgv's length equal pipeIdx
		// second Argv's length equal ARGC-1-pipeIdx

		int firstLen = pipeIdx;
		int secondLen = ARGC - pipeIdx - 1;

		//printf("length of first : %d\n", firstLen);
		//printf("length of second : %d\n", secondLen);

		/*
		for(int i=0;i<16;i++){
			if(firstArgv[i]!=NULL)
				printf("firstArgv[%d] : %s\n",i,firstArgv[i]);
			else
				printf("firstArgv[%d] : NULL\n",i);
		}
		for(int j=0;j<16;j++){
			if(secondArgv[j]!=NULL)
				printf("secondArgv[%d] : %s\n",j,secondArgv[j]);
			else
				printf("secondArgv[%d] : NULL\n",j);
		}
		*/
		char** prog1 = (char**)malloc(sizeof(char*) * (firstLen + 1));
		for (int i = 0; i < firstLen + 1; i++)
			prog1[i] = (char*)malloc(sizeof(char) * 16);
		for (int i = 0; i < firstLen + 1; i++)
			memset(prog1[i], 0, sizeof(prog1[i]));

		char** prog2 = (char**)malloc(sizeof(char*) * (secondLen + 1));
		for (int j = 0; j < secondLen + 1; j++)
			prog2[j] = (char*)malloc(sizeof(char) * 16);
		for (int j = 0; j < secondLen + 1; j++)
			memset(prog2[j], 0, sizeof(prog2[j]));




		for (int i = 0; i < firstLen; i++)
			strcpy(prog1[i], firstArgv[i]);
		for (int j = 0; j < secondLen; j++)
			strcpy(prog2[j], secondArgv[j]);

		prog1[firstLen] = NULL;
		prog2[secondLen] = NULL;

		/*
		for (int i = 0; i < firstLen + 1; i++) {
			if (prog1[i] != NULL)
				printf("prog1[%d] : %s\n", i, prog1[i]);
			else
				printf("prog1[%d] : NULL\n", i);
		}

		for (int j = 0; j < secondLen + 1; j++) {
			if (prog2[j] != NULL)
				printf("prog2[%d] : %s\n", j, prog2[j]);
			else
				printf("prog2[%d] : NULL\n", j);
		}
		*/



		int fd[2];
		pipe(fd);


		if (Fork() == 0) {
			//printf("First argv\n");
			close(STDOUT_FILENO);
			dup(fd[1]);
			close(fd[0]);
			close(fd[1]);
			//execvp(firstArgv[0],firstArgv);
			execvp(prog1[0], prog1);
			perror("excp of first failed\n");
			exit(1);
		}

		if (Fork() == 0) {
			//printf("Second argv\n");
			close(STDIN_FILENO);
			dup(fd[0]);
			close(fd[1]);
			close(fd[0]);

			//execvp(secondArgv[0],secondArgv);
			execvp(prog2[0], prog2);
			perror("exe of second failed\n");
			exit(1);
		}

		close(fd[0]);
		close(fd[1]);
		/* Parent waits for foreground job to terminate */
		if (!bg) {
			int status;
			if (waitpid(pid, &status, 0) < 0)
				unix_error("waitfg: waitpid error");
		}
		else
			printf("%d %s", pid, cmdline);

	} // end of builtin

	return;
}

void eval(char* cmdline)
{
	char* argv[MAXARGS]; /* Argument list execve() */
	char buf[MAXLINE];   /* Holds modified command line */
	int bg;              /* Should the job run in bg or fg? */
	pid_t pid;           /* Process id */

	char buf_copy[MAXLINE];
	strcpy(buf_copy, cmdline);

	

	strcpy(buf, cmdline);
	bg = parseline(buf, argv);
	if (argv[0] == NULL)
		return;   /* Ignore empty lines */
	if (!builtin_command(argv)) {

		// Not in bulletin, try to run execve
		if ((pid = Fork()) == 0) {   /* Child runs user job */

			//printf("Child forked\n");

			/*
			char* tmp=(char*)malloc(sizeof(char)*16);
			strcpy(tmp,"/bin/");
			strcat(tmp,argv[0]);

			//execve(argv[0],argv,environ);

			for(int i=0;i<10;i++){
				if(argv[i]!=NULL)
					printf("argv[%d] : %s\n",i,argv[i]);
			}
			printf("Res : %d\n\n",execve(tmp,argv,environ));
			if(execve(tmp,argv,environ)<0){
			*/


			//printf("Here!");
			int i,childStat;
			if(!strcmp(argv[0],"exit")){

				printf("Here\n");
				kill(pid,SIGINT);


			}
			else{
				if (execvp(argv[0], argv) < 0) {
					printf("%s: Command not found.\n", argv[0]);
					exit(0);
				}
			}

		} // end of pid=Fork
	/* Parent waits for foreground job to terminate */
		if (!bg) {
			int status;
			if (waitpid(pid, &status, 0) < 0)
				unix_error("waitfg: waitpid error");
		}
		else
			printf("%d %s", pid, cmdline);
	}// end of bulletin

	return;
}

/* If first arg is a builtin command, run it and return true */
int builtin_command(char** argv)
{
	if (!strcmp(argv[0], "quit")) /* quit command */
		exit(0);
	else if (!strcmp(argv[0], "&"))    /* Ignore singleton & */
		return 1;
	else if (!strcmp(argv[0],"exit")){
		return 0;
	}
	else if (!strcmp(argv[0], "cd")) {
		changeDirectory(argv);
		//printf("res : %d\n",changeDirectory(argv));
		return 3;
	}
	return 0;                     /* Not a builtin command */
}
/* $end eval */

/* $begin parseline */
/* parseline - Parse the command line and build the argv array */
int parseline(char* buf, char** argv)
{
	char* delim;         /* Points to first space delimiter */
	int argc;            /* Number of args */
	int bg;              /* Background job? */

	buf[strlen(buf) - 1] = ' ';  /* Replace trailing '\n' with space */
	while (*buf && (*buf == ' ')) /* Ignore leading spaces */
		buf++;

	/* Build the argv list */
	argc = 0;
	while ((delim = strchr(buf, ' '))) {
		argv[argc++] = buf;
		*delim = '\0';
		buf = delim + 1;
		while (*buf && (*buf == ' ')) /* Ignore spaces */
			buf++;
	}
	argv[argc] = NULL;

	if (argc == 0)  /* Ignore blank line */
		return 1;

	/* Should the job run in the background? */
	if ((bg = (*argv[argc - 1] == '&')) != 0)
		argv[--argc] = NULL;

	ARGC = argc;
	return bg;
}
/* $end parseline */


