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

void	pipex(t_struct **tab, char **parsed_path, char **envp)
{
	int			pipefds[2];
	t_struct	*copy;

	copy = *tab;
	while (copy)
	{
		if (copy->next)
		{
			pipe(pipefds);
			copy->fds[1] = pipefds[1];
			copy->next->fds[0] = pipefds[0];
		}
		copy->child = fork();
		execute_function(copy, parsed_path, envp);
		close(copy->fds[0]);
		close(copy->fds[1]);
		copy = copy->next;
	}
	copy = *tab;
	while (copy)
	{
		waitpid(copy->child, &(copy->wstatus), 0);
		copy = copy->next;
	}
	return ;
}

void	execute_function(t_struct *head, char **parsed_path, char **envp)
{
	char	*path_iteri;
	int		size;

	size = 0;
	if (head->child < 0)
		return (perror("Fork:"));
	if (!(head->child))
	{
		if (dup2(head->fds[0], STDIN_FILENO) < 0)
			perror("dup2 stdin:");
		if (dup2(head->fds[1], STDOUT_FILENO) < 0)
			perror("dup2 stdout:");
		while (*parsed_path)
		{
			size = ft_strlen(*parsed_path);
			if (ft_strncmp(*parsed_path, *(head->cmd), size) != 0)
				path_iteri = ft_strjoin(*parsed_path, *(head->cmd));
			else
				path_iteri = ft_strdup(*(head->cmd));
			execve(path_iteri, head->cmd, envp);
			free(path_iteri);
			(parsed_path)++;
		}
		exit(EXIT_FAILURE);
	}
}

int	all_access_check(t_struct **tab, char **parsed_path)
{
	t_struct	*copy;

	copy = *tab;
	while (copy && access_check(copy->cmd, parsed_path) == 0)
		copy = copy->next;
	if (!copy)
		return (0);
	while (copy)
	{
		if (access_check(copy->cmd, parsed_path) == 1)
			printf("command not found: %s\n", *(copy->cmd));
		copy = copy->next;
	}
	return (close((*tab)->fds[0]), close(sc_lstlast(*tab)->fds[1]), 1);
}

char	**parsing(char *find, char **str)
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
		if (temp)
		{
			tab_temp = ft_split(temp, ':');
			while (tab_temp && tab_temp[k])
				paths[j++] = ft_strjoin(tab_temp[k++], "/");
			ft_free(tab_temp, k);
			free(temp);
		}
		str++;
	}
	paths[j] = '\0';
	return (paths);
}

int	main(int ac, char **ag, char **envp)
{
	int			fd1;
	int			fd2;
	char		**parsed_path;
	t_struct	*elements;

	elements = NULL;
	if (ac > 5 && ft_strncmp(ag[1], "here_doc", 9) == 0)
	{
//		fd1 = open(ag[1], O_CREAT | O_RDWR, 0777);
//		if (fd1 < 0)
//			return (printf("error with creating here_doc\n"), -1);
		fd1 = write_to_file(0, ft_strjoin(ag[2], "\n"), ag[1]);
//		fd1 = open(ag[1], O_RDONLY, 0777);
	}
	else if (ac > 4 && ft_strncmp(ag[1], "here_doc", 9) != 0)
		fd1 = open(ag[1], O_RDONLY);
	else
		return (0);
	if (fd1 < 0)
		return (printf("no such file or directory: %s\n", ag[1]), -1);
	fd2 = open(ag[ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd2 < 0)
		return (printf("error with creating/opening output file\n"), -1);
	parsed_path = parsing("PATH=", envp);
	initialize_lst(&elements, fd1, fd2, ag);
	if (all_access_check(&elements, parsed_path) == 1)
		return (ft_free_lst(elements), glob_free(parsed_path), -1);
	pipex(&elements, parsed_path, envp);
	unlink("here_doc");
	return (ft_free_lst(elements), glob_free(parsed_path), 0);
}

/*
void	display(t_struct *lst)
{
	t_struct	*copy;

	printf("-----lst start-----\n");
	copy = lst;
	while(copy)
	{
		printf("child is: %d\n", copy->child);
		printf("cmd is: %s\n",  *(copy->cmd));
//		printf("wstatus is: %d\n", copy->wstatus);
		printf("read end is: %d\n", copy->fds[0]);
		printf("write end is: %d\n", copy->fds[1]);
		copy = copy->next;
	}
	printf("-----lst end-----\n");
	return ;
}
*/
