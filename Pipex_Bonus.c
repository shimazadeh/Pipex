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

void	ft_free_lst(t_struct *lst)
{
	t_struct	*tmp;

	if (!lst)
		return ;
	while (lst)
	{
		glob_free(lst->cmd);
		tmp = lst;
		lst = lst->next;
		free(tmp);
	}
	return ;
}
void	ft_close(t_struct **lst, int position)
{
	int	i;
	t_struct *copy;

	copy = *lst;
	i = 0;
	while (copy && i < (position - 1))
	{
		copy = copy->next;
		i++;
	}
	close(copy->fds[0]);
	close(copy->fds[1]);
	return;
}

void	pipex(t_struct **tab, int fd1, int fd2, char **parsed_path, char **envp)
{
	int			pipefds[2];
	t_struct	*copy;
//	int			wstatus;
	int			i;

	i = 0;
	copy = *tab;
//	if (all_access_check(tab, parsed_path) == 1)
//		return ;
	while(copy)
	{
		if (copy->next)
		{
			pipe(pipefds);
			close(pipefds[0]);
			copy->fds[1] = pipefds[1];
			copy->next->fds[0] = copy->fds[1];
		}
		else
			copy->fds[1] = fd2;
		if (i == 0)
			copy->fds[0] = fd1;
		copy->child = fork();
		if (copy->child < 0)
			return (perror("Fork:"));
		if (!(copy->child))
			child_process(*tab, i, parsed_path, envp);
		copy = copy->next;
		i++;
	}
	display(*tab);
	copy = *tab;
	while (copy)
	{
//		display(*tab);
		waitpid(copy->child, &(copy->wstatus), 0);
		copy = copy->next;
	}
	return ;
}

void	child_process(t_struct *head, int j, char **parsed_path, char **envp)
{
	char	*path_iteri;
	int		i;
	(void)	j;
	i = 0;

	if (dup2(head->fds[0], STDIN_FILENO) < 0)
		perror("dup2 stdin:");
	printf("the value of child: %d\n", head->child);
//	if (dup2(head->fds[1], STDOUT_FILENO) < 0)
//		perror("dup2 stdout:");
	while(parsed_path[i])
	{
		if (ft_strncmp(parsed_path[i], *(head->cmd), ft_strlen(parsed_path[i])) == 0)
			execve(*(head->cmd), head->cmd, envp);
		else
		{
			path_iteri = ft_strjoin(parsed_path[i],*(head->cmd));
			execve(path_iteri, head->cmd, envp);
			free(path_iteri);
		}
		i++;
	}
	close(head->fds[0]);
	close(head->fds[1]);
	exit(EXIT_FAILURE);
}

int	all_access_check(t_struct *tab, char **parsed_path)
{
	t_struct	*tab_copy;

	tab_copy = tab;
	while (tab_copy && access_check(tab_copy->cmd, parsed_path) == 0)
		tab_copy = tab_copy->next;
	if (!tab_copy)
		return (0);
	while (tab_copy)
	{
		if (access_check(tab_copy->cmd, parsed_path) == 1)
			printf("%s: command not found\n", *(tab_copy->cmd));
		tab_copy = tab_copy->next;
	}
	//free the cmds?
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

void	initialize_lst(t_struct **tab, char **ag)
{
	t_struct 	*copy;
	int			i;

	i = 2;//the first command always starts at position 2
	while (ag[i + 1]) //last command is the file output
	{
		copy = (t_struct *) malloc(sizeof(t_struct));
		copy->cmd = ft_split(ag[i], ' ') ;
		copy->next = NULL;
		ft_lstadd_back(tab, copy);
		i++;
		copy = copy->next;
	}
	return ;
}

int	main(int ac, char **ag, char **envp)
{
	int			fd1;
	int			fd2;
	char		**parsed_path;
	t_struct	*elements;
	(void)envp;

	fd1 = open(ag[1], O_RDONLY);
	fd2 = open(ag[ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd1 < 0 || fd2 < 0)
		return (-1);
//	printf("the value of fd1 and fd2: %d, %d\n", fd1, fd2);
	parsed_path = parsing("PATH=", envp);
	elements = NULL;


	initialize_lst(&elements, ag);
//	display(tab);



	pipex(&elements, fd1, fd2, parsed_path, envp);
//	display(elements);
//	glob_free(parsed_path);
//	ft_free(tab);
	return (0);
}

void	display(t_struct *lst)
{
	t_struct	*copy;

	printf("-----lst start-----\n");
	copy = lst;
	while(copy)
	{
		printf("child is: %d\n", copy->child);
		printf("cmd is: %s\n",  *(copy->cmd));
		printf("wstatus is: %d\n", copy->wstatus);
		printf("read end is: %d\n", copy->fds[0]);
		printf("write end is: %d\n", copy->fds[1]);
		copy = copy->next;
	}
	printf("-----lst end-----\n");
	return ;
}
