/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlyshchu <hlyshchu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 21:47:38 by root              #+#    #+#             */
/*   Updated: 2025/01/22 15:05:27 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <libft.h>
# include <cub3D.h>

/**
 * ----------------------------------------------------------------------------
 * Constants.
 * ----------------------------------------------------------------------------
 */
# define CUB_PREFIX "Cub3D: Error: "
# define WRITE_ERR_MSG "Error write failed."

/**
 * ----------------------------------------------------------------------------
 * Functions.
 * ----------------------------------------------------------------------------
 */
/**
 * Add prefix "cub3D: Error" and print to standard error output.
 * \p msg and \p detail can be printed to specify the error.
 * Returns the \p exit_code.
 * @param	err_msg
 * @param	detail
 * @param	exit_code
 * @return	exit_code
 */
int		ft_errmsg(const char *msg, const char *detail, int exit_code);

/**
 * Gets a row with index \p idx from \p map.
 * @warning	A returned row isn't a copy,
 * 			but a pointer to a content of a map's node.
 * @param	map	Map to get row from.
 * @param	idx	Index of the row.
 * @return	A row with the requested \p idx;
 * 			NULL, if such a row doesn't exist within \p map.
 */
char	*ft_get_map_row(t_list *map, int idx);

/**
 * Frees all data in \p data and exits the program.
 * This function, if called, will NEVER return.
 * @param	data	cub3D's data.
 * @return	No value will ever be returned. Safe to ignore.
 * 			If exit() fails for some REALLY weird reason, -1 will be returned.
 */
int		ft_mlx_exit(struct s_data *data);

#endif /* UTILS_H */
