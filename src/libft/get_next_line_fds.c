/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_fds.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchen <jchen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 13:37:37 by jchen             #+#    #+#             */
/*   Updated: 2024/09/25 11:45:47 by jchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*set_line(char *line_buffer)
{
	int		i;
	char	*rest;

	i = 0;
	while (line_buffer[i] != '\n' && line_buffer[i] != '\0')
		i++;
	if (line_buffer[i] == '\0' || line_buffer[1] == '\0')
		return (NULL);
	rest = ft_substr(line_buffer, i + 1, ft_strlen(line_buffer) - i);
	if (*rest == '\0')
	{
		free(rest);
		rest = NULL;
	}
	line_buffer[i + 1] = '\0';
	return (rest);
}

static char	*fill_line_buffer(int fd, char *rest, char *buffer)
{
	ssize_t	bytes_read;
	char	*temp;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(rest), NULL);
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		if (!rest)
			rest = ft_strdup("");
		temp = rest;
		rest = ft_strjoin(temp, buffer);
		free(temp);
		temp = NULL;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (rest);
}

char	*get_next_line_fds(int fd)
{
	char		*buffer;
	char		*line;
	static char	*rest[FDMAX];

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(rest[fd]);
		free(buffer);
		rest[fd] = NULL;
		buffer = NULL;
		return (NULL);
	}
	if (!buffer)
		return (NULL);
	line = fill_line_buffer(fd, rest[fd], buffer);
	free(buffer);
	buffer = NULL;
	if (!line)
		return (NULL);
	rest[fd] = set_line(line);
	return (line);
}
