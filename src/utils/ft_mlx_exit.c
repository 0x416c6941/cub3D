/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:50:01 by asagymba          #+#    #+#             */
/*   Updated: 2025/01/22 17:21:07 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <utils.h>
#include <cub3D.h>
#include <init.h>
#include <stdlib.h>

int	ft_mlx_exit(struct s_data *data, int exit_code)
{
	ft_free_s_data_content(data);
	exit(exit_code);
	return (-1);
}
