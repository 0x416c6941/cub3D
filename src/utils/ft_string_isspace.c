/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_isspace.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 19:38:05 by root              #+#    #+#             */
/*   Updated: 2025/01/22 19:50:39 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <utils.h>

/**
 * @brief Checks if a string contains only white spaces.
 *
 * This function iterates through the string and returns true if all characters
 * are white spaces. Returns false if any non-white-space character is found.
 *
 * @param line Pointer to the input string.

 * @return (true if the string contains only white spaces or is empty);
	false otherwise.
 */
bool	ft_string_isspace(const char *line)
{
	if (!line)
		return (true);
	while (*line)
	{
		if (!ft_isspace((unsigned char)*line))
			return (false);
		line++;
	}
	return (true);
}
