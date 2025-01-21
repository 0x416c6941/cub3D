/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 18:44:24 by root              #+#    #+#             */
/*   Updated: 2025/01/21 14:09:12 by asagymba         ###   ########.fr       */
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

	if (argc != 2)
		return (ft_errmsg("invalid number of parameters", ERR_USAGE, 2));
	else if (ft_parse(*(++argv), &args) == -1)
		return (perror("cub3D: "), EXIT_FAILURE);
}
