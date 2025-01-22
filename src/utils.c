/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 21:42:28 by root              #+#    #+#             */
/*   Updated: 2025/01/22 18:50:45 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <utils.h>
#include <unistd.h>
#include <stdio.h>
#include <libft.h>
#include <stddef.h>
#include <cub3D.h>
#include <init.h>
#include <stdlib.h>

int	ft_errmsg(const char *msg, const char *detail, int exit_code)
{
	if ((write(STDERR_FILENO, CUB_PREFIX, ft_strlen(CUB_PREFIX)) == -1)
		|| (write(STDERR_FILENO, msg, ft_strlen(msg)) == -1))
	{
		perror(WRITE_ERR_MSG);
		return (-1);
	}
	if (detail)
	{
		if ((write(STDERR_FILENO, ": ", 2) == -1) || (write(STDERR_FILENO,
					detail, ft_strlen(detail)) == -1))
		{
			perror(WRITE_ERR_MSG);
			return (-1);
		}
	}
	if (write(STDERR_FILENO, "\n", 1) == -1)
	{
		perror(WRITE_ERR_MSG);
		return (-1);
	}
	return (exit_code);
}

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

int	ft_mlx_exit(struct s_data *data, int exit_code)
{
	ft_free_s_data_content(data);
	exit(exit_code);
	return (-1);
}
