/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlyshchu <hlyshchu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 19:29:26 by root              #+#    #+#             */
/*   Updated: 2025/01/24 18:49:37 by hlyshchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>
#include <errno.h>
#include <fcntl.h>
#include <libft.h>
#include <parse.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>
#include <utils.h>

/**
 * @brief Checks if all textures and colors are set in the args structure.
 *
 * This function verifies whether all textures and colors have been properly
 * initialized in the `t_args` structure. It ensures all texture pointers are
 * non-NULL and all color values are marked as set.
 *
 * @param args A pointer to the `t_args` structure to validate.
 * @return bool Returns true if all textures and colors are set,
	otherwise false.
 */
bool	ft_check_textures_and_colors_set(t_args *args)
{
	int	i;

	i = 0;
	while (i < TEXTURES_SIZE)
	{
		if (args->textures[i] == NULL)
			return (false);
		i++;
	}
	i = 0;
	while (i < COLORS_SIZE)
	{
		if (!args->colors[i].set)
			return (false);
		i++;
	}
	return (true);
}

/**
 * @brief Checks if a string is NULL or contains only whitespace characters.
 *
 * This function iterates through the given string and verifies whether all
 * characters are whitespace (as determined by `ft_isspace`). If the string
 * is NULL, it is considered to contain only whitespace.
 * 
 * @param line The input string to check.
 * @return bool Returns true if the string is NULL or contains only whitespace
 * characters; otherwise, returns false.
 */
bool	ft_string_isspace(const char *line)
{
	if (line == NULL)
		return (true);
	while (*line != '\0')
	{
		if (!ft_isspace(*line))
			return (false);
		line++;
	}
	return (true);
}
/**
 * @brief Checks if a file path has the specified extension.
 *
 * This function verifies whether the given file path ends with the specified
 * extension. It ensures that the extension is preceded by a dot ('.') and is
 * not longer than the file path itself.
 * 
 * @param path The file path to check.
 * @param ext The expected file extension (e.g., "cub", "xpm").
 * @return bool Returns true if the file path has the specified extension;
 * otherwise, returns false.
 */

bool	ft_check_file_ext(const char *path, const char *ext)
{
	size_t	path_len;
	size_t	ext_len;

	path_len = ft_strlen(path);
	ext_len = ft_strlen(ext);
	if (path_len <= ext_len || path[path_len - ext_len - 1] != '.'
		|| ft_strcmp((path + path_len) - ext_len, ext) != 0)
		return (false);
	return (true);
}

/**
 * @brief Checks if the given path points to a directory.
 *
 * This function determines whether the provided path corresponds to a directory
 * by attempting to open it with the `O_DIRECTORY` flag. If the path is a
 * directory, the function returns true; otherwise, it returns false.
 * 
 * @param path The file system path to check.
 * @return bool Returns true if the path is a directory, otherwise false.
 */

bool	ft_path_is_dir(const char *path)
{
	int	fd;

	fd = open(path, O_DIRECTORY);
	if (fd == -1)
		return (false);
	return ((void)close(fd), true);
}

/**
 * @brief Validates a file path, ensuring it is accessible and has the correct 
 * 	extension.
 *
 * This function checks if the given file path is accessible for reading and
 * optionally validates its extension. If the `cub` flag is true, the function
 * ensures the file has a `.cub` extension. Otherwise, it checks for a `.xpm`
 * extension. The function also ensures the path is not a directory.
 * 
 * @param path The file path to validate.
 * @param cub A flag indicating whether to check for a `.cub` extension (true)
 * or a `.xpm` extension (false).
 * @return int Returns 0 if the file is valid, or an error code if the file
 * is invalid, inaccessible, or has the wrong extension.
 */
int	ft_check_file(const char *path, bool cub)
{
	int	fd;

	if (ft_path_is_dir(path))
		return (ft_errmsg(path, "Is a directory", EISDIR));
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (ft_errmsg(path, strerror(errno), errno));
	(void)close(fd);
	if (cub && !ft_check_file_ext(path, "cub"))
		return (ft_errmsg(path, "Not a .cub file", EINVAL));
	else if (!cub && !ft_check_file_ext(path, "xpm"))
		return (ft_errmsg(path, "Not a .xpm file", EINVAL));
	return (0);
}
