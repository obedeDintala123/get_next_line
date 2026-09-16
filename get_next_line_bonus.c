/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obdintal <obdintal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/05 12:28:27 by obdintal          #+#    #+#             */
/*   Updated: 2026/09/16 13:19:15 by obdintal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static	void	update_saved(char **saved)
{
	char	*pos;
	char	*new_content;

	pos = ft_strchr(*saved, '\n');
	if (pos && *(pos + 1))
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

static char	*get_line(char **saved, char **buffer)
{
	char	*line;
	size_t	count;

	free(*buffer);
	*buffer = NULL;
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

static int	get_alloc(int fd, char *(*saved)[1024], char **buffer)
{
	*buffer = NULL;
	if (!(*saved)[fd])
		(*saved)[fd] = ft_strdup("");
	if (!(*saved)[fd])
		return (1);
	if (!*buffer)
	{
		*buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!*buffer)
		{
			free((*saved)[fd]);
			(*saved)[fd] = NULL;
			return (1);
		}
	}
	return (0);
}

char	*get_next_line(int fd)
{
	ssize_t		bytes_read;
	char		*buffer;
	static char	*saved[1024];

	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	if (get_alloc(fd, &saved, &buffer))
		return (NULL);
	while (!ft_strchr(saved[fd], '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(saved[fd]);
			saved[fd] = NULL;
			return (NULL);
		}
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		saved[fd] = ft_strjoin(saved[fd], buffer);
		if (!saved[fd])
			return (NULL);
	}
	return (get_line(&saved[fd], &buffer));
}
