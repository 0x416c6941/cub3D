/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_map_closed.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlyshchu <hlyshchu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 11:50:57 by root              #+#    #+#             */
/*   Updated: 2025/01/24 18:30:49 by hlyshchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>
#include <parse.h>
#include <errno.h>
#include <libft.h>
#include <stdlib.h>
#include <utils.h>

/**
 * Frees the 2D \p map_array.
 * @param	map_array	The map saved as 2D char array to free.
 * @param	rows		The number of rows in the array.
 */
static void	ft_free_map_array(char **map_array, int rows)
{
	int	i;

	i = 0;
	while (i < rows)
		free(map_array[i++]);
	free(map_array);
}

/**
 * Finds the player's starting position in the \p map.
 * Searches the 2D char array for the player's starting position
 * (character 'N', 'S', 'E' or 'W')
 * and updates the "player_x", "player_y",
 * and "player_sign" fields in the \p info.
 * @param	map		2D char array representing the map.
 * @param	info	Pointer to the structure containing \p map's info.
 * @return	0 if the player is found; -1 otherwise.
 */
static int	ft_find_player(char **map, t_map_info *info)
{
	int	x;
	int	y;

	if (!map || !info)
		return (-1);
	y = 0;
	while (y < info->rows)
	{
		x = 0;
		while (x < info->cols)
		{
			if (map[y][x] == 'N' || map[y][x] == 'S' || map[y][x] == 'E'
				|| map[y][x] == 'W')
			{
				info->player_x = x;
				info->player_y = y;
				info->player_sign = map[y][x];
				return (0);
			}
			x++;
		}
		y++;
	}
	return (-1);
}

/**
 * Allocates a 2D char array from the linked list for easier validation and
 * fills the "rows" and "cols" fields in \p info.
 * @brief	Converts a \p map to a 2D array and populates maps \p info.
 * @param	map		Pointer to the map's linked list.
 * @param	info	Pointer where to save maps info.
 * @return	\p map saved as 2D array;
 * 			NULL on failure.
 */
static char	**ft_map_to_array(t_list *map, t_map_info *info)
{
	t_list	*current;
	char	**array;
	int		i;

	if (map == NULL || info == NULL)
		return (NULL);
	info->rows = ft_lstsize(map);
	info->cols = ft_strlen((char *)map->content);
	array = (char **)malloc((size_t)(info->rows) * sizeof(char *));
	if (array == NULL)
		return (NULL);
	current = map;
	i = 0;
	while (current != NULL)
	{
		array[i] = ft_strdup((char *)current->content);
		if (array[i++] == NULL)
		{
			ft_free_map_array(array, i - 1);
			return (NULL);
		}
		current = current->next;
	}
	return (array);
}

/**
 * @brief Recursively performs a flood-fill algorithm to validate or mark a map.
 *
 * This function traverses and validates a 2D map represented as a character
 * grid. It recursively fills the map from a starting point `(x, y)`, marking
 * visited cells with 'X'. The function also checks for boundary conditions or
 * invalid cells (e.g., spaces ' ') and returns `-1` if an error is encountered.
 *
 * @param map A 2D character array representing the map.
 * @param info A struct containing map metadata (e.g., rows and columns).
 * @param x The current x-coordinate in the map.
 * @param y The current y-coordinate in the map.
 * @return int Returns 0 if successful, or -1 if an invalid cell is encountered.
 */

static int	ft_flood_fill(char **map, t_map_info info, int x, int y)
{
	if (x < 0 || x >= info.cols || y < 0 || y >= info.rows
		|| map[y][x] == ' ')
		return (-1);
	if (map[y][x] == '1' || map[y][x] == 'X')
		return (0);
	map[y][x] = 'X';
	if (ft_flood_fill(map, info, x + 1, y + 1) == -1)
		return (-1);
	if (ft_flood_fill(map, info, x + 1, y - 1) == -1)
		return (-1);
	if (ft_flood_fill(map, info, x - 1, y + 1) == -1)
		return (-1);
	if (ft_flood_fill(map, info, x - 1, y - 1) == -1)
		return (-1);
	if (ft_flood_fill(map, info, x + 1, y) == -1)
		return (-1);
	if (ft_flood_fill(map, info, x - 1, y) == -1)
		return (-1);
	if (ft_flood_fill(map, info, x, y + 1) == -1)
		return (-1);
	if (ft_flood_fill(map, info, x, y - 1) == -1)
		return (-1);
	return (0);
}

/**
 * This function uses flood fill to ensure the map is fully enclosed by walls.
 * It starts from the player's position ('N', 'S', 'E', 'W') and checks
 * for any escape routes (reaching the edges of the map).
 * @brief	Validates if the \p map is surrounded by walls using flood fill.
 * @param	map	Pointer to the head of the map linked list.
 * @return	0 if the map is surrounded by walls; error code otherwise.
 */
int	ft_is_map_closed(t_list *map)
{
	t_map_info	info;
	char		**map_array;
	int			exit_code;

	map_array = ft_map_to_array(map, &info);
	if (map_array == NULL)
		return (ft_errmsg("Memory allocation error",
				"Failed to convert map to array", ENOMEM));
	if (ft_find_player(map_array, &info) < 0)
	{
		ft_free_map_array(map_array, info.rows);
		return (ft_errmsg("Invalid map", "No player found in the map", EINVAL));
	}
	map_array[info.player_y][info.player_x] = '0';
	exit_code = ft_flood_fill(map_array, info, info.player_x, info.player_y);
	ft_free_map_array(map_array, info.rows);
	if (exit_code != 0)
		return (ft_errmsg("Invalid map", "Map is not surrounded by walls",
				EINVAL));
	return (exit_code);
}
