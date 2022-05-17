/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdou <aabdou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 20:02:33 by aabdou            #+#    #+#             */
/*   Updated: 2022/04/17 20:19:21 by aabdou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int ft_strcmp(const char *s1, const char *s2)
{
	// int i = 0;
	// int j = 0;
	// while(s1[i])
	// {
	// 	while(s2[j])
	// 	{
	// 		if(s1[j] != s2[j])
	// 		{
	// 			if (s1[j] > s2[j])
	// 				return 1;
	// 			else
	// 				return -1;
	// 		}
	// 		j++;
	// 	}
	// 	i++;
	// }
	// return 0;
	if (!s1 || !s2)
		return (0);
	while (*s1 == *s2 && *s1 && *s2)
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}


// int main()
// {
// 	printf("%d\n", strcmp("≈helo", "≈hello "));
// 	printf("%d\n", ft_strcmp("≈helo", "≈hello "));
// 	return 0;
// }
