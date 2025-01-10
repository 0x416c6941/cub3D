/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok_r.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 19:45:58 by asagymba          #+#    #+#             */
/*   Updated: 2024/11/23 19:46:26 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtok_r(char *str, const char *delim, char **saveptr)
{
	if (str != NULL)
		*saveptr = str;
	while (**saveptr != '\0')
	{
		if (ft_strchr(delim, **saveptr) == NULL)
			break ;
		(*saveptr)++;
	}
	str = *saveptr;
	if (*str == '\0')
		return (NULL);
	while (**saveptr != '\0')
	{
		if (ft_strchr(delim, **saveptr) != NULL)
		{
			*(*saveptr)++ = '\0';
			break ;
		}
		(*saveptr)++;
	}
	return (str);
}
