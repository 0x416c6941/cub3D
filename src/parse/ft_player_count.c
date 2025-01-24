/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_player_count.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 11:37:34 by root              #+#    #+#             */
/*   Updated: 2025/01/24 02:15:58 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>
#include <parse.h>

int	ft_player_count(t_list *map)
{
	t_list	*current;
	char	*line;
	int		player_count;
	int		i;

	player_count = 0;
	current = map;
	while (current != NULL)
	{
		line = (char *)current->content;
		i = 0;
		while (line[i] != '\0')
		{
			if (line[i] == 'N' || line[i] == 'S'
				|| line[i] == 'E' || line[i] == 'W')
				player_count++;
			i++;
		}
		current = current->next;
	}
	return (player_count);
}
