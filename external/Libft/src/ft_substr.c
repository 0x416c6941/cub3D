/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 22:09:29 by asagymba          #+#    #+#             */
/*   Updated: 2024/11/23 20:13:55 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stddef.h>
#include <stdlib.h>

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*substr;

	if (s == NULL)
		return (NULL);
	else if (start > ft_strlen(s))
		return (ft_strdup(""));
	len = ft_strnlen(s + start, len);
	substr = (char *)malloc(len + 1);
	if (substr == NULL)
		return (NULL);
	(void) ft_strlcpy(substr, s + start, len + 1);
	return (substr);
}
