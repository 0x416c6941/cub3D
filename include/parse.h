/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:00:08 by asagymba          #+#    #+#             */
/*   Updated: 2025/01/22 14:01:36 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <cub3D.h>

/**
 * ----------------------------------------------------------------------------
 * Functions.
 * ----------------------------------------------------------------------------
 */
/**
 * Parses file at \p file_path and saves parsed information to \p out.
 * @param	file_path	Path to a .cub file.
 * @param	out			Output.
 * @return	-1, if something went wrong. errno will also be set;
 * 			Some non-negative value, if everything went fine.
 */
int		ft_parse(const char *file_path, struct s_args *out);

#endif /* PARSE_H */
