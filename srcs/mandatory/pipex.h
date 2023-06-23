/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 17:37:15 by lboulang          #+#    #+#             */
/*   Updated: 2023/06/23 09:06:47 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include "../../libft/libft.h"
# include <sys/wait.h>

typedef struct s_pipex
{
	char	**env_path;
	char	**cmd_args;
	char	*cmd_path;
	int		infile_fd;
	int		outfile_fd;
	int		link_fd[2];
	int		pid1;
	int		pid2;
}	t_pipex;

void	ft_exec(t_pipex *pipex, int ac, char **av, char **env);
void	ft_child2(t_pipex *pipex, char **env, char *str);
void	ft_child1(t_pipex *pipex, char **env);
void	ft_free_pipex(t_pipex *pipex);
void	ft_close_fd(t_pipex *pipex, int pwr);
int	main(int ac, char **av, char **env); 
char	*ft_check_acces(char **env_path, char *cmd_name);
void	ft_wrong_access(char *cmd_path, char *cmd_name);
char	**ft_get_env_path(char **env);
void	ft_get_exec_assets(t_pipex *pipex, char *str);

#endif