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

char	**glob_free(char **dst)
{
	int	i;

	i = 0;
	while (dst && dst[i])
		i++;
	while (i > 0)
	{
		i--;
		free((void *)dst[i]);
	}
	free (dst);
	return (NULL);
}

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
	if (access_check(cmd1, parsed_path) == 0)
	{
		printf("%s: command not found\n", cmd1[0]);
		glob_free(cmd1);
		glob_free(cmd2);
		return ;
	}
	if (access_check(cmd2, parsed_path) == 0)
	{
		printf("%s: command not found\n", cmd2[0]);
		glob_free(cmd1);
		glob_free(cmd2);
		return ;
	}
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
	glob_free(cmd1);
	glob_free(cmd2);
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
//	close(f2);
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
}

int	access_check(char **cmd, char **parsed_path)
{
	int		i;
	char	*path_iteri;

	i = 0;
	while (parsed_path[i])
	{
		if (ft_strncmp(parsed_path[i], cmd[0], ft_strlen(parsed_path[i])) == 0)
		{
			if (access(cmd[0], F_OK) == 0 && access(cmd[0], X_OK) == 0)
				return (1);
		}
		else
		{
			path_iteri = ft_strjoin(parsed_path[i], cmd[0]);
			if (access(path_iteri, F_OK) == 0 && access(path_iteri, X_OK) == 0)
				return (free(path_iteri), 1);
			free(path_iteri);
		}
		i++;
	}
	return (0);
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
		tab_temp = ft_split(temp, ':');//there is a leak here!
//		display(tab_temp);
		while (tab_temp && tab_temp[k])
		{
			paths[j] = ft_strjoin(tab_temp[k], "/");
			j++;
			k++;
		}
		ft_free(tab_temp, k);
//		glob_free(tab_temp);
		free(temp);
		str++;
	}
	paths[j] = '\0';
	return (paths);
}

void	display(char **str)
{
	int i;

	i = 0;
	while (str && str[i])
	{
		printf("%s", str[i]);
		i++;
	}
	printf("\n");
}

int	main(int ac, char **ag, char **envp)
{
	(void)ac;
	int		fd1;
	int		fd2;
	char	**parsed_path;

	fd1 = open(ag[1], O_RDONLY);
	fd2 = open(ag[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd1 < 0 || fd2 < 0)
		return (-1);
	parsed_path = parsing("PATH=", envp);
	pipex(fd1, fd2, ag, parsed_path, envp);
	glob_free(parsed_path);
	return (0);
}
