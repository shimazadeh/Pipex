#include "pipex.h"

int main (int ac, char **av, char **envp)
{
	(void)av;
	(void)ac;
	int	i;
//	int	id;
//	int wstatus;
	char **paths;
	char **tab_temp;
	char *temp;
	char *path_iteri;
	char *cmd[]= {"wc", NULL};
	int	j;

	i = 0;
	j = 0;
//	wstatus = 1000000;
	paths = (char **)malloc (sizeof(char *) * (ft_strlen(*envp) + 1));
	while (envp[i])
	{
		temp = ft_strnstr(envp[i], "PATH=", ft_strlen(envp[i]));
		temp = ft_strtrim(temp, "PATH=");
		if(temp)
		{
			tab_temp = ft_split(temp, ':');
			while (tab_temp[j])
			{
				paths[j] = ft_strdup(ft_strjoin(tab_temp[j], "/"));
				printf("the assigned path is: %s\n\n", paths[j]);
				j++;
			}
		}
		free(temp);
		i++;
	}
	paths[j] = '\0';
	j = 0;
	while(paths[j])
	{
		path_iteri = ft_strjoin(paths[j], "wc");
		printf("the path iteri is: %s\n", path_iteri);
		printf("the result of execv: %d \n", execve(path_iteri, cmd, envp));
		j++;
	}
	ft_free(paths, j);
	ft_free(tab_temp, j);
	return (0);
/*
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
*/
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


/*
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


*/


/* what I had originally:
<<<<<<< HEAD

	//	child1_process(f1, cmd1, pipefds, parsed_path, envp);
	//	child2_process(f2, cmd2, pipefds, parsed_path, envp);


=======
>>>>>>> 729b84fb0363e4b4fb3fde4980839ea7ea5b41bc
void	child1_process(int f1, int f2, char **cmd1, int pipefds[2], char **parsed_path, char **envp)
{
	char	*path_iteri;
	int		i;
	(void) f2;

	i = 0;
	close(pipefds[0]);
	if (dup2(f1, STDIN_FILENO) < 0)
		perror("dup2 stdin cmd1:");
	if (dup2(pipefds[1], STDOUT_FILENO) < 0)
		perror("dup2 stdout cmd1:");
	while(parsed_path[i])
	{
		if (ft_strncmp(parsed_path[i], cmd1[0], ft_strlen(parsed_path[i])) == 0)
			execve(cmd1[0], cmd1, envp);
		else
		{
			path_iteri = ft_strjoin(parsed_path[i],cmd1[0]);
			execve(path_iteri, cmd1, envp);
			free(path_iteri);
		}
		i++;
	}
	close(pipefds[1]);
	close(f1);
	exit(EXIT_FAILURE);
}

void	child2_process(int f2, char **cmd2, int pipefds[2], char **parsed_path, char **envp)
{
	char	*path_iteri;
	int		i;

	close(pipefds[1]);
	if (dup2(f2, STDOUT_FILENO) < 0)
		perror("dup2 stdin cmd2:");
	if (dup2(pipefds[0], STDIN_FILENO) < 0)
		perror("dup2 stdout cmd2:");
	i = 0;
	while(parsed_path[i])
	{
		if (ft_strncmp(parsed_path[i], cmd2[0], ft_strlen(parsed_path[i])) == 0)
			execve(cmd2[0], cmd2, envp);
		else
		{
			path_iteri = ft_strjoin(parsed_path[i], cmd2[0]);
			execve(path_iteri, cmd2, envp);
			free(path_iteri);
		}
		i++;
	}
	close(pipefds[0]);
	close(f2);
	exit(EXIT_FAILURE);
	*/
