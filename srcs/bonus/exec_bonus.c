/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 20:59:44 by lboulang          #+#    #+#             */
/*   Updated: 2023/05/14 16:55:48 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_close_fd(t_pipex *pipex, int pwr)
{
	if (pwr >= 8)
	{
		close(pipex->link_fd[1]);
		pwr -= 8;
	}
	if (pwr >= 4)
	{
		close(pipex->link_fd[0]);
		pwr -= 4;
	}
	if (pwr >= 2)
	{
		close(pipex->outfile_fd);
		pwr -= 2;
	}
	if (pwr >= 1)
	{
		close(pipex->infile_fd);
		pwr -= 1;
	}
}

void	ft_free_pipex(t_pipex *pipex)
{
	if (pipex->cmd_path)
		free(pipex->cmd_path);
	ft_free_tab((void **)pipex->cmd_args);
	ft_free_tab((void **)pipex->env_path);
}

void	ft_child1(t_pipex *pipex, char **env)
{
	pipex->pid1 = fork();
	if (pipex->pid1 == 0)
	{
		dup2(pipex->infile_fd, 0);
		dup2(pipex->link_fd[1], 1);
		ft_close_fd(pipex, 13);
		if (pipex->cmd_path && pipex->cmd_args)
			execve(pipex->cmd_path, pipex->cmd_args, env);
		ft_free_pipex(pipex);
		exit(1);
	}
	close(pipex->infile_fd);
	pipex->infile_fd = pipex->link_fd[0];
	close(pipex->link_fd[1]);
	waitpid(pipex->pid1, NULL, 0);
}

void	ft_child2(t_pipex *pipex, char **env, char *str)
{
	pipex->outfile_fd = open(str, O_RDWR | O_CREAT | O_TRUNC, 0666);
	pipex->pid2 = fork();
	if (pipex->pid2 == 0)
	{
		dup2(pipex->infile_fd, 0);
		dup2(pipex->outfile_fd, 1);
		ft_close_fd(pipex, 17);
		if (pipex->cmd_path && pipex->cmd_args)
			execve(pipex->cmd_path, pipex->cmd_args, env);
		ft_free_pipex(pipex);
		exit(1);
	}
	waitpid(pipex->pid2, NULL, 0);
}
/*
if first is here_doc
second is limiter
get next line eveerytime
if !ft_strncmp(limiter, line)
	on a lu tout le heredoc
exec sur here_doc

*/
int	ft_check_heredoc(t_pipex *pipex, char *arg, char *limiter)
{
	if (!ft_strncmp("here_doc", arg, ft_strlen(arg)))
	{
		
		
		return (1);
	}
	return (0);
}

void	ft_exec(t_pipex *pipex, int ac, char **av, char **env)
{
	int	i;

	i = 1;
	pipex->infile_fd = open(av[1], O_RDONLY);
	if (ft_check_heredoc(pipex, av[i], av[i+1]))
		i += 2;
	while (av[++i + 1])
	{
		ft_get_exec_assets(pipex, av[i]);
		pipe(pipex->link_fd);
		if (i < ac - 2)
			ft_child1(pipex, env);
		else
			ft_child2(pipex, env, av[i + 1]);
		if (pipex->cmd_path)
			free(pipex->cmd_path);
		ft_free_tab((void **)pipex->cmd_args);
	}
	ft_close_fd(pipex, 17);
}
