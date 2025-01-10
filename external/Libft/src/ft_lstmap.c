/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:58:46 by asagymba          #+#    #+#             */
/*   Updated: 2024/11/23 20:08:57 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stddef.h>

/**
 * A small wrapper for ft_lstclear(), which would return NULL
 * after it's call. Written to bypass Norminette.
 * @param	lst	A lst to clear (same as in ft_lstclear()).
 * @param	del	A del function for nodes in lst (same as in ft_lstclear()).
 * @return	NULL.
 */
static t_list	*ft_lstclear_wrapper(t_list **lst, void (*del)(void *))
{
	if (lst == NULL)
		return (NULL);
	ft_lstclear(lst, del);
	return (NULL);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	void	*new_content;
	t_list	*node;

	if (lst == NULL || f == NULL || del == NULL)
		return (NULL);
	head = NULL;
	while (lst != NULL)
	{
		new_content = f(lst->content);
		if (new_content == NULL)
			return (ft_lstclear_wrapper(&head, del));
		node = ft_lstnew(new_content);
		if (node == NULL)
		{
			del(new_content);
			return (ft_lstclear_wrapper(&head, del));
		}
		ft_lstadd_back(&head, node);
		lst = lst->next;
	}
	return (head);
}
