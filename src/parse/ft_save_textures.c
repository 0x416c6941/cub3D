/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_save_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 20:23:45 by root              #+#    #+#             */
/*   Updated: 2025/01/22 21:33:44 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <utils.h>

/**
 * @brief Saves a texture file path to the `t_args` structure.
 *
 * This function validates the file path for a texture and stores it in the
 * appropriate index of the `textures` array within `t_args`. It prevents
 * overwriting textures that are already set.
 *
 * @param line The line containing the texture identifier and file path.
 * @param args Pointer to the `t_args` structure where textures are stored.
 * @param index The index in the `textures` array to store the texture.
 * @return int 0 on success, or a negative error code on failure.
 */
int	ft_save_textures(char *line, t_args *args, int index)
{
	char	*file_path;
	int		exit_status;

	exit_status = 0;
	if (args->textures[index] != NULL)
		return (ft_errmsg("Texture already set", line, EINVAL));
	file_path = ft_strtrim(line + 2, " \t\n");
	if (!file_path)
		return (ft_errmsg("Memory allocation error", "ft_strtrim", ENOMEM));
	exit_status = check_file(file_path, false);
	if (exit_status == 0)
		args->textures[index] = file_path;
	else
		free(file_path);
	return (exit_status);
}
