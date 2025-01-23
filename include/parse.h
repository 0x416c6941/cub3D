/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:00:08 by asagymba          #+#    #+#             */
/*   Updated: 2025/01/23 15:38:19 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <cub3D.h>

/**
 * ----------------------------------------------------------------------------
 * Structures.
 * ----------------------------------------------------------------------------
 */
/**
 * Info for flood fill.
 */
typedef struct s_map_info
{
	int		rows;
	int		cols;
	int		player_x;
	int		player_y;
	char	player_sign;
}	t_map_info;

/**
 * ----------------------------------------------------------------------------
 * Functions.
 * ----------------------------------------------------------------------------
 */
/**
 * Parses file at \p file_path and saves parsed information to \p out.
 * @param	file_path	Path to a .cub file.
 * @param	out			Output.
 * @return	-1, if something went wrong. errno will also be set;
 * 			Some non-negative value, if everything went fine.
 */
int		ft_parse(const char *file_path, struct s_args *out);

/**
 * Checks if all textures and colors in \p args are set.
 * @param	args	Arguments to check.
 * @return	true, if all textures and colors are set;
 * 			false otherwise.
 */
bool	ft_check_textures_and_colors_set(t_args *args);

/**
 * Checks if a \p line contains only whitespaces.
 * @param	line	Input string.
 * @return	true, if string is empty, NULL or contains only white spaces;
 * 			false otherwise.
 */
bool	ft_string_isspace(const char *line);

/**
 * Check if file stored at \p path ends with \p ext.
 * @param	path	Path to file.
 * @param	ext		File extension to check (excluding '.').
 * @return	true, if does; false otherwise.
 */
bool	ft_check_file_ext(const char *path, const char *ext);

/**
 * Checks if the provided \p path is a directory.
 * @param	path	Path to check.
 * @return	true, if yes; false otherwise.
 */
bool	ft_path_is_dir(const char *path);

/**
 * Checks if file at \p path is .cub (if \p cub is true) or .xpm,
 * and if it's possible to open it.
 * @param	path	Path to file to check.
 * @param	cub		true, if should check for ".cub",
 * 					false, if should check for ".xpm".
 * @return	0 on success, some other value on failure.
 */
int		ft_check_file(const char *path, bool cub);

#endif /* PARSE_H */
