/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstinsert_at.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 19:23:35 by asagymba          #+#    #+#             */
/*   Updated: 2024/11/23 20:08:39 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_lstinsert_at(t_list **lst, size_t at, t_list *node)
{
	t_list	*prev;
	t_list	*i;

	if (lst == NULL || *lst == NULL || node == NULL)
		return ;
	prev = NULL;
	i = *lst;
	while (at-- > 0 && i != NULL)
	{
		prev = i;
		i = i->next;
	}
	if (prev == NULL)
		*lst = node;
	else
		prev->next = node;
	node->next = i;
}
