/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdou <aabdou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 17:32:29 by hmoubal           #+#    #+#             */
/*   Updated: 2022/06/10 14:17:51 by aabdou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>
# define BUFFER_SIZE 1

char	*get_next_line(int fd);
char	*ft_strdup2(const char *src);
char	*ft_strjoin_gnl2(char const *s1,	char const *s2);
void	*ft_memcpy2(void *dest,	const void *src,	size_t size);
size_t	ft_strlen2(char const	*str);
#endif
