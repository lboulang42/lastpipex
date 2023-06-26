/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 16:50:30 by lboulang          #+#    #+#             */
/*   Updated: 2023/06/26 18:46:02 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/*
free every malloc assets in t_pipex struct
*/
void	ft_free_pipex(t_pipex *pipex)
{
	if (pipex->cmd_path)
		free(pipex->cmd_path);
	ft_free_tab((void **)pipex->cmd_args);
	ft_free_tab((void **)pipex->env_path);
	free(pipex->pid);
}

/*
to_close = 0 : close link_fd[0]
to_close = 1 : close link_fd[1]
to_close = 2 : close both
*/
void	ft_close_link_fd(t_pipex *pipex, int to_close)
{
	if (to_close == 0 || to_close == 2)
		if (pipex->link_fd[0] > -1)
			close(pipex->link_fd[0]);
	if (to_close == 1 || to_close == 2)
		if (pipex->link_fd[1] > -1)
			close(pipex->link_fd[1]);
}

/*
to_close = 0 : close infile_fd
to_close = 1 : close outfile_fd
to_close = 2 : close both
*/
void	ft_close_inout(t_pipex *pipex, int to_close)
{
	if (to_close == 0 || to_close == 2)
		if (pipex->infile_fd > -1)
			close(pipex->infile_fd);
	if (to_close == 1 || to_close == 2)
		if (pipex->outfile_fd > -1)
			close(pipex->outfile_fd);
}

void	ft_clear_pipex(t_pipex *pipex)
{
	ft_close_link_fd(pipex, 2);
	ft_close_inout(pipex, 2);
	ft_free_pipex(pipex);
}
