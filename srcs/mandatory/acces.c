/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   acces.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 20:58:51 by lboulang          #+#    #+#             */
/*   Updated: 2023/06/23 19:49:33 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_get_exec_assets(t_pipex *pipex, char *str)
{
	pipex->cmd_args = ft_split(str, ' ');
	if (!pipex->cmd_args)
		return ;
	pipex->cmd_path = ft_check_acces(pipex->env_path, pipex->cmd_args[0]);
}

char	**ft_get_env_path(char **env)
{
	int		i;
	char	**tmp;
	char	**env_path;

	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp("PATH=", env[i], 5))
		{
			tmp = ft_split(env[i], '=');
			if (!tmp)
				return (NULL);
			env_path = ft_split(tmp[1], ':');
			if (!env_path)
				return (ft_free_tab((void **)tmp), NULL);
			return (ft_free_tab((void **)tmp), env_path);
		}
	}
	return (NULL);
}

void	ft_wrong_access(char *cmd_path, char *cmd_name)
{
	if (cmd_path[ft_strlen(cmd_path)-1] == '/')
	{
		ft_printf("pipex: %s: not a directory\n");
		// return (free(cmd_path));
	}
	if (access(cmd_path, F_OK))
	{
		ft_printf("pipex: command not found : '%s'\n", cmd_name);
		// return (free(cmd_path));
	}
	if (access(cmd_path, X_OK))
	{
		ft_printf("pipex: %s: permission denied\n", cmd_path);
		// return (free(cmd_path));
	}
	free(cmd_path);
}

char	*ft_check_acces(char **env_path, char *cmd_name)
{
	char	*tmp_path;
	char	*cmd_path;
	int		i;
	int check = 0;
	
	i = -1;
	while (env_path[++i])
	{
		if (!ft_strncmp(cmd_name, "/", 1))
		{
			check = 1;
			cmd_path = ft_strdup(cmd_name);
			if (!cmd_path)
				return (NULL);
		}
		else
		{
			tmp_path = ft_strjoin(env_path[i], "/");
			if (!tmp_path)
				return (NULL);
			cmd_path = ft_strjoin(tmp_path, cmd_name);
			if (!cmd_path)
				return (free(tmp_path), NULL);
			free(tmp_path);	
		}
		if (!access(cmd_path, F_OK | X_OK))
				return (cmd_path);
		if (env_path[i + 1] && check != 1)
			free(cmd_path);
		else
			return (ft_wrong_access(cmd_path, cmd_name), NULL);
	}
	return (NULL);
}
