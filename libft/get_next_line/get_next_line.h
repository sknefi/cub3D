/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmateja <tmateja@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:11:00 by tmateja           #+#    #+#             */
/*   Updated: 2024/10/13 14:04:30 by tmateja          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 64
# endif

# include <unistd.h>
# include <stdlib.h>

char	*get_next_line(int fd, int cleanup);
void	*ft_calloc_gnl(size_t count, size_t size);
char	*ft_strchr_gnl(const char *s, int c);
size_t	ft_strlen_gnl(const char *str);
char	*ft_strjoin_gnl(char const *s1, char const *s2);
char	*ft_substr_gnl(const char *s, unsigned int start, size_t len);

#endif
