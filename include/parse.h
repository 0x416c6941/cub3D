/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:00:08 by asagymba          #+#    #+#             */
/*   Updated: 2025/01/24 02:18:19 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <cub3D.h>
# include <stdbool.h>

/**
 * ----------------------------------------------------------------------------
 * Constants.
 * ----------------------------------------------------------------------------
 */
# define DEFAULT_TAB_WIDTH	8

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
 * If any error is encountered, error log will be written to stderr.
 * @param	file_path	Path to a .cub file.
 * @param	out			Output.
 * @return	0 on success; error code otherwise.
 * 			Some non-negative value, if everything went fine.
 */
int		ft_parse(const char *file_path, struct s_args *out);

/**
 * Checks if \p map around the player is closed or not.
 * @param	map	Pointer to the head of the map linked list.
 * @return	0 if the map is surrounded by walls; error code otherwise.
 */
int		ft_is_map_closed(t_list *map);

/**
 * Return the number of player characters in the map.
 * Ensures that the map contains exactly one player character
 * (characters 'N', 'S', 'E' or 'W').
 * @warning	It's your responsibility to make sure \p map isn't NULL.
 * @param	map	Pointer to the head of the map linked list.
 * @return	Number of player characters.
 */
int		ft_player_count(t_list *map);

/**
 * Iterates through the entire \p map and replaces all tabs with spaces.
 * @param	map			Pointer to the head of the map linked list.
 * @param	tab_width	Width of each tab stop (use DEFAULT_TAB_WIDTH for 8).
 * @return	0 on success; error code otherwise.
 */
int		ft_process_tabs_in_map(t_list *map, int tab_width);

int		ft_save_colors(char *line, t_args *args, int index);

/**
 * Saves a texture file path to \p args.
 * @param	line	The line containing the texture identifier and file path.
 * @param	args	Pointer to the structure where textures' paths are stored.
 * @param	index	The index in the "textures" array to store the texture path.
 * @return	0 on success; error code otherwise.
 */
int		ft_save_textures(char *line, struct s_args *args, int index);

/**
 * In map stored in \p args:
 * Removes all empty lines;
 * replace tabs with spaces;
 * replace spaces with '0';
 * check if map is closed;
 * check if there is only one player position;
 * check if there are only valid characters.
 * This function is massive, however it makes sense in our case.
 * @brief	Does all required checks and map modifications.
 * @param	args	Pointer to arguments, containing the map
 * 					to validate and modify (clean / extend).
 * @return	0 on success; error code otherwise.
 */
int		ft_map_clean_validate(struct s_args *args);

/**
 * -------- ft_map_clean_validate utils. --------
 */
/**
 * This function iterates through the \p map and removes any
 * line that is either empty or contains only spaces or tabs.
 * @brief	Removes all empty lines from the \p map.
 * @param	map	Double pointer to the head of the map linked list.
 * @return	0 on success; error code otherwise.
 */
int		ft_remove_all_empty_lines(t_list **map);

/**
 * If the last character in the string is '\n', it is replaced with the
 * null terminator ('\0'), effectively removing it.
 * @brief	Removes the trailing newline character ('\n') from a \p line.
 * @param	line	The input string to process.
 * @return	0 on success; error code otherwise, e.g. if input is invalid.
 */
int		ft_remove_newline(char *line);

/**
 * Find the maximum line length in the \p map.
 * @param	map	Pointer to the head of the map linked list.
 * @return	Maximum line length;
 * 			-1 if the map is NULL or empty.
 */
int		ft_find_max_length(t_list *map);

/**
 * Pads a \p line to the required length by appending the \p pad_char
 * until it reaches the specified \p max_length.
 * @param	line		The original line to pad.
 * @param	max_length	The required length of the line after padding.
 * @param	pad_char	The character used for padding (e.g., ' ' or '0').
 * @return	The padded line; NULL on failure.
 */
char	*ft_pad_line_to_length(const char *line, int max_length, char pad_char);

/**
 * Checks that all characters in the map are either '1', '0'
 * or one of the player characters ('N', 'S', 'E' or 'W').
 * @param	map	Pointer to the head of the map linked list.
 * @return	0 if valid; error code otherwise.
 */
int		ft_check_valid_characters(t_list *map);

/**
 * -------- Utils. --------
 */
/**
 * Checks if all textures and colors in \p args are set.
 * @param	args	Arguments to check.
 * @return	true, if all textures and colors are set;
 * 			false otherwise.
 */
bool	ft_check_textures_and_colors_set(struct s_args *args);

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
