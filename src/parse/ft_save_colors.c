/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_save_colors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 20:24:33 by root              #+#    #+#             */
/*   Updated: 2025/01/22 21:33:24 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>
#include <errno.h>
#include <stdlib.h>
#include <utils.h>

int	ft_save_colors(char *line, t_args *args, int index)
{
	char	*trimmed;
	char	**rgb_values;
	int		rgb_val[3];

	if (args->colors[index].setted)
		return (ft_errmsg(line, "Color already set", EINVAL));
	trimmed = ft_strtrim(line + 1, " \t\n");
	if (!trimmed)
		return (ft_errmsg("Memory allocation error", "ft_strtrim", ENOMEM));
	rgb_values = ft_split(trimmed, ',');
	free(trimmed);
	if (!rgb_values)
		return (ft_errmsg("Memory allocation error", "ft_split", ENOMEM));
	if (!rgb_values[0] || !rgb_values[1] || !rgb_values[2] || rgb_values[3])
	{
		ft_split_free(rgb_values);
		return (ft_errmsg("Invalid color format", line, EINVAL));
	}
	rgb_val[0] = ft_atoi(rgb_values[0]);
	rgb_val[1] = ft_atoi(rgb_values[1]);
	rgb_val[2] = ft_atoi(rgb_values[2]);
	ft_split_free(rgb_values);
	if (rgb_val[0] < 0 || rgb_val[0] > 255 || rgb_val[1] < 0 || rgb_val[1] > 255
		|| rgb_val[2] < 0 || rgb_val[2] > 255)
		return (ft_errmsg("RGB values out of range", line, EINVAL));
	args->colors[index] = (t_rgb){(unsigned char)rgb_val[0],
		(unsigned char)rgb_val[1], (unsigned char)rgb_val[2], true};
	return (0);
}
