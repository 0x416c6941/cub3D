/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 19:29:26 by root              #+#    #+#             */
/*   Updated: 2025/01/24 02:22:56 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>
#include <parse.h>
#include <stdbool.h>
#include <stddef.h>
#include <libft.h>
#include <utils.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

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

bool	ft_string_isspace(const char *line)
{
	if (line == NULL)
		return (true);
	while (*line != '\0')
	{
		if (!ft_isspace(*((int *)line)))
			return (false);
		line++;
	}
	return (true);
}

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

bool	ft_path_is_dir(const char *path)
{
	int		fd;

	fd = open(path, O_DIRECTORY);
	if (fd == -1)
		return (false);
	return ((void)close(fd), true);
}

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
