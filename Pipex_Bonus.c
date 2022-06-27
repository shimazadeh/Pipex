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
#include "pipex_bonus.h"

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

void	pipex(int **tab_fd, char **tab_cmd, char **parsed_path, char **envp)
{
	int 	pipefds[2];
	pid_t	child;

	int		i;
	int		j;
	int		temp;
	int		num_cmds;

	num_cmds = ft_strlen(*ag) - 3;
	i = 0;
	while (tab_fd[i * 2 + 1])
	{
		pipe(tab_fd[i * 2 + 1]);//???
		temp = tab_fd[i * 2 + 1];
		tab_fd[i * 2 + 1] = tab_fd[(i *2 + 1) + 1];
		tab_fd[(i * 2 + 1) + 1] = temp;
		i++;
	}
//	if (all_access_check(cmd1, cmd2, parsed_path) == 1)
//		return ;
	i = 0;
	while (i < num_cmds)
	{
		child = fork();
		if (child < 0)
			return (perror("Fork:"));
		if (!child)
			child_process(tab_fd[i * 2], tab_fd[2 * i + 1], tab_fd[] tab_cmd[i], parsed_path, envp);
		i++;
	}
//	close(pipefds[0]);
	close(pipefds[1]);
	waitpid(child1, &wstatus, 0);
	waitpid(child2, &wstatus, 0);
	glob_free(cmd1);
	glob_free(cmd2);
	return ;
}

void	child_process(int input, int output, int to_close, char **cmd, char **parsed_path, char **envp)
{
	char	*path_iteri;
	int		i;

	i = 0;
	close(to_close);
	if (dup2(input, STDIN_FILENO) < 0)
		perror("dup2 stdin:");
	if (dup2(output, STDOUT_FILENO) < 0)
		perror("dup2 stdout:");
	while(parsed_path[i])
	{
		if (ft_strncmp(parsed_path[i], cmd[0], ft_strlen(parsed_path[i])) == 0)
			execve(cmd[0], cmd, envp);
		else
		{
			path_iteri = ft_strjoin(parsed_path[i],cmd[0]);
			execve(path_iteri, cmd, envp);
			free(path_iteri);
		}
		i++;
	}
	close(output);
	close(input);
	exit(EXIT_FAILURE);
}

int	all_access_check(char **cmd1, char **cmd2, char **parsed_path)
{
	if (access_check(cmd1, parsed_path) == 1 && access_check(cmd2, parsed_path) == 1)
		printf("%s: command not found\n%s: command not found\n", cmd1[0], cmd2[0]);
	else if (access_check(cmd1, parsed_path) == 1)
		printf("%s: command not found\n", cmd1[0]);
	else if (access_check(cmd2, parsed_path) == 1)
		printf("%s: command not found\n", cmd2[0]);
	else
		return (0);
	glob_free(cmd1);
	glob_free(cmd2);
	return (1);
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
				return (0);
		}
		else
		{
			path_iteri = ft_strjoin(parsed_path[i], cmd[0]);
			if (access(path_iteri, F_OK) == 0 && access(path_iteri, X_OK) == 0)
				return (free(path_iteri), 0);
			free(path_iteri);
		}
		i++;
	}
	return (1);
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
		tab_temp = ft_split(temp, ':');//there is a leak here!//
//		display(tab_temp);
		while (tab_temp && tab_temp[k])
		{
			paths[j] = ft_strjoin(tab_temp[k], "/");
			j++;
			k++;
		}
//		ft_free(tab_temp, k);
		glob_free(tab_temp);
		free(temp);
		str++;
	}
	paths[j] = '\0';
	return (paths);
}

int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

int	main(int ac, char **ag, char **envp)
{
	int		fd1;
	int		fd2;
	char	**parsed_path;
	int		*tab_fd;
	int		i;

	fd1 = open(ag[1], O_RDONLY);
	fd2 = open(ag[ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd1 < 0 || fd2 < 0)
		return (-1);
	tab_fd = (int *) malloc(sizeof(int) * (2 * (ac - 3)));	//3 is for name of the exe and two files
	tab_fd[0] = fd1;
	tab_fd[2 * (ac - 3) - 1] = fd2;
	parsed_path = parsing("PATH=", envp);

	i = 2;//the first command always starts at position 2
	while (ag[i] && i < (ac - 3))
	{
		tab_cmd[i - 2] = ft_split(ag[i], ' ');
		i++;
	}
	pipex(tab_fd, tab_cmd, parsed_path, envp);
	glob_free(parsed_path);
	return (0);
}
