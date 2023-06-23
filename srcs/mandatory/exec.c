/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 20:59:44 by lboulang          #+#    #+#             */
/*   Updated: 2023/06/23 13:51:19 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// void	ft_close_fd(t_pipex *pipex, int pwr)
// {
// 	if (pwr >= 8)
// 	{
// 		close(pipex->link_fd[1]);
// 		pwr -= 8;
// 	}
// 	if (pwr >= 4)
// 	{
// 		close(pipex->link_fd[0]);
// 		pwr -= 4;
// 	}
// 	if (pwr >= 2)
// 	{
// 		close(pipex->outfile_fd);
// 		pwr -= 2;
// 	}
// 	if (pwr >= 1)
// 	{
// 		close(pipex->infile_fd);
// 		pwr -= 1;
// 	}
// }

void	ft_free_pipex(t_pipex *pipex)
{
	if (pipex->cmd_path)
		free(pipex->cmd_path);
	ft_free_tab((void **)pipex->cmd_args);
	ft_free_tab((void **)pipex->env_path);
}

void ft_close_link_fd(t_pipex *pipex, int to_close)
{
	if (to_close < 0 || to_close > 2)
		return ((void)ft_printf("tu veux close quoi fdp 1\n"));
	if (to_close == 0 || to_close == 2)
		if (pipex->link_fd[0] > -1)
			close(pipex->link_fd[0]);
	if (to_close == 1 || to_close == 2)
		if (pipex->link_fd[1] > -1)
			close(pipex->link_fd[1]);
}

void ft_close_inout(t_pipex *pipex, int to_close)
{
	if (to_close < 0 || to_close > 2)
		return ((void)ft_printf("tu veux close quoi fdp 2\n"));
	if (to_close == 0 || to_close == 2)
		if (pipex->infile_fd > -1)
			close(pipex->infile_fd);
	if (to_close == 1 || to_close == 2)
		if (pipex->outfile_fd > -1)
			close(pipex->outfile_fd);
}

void	ft_child1(t_pipex *pipex, char **env)
{
	pipex->pid1 = fork();
	if (pipex->pid1 == 0)
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
		exit(1);
	}
	ft_close_inout(pipex, 0);
	pipex->infile_fd = pipex->link_fd[0];
	ft_close_link_fd(pipex, 1);
	// close(pipex->link_fd[1]);
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
		close(pipex->link_fd[1]);
		close(pipex->link_fd[0]);
		if (pipex->infile_fd > -1)
			close(pipex->infile_fd);
		close(pipex->outfile_fd);
		// ft_close_fd(pipex, 17);
		if (pipex->cmd_path && pipex->cmd_args)
			execve(pipex->cmd_path, pipex->cmd_args, env);
		ft_free_pipex(pipex);
		exit(1);
	}
	waitpid(pipex->pid2, NULL, 0);
}

/*
tout doit etre close en sortie de ft_exec
tout doit etre close dans chaque child;
*/
void	ft_exec(t_pipex *pipex, int ac, char **av, char **env)
{
	int	i;

	i = 1;
	pipex->infile_fd = open(av[1], O_RDONLY);
	if (pipex->infile_fd < 0)
		ft_printf("pipex: %s: no such file or directory\n");
	while (av[++i + 1])
	{
		ft_get_exec_assets(pipex, av[i]);
		pipe(pipex->link_fd);
		if (i < ac - 2)//same exec jusqu'a outfile -1
			ft_child1(pipex, env);
		else
			ft_child2(pipex, env, av[i + 1]);
		free(pipex->cmd_path);
		ft_free_tab((void **)pipex->cmd_args);
	}
	ft_close_inout(pipex, 2);
	ft_close_link_fd(pipex, 2);
}
