/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:10:25 by asagymba          #+#    #+#             */
/*   Updated: 2025/01/24 00:59:30 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>
#include <parse.h>
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
 * Processes a single \p line of the map and adds it to \p out->map.
 * Validates the line to ensure it adheres to the map structure rules:
 * - No empty lines are allowed in the middle of the map.
 * - Appends non-empty lines to the map linked list.
 * @param	line	Non-NULL line to process.
 * @param	out		Non-NULL pointer to structure to store the map.
 * @return	0 on success; error code otherwise.
 */
static int	ft_process_map_line(char *line, struct s_args *out)
{
	t_list	*node;

	if (*line == '\0' || ((ft_string_isspace(line) && out->map == NULL)))
		return (0);
	node = ft_lstnew(ft_strdup(line));
	if (node == NULL)
		return (ft_errmsg("Memory allocation error", "ft_strdup", ENOMEM));
	if (out->map == NULL)
		out->map = node;
	else
		ft_lstadd_back(&out->map, node);
	return (0);
}

/**
 * Parses the \p line to identify a texture or color parameter.
 * If the line is empty or whitespace only, it is ignored.
 * Trims spaces and validates the parameter before saving it to \p out.
 * Supported parameters:
 * - NO, SO, WE, EA: Texture paths.
 * - F, C: Floor and ceiling colors in RGB (e.g., F 220,100,0).
 * Errors:
 * - EINVAL: Invalid parameter or format.
 * - ENOMEM: Memory allocation failure.
 * @brief	Processes a parameter line and saves the data to \p out.
 * @param	line	Non-NULL string containing the line to process.
 * @param	out		Non-NULL pointer to the structure to store parsed data.
 * @return	0 on success, or a negative error code.
 */
static int	ft_process_params_line(char *line, struct s_args *out)
{
	char	*trimmed;
	int		result;

	if (*line == '\0' || ft_string_isspace(line))
		return (0);
	trimmed = ft_strtrim(line, " \t\n");
	if (trimmed == NULL)
		return (ft_errmsg("Memory allocation error", "ft_strtrim", ENOMEM));
	if (ft_strncmp(trimmed, "NO ", sizeof("NO ") - 1) == 0)
		result = ft_save_textures(trimmed, out, TEXTURE_NO);
	else if (ft_strncmp(trimmed, "SO ", sizeof("SO ") - 1) == 0)
		result = ft_save_textures(trimmed, out, TEXTURE_SO);
	else if (ft_strncmp(trimmed, "WE ", sizeof("WE ") - 1) == 0)
		result = ft_save_textures(trimmed, out, TEXTURE_WE);
	else if (ft_strncmp(trimmed, "EA ", sizeof("EA ") - 1) == 0)
		result = ft_save_textures(trimmed, out, TEXTURE_EA);
	else if (ft_strncmp(trimmed, "F ", sizeof("F ") - 1) == 0)
		result = ft_save_colors(trimmed, out, COLOR_FLOOR);
	else if (ft_strncmp(trimmed, "C ", sizeof("C ") - 1) == 0)
		result = ft_save_colors(trimmed, out, COLOR_CEILING);
	else
		result = ft_errmsg("Invalid parameter or map started with missing info",
				trimmed, EINVAL);
	free(trimmed);
	return (result);
}

/**
 * Processes a single \p line from the input file.
 * This function determines whether the line belongs to the "parameters" phase
 * or the "map" phase, based on whether all textures and colors are set.
 * It then delegates the processing to the appropriate function.
 * @param	line	The line to process.
 * @param	out		Pointer to the structure where parsed data is stored.
 * @return	0 on success; error code otherwise.
 */
static int	ft_process_line(char *line, struct s_args *out)
{
	if (line == NULL || out == NULL)
		return (ft_errmsg("Invalid arguments", "Null ptr provided", EINVAL));
	if (ft_check_textures_and_colors_set(out))
		return (ft_process_map_line(line, out));
	else
		return (ft_process_params_line(line, out));
}

/**
 * Reads all the file with file descriptor \p fd line by line
 * and passes it to function that will process the lines and parse them.
 * In case error occurs reads until the end of file,
 * and error message would be written to stderr.
 * @param	fd	File descriptor of the file to read.
 * @param	out	Where to save 
 * @return	0 on success; error code otherwise.
 */
static int	ft_process_file(int fd, t_args *out)
{
	int		exit_code;
	bool	error;
	char	*line;

	/* Should this be 1 instead by default?...
	 * Anyway, without this unconditional jump would occur.
	 * We don't want that, do we? */
	exit_code = 0;
	error = false;
	line = get_next_line(fd);
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
	if (errno != 0)
		exit_code = ft_errmsg("Read error", strerror(errno), errno);
	return (exit_code);
}

int	ft_parse(const char *file_path, struct s_args *out)
{
	int	file;
	int	exit_code;

	if (file_path == NULL || out == NULL)
		return (ft_errmsg("Invalid arguments", "Null ptr provided", EINVAL));
	exit_code = ft_check_file(file_path, true);
	if (exit_code != 0)
		return (exit_code);
	file = open(file_path, O_RDONLY);
	if (file == -1)
		return (ft_errmsg(file_path, strerror(errno), errno));
	exit_code = ft_process_file(file, out);
	if (exit_code == 0)
		exit_code = ft_map_clean_validate(out);
	ft_print_t_args(out);
	if (close(file) == -1)
		return (ft_errmsg(file_path, strerror(errno), errno));
	return (exit_code);
}
