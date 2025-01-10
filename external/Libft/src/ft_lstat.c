/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 18:55:10 by asagymba          #+#    #+#             */
/*   Updated: 2024/11/23 20:08:15 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stddef.h>

t_list	*ft_lstat(t_list *lst, size_t at)
{
	while (at-- > 0 && lst != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}
