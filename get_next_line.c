/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obdintal <obdintal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/05 12:28:27 by obdintal          #+#    #+#             */
/*   Updated: 2026/09/05 16:57:02 by obdintal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char	*bytes;
	ssize_t	bytes_lidos;

	if (fd < 0)
		return (NULL);
	bytes = malloc(BUFFER_SIZE + 1);
	if (!bytes)
		return (NULL);
	bytes_lidos = read(fd, bytes, BUFFER_SIZE);
	if (bytes_lidos >= 0)
		bytes[bytes_lidos] = '\0';
	else 
	{
		free(bytes);
		return (NULL);
	}
	return (bytes);
}
