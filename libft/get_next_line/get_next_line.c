/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmateja <tmateja@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:09:33 by tmateja           #+#    #+#             */
/*   Updated: 2024/10/13 16:32:00 by tmateja          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_file(int fd, char *str);
static char	*ft_line(char *buffer);
static char	*ft_rm_read(char *buffer);
static char	*ft_append(char *buffer, char *buf);

char	*get_next_line(int fd, int cleanup)
{
	static char	*buffer;
	char		*line;

	if (cleanup)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= 1024)
		return (NULL);
	buffer = read_file(fd, buffer);
	if (!buffer)
		return (NULL);
	line = ft_line(buffer);
	buffer = ft_rm_read(buffer);
	return (line);
}

static char	*read_file(int fd, char *str)
{
	char	*buffer;
	int		byte_read;

	if (!str)
		str = ft_calloc_gnl(1, 1);
	buffer = ft_calloc_gnl(BUFFER_SIZE + 1, sizeof(char));
	byte_read = 1;
	while (0 < byte_read)
	{
		byte_read = read(fd, buffer, BUFFER_SIZE);
		if (-1 == byte_read)
		{
			free(buffer);
			free(str);
			return (NULL);
		}
		buffer[byte_read] = 0;
		str = ft_append(str, buffer);
		if (ft_strchr_gnl(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (str);
}

static char	*ft_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = ft_calloc_gnl(i + 2, sizeof(char));
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] && buffer[i] == '\n')
		line[i++] = '\n';
	return (line);
}

static char	*ft_rm_read(char *buffer)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	line = ft_calloc_gnl((ft_strlen_gnl(buffer) - i + 1), sizeof(char));
	i++;
	j = 0;
	while (buffer[i])
		line[j++] = buffer [i++];
	free(buffer);
	return (line);
}

static char	*ft_append(char *buffer, char *buf)
{
	char	*tmp;

	tmp = ft_strjoin_gnl(buffer, buf);
	free(buffer);
	return (tmp);
}
