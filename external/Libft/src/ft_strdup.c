/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 17:26:05 by asagymba          #+#    #+#             */
/*   Updated: 2024/11/23 20:11:40 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stddef.h>
#include <stdlib.h>

char	*ft_strdup(const char *s)
{
	char	*dup;
	size_t	dup_size;

	dup_size = 1;
	if (s != NULL)
		dup_size = ft_strlen(s) + 1;
	dup = (char *)malloc(dup_size);
	if (dup == NULL)
		return (NULL);
	*dup = '\0';
	if (s != NULL)
		(void)ft_strlcpy(dup, s, dup_size);
	return (dup);
}
