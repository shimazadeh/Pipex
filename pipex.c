/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shabibol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 17:38:31 by shabibol          #+#    #+#             */
/*   Updated: 2022/06/07 17:38:33 by shabibol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

void	pipex(int f1, int f2, char **ag, char **parsed_path, char **envp)
{
	int 	pipefds[2];
	pid_t	parent;
	char	**cmd1;
	char	**cmd2;
	int		wstatus;

	pipe(pipefds);
	cmd1 = ft_split(ag[2], ' ');
	cmd2 = ft_split(ag[3], ' ');
	parent = fork();
	if (parent < 0)
		return (perror("Fork:"));
	printf("the value of parent: %d\n", parent);
	if (!parent) //if fork() returns 0 we are in the child process
	{
		child_process(f1, cmd1, pipefds, parsed_path, envp);
		printf("the value of parent for child process is %d\n", parent);
	}
	else
	{
		printf("the value of parent for parent process is %d\n", parent);
		waitpid(parent, &wstatus, 0);
		parent_process(f2, cmd2, pipefds, parsed_path, envp);
		printf("parent process finished\n");
	}
}

void	child_process(int f1, char **cmd1, int pipefds[2], char **parsed_path, char **envp)
{
	char	*path_iteri;
	int		i;

	i = 0;
	dup2(STDIN_FILENO, f1);
	dup2(STDOUT_FILENO, pipefds[1]);
	while(parsed_path[i])
	{
		path_iteri = ft_strjoin(parsed_path[i],cmd1[0]);
		execve(path_iteri, cmd1, envp);
		i++;
	}
	close(pipefds[0]);
	close(f1);
	exit(EXIT_FAILURE);
}

void	parent_process(int f2, char **cmd2, int pipefds[2], char **parsed_path, char **envp)
{
	char	*path_iteri;
	int		i;

	dup2(STDOUT_FILENO, f2);
	dup2(STDIN_FILENO, pipefds[0]);
	i = 0;
	while(parsed_path[i])
	{
		path_iteri = ft_strjoin(parsed_path[i], cmd2[0]);
		execve(path_iteri, cmd2, envp);
		i++;
	}
	close(pipefds[1]);
	close(f2);
	exit(EXIT_FAILURE);
}

char **parsing(char *find, char **str)
{
	char	**paths;
	char	*temp;
	char	**tab_temp;
	int		j;
	int		k;

	j = 0;
	paths = (char **)malloc (sizeof(char *) * (ft_strlen(*str) + 1));
	while (*str)
	{
		k = 0;
		temp = ft_strtrim(ft_strnstr(*str, find, ft_strlen(*str)), find);
//		if (temp)
//		{
		tab_temp = ft_split(temp, ':');
		while (tab_temp && tab_temp[k])
		{
		//	printf("the value of k is %d\n", k);
			paths[j] = ft_strjoin(tab_temp[k], "/");
			j++;
			k++;
		}
		ft_free(tab_temp, k);
//		}
		free(temp);
		str++;
	}
	paths[j] = '\0';
	return (paths);
}

int	main(int ac, char **ag, char **envp)
{
	(void)ac;
	(void)ag;
	int		fd1;
	int		fd2;
	char	**parsed_path;

	fd1 = open(ag[1], O_RDONLY);
	fd2 = open(ag[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd1 < 0 || fd2 < 0)
		return (-1);
	parsed_path = parsing("PATH=", envp);
/*	while(parsed_path[i])
	{
		printf("parsed path is: %s\n", parsed_path[i]);
		i++;
	}*/
	pipex(fd1, fd2, ag, parsed_path, envp);
	ft_free(parsed_path, ft_strlen(*parsed_path));
	return (0);
}
