/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_clean_validate.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 09:20:52 by root              #+#    #+#             */
/*   Updated: 2025/01/24 02:06:10 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>
#include <parse.h>
#include <errno.h>
#include <libft.h>
#include <stdlib.h>
#include <utils.h>

/**
 * Skips leading empty lines and ensures no empty lines
 * and lines with only spaces appear in the middle of the \p map.
 * Trailing empty lines (or lines with spaces) after the \p map ends are valid.
 * @brief	Checks for empty lines in the middle of the \p map.
 * @param	map	Pointer to the head of the map linked list.
 * @return	0 if valid; error code otherwise.
 */
static int	ft_check_empty_lines_in_map(t_list *map)
{
	bool	map_started;
	bool	map_ended;
	char	*line;

	map_started = false;
	map_ended = false;
	while (map)
	{
		line = (char *)map->content;
		if (line[0] == '\0' || ft_string_isspace(line))
		{
			if (map_started)
				map_ended = true;
		}
		else
		{
			if (map_ended)
				return (ft_errmsg("Invalid map",
						"Empty line in the middle of the map", EINVAL));
			map_started = true;
		}
		map = map->next;
	}
	return (0);
}

/**
 * This function:
 * 1. Finds the maximum line length in the \p map.
 * 2. Pads all shorter lines to match the maximum length using the specified
 *    \p pad_char by calling ft_pad_line_to_length() for each line.
 * @brief	Uniforms the \p map by making all lines the same length.
 * @param	map			Pointer to the head of the map linked list.
 * @param	pad_char	The character used for padding (e.g., ' ' or '0').
 * @return	0 on success; error code otherwise.
 */
static int	ft_uniform_map(t_list *map, char pad_char)
{
	int		max_length;
	char	*new_line;
	t_list	*current;

	if (map == NULL)
		return (ft_errmsg("Invalid map", "Map is NULL", EINVAL));
	max_length = ft_find_max_length(map);
	if (max_length < 0)
		return (ft_errmsg("Error finding max length", "Map is empty", EINVAL));
	current = map;
	while (current != NULL)
	{
		new_line = ft_pad_line_to_length((char *)current->content, max_length,
				pad_char);
		if (!new_line)
			return (ft_errmsg("Memory allocation error",
					"ft_pad_line_to_length failed", ENOMEM));
		free(current->content);
		current->content = new_line;
		current = current->next;
	}
	return (0);
}

/**
 * Iterates through the linked list of \p map lines and removes
 * the trailing newline character ('\n') from each line.
 * @brief	Removes trailing newline characters from all lines in the \p map.
 * @param	map Pointer to the head of the map linked list.
 * @return	0 on success; error code otherwise.
 */
static int	ft_remove_newlines_from_map(t_list *map)
{
	t_list	*current;

	if (map == NULL)
		return (ft_errmsg("Invalid map", "Map is NULL", EINVAL));
	current = map;
	while (current != NULL)
	{
		if (ft_remove_newline((char *)current->content) != 0)
			return (EINVAL);
		current = current->next;
	}
	return (0);
}

/**
 * Combines checks for valid characters and player presence.
 * @brief	Validates the \p map for valid characters and exactly one player.
 * @param	map	Pointer to the head of the map linked list.
 * @return	0 if valid; error code otherwise.
 */
static int	ft_validate_map_characters_and_player(t_list *map)
{
	int	exit_code;
	int	player_count;

	if (map == NULL)
		return (ft_errmsg("Invalid map", "Map is NULL", EINVAL));
	player_count = ft_player_count(map);
	if (player_count == 0)
		return (ft_errmsg("Invalid map", "No player found in the map", EINVAL));
	else if (player_count > 1)
		return (ft_errmsg("Invalid map", "Multiple players found in the map",
				EINVAL));
	exit_code = ft_check_valid_characters(map);
	if (exit_code != 0)
		return (exit_code);
	return (0);
}

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
int	ft_map_clean_validate(struct s_args *args)
{
	if (args == NULL)
		return (ft_errmsg("Invalid arguments", "Null ptr provided", EINVAL));
	if (args->map == NULL)
		return (ft_errmsg("Invalid map", "Map is empty", EINVAL));
	if (ft_check_empty_lines_in_map(args->map) != 0)
		return (EINVAL);
	if (ft_remove_all_empty_lines(&(args->map)) != 0)
		return (EINVAL);
	if (ft_process_tabs_in_map(args->map, DEFAULT_TAB_WIDTH) != 0)
		return (EINVAL);
	if (ft_remove_newlines_from_map(args->map) != 0)
		return (EINVAL);
	if (ft_validate_map_characters_and_player(args->map) != 0)
		return (EINVAL);
	if (ft_uniform_map(args->map, '0') != 0)
		return (EINVAL);
	if (ft_is_map_closed(args->map) != 0)
		return (EINVAL);
	return (0);
}
