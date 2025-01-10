/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 17:23:33 by asagymba          #+#    #+#             */
/*   Updated: 2024/11/23 20:06:29 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stddef.h>
#include <stdlib.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ret;
	size_t	ret_size;

	ret_size = nmemb * size;
	if (!nmemb || !size || ret_size / size != nmemb)
		return (NULL);
	ret = malloc(ret_size);
	if (ret == NULL)
		return (NULL);
	return (ft_memset(ret, 0, ret_size));
}
