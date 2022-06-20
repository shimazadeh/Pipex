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
	char *garb;
	char *cmd[]= {"ls", NULL};
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
//	wstatus = 1000000;
	paths = (char **)malloc (sizeof(char *) * (ft_strlen(*envp) + 1));

	while (envp[i])
	{
		temp = ft_strnstr(envp[i], "PATH=", ft_strlen(envp[i]));
		temp = ft_strtrim(temp, "PATH=");
		if(temp)
		{
			if (ft_strchr(temp, ':'))
			{
				tab_temp = ft_split(temp, ':');
				while (tab_temp[k])
				{
					garb = ft_strjoin(tab_temp[k],"/");
					paths[j] = ft_strdup(garb);
					printf("the assigned path is: %s\n\n", paths[j]);
					k++;
					j++;
					free(garb);
				}
			}
			else
			{
				garb = ft_strjoin(temp,"/");
				paths[j] = ft_strdup(garb);
				free(garb);
				printf("the assigned path is: %s\n\n", paths[j]);
			}
			j++;
			free(temp);
		}
//		free(temp);
		i++;
	}
	paths[j] = '\0';
	j = 0;
	while(paths[j])
	{
		path_iteri = ft_strjoin(paths[j], cmd[0]);
		printf("the path iteri is: %s\n", path_iteri);
	//	execve(paths[j], av, envp);
		printf("the result of execv: %d \n", execve(path_iteri, cmd, envp));
		j++;
	}
	ft_free(paths, j);
	ft_free(tab_temp, k);
//	printf("\n\n");

/*	while (parsed_paths[i])
	{
		printf("parsed path %i is: %s\n", i, parsed_paths[i]);
		i++;
	}
	cmd1 = ft_split(av[2], ' ');
	cmd2 = ft_split(av[3], ' ');
	i = 0;
	while (cmd1[i])
	{
		printf("cmd1 is: %s\n", cmd1[i]);
		i++;
	}
	i = 0;
	while (cmd2[i])
	{
		printf("cmd2 is: %s\n", cmd2[i]);
		i++;
	}*/
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
