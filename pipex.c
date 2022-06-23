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
	pid_t	child1;
	pid_t	child2;
	char	**cmd1;
	char	**cmd2;
	int		wstatus;

	pipe(pipefds);
	cmd1 = ft_split(ag[2], ' ');
	cmd2 = ft_split(ag[3], ' ');
	child1 = fork();
	if (child1 < 0)
		return (perror("Fork:"));
	if (!child1) //if fork() returns 0 we are in the child process
		child1_process(f1, f2, cmd1, pipefds, parsed_path, envp);
	child2 = fork();
	if (child2 < 0)
		return (perror("Fork:"));
	if (!child2)
		child2_process(f2, cmd2, pipefds, parsed_path, envp);
	close(pipefds[0]);
	close(pipefds[1]);
	waitpid(child1, &wstatus, 0);
	waitpid(child2, &wstatus, 0);
	return ;
}

void	child1_process(int f1, int f2, char **cmd1, int pipefds[2], char **parsed_path, char **envp)
{
	char	*path_iteri;
	int		i;
	(void) f2;

	i = 0;
	close(pipefds[0]);
	if (dup2(f1, STDIN_FILENO) < 0)
		perror("dup2 stdin:");
	if (dup2(pipefds[1], STDOUT_FILENO) < 0)
		perror("dup2 stdout:");
	while(parsed_path[i])
	{
//		printf("in the child loop\n");
		path_iteri = ft_strjoin(parsed_path[i],cmd1[0]);
		execve(path_iteri, cmd1, envp);
		free(path_iteri);
		i++;
	}
//	printf("END OF LOOP\n");
	close(pipefds[1]);
	close(f1);
//	close(f2);
	exit(EXIT_FAILURE);
}


void	child2_process(int f2, char **cmd2, int pipefds[2], char **parsed_path, char **envp)
{
	char	*path_iteri;
	int		i;

	close(pipefds[1]);
	if (dup2(f2, STDOUT_FILENO) < 0)
		perror("dup2 stdin parent:");
	if (dup2(pipefds[0], STDIN_FILENO) < 0)
		perror("dup2 stdout parent:");
	i = 0;
	while(parsed_path[i])
	{
		path_iteri = ft_strjoin(parsed_path[i], cmd2[0]);
//		printf("i is %d in the parent loop with path of %s\n", i, path_iteri);
		execve(path_iteri, cmd2, envp);
		free(path_iteri);
		i++;
	}
	close(pipefds[0]);
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
	int		i;

	i = 0;
	fd1 = open(ag[1], O_RDONLY);
	fd2 = open(ag[4], O_CREAT | O_RDWR | O_TRUNC, 777);
	if (fd1 < 0 || fd2 < 0)
		return (-1);
	parsed_path = parsing("PATH=", envp);
	while(parsed_path[i])
	{
//		printf("i is %d with parsed path of: %s\n", i, parsed_path[i]);
		i++;
	}
	pipex(fd1, fd2, ag, parsed_path, envp);
	ft_free(parsed_path, i);
	return (0);
}
