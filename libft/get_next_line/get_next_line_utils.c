/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmateja <tmateja@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 19:55:00 by tmateja           #+#    #+#             */
/*   Updated: 2024/10/13 15:41:26 by tmateja          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc_gnl(size_t count, size_t size)
{
	unsigned char	*ptr;
	size_t			i;

	if (count && (count * size) / count != size)
		return (NULL);
	i = 0;
	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	while (i < count * size)
		ptr[i++] = 0;
	return (ptr);
}

char	*ft_strchr_gnl(const char *s, int c)
{
	unsigned int	i;
	char			cc;

	if (!s)
		return (NULL);
	cc = (char) c;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return ((char *) &s[i]);
		i++;
	}
	if (s[i] == cc)
		return ((char *) &s[i]);
	return (NULL);
}

size_t	ft_strlen_gnl(const char *str)
{
	size_t	len;

	if (!str)
		return (0);
	len = 0;
	while (*str++)
		len++;
	return (len);
}

char	*ft_strjoin_gnl(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	str = malloc((ft_strlen_gnl(s1) + ft_strlen_gnl(s2) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		str[j++] = s1[i++];
	i = 0;
	while (s2[i])
		str[j++] = s2[i++];
	str[j] = '\0';
	return (str);
}

char	*ft_substr_gnl(const char *s, unsigned int start, size_t len)
{
	size_t	j;
	size_t	i;
	char	*str;

	if (!s)
		return (NULL);
	str = (char *)ft_calloc_gnl(len + 1, sizeof(*s));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (i >= start && j < len)
		{
			str[j] = s[i];
			j++;
		}
		i++;
	}
	return (str);
}
