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

void	pipex(int f1, int f2, char **ag, char **parsed_path)
{
	int 	pipefds[2];
	pid_t	parent;
	char	**cmd1;
	char	**cmd2;

	pipe(pipefds);
	cmd1 = ft_split(ag[2], " ");
	cmd2 = ft_split(ag[3], " ");
	parent = fork();
	if (parent < 0)
		return (perror("Fork:"));
	if (!parent) //if fork() returns 0 we are in the child process
		child_process(f1, cmd1, pipefds, parsed_path, ag);
	else
		parent_process(f2, cmd2, pipefds, parsed_path, ag);
}

void	child_process(int f1, char **cmd1, int pipefds[2], char **parsed_path, char **ag)
{
	char	*path_iteri;
	int		i;

	dup2(f1, STDIN_FILENO);
	dup2(pipefds[1], STDOUT_FILENO);
	i = 0;
	while(parsed_path[i])
	{
		path_iteri = ft_strjoin(parsed_path[i],ag[2]);
		execve(path_iteri, cmd1, envp);
		i++;
	}
	close(pipefds[1]);
	close(f1);
	exit(EXIT_FAILURE);
}

void	parent_process(int f2, char **cmd2, int pipefds[2], char **parsed_path, char **ag)
{
	int wstatus;

	waitpid(id, &wstatus, 0);
	dup2(pipefds[0], STDIN_FILENO);
	dup2(f2, STDOUT_FILENO);
	i = 0;
	while(parsed_path[i])
	{
		path_iteri = ft_strjoin(parsed_path[i], ag[3]);
		execve(path_iteri, cmd2, envp);
		i++;
	}
	close(pipefds[0]);
	close(f2);
	exit(EXIT_FAILURE);
}

int	main(int ac, char **ag, char **envp)
{
	int		fd1;
	int		fd2;
	char	*PATH;
	char	**parsed_path;


	f1 = open(ag[1], O_RDONLY);
	f2 = open(ag[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (f1 < 0 || f2 < 0)
		return (-1);
//parsing
//	PATH = ft_substr(envp[23], 5, (ft_strlen(envp[23])));
//	PATH = ft_strnstr(envp, 'PATH')
	parsed_path = ft_split(PATH, ':');
//
	pipex(f1, f2, ag, parsed_path);
	return (0);
}
