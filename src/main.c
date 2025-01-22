/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 18:44:24 by root              #+#    #+#             */
/*   Updated: 2025/01/22 15:03:27 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>
#include <utils.h>
#include <libft.h>
#include <parse.h>
#include <init.h>
#include <stdio.h>
#include <mlx.h>
#include <controls.h>
#include <X11/X.h>
#include <stdlib.h>
#include <stddef.h>

/**
 * Norminette bypass.
 * @param	args	Args to initialize.
 * @return	-1, if something went wrong (errno will NOT be set);
 * 			Some non-negative value otherwise.
 */
static int	ft_tmp_init_args_norminette(struct s_args *args)
{
	const char *const	rows[] = {"11111", "1N001", "10001", "11111", NULL};
	size_t				i;
	char				*row;
	t_list				*node;

	args->map = NULL;
	i = 0;
	while (rows[i] != NULL)
	{
		row = ft_strdup(rows[i]);
		if (row == NULL)
			return (ft_lstclear(&args->map, free), -1);
		node = ft_lstnew(row);
		if (node == NULL)
			return (free(row), ft_lstclear(&args->map, free), -1);
		ft_lstadd_back(&args->map, node);
		i++;
	}
	return (0);
}

/**
 * Temporarily initialises \p args, as parser isn't ready yet.
 * @param	args	Args to initialize.
 * @return	-1, if something went wrong (errno will NOT be set);
 * 			Some non-negative value otherwise.
 */
static int	ft_tmp_init_args(struct s_args *args)
{
	int	i;
	int	j;

	i = 0;
	while (i < TEXTURES_SIZE)
	{
		args->textures[i] = ft_strdup("textures/minecraft/diamond.xpm");
		if (args->textures[i] == NULL)
		{
			j = 0;
			while (j < i)
			{
				free(args->textures[j]);
				args->textures[j++] = NULL;
			}
			return (-1);
		}
		i++;
	}
	args->colors[COLOR_FLOOR] = (struct s_rgb){50, 50, 50};
	args->colors[COLOR_CEILING] = (struct s_rgb){100, 100, 100};
	return (ft_tmp_init_args_norminette(args));
}

/**
 * Add this when parser is finished:
	if (ft_parse(*(++argv), &args) == -1
		|| ft_prep_data(&args, &data) == -1)
		...
 * This will also be required to handle
 * window resizing and other possible events:
 * mlx_hook(data.win, Expose, ExposureMask, RENDERFUNC, &data);
 */
int	main(int argc, char **argv)
{
	struct s_args	args;
	struct s_data	data;

	if (argc != 2)
		return (ft_errmsg("invalid number of parameters", ERR_USAGE, 2));
	(void)argv;
	(void)ft_memset(&args, 0, sizeof(struct s_args));
	if (ft_tmp_init_args(&args) == -1)
	{
		return (ft_errmsg("Something went wrong in ft_tmp_init_args()",
				NULL, 1));
	}
	(void)ft_memset(&data, 0, sizeof(struct s_data));
	if (ft_prep_data(&args, &data) == -1)
		return (perror("cub3D"), ft_free_s_args_content(&args),
			ft_free_s_data_content(&data), EXIT_FAILURE);
	ft_free_s_args_content(&args);
	mlx_key_hook(data.win, ft_handle_keysyms, &data);
	mlx_hook(data.win, DestroyNotify, NoEventMask, ft_mlx_exit, &data);
	mlx_loop(data.conn);
	return (0);
}
