/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 22:21:12 by asagymba          #+#    #+#             */
/*   Updated: 2024/11/23 20:12:42 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stddef.h>
#include <stdlib.h>

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*ret;
	size_t	s1_len;
	size_t	ret_size;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	else if (s1 != NULL && s2 == NULL)
		return (ft_strdup(s1));
	else if (s1 == NULL && s2 != NULL)
		return (ft_strdup(s2));
	s1_len = ft_strlen(s1);
	ret_size = s1_len + ft_strlen(s2) + 1;
	ret = (char *)malloc(ret_size);
	if (ret == NULL)
		return (NULL);
	(void) ft_strlcpy(ret, s1, s1_len + 1);
	(void) ft_strlcat(ret, s2, ret_size);
	return (ret);
}
