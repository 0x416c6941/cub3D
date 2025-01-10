/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errmsg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 21:42:28 by root              #+#    #+#             */
/*   Updated: 2025/01/10 22:24:01 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <utils.h>

/**
 * @brief Add prefix "cub3D: Error" and print to standard error output.
 *  err_msg and detail can be printed to specify the error. Return the exit code
 * passed as a parameter.
 *
 * @param msg
 * @param detail
 * @param exit_code
 * @return int exit_code
 */
int	ft_errmsg(const char *msg, const char *detail, int exit_code)
{
	if ((write(STDERR_FILENO, CUB_PREFIX, ft_strlen(CUB_PREFIX)) == -1)
		|| (write(STDERR_FILENO, msg, ft_strlen(msg)) == -1))
	{
		perror(WRITE_ERR_MSG);
		return (-1);
	}
	if (detail)
	{
		if ((write(STDERR_FILENO, ": ", 2) == -1) || (write(STDERR_FILENO,
					detail, ft_strlen(detail)) == -1))
		{
			perror(WRITE_ERR_MSG);
			return (-1);
		}
	}
	if (write(STDERR_FILENO, "\n", 1) == -1)
	{
		perror(WRITE_ERR_MSG);
		return (-1);
	}
	return (exit_code);
}
