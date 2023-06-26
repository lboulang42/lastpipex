/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 20:59:44 by lboulang          #+#    #+#             */
/*   Updated: 2023/06/26 20:31:52 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

char	*ft_join_free(char *str1, char *str2)
{
	char	*new_str;
	int		i;
	int		j;

	i = -1;
	j = -1;
	new_str = malloc(sizeof(char) * (ft_strlen(str1) + ft_strlen(str2) + 1));
	if (!new_str)
		return (NULL);
	while (str1[++i])
		new_str[i] = str1[i];
	while (str2[++j])
		new_str[i + j] = str2[j];
	new_str[i + j] = '\0';
	free(str1);
	return (new_str);
}

char	*ft_get_file(char *buffer, int fd)
{
	char	*temp_buffer;
	int		bytes_readed;

	bytes_readed = 1;
	temp_buffer = malloc(1 +1 * sizeof(char));
	if (!temp_buffer)
		return (NULL);
	if (!buffer)
		buffer = ft_calloc(1, sizeof(char));
	while (bytes_readed > 0 && !ft_strchr(buffer, '\n'))
	{
		bytes_readed = read(fd, temp_buffer, 1);
		if (bytes_readed == -1)
			return (free(buffer), free(temp_buffer), NULL);
		temp_buffer[bytes_readed] = '\0';
		buffer = ft_join_free(buffer, temp_buffer);
	}
	return (free(temp_buffer), buffer);
}

char	*ft_get_line(char *buffer)
{
	char	*new_line;
	int		i;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	new_line = ft_calloc(i + 2, sizeof(char));
	if (!new_line)
		return (NULL);
	i = -1;
	while (buffer[++i] && buffer[i] != '\n')
		new_line[i] = buffer[i];
	if (buffer[i] == '\n')
		new_line[i++] = '\n';
	new_line[i] = '\0';
	return (new_line);
}

char	*ft_update_buffer(char *buffer)
{
	char	*updated_buffer;
	int		i;
	int		j;

	i = 0;
	j = -1;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
		return (free(buffer), NULL);
	i++;
	updated_buffer = ft_calloc((ft_strlen(buffer) - i + 1), sizeof(char));
	if (!updated_buffer)
		return (NULL);
	while (buffer[++j + i])
		updated_buffer[j] = buffer[i + j];
	updated_buffer[j] = '\0';
	return (free(buffer), updated_buffer);
}

char	*get_next_line(int fd, char *buffer)
{
	char		*line;

	if (fd < 0)
		return (NULL);
	buffer = ft_get_file(buffer, fd);
	if (!buffer)
		return (free(buffer), NULL);
	line = ft_get_line(buffer);
	buffer = ft_update_buffer(buffer);
	return (line);
}

int ft_check_here_doc(t_pipex *pipex, char **av)
{
	(void)pipex;
	static char *buffer;
	char *line;
	char *instr;
	// int turn = 0;
	
	int len;
	len = ft_strlen(av[1]);
	
	if (!ft_strncmp(av[1], "here_doc", len) && len == 8)
	{
		// instr = ft_calloc(sizeof(char), 1);
		while (1)
		{
			line = get_next_line(0, buffer);
			ft_printf("line = %s\n", line);
			if (!ft_strncmp(line, av[2], ft_strlen(line)-1))
				break;
			instr = ft_join_free(instr, line);
			
			//free(line);
			// line = get_next_line(0, buffer);
			// if (ft_strncmp(line, av[2], ft_strlen(line)-1))
			// {
			// 	instr = ft_join_free(instr, line);
			// 	free(line);
			// }
			// else
			// {
			// 	free(line);
			// 	break;
			// }
			// ft_printf("line = '%s'", line);
			// if (!ft_strncmp(line, av[2], ft_strlen(line)-1))
			// {
			// 	free(line);
			// 	break;
			// }
			// if (turn == 0)
			// {
			// 	instr = ft_strdup(line);
			// 	free(line);
			// 	turn++;
			// }
			// else
			// 	instr = ft_join_free(instr, line);
		}
		free(line);
		free(instr);
		free(buffer);
		// ft_printf("BUFFER :\n");
		// ft_printf("%s", buffer);
		// free(buffer);
		
		// read toutes les lines de sortie jusqu'a ce aue ce soit la mm aue av[2] (LIMITER)
		// foutre tout dans un fd (dup ?)
		// et foutre pipex->infile_fd = le fd du dup.
		return (1);
	}
	return (0);
}

/*
Open infile O_RDONLY (check if file is accessible)
*/
void	ft_exec(t_pipex *pipex, int ac, char **av, char **env)
{
	int	i;

	i = 1;
	ft_check_here_doc(pipex,av);
	// if (!)
	// {
		pipex->infile_fd = open(av[1], O_RDONLY);
		if (pipex->infile_fd < 0)
			ft_printf("Pipex: %s: %s\n", av[1], ERR_NOSUCHF);
	// }
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
