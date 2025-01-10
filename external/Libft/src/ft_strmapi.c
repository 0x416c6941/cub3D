/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:57:32 by asagymba          #+#    #+#             */
/*   Updated: 2024/11/23 20:13:07 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stddef.h>

char	*ft_strmapi(const char *s, char (*f)(unsigned int i, char c))
{
	char	*ret;
	size_t	i;

	if (s == NULL || f == NULL)
		return (NULL);
	ret = ft_strdup(s);
	if (ret == NULL)
		return (NULL);
	i = 0;
	while (ret[i] != '\0')
	{
		ret[i] = f(i, ret[i]);
		i++;
	}
	return (ret);
}
