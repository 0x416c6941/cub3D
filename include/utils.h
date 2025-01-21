/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlyshchu <hlyshchu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 21:47:38 by root              #+#    #+#             */
/*   Updated: 2025/01/21 15:00:38 by hlyshchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <errno.h>
# include <libft.h>
# include <stdbool.h>
# include <stdio.h>
# include <unistd.h>

# define CUB_PREFIX "Cub3D: Error: "
# define WRITE_ERR_MSG "Error write failed."

/**
 * @brief Add prefix "cub3D: Error" and print to standard error output.
 *  err_msg and detail can be printed to specify the error. Return the exit code
 * passed as a parameter.
 *
 * @param err_msg
 * @param detail
 * @param exit_code
 * @return int exit_code
 */
int	ft_errmsg(const char *msg, const char *detail, int exit_code);

/**
 * Returns true if the character `c` is a whitespace, otherwise false.
 */
bool ft_isspace(char c);


#endif
