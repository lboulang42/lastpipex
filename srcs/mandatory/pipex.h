/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 17:37:15 by lboulang          #+#    #+#             */
/*   Updated: 2023/06/26 18:23:50 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../../libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

/*MACROS*/
# ifndef ERR_SYNTX
#  define ERR_SYNTX "Pipex: Syntax error near unexpected token:"
# endif

# ifndef ERR_NOSUCHF
#  define ERR_NOSUCHF "No such file or directory"
# endif

# ifndef ERR_NOTDIR
#  define ERR_NOTDIR "not a directory"
# endif

# ifndef ERR_CMD
#  define ERR_CMD "command not found: "
# endif
# ifndef ERR_PERM
#  define ERR_PERM "permission denied"
# endif

/*STRUCTURES*/
typedef struct s_pipex
{
	char	**env_path;
	char	**cmd_args;
	char	*cmd_path;
	int		infile_fd;
	int		outfile_fd;
	int		link_fd[2];
	int		exit_code;
	int		pid[2];
}			t_pipex;

/*FUNCTIONS*/
/*main.c*/
int			main(int ac, char **av, char **env);
/*exec.c*/
void		ft_child1(t_pipex *pipex, char **env, int index);
void		ft_child2(t_pipex *pipex, char **env, char *out_path, int index);
void		ft_exec(t_pipex *pipex, int ac, char **av, char **env);
/*clean.c*/
void		ft_free_pipex(t_pipex *pipex);
void		ft_close_link_fd(t_pipex *pipex, int to_close);
void		ft_close_inout(t_pipex *pipex, int to_close);
void		ft_clear_pipex(t_pipex *pipex);
/*acces.c*/
void		ft_get_exec_assets(t_pipex *pipex, char *command);
char		*ft_join_path(char *try_path, char *cmd_name);
char		*ft_check_acces(char **env_path, char *cmd_name);
void		ft_access_fail(char *cmd_path, char *cmd_name);
char		**ft_get_env_path(char **env);

#endif