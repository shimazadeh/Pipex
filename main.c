#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>


int main (int ac, char **av, char **envp)
{
	int i;
	int	id;
	int wstatus;

	i = 9999;
	wstatus = 1000000;
	id = fork();
	if (id == 0)
	{
		i = 1000;
		printf("adress in child of i = %p\n", &i);
		printf("in child i = %d\n", i);
		printf("IM the child :p\n");
		printf("\n\n");
	}
	else
	{
		waitpid(id, &wstatus, 0);
		printf("adress in parent of i = %p\n", &i);
		printf("in parent i = %d\n", i);
		printf("status = %d\n", wstatus);
		printf("IM the fucking mom\n");
	}
/*
	printf ("hahah I m here\n");
	while (envp[++i])
		printf("line : %d = %s\n",i, envp[i]);

	if (access("file1", F_OK) == 0)
		printf("F_OK;\n");
	else
		printf ("oups\n");
	if (access("file3", F_OK) == 0)
		printf("F_OK;\n");
	else
		printf ("oups\n");
*/
}



int pipefds[2];

open("filetest", O_RDONLY);
pipe(pipefds);
dup(int STDIN);
dup2(STDOUT, pipe write end);
dup2(STDIN, pipe READ end);
fds;
- 0 pipe write end
- 1 STDOUT
- 2 STDERR
- 3 filetest
- 4 pipe read end


