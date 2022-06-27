#ifndef PIPEX_H
# define PIPEX_H

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stddef.h>
#include <stdlib.h>

typedef

char	**ft_split(char const *s, char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_strlen(const char *s);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strdup(const char	*src);
char	**ft_free(char **dst, int i);
char	*ft_strchr(const char *s, int c);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strjoin(char const *s1, char const *s2);
int	ft_strncmp(const char *s1, const char *s2, size_t n);

void	child_process(int input, int output, int to_close, char **cmd, char **parsed_path, char **envp);

void	pipex(int f1, int f2, char **ag, char **parsed_path, char **envp);
char 	**parsing(char *find, char **str);
int		access_check(char **cmd, char **parsed_path);
int		all_access_check(char **cmd1, char **cmd2, char **parsed_path);

char	**glob_free(char **dst);


void	display(char **str);

#endif