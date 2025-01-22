/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:27:24 by asagymba          #+#    #+#             */
/*   Updated: 2025/01/22 15:05:07 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTROLS_H
# define CONTROLS_H

# include <cub3D.h>

/**
 * ----------------------------------------------------------------------------
 * Constants.
 * ----------------------------------------------------------------------------
 */
/**
 * When moving the camera to the left or to the right,
 * it will be moved by this angle.
 */
# define ANGLE_EPS	0.1

/**
 * ----------------------------------------------------------------------------
 * Functions.
 * ----------------------------------------------------------------------------
 */
/**
 * Handles keypresses.
 * @param	keycode	Code of the pressed key.
 * @param	data	cub3D's data.
 * @return	0, since theoretically nothing may go wrong. Safe to ignore.
 */
int	ft_handle_keysyms(int keycode, struct s_data *data);

#endif /* CONTROLS_H */
