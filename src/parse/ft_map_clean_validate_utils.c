/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_clean_validate_utils.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlyshchu <hlyshchu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 10:33:09 by root              #+#    #+#             */
/*   Updated: 2025/01/24 18:43:19 by hlyshchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * This file contains literally everything
 * ft_map_clean_validate.c couldn't contain due to Norminette.
 */

#include <cub3D.h>
#include <parse.h>
#include <errno.h>
#include <libft.h>
#include <stdlib.h>
#include <utils.h>

/**
 * @brief Removes all empty or whitespace-only lines from a linked list.
 *
 * This function iterates through a linked list of strings (`t_list`) and removes
 * any nodes containing an empty string or a string consisting only of 
 * whitespace.
 * 
 * @param map A double pointer to the head of the linked list.
 * @return int Returns 0 on success, or an error code if the input is invalid.
 */

int	ft_remove_all_empty_lines(t_list **map)
{
	t_list	**current;
	t_list	*next;

	if (map == NULL || *map == NULL)
		return (ft_errmsg("Invalid map", "Map is NULL", EINVAL));
	current = map;
	while (*current != NULL)
	{
		if (((char *)(*current)->content)[0] == '\0'
			|| ft_string_isspace((char *)(*current)->content))
		{
			next = (*current)->next;
			ft_lstdelone(*current, free);
			*current = next;
		}
		else
			current = &((*current)->next);
	}
	return (0);
}

/**
 * @brief Removes a trailing newline character from a string, if present.
 *
 * This function checks if the given string ends with a newline character ('\n')
 * and removes it by replacing it with a null terminator ('\0'). If the string
 * is NULL, an error is returned.
 * 
 * @param line A pointer to the string to process.
 * @return int Returns 0 on success, or an error code if the input is invalid.
 */

int	ft_remove_newline(char *line)
{
	int	length;

	if (line == NULL)
		return (ft_errmsg("Invalid line", "Line is NULL", EINVAL));
	length = ft_strlen(line);
	if (length > 0 && line[length - 1] == '\n')
		line[length - 1] = '\0';
	return (0);
}

/**
 * @brief Finds the maximum line length in a linked list of strings.
 *
 * This function iterates through a linked list (`t_list`) of strings, computes
 * the length of each string, and returns the length of the longest string. If
 * the input list is NULL, an error is returned.
 * 
 * @param map A pointer to the head of the linked list of strings.
 * @return int Returns the maximum line length, or an error code if the input
 * is invalid.
 */

int	ft_find_max_length(t_list *map)
{
	int	max_length;
	int	line_length;

	if (map == NULL)
		return (ft_errmsg("Invalid map", "Map is NULL", EINVAL));
	max_length = 0;
	while (map != NULL)
	{
		line_length = ft_strlen((char *)map->content);
		if (line_length > max_length)
			max_length = line_length;
		map = map->next;
	}
	return (max_length);
}

/**
 * @brief Pads a string to a specified length with a given character.
 *
 * This function creates a new string by copying the input string and padding
 * it with the specified character until it reaches the desired length. If the
 * input string already matches the desired length, a duplicate is returned.
 * 
 * @param line The input string to pad.
 * @param max_length The target length of the padded string.
 * @param pad_char The character used for padding.
 * @return char* A newly allocated padded string, or NULL on error.
 */

char	*ft_pad_line_to_length(const char *line, int max_length, char pad_char)
{
	char	*new_line;
	int		line_length;
	int		padding_needed;

	if (line == NULL || max_length <= 0)
		return (NULL);
	line_length = ft_strlen(line);
	if (line_length == max_length)
		return (ft_strdup(line));
	padding_needed = max_length - line_length;
	new_line = malloc((size_t)(max_length + 1) * sizeof(char));
	if (new_line == NULL)
		return (NULL);
	ft_memcpy(new_line, line, (size_t)line_length);
	ft_memset(new_line + line_length, pad_char, (size_t)padding_needed);
	new_line[max_length] = '\0';
	return (new_line);
}

/**
 * @brief Validates that all characters in a map are valid.
 *
 * This function iterates through a linked list (`t_list`) of strings 
 * representing the map. It ensures that each character in the map is one of 
 * the allowed characters: '1', '0', 'N', 'S', 'E', 'W', or ' ' (space). If an 
 * invalidcharacter is found, an error is returned.
 * 
 * @param map A pointer to the head of the linked list of strings representing
 * the map.
 * @return int Returns 0 if all characters are valid, or an error code if an
 * invalid character is encountered.
 */

int	ft_check_valid_characters(t_list *map)
{
	t_list	*current;
	char	*line;
	int		i;

	current = map;
	while (current != NULL)
	{
		line = (char *)current->content;
		i = 0;
		while (line[i] != '\0')
		{
			if (line[i] != '1' && line[i] != '0' && line[i] != 'N'
				&& line[i] != 'S' && line[i] != 'E' && line[i] != 'W'
				&& line[i] != ' ')
				return (ft_errmsg("Invalid map",
						"Map contains invalid characters", EINVAL));
			i++;
		}
		current = current->next;
	}
	return (0);
}
