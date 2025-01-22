/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 21:10:31 by root              #+#    #+#             */
/*   Updated: 2025/01/22 21:37:39 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <utils.h>

/**
 * @brief Checks if the given path is a directory.
 *
 * This function attempts to open the path as a directory. If successful, it
 * confirms that the path is a directory and returns true.
 *
 * @param path The path to check.
 * @return true if the path is a directory, false otherwise.
 */
static bool	path_is_dir(const char *path)
{
	int		fd;
	bool	res;

	res = false;
	fd = open(path, O_DIRECTORY);
	if (fd >= 0)
	{
		close(fd);
		res = true;
	}
	return (res);
}

static bool	check_cub_ext(const char *path)
{
	size_t	len;

	len = ft_strlen(path);
	if (len < 4 || (path[len - 3] != 'c' || path[len - 2] != 'u' || path[len
			- 1] != 'b' || path[len - 4] != '.'))
		return (false);
	return (true);
}

static bool	check_xpm_ext(const char *path)
{
	size_t	len;

	len = ft_strlen(path);
	if (len < 4 || (path[len - 3] != 'x' || path[len - 2] != 'p' || path[len
			- 1] != 'm' || path[len - 4] != '.'))
		return (false);
	return (true);
}

/**
 * @brief  Checks if the given file is a valid .cub or .xpm file and it's
 * 	possible to open
 *
 * @param path path to file
 * @param cub true if the file should be a .cub file
 * @return int	0 in SUCCESS
 */
int	check_file(const char *path, bool cub)
{
	int	fd;

	if (path_is_dir(path))
		return (ft_errmsg(path, "Is a directory", EISDIR));
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (ft_errmsg(path, strerror(errno), errno));
	close(fd);
	if (cub && !check_cub_ext(path))
		return (ft_errmsg(path, "Not a .cub file", EINVAL));
	if (!cub && !check_xpm_ext(path))
		return (ft_errmsg(path, "Not a .xpm file", EINVAL));
	return (0);
}
