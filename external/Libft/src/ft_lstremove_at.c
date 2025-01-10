/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstremove_at.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 19:11:17 by asagymba          #+#    #+#             */
/*   Updated: 2024/11/23 20:09:15 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stddef.h>
#include <stdlib.h>

void	ft_lstremove_at(t_list **lst, void (*del)(void *), size_t at)
{
	t_list	*prev;
	t_list	*i;

	if (lst == NULL || *lst == NULL || del == NULL)
		return ;
	prev = NULL;
	i = *lst;
	while (at-- > 0 && i != NULL)
	{
		prev = i;
		i = i->next;
	}
	if (prev == NULL)
		*lst = (*lst)->next;
	else
		prev->next = i->next;
	del(i->content);
	free(i);
}
