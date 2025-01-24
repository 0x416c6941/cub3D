/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_save_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 20:23:45 by root              #+#    #+#             */
/*   Updated: 2025/01/24 01:52:19 by asagymba         ###   ########.fr       */
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
 * Validate the file path stored in \p line for a texture and store it
 * at \p index of the "textures" array in \p args.
 * Already set textures won't be overwritten.
 * @brief	Saves a texture file path to \p args.
 * @param	line	The line containing the texture identifier and file path.
 * @param	args	Pointer to the structure where textures' paths are stored.
 * @param	index	The index in the "textures" array to store the texture path.
 * @return	0 on success; error code otherwise.
 */
int	ft_save_textures(char *line, struct s_args *args, int index)
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
