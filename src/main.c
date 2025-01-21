/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 18:44:24 by root              #+#    #+#             */
/*   Updated: 2025/01/21 14:46:17 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>
#include <utils.h>
#include <parse.h>
#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	struct s_args	args;
	struct s_data	data;

	if (argc != 2)
		return (ft_errmsg("invalid number of parameters", ERR_USAGE, 2));
	(void)ft_memset(&data, 0, sizeof(struct s_data));
	if (ft_parse(*(++argv), &args) == -1
		|| ft_prep_mlx(&args, &data) == -1)
		return (perror("cub3D: "), EXIT_FAILURE);
}
