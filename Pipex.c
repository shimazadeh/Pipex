/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shabibol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 19:14:18 by shabibol          #+#    #+#             */
/*   Updated: 2022/07/05 19:14:21 by shabibol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **ag, char **envp)
{
	int			fds[2];
	char		**parsed_path;
	t_struct	*elements;

	elements = NULL;
	if (ac == 5)
	{
		fds[0] = open(ag[1], O_RDONLY);
		fds[1] = open(ag[ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	}
	else
		return (printf("too many arguments\n"),-1);
	if (file_access_check(ag[1], fds[0], ag[ac - 1], fds[1]) == -1)
		return (-1);
	parsed_path = parsing("PATH=", envp);
	initialize_lst(&elements, fds[0], fds[1], ag);
	if (all_access_check(&elements, parsed_path) == 1)
		return (ft_free_lst(elements), glob_free(parsed_path), -1);
	pipex(&elements, parsed_path, envp);
	unlink("here_doc");
	return (ft_free_lst(elements), glob_free(parsed_path), 0);
}
