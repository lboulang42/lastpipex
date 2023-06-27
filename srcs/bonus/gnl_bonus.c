/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 14:30:34 by lboulang          #+#    #+#             */
/*   Updated: 2023/06/27 14:33:54 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

int	ft_is_same_line(char *line, char *limiter)
{
	if (ft_strlen(line) != ft_strlen(limiter)+1)
		return (0);
	if (ft_strncmp(line, limiter, ft_strlen(line)-1))
		return (0);
	if (line[ft_strlen(line)-1] != '\n')
		return (0);
	return (1);
}
