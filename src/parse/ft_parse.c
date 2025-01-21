/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlyshchu <hlyshchu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:10:25 by asagymba          #+#    #+#             */
/*   Updated: 2025/01/21 16:27:37 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>
#include <fcntl.h>
#include <libft.h>
#include <stdlib.h>
#include <unistd.h>

static int	ft_save_textures(char *line, struct s_args *out, int identifier)
{
	if (!line || !out || identifier < 0 || identifier >= TEXTURES_SIZE)
		return (-1);
	if (out->textures[identifier])
	{
		errno = DUP_PAR;
		return (-1);
	}
	out->textures[identifier] = ft_strdup(line);
	if (!out->textures[identifier])
		return (-1);
	out->map_info_added++;
	return (0);
}

static int	ft_save_colors(char *line, struct s_args *out, int identifier)
{
	if (!line || !out)
		return (-1);
	// To temporarily bypass compilation error:
	(void)identifier;
	// out->colors[identifier] = line;
	out->map_info_added++;
	return (0);
}

static int	ft_line_manager(char *line, struct s_args *out)
{
	char	*trimmed;

	if (!line)
		return (-1);
	else if (*line == '\0')
		return (0);
	if (out->map_info_added < 6)
	{
		trimmed = ft_strtrim(line, " \t\n");
		if (!trimmed)
			return (-1);
	}
	else
		ft_lstadd_back(&out->map, ft_lstnew(line));
	if (ft_strncmp(trimmed, "NO", 2) == 0)
		return (ft_save_textures(trimmed, out, TEXTURE_NO));
	else if (ft_strncmp(trimmed, "SO", 2) == 0)
		return (ft_save_textures(trimmed, out, TEXTURE_SO));
	else if (ft_strncmp(trimmed, "WE", 2) == 0)
		return (ft_save_textures(trimmed, out, TEXTURE_WE));
	else if (ft_strncmp(trimmed, "EA", 2) == 0)
		return (ft_save_textures(trimmed, out, TEXTURE_EA));
	else if (ft_strncmp(trimmed, "F", 1) == 0)
		return (ft_save_colors(trimmed, out, COLOR_FLOOR));
	else if (ft_strncmp(trimmed, "C", 1) == 0)
		return (ft_save_colors(trimmed, out, COLOR_CEILING));
	errno = INV_PAR;
	return (-1);
}

static int	ft_read_file_to_struct(int fd, struct s_args *out)
{
	char	*line;

	line = get_next_line(fd);
	while (*line)
	{
		if (ft_line_manager(line, out) == -1)
		{
			free(line);
			return (-1);
		}
		free(line);
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	// Temporarily to bypass compilation error (no return value before):
	return (0);
}

int	ft_parse(const char *file_path, struct s_args *out)
{
	int	file;

	file = open(file_path, O_RDONLY);
	if (file == -1)
		return (-1);
	(void)ft_memset(out, 0, sizeof(struct s_args));
	if (ft_read_file_to_struct(file, out) == -1)
	{
		close(file);
		return (-1);
	}
	close(file);
	return (0);
}
