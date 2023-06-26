/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 20:59:44 by lboulang          #+#    #+#             */
/*   Updated: 2023/06/26 18:23:55 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_child1(t_pipex *pipex, char **env, int index)
{
	pipex->pid[index] = fork();
	if (pipex->pid[index] == 0)
	{
		if (pipex->infile_fd > -1)
		{
			dup2(pipex->infile_fd, 0);
			dup2(pipex->link_fd[1], 1);
			ft_close_link_fd(pipex, 2);
			ft_close_inout(pipex, 0);
			if (pipex->cmd_path && pipex->cmd_args)
				execve(pipex->cmd_path, pipex->cmd_args, env);
		}
		else
			ft_close_link_fd(pipex, 2);
		ft_free_pipex(pipex);
		exit(127);
	}
	ft_close_inout(pipex, 0);
	pipex->infile_fd = pipex->link_fd[0];
	ft_close_link_fd(pipex, 1);
}

void	ft_child2(t_pipex *pipex, char **env, char *out_path, int index)
{
	pipex->outfile_fd = open(out_path, O_RDWR | O_CREAT | O_TRUNC, 0666);
	pipex->pid[index] = fork();
	if (pipex->pid[index] == 0)
	{
		if (pipex->outfile_fd == -1)
		{
			ft_printf("Pipex: %s %s\n", out_path, ERR_NOSUCHF);
			ft_clear_pipex(pipex);
			exit(1);
		}
		dup2(pipex->infile_fd, 0);
		dup2(pipex->outfile_fd, 1);
		ft_close_link_fd(pipex, 2);
		ft_close_inout(pipex, 2);
		if (pipex->cmd_path && pipex->cmd_args)
			execve(pipex->cmd_path, pipex->cmd_args, env);
		ft_free_pipex(pipex);
		exit(127);
	}
}

void	ft_wait_pid(t_pipex *pipex, int limit)
{
	int	i;
	int	wstatus;

	i = -1;
	while (++i < limit)
	{
		waitpid(pipex->pid[i], &wstatus, 0);
		if (WIFEXITED(wstatus))
			pipex->exit_code = WEXITSTATUS(wstatus);
	}
}

/*
Open infile O_RDONLY (check if file is accessible)
*/
void	ft_exec(t_pipex *pipex, int ac, char **av, char **env)
{
	int	i;

	i = 1;
	pipex->infile_fd = open(av[1], O_RDONLY);
	if (pipex->infile_fd < 0)
		ft_printf("Pipex: %s: %s\n", av[1], ERR_NOSUCHF);
	while (av[++i + 1])
	{
		ft_get_exec_assets(pipex, av[i]);
		pipe(pipex->link_fd);
		if (i < ac - 2)
			ft_child1(pipex, env, i - 2);
		else
			ft_child2(pipex, env, av[i + 1], i - 2);
		free(pipex->cmd_path);
		ft_free_tab((void **)pipex->cmd_args);
	}
	ft_wait_pid(pipex, i - 2);
	ft_close_inout(pipex, 2);
	ft_close_link_fd(pipex, 2);
}
