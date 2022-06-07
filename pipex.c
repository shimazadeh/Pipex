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


void	pipex(int f1, int f2)
{
	int 	pipefds[2];
	pid_t	parent;

	pipe(pipefds);
	parent = fork();
	if (parent < 0)
		return (perror("Fork:"));
	if (!parent) //if fork() returns 0 we are in the child process
		child_process(f1, cmd1);
	else
		parent_process(f2, cmd2);
}

void	child_process(f1, cmd1)
{
	dup2(f1, STDIN_FILENO);
	dup2(pipefds[0], STDOUT_FILENO);
	close (pipefds[0]);
	close(f1);
	exit(EXIT_FAILURE);
}

void	parent_process(f2, cmd2)
{
	int wstatus;

	waitpid(id, &wstatus, 0);
	dup2(f2, STDIN_FILENO);
	dup2(pipefds[0], )

}

int	main(int ac, char **ag, char **envp)
{
	int fd1;
	int fd2;

	f1 = open(ag[1], O_RDONLY);
	f2 = open(ag[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (f1 < 0 || f2 < 0)
		return (-1);
	pipex(f1, f2, ag, envp);
	return (0);
}
