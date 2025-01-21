/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlyshchu <hlyshchu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 21:47:38 by root              #+#    #+#             */
/*   Updated: 2025/01/21 17:54:12 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <libft.h>

# define CUB_PREFIX "Cub3D: Error: "
# define WRITE_ERR_MSG "Error write failed."

/**
 * Add prefix "cub3D: Error" and print to standard error output.
 * \p msg and \p detail can be printed to specify the error.
 * Returns the \p exit_code.
 * @param	err_msg
 * @param	detail
 * @param	exit_code
 * @return	exit_code
 */
int		ft_errmsg(const char *msg, const char *detail, int exit_code);

#endif /* UTILS_H */
