/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:26:17 by asagymba          #+#    #+#             */
/*   Updated: 2024/11/23 20:13:31 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stddef.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	bytes_to_cmp;

	if (big == NULL)
		return (NULL);
	bytes_to_cmp = ft_strlen(little);
	if (!bytes_to_cmp)
		return ((char *)big);
	else if (!len)
		return (NULL);
	len = ft_strnlen(big, len);
	while (len-- >= bytes_to_cmp)
	{
		if (ft_strncmp(big, little, bytes_to_cmp) == 0)
			return ((char *)big);
		big++;
	}
	return (NULL);
}
