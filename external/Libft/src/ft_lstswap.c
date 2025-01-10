/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstswap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 22:13:20 by asagymba          #+#    #+#             */
/*   Updated: 2024/11/23 20:09:38 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stddef.h>

/**
 * Searches for 'to_find' in 'lst'.
 * Track of a previous pointer is kept in '*prev'.
 * @param	lst		A list to go through.
 * @param	to_find	A node to look for in 'lst'.
 * @param	prev	To keep the track of previous pointer.
 * 					In case if 'to_find' isn't found, '*prev' will be NULL.
 * @return	'to_find' in 'lst', if found;
 * 			NULL otherwise.
 */
static t_list	*ft_lstswap_search(t_list *lst, t_list *to_find, t_list **prev)
{
	if (lst == NULL)
		return (NULL);
	*prev = NULL;
	while (lst != NULL)
	{
		if (lst == to_find)
			return (to_find);
		*prev = lst;
		lst = lst->next;
	}
	*prev = NULL;
	return (NULL);
}

void	ft_lstswap(t_list **lst, t_list *x, t_list *y)
{
	t_list	*prev_x;
	t_list	*prev_y;
	t_list	*curr_x;
	t_list	*curr_y;
	t_list	*tmp;

	if (lst == NULL || *lst == NULL || x == y)
		return ;
	prev_x = NULL;
	prev_y = NULL;
	curr_x = ft_lstswap_search(*lst, x, &prev_x);
	curr_y = ft_lstswap_search(*lst, y, &prev_y);
	if (curr_x == NULL || curr_y == NULL)
		return ;
	if (prev_x != NULL)
		prev_x->next = curr_y;
	else
		*lst = curr_y;
	if (prev_y != NULL)
		prev_y->next = curr_x;
	else
		*lst = curr_x;
	tmp = curr_y->next;
	curr_y->next = curr_x->next;
	curr_x->next = tmp;
}
