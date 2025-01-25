/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 18:44:24 by root              #+#    #+#             */
/*   Updated: 2025/01/25 21:00:13 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>
#include <utils.h>
#include <libft.h>
#include <parse.h>
#include <init.h>
#include <stdio.h>
#include <render.h>
#include <mlx.h>
#include <controls.h>
#include <X11/X.h>
#include <stdlib.h>
#include <stddef.h>

/**
 * Add this when parser is finished:
	if (ft_parse(*(++argv), &args) == -1
		|| ft_prep_data(&args, &data) == -1)
		...
 */
int	main(int argc, char **argv)
{
	struct s_args	args;
	struct s_data	data;

	if (argc != 2)
		return (ft_errmsg("invalid number of parameters", ERR_USAGE, 2));
	(void)argv;
	(void)ft_memset(&args, 0, sizeof(struct s_args));
	if (ft_parse(*(++argv), &args) != 0)
		return (ft_free_s_args_content(&args), EXIT_FAILURE);
	(void)ft_memset(&data, 0, sizeof(struct s_data));
	if (ft_prep_data(&args, &data) == -1)
		return (perror("cub3D"), ft_free_s_args_content(&args),
			ft_free_s_data_content(&data), EXIT_FAILURE);
	ft_free_s_args_content(&args);
	(void)ft_render(&data);
	(void)mlx_expose_hook(data.win, ft_render, &data);
	(void)mlx_hook(data.win, KeyPress, KeyPressMask, ft_handle_keysyms, &data);
	(void)mlx_hook(data.win, DestroyNotify, NoEventMask, ft_mlx_exit, &data);
	(void)mlx_loop(data.conn);
	return (0);
}
