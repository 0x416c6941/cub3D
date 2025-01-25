/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:27:24 by asagymba          #+#    #+#             */
/*   Updated: 2025/01/25 01:17:01 by asagymba         ###   ########.fr       */
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
 * When moving the player to some side
 * or camera to the left or to the right,
 * they will be moved by those values respectively.
 * In case of movement, value of MOV_EPS will be amplified by the angle
 * player is looking at.
 */
# define MOV_EPS	8	/* cub3D.h -> BLOCK_X / 16. */
# define ANGLE_EPS	0.2

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
