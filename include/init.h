/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:00:34 by asagymba          #+#    #+#             */
/*   Updated: 2025/01/22 14:01:33 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include <cub3D.h>

/**
 * ----------------------------------------------------------------------------
 * Functions.
 * ----------------------------------------------------------------------------
 */
/**
 * Frees content of \p to_free.
 * @param	to_free	Parsed arguments to free().
 */
void	ft_free_s_args_content(struct s_args *to_free);

/**
 * Prepares MLX: opens the connection, window, reads all textures from \p args;
 * and also prepares all other data required for cub3D, e.g. user's base coords.
 * @param	args	Parsed arguments.
 * @param	data	Where to save MLX connection, window and textures.
 * @return	-1, if something went wrong. errno will also be set;
 * 			Some non-negative value, if everything went fine.
 */
int		ft_prep_data(struct s_args *args, struct s_data *data);

/**
 * Frees content of \p to_free.
 * @param	to_free	cub3D's data to free().
 */
void	ft_free_s_data_content(struct s_data *to_free);

#endif /* INIT_H */
