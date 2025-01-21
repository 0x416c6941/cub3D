/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:10:25 by asagymba          #+#    #+#             */
/*   Updated: 2025/01/21 14:12:57 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
#include <cub3D.h>
#include <fcntl.h>
#include <libft.h>

int	ft_parse(const char *file_path, struct s_args *out)
{
	int	file;

	file = open(file_path, O_RDONLY);
	if (file == -1)
		return (-1);
	(void)ft_memset(out, 0, sizeof(struct s_args));
}
