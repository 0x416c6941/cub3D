/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 21:47:38 by root              #+#    #+#             */
/*   Updated: 2025/01/22 21:44:38 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <cub3D.h>
# include <libft.h>

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
 * @brief Checks if all textures and colors in the `t_args` structure are set.
 *
 * This function verifies that each entry in the `textures` array is non-NULL
 * and each `t_rgb` color in the `colors` array has `setted` set to true.
 *
 * @param args Pointer to the `t_args` structure to check.
 * @return (true if all textures and colors are set); false otherwise.
 */
bool	check_textures_and_colors_set(t_args *args);

/**
 * @brief Checks if a string contains only white spaces.
 *
 * This function iterates through the string and returns true if all characters
 * are white spaces. Returns false if any non-white-space character is found.
 *
 * @param line Pointer to the input string.

 * @return (true if the string contains only white spaces or is empty);
	false otherwise.
 */
bool	ft_string_isspace(const char *line);

/**
 * @brief Prints the contents of the `t_args` structure for debugging.
 *
 * This function iterates over the textures, colors, and map stored in the
 * `t_args` structure and prints their values to the console.
 *
 * @param args Pointer to the `t_args` structure to print (non-NULL).
 */
void	ft_print_t_args(const t_args *args);

/**
 * Gets a row with index \p idx from \p map.
 * @warning	A returned row isn't a copy,
 * 			but a pointer to a content of a map's node.
 * @param	map	Map to get row from.
 * @param	idx	Index of the row.
 * @return (A row with the requested \p idx);
 * 			NULL, if such a row doesn't exist within \p map.
 */
char	*ft_get_map_row(t_list *map, int idx);

/**
 * Frees all data in \p data and exits the program with the \p exit_code.
 * This function, if called, will NEVER return.
 * @param	data		cub3D's data.
 * @param	exit_code	Code to exit the program with.
 * @return	No value will ever be returned. Safe to ignore.
 * 			If exit() fails for some REALLY weird reason, -1 will be returned.
 */
int		ft_mlx_exit(struct s_data *data, int exit_code);

/**
 * If \p angle is out of range of [0, 2 * M_PI], sets it to be in that range.
 * Otherwise doesn't change it.
 * @param	angle	Angle to iniitialize.
 * @return	Initialized angle.
 */
double	ft_initialize_angle(double angle);

#endif /* UTILS_H */
