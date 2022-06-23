#ifndef PIPEX_H
# define PIPEX_H

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stddef.h>
#include <stdlib.h>

enum {
	READ_END,
	WRITE_END
};
char	**ft_split(char const *s, char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_strlen(const char *s);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strdup(const char	*src);
char	**ft_free(char **dst, int i);
char	*ft_strchr(const char *s, int c);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strjoin(char const *s1, char const *s2);



void	child1_process(int f1, int f2, char **cmd1, int pipefds[2], char **parsed_path, char **envp);
void	child2_process(int f2, char **cmd2, int pipefds[2], char **parsed_path, char **envp);
void	pipex(int f1, int f2, char **ag, char **parsed_path, char **envp);
char 	**parsing(char *find, char **str);


#endif
