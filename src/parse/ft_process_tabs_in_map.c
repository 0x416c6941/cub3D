/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_tabs_in_map.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlyshchu <hlyshchu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 10:38:05 by root              #+#    #+#             */
/*   Updated: 2025/01/24 18:44:00 by hlyshchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>
#include <parse.h>
#include <errno.h>
#include <libft.h>
#include <stdlib.h>
#include <utils.h>

/**
 * Calculates the size of \p line with tabs replaced by spaces.
 * @param	line		The input string (line of the map).
 * @param	tab_width	Width of each tab stop (use DEFAULT_TAB_WIDTH for 8).
 * @return	The required size for the resulting string;
 * 			-1 on failure.
 */
static int	ft_calculate_space_for_tabs(const char *line, int tab_width)
{
	int	size;
	int	cursor_pos;

	if (!line || tab_width <= 1)
		return (-1);
	size = 0;
	cursor_pos = 0;
	while (*line)
	{
		if (*line == '\t')
		{
			size += tab_width - (cursor_pos % tab_width);
			cursor_pos += tab_width - (cursor_pos % tab_width);
		}
		else
		{
			size++;
			cursor_pos++;
		}
		line++;
	}
	return (size);
}

/**
 * Copies the \p input string to the \p output string, replacing each tab
 * ('\t') with the appropriate number of spaces.
 * Assumes the output buffer is pre-allocated with sufficient space.
 * @brief	Expands tabs in the \p input string into spaces.
 * @param	input		The input string (line of the map).
 * @param	output		The output string (pre-allocated).
 * @param	tab_width	Width of each tab stop (use DEFAULT_TAB_WIDTH for 8).
 */
static void	ft_expand_tabs(const char *input, char *output, int tab_width)
{
	int	cursor_pos;
	int	spaces_needed;

	cursor_pos = 0;
	while (*input != '\0')
	{
		if (*input == '\t')
		{
			spaces_needed = tab_width - (cursor_pos % tab_width);
			while (spaces_needed-- > 0)
				*output++ = ' ';
			cursor_pos += tab_width - (cursor_pos % tab_width);
		}
		else
		{
			*output++ = *input;
			cursor_pos++;
		}
		input++;
	}
	*output = '\0';
}

/**
 * Detabs a single \p line with \p tab_width spaces.
 * @param	line		The input string (line of the map).
 * @param	tab_width	Width of each tab stop (use DEFAULT_TAB_WIDTH for 8).
 * @return	A new string with tabs replaced; NULL on failure.
 */
static char	*ft_replace_tabs(const char *line, int tab_width)
{
	int		required_size;
	char	*result;

	if (line == NULL)
		return (NULL);
	required_size = ft_calculate_space_for_tabs(line, tab_width);
	if (required_size < 0)
		return (NULL);
	result = (char *)malloc(((size_t)required_size + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	ft_expand_tabs(line, result, tab_width);
	return (result);
}

/**
 * @brief Replaces tabs in the map with spaces of a specified width.
 *
 * This function iterates through a linked list (`t_list`) of strings 
 * representing the map. It replaces all tabs ('\t') in each line with spaces 
 * based on the specified tab width. The original lines are freed and replaced 
 * with the new modified lines.
 * 
 * @param map A pointer to the head of the linked list of strings representing
 * the map.
 * @param tab_width The number of spaces to replace each tab with (must be > 1).
 * @return int Returns 0 on success, or an error code if an error occurs.
 */

int	ft_process_tabs_in_map(t_list *map, int tab_width)
{
	t_list	*current;
	char	*new_line;
	char	*original_line;

	if (map == NULL || tab_width <= 1)
		return (ft_errmsg("Invalid arguments", "Map invalid or tab width < 2",
				EINVAL));
	current = map;
	while (current != NULL)
	{
		original_line = (char *)current->content;
		if (original_line == NULL)
			return (ft_errmsg("Invalid map", "Line is NULL", EINVAL));
		new_line = ft_replace_tabs(original_line, tab_width);
		if (new_line == NULL)
			return (ft_errmsg("Memory allocation error",
					"Unable to replace tabs in line", ENOMEM));
		free(original_line);
		current->content = new_line;
		current = current->next;
	}
	return (0);
}
