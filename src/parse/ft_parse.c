/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:10:25 by asagymba          #+#    #+#             */
/*   Updated: 2025/01/22 21:22:43 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>
#include <errno.h>
#include <fcntl.h>
#include <libft.h>
#include <parse.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <utils.h>

/**
 * @brief Processes a single line of the map and adds it to `out->map`.
 *
 * Validates the line to ensure it adheres to the map structure rules:
 * - No empty lines are allowed in the middle of the map.
 * - Appends non-empty lines to the map linked list.
 *
 * @param line The line to process (guaranteed non-NULL).
 * @param out The structure to store the map (guaranteed non-NULL).
 * @return int 0 on success, or a negative error code on failure.
 */
static int	ft_process_map_line(char *line, struct s_args *out)
{
	t_list	*node;

	if (*line == '\0' || ((ft_string_isspace(line) && out->map == NULL)))
		return (0);
	node = ft_lstnew(ft_strdup(line));
	if (!node)
		return (ft_errmsg("Memory allocation error", "ft_strdup", ENOMEM));
	if (out->map == NULL)
		out->map = node;
	else
		ft_lstadd_back(&out->map, node);
	return (0);
}

/**
 * @brief Processes a parameter line and saves the data to `out`.
 *
 * Parses the line to identify a texture or color parameter. If the line is
 * empty or whitespace-only, it is ignored. Trims spaces and validates the
 * parameter before saving it to `out`.
 *
 * Supported parameters:
 * - NO, SO, WE, EA: Texture paths.
 * - F, C: Floor and ceiling colors in RGB (e.g., F 220,100,0).
 *
 * @param line Non-NULL string containing the line to process.
 * @param out Non-NULL pointer to the structure to store parsed data.
 * @return int 0 on success, or a negative error code.
 *
 * Errors:
 * - EINVAL: Invalid parameter or format.
 * - ENOMEM: Memory allocation failure.
 *
 */
static int	ft_process_params_line(char *line, struct s_args *out)
{
	char	*trimmed;
	int		result;

	if (*line == '\0' || ft_string_isspace(line))
		return (0);
	trimmed = ft_strtrim(line, " \t\n");
	if (!trimmed)
		return (ft_errmsg("Memory allocation error", "ft_strtrim", ENOMEM));
	if (ft_strncmp(trimmed, "NO ", 3) == 0)
		result = ft_save_textures(trimmed, out, TEXTURE_NO);
	else if (ft_strncmp(trimmed, "SO ", 3) == 0)
		result = ft_save_textures(trimmed, out, TEXTURE_SO);
	else if (ft_strncmp(trimmed, "WE ", 3) == 0)
		result = ft_save_textures(trimmed, out, TEXTURE_WE);
	else if (ft_strncmp(trimmed, "EA ", 3) == 0)
		result = ft_save_textures(trimmed, out, TEXTURE_EA);
	else if (ft_strncmp(trimmed, "F ", 2) == 0)
		result = ft_save_colors(trimmed, out, COLOR_FLOOR);
	else if (ft_strncmp(trimmed, "C ", 2) == 0)
		result = ft_save_colors(trimmed, out, COLOR_CEILING);
	else
		result = ft_errmsg("Invalid parameter", trimmed, EINVAL);
	free(trimmed);
	return (result);
}

/**
 * @brief Processes a single line from the input file.
 *
 * This function determines whether the line belongs to the "parameters" phase
 * or the "map" phase, based on whether all textures and colors are set.
 * It then delegates the processing to the appropriate function.
 *
 * @param line The line to process.
 * @param out Pointer to the structure where parsed data is stored.
 * @return int 0 on success, or an error code on failure.
 */
static int	ft_process_line(char *line, t_args *out)
{
	if (!line || !out)
		return (ft_errmsg("Invalid arguments", "Null ptr provided", EINVAL));
	if (check_textures_and_colors_set(out))
		return (ft_process_map_line(line, out));
	else
		return (ft_process_params_line(line, out));
}

/**
 * @brief Should read all the file line by line and pass it to function that
 * 		will process the lines and parse them. In case error occurs should reed
 * 		until the end of file and return error exit_code
 *
 * @param fd
 * @param out
 * @return int
 */
static int	ft_process_file(int fd, t_args *out)
{
	bool	error;
	char	*line;
	int		exit_code;

	line = get_next_line(fd);
	error = false;
	while (line != NULL)
	{
		if (!error)
		{
			exit_code = ft_process_line(line, out);
			if (exit_code != 0)
				error = true;
		}
		free(line);
		line = get_next_line(fd);
	}
	// if (errno != 0)
	// 	exit_code = ft_errmsg("Read error", strerror(errno), errno);
	return (exit_code);
}

/**
	* @brief Parse function to open a file, process it, validate data,
	and handle cleanup.
	*
	* This function opens the specified file,
		processes it using `ft_process_file`,
	* validates the parsed data using `validate_data`,
		and ensures the file is
	* closed properly. Errors during any step are handled gracefully.
	* @warning need to add file_path validation
	* @param file_path Path to the input file.
	* @param out Pointer to the output structure for parsed data.
	* @return int Returns 0 on success, or a negative error code on failure.
	*/
int	ft_parse(const char *file_path, t_args *out)
{
	int	file;
	int	exit_code;

	if (!file_path || !out)
		return (ft_errmsg("Invalid arguments", "Null ptr provided", EINVAL));
	exit_code = check_file(file_path, true);
	if (exit_code != 0)
		return (exit_code);
	file = open(file_path, O_RDONLY);
	if (file == -1)
		return (ft_errmsg(file_path, strerror(errno), errno));
	exit_code = ft_process_file(file, out);
	ft_print_t_args(out);
	// if (exit_code == 0)
	// 	exit_code = validate_data(out);
	if (close(file) == -1)
		return (ft_errmsg(file_path, strerror(errno), errno));
	return (exit_code);
}
