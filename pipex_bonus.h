#ifndef PIPEX_H
# define PIPEX_H

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stddef.h>
#include <stdlib.h>
#include "get_next_line.h"

typedef	struct	s_struct
{
	char				**cmd;
	int					fds[2];//0 is the read end, 1 is the write end
	int					wstatus;
	pid_t				child;
	struct	s_struct	*next;

}t_struct;

char	**ft_split(char const *s, char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_strlen(const char *s);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strdup(const char	*src);
char	**ft_free(char **dst, int i);
char	*ft_strchr(const char *s, int c);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

int		ft_max(int a, int b);

void		ft_lstadd_back(t_struct **lst, t_struct *new);
void		ft_lstadd_front(t_struct **lst, t_struct *new);
t_struct	*ft_lstlast(t_struct	*lst);
int			ft_lstsize(t_struct *lst);


void	execute_function(t_struct *head, char **parsed_path, char **envp);

void	pipex(t_struct **tab, char **parsed_path, char **envp);
char 	**parsing(char *find, char **str);
int		access_check(char **cmd, char **parsed_path);
int		all_access_check(t_struct **tab, char **parsed_path);

void	initialize_lst(t_struct **tab, int fd1, int fd2, char **ag);

char	**glob_free(char **dst);

//bonus related

void	write_to_temp(int fd1);

void	display(t_struct *lst);

#endif
