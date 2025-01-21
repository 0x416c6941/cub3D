/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_map_row.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 18:00:16 by asagymba          #+#    #+#             */
/*   Updated: 2025/01/21 18:01:30 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <utils.h>
#include <libft.h>
#include <stddef.h>

char	*ft_get_map_row(t_list *map, int idx)
{
	t_list	*node;

	if (idx < 0)
		return (NULL);
	node = ft_lstat(map, (size_t)idx);
	if (node == NULL)
		return (NULL);
	return (node->content);
}
