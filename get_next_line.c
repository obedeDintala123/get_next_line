/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obdintal <obdintal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/05 12:28:27 by obdintal          #+#    #+#             */
/*   Updated: 2026/09/09 16:20:24 by obdintal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static	void	update_saved(char **saved)
{
	char	*pos;
	char	*new_content;

	pos = ft_strchr(*saved, '\n');
	if (pos)
		new_content = ft_strdup(pos + 1);
	else
		new_content = NULL;
	free(*saved);
	*saved = new_content;
}

static	char	*read_line(char **saved, size_t size)
{
	char	*line;
	size_t	i;

	line = (char *)malloc(sizeof(char) * (size + 1));
	if (!line)
	{
		free(*saved);
		*saved = NULL;
		return (NULL);
	}
	i = 0;
	while ((*saved)[i] && (*saved)[i] != '\n')
	{
		line[i] = (*saved)[i];
		i++;
	}
	if ((*saved)[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*get_line(char **saved)
{
	char	*line;
	size_t	count;

	if (!*saved || (*saved)[0] == '\0')
	{
		free(*saved);
		*saved = NULL;
		return (NULL);
	}
	count = 0;
	while ((*saved)[count] && (*saved)[count] != '\n')
		count++;
	if ((*saved)[count] == '\n')
		count++;
	line = read_line(saved, count);
	update_saved(saved);
	return (line);
}

char	*get_next_line(int fd)
{
	ssize_t		bytes_read;
	char		buffer[BUFFER_SIZE + 1];
	static char	*saved;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!saved)
		saved = ft_strdup("");
	while (!ft_strchr(saved, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(saved);
			saved = NULL;
			return (NULL);
		}
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		saved = ft_strjoin(saved, buffer);
		if (!saved)
			return (NULL);
	}
	return (get_line(&saved));
}
