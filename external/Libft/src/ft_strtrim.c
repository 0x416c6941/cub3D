/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 22:41:22 by asagymba          #+#    #+#             */
/*   Updated: 2024/11/23 20:13:49 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stddef.h>
#include <stdlib.h>

char	*ft_strtrim(const char *s1, const char *set)
{
	char	*ret;
	size_t	i;

	if (s1 == NULL)
		return (NULL);
	while (*s1 != '\0' && ft_strchr(set, *s1) != NULL)
		s1++;
	i = ft_strlen(s1);
	while (i > 0)
	{
		if (ft_strchr(set, *(s1 + (i - 1))) == NULL)
			break ;
		i--;
	}
	ret = (char *)malloc(i + 1);
	if (ret == NULL)
		return (NULL);
	(void) ft_strlcpy(ret, s1, i + 1);
	return (ret);
}
