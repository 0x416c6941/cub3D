/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 13:05:10 by asagymba          #+#    #+#             */
/*   Updated: 2025/01/21 14:04:56 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <cub3D.h>

/**
 * Parses arguments and saves them to \p out.
 * @param	argc	Argument count.
 * @param	argv	Argument vector.
 * @param	out		Output.
 * @return	-1, if something went wrong. errno will also be set;
 * 			Some non-negative value, if everything went fine.
 */
int	ft_parse(int argc, char **argv, struct s_args *out);

#endif /* PARSE_H */
