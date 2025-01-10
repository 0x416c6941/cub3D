/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcspn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 22:32:21 by asagymba          #+#    #+#             */
/*   Updated: 2024/11/23 20:12:19 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/**
 * Props to OpenBSD.
 */
size_t	ft_strcspn(const char *s, const char *reject)
{
	size_t		i;
	const char	*r;

	i = 0;
	while (42)
	{
		r = reject;
		while (42)
		{
			if (s[i] == *r)
				return (i);
			else if (*r++ == '\0')
				break ;
		}
		i++;
	}
}
