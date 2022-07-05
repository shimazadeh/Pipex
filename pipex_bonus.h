/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shabibol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 17:21:35 by shabibol          #+#    #+#             */
/*   Updated: 2022/07/02 17:21:39 by shabibol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stddef.h>
# include <stdlib.h>
# include "get_next_line.h"
# include "Libft/libft.h"

typedef struct s_struct
{
	char				**cmd;
	int					fds[2];
	int					wstatus;
	pid_t				child;
	struct s_struct		*next;

}t_struct;

void		sc_lstadd_back(t_struct **lst, t_struct *new);
void		sc_lstadd_front(t_struct **lst, t_struct *new);
t_struct	*sc_lstlast(t_struct	*lst);
int			sc_lstsize(t_struct *lst);

char		**ft_free(char **dst, int i);

void		pipex(t_struct **tab, char **parsed_path, char **envp);
void		execute_function(t_struct *head, char **parsed_path, char **envp);
char		**parsing(char *find, char **str);
int			access_check(char **cmd, char **parsed_path);
int			all_access_check(t_struct **tab, char **parsed_path);
void		initialize_lst(t_struct **tab, int fd1, int fd2, char **ag);
char		**glob_free(char **dst);
void		ft_free_lst(t_struct *lst);
int			write_to_file(int fd1, char *stop, char	*file_name);
int			file_access_check(char *file1, int fd1, char *file2, int fd2);
int			set_files(int ac, char **ag, int *fds);

#endif
