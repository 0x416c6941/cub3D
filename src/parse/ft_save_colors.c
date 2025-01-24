/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_save_colors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 20:24:33 by root              #+#    #+#             */
/*   Updated: 2025/01/24 01:49:53 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>
#include <parse.h>
#include <errno.h>
#include <libft.h>
#include <stdlib.h>
#include <utils.h>

#define RGB_VAL_SIZE	3

/**
 * Validates that the \p str represents a positive integer with no more than
 * three digits and contains only valid characters (digits, '+', spaces).
 * @brief	Checks for overflow (3+ digits) and garbage values in \p str.
 * @param	str	The string to check.
 * @return	true if valid; false otherwise.
 */
static bool	ft_check_overflow(const char *str)
{
	const char	*ptr;
	int			len;

	if (str == NULL)
		return (false);
	ptr = str;
	while (ft_isspace(*ptr))
		ptr++;
	if (*ptr == '+')
		ptr++;
	while (*ptr == '0')
		ptr++;
	len = 0;
	while (ft_isdigit((unsigned char)ptr[len]))
		len++;
	if (len > RGB_VAL_SIZE)
		return (false);
	while (ft_isspace(ptr[len]))
		len++;
	return (ptr[len] == '\0');
}

/**
 * Ensures the RGB array contains exactly three strings, each representing
 * a valid positive integer (digits only, optionally prefixed with '+')
 * within the range [0, 255].
 * @brief	Validates \p rgb_values for proper format and range.
 * @param	rgb_values	Array of strings representing RGB values.
 * @return	true if valid; false otherwise.
 */
static bool	ft_validate_color(const char **rgb_values)
{
	int	i;
	int	value;

	i = 0;
	while (rgb_values[i] != NULL)
	{
		if (!ft_check_overflow(rgb_values[i]))
			return (false);
		value = ft_atoi(rgb_values[i]);
		if (value < 0x0 || value > 0xff)
			return (false);
		i++;
	}
	return (i == RGB_VAL_SIZE);
}

#define RGB_R			0
#define RGB_G			1
#define RGB_B			2

int	ft_save_colors(char *line, t_args *args, int index)
{
	/**
	 * TODO: Please add docs on this function :(
	 * Please kindly add them to parse.h file directly.
	 */
	char	*trimmed;
	char	**rgb_values;
	int		rgb_val[RGB_VAL_SIZE];

	if (args->colors[index].set)
		return (ft_errmsg(line, "Color already set", EINVAL));
	trimmed = ft_strtrim(line + 1, " \t\n");
	if (trimmed == NULL)
		return (ft_errmsg("Memory allocation error", "ft_strtrim", ENOMEM));
	rgb_values = ft_split(trimmed, ',');
	free(trimmed);
	if (rgb_values == NULL)
		return (ft_errmsg("Memory allocation error", "ft_split", ENOMEM));
	if (!ft_validate_color((const char **)rgb_values))
	{
		ft_split_free(rgb_values);
		return (ft_errmsg("Invalid color format or range", line, EINVAL));
	}
	rgb_val[RGB_R] = ft_atoi(rgb_values[RGB_R]);
	rgb_val[RGB_G] = ft_atoi(rgb_values[RGB_G]);
	rgb_val[RGB_B] = ft_atoi(rgb_values[RGB_B]);
	ft_split_free(rgb_values);
	args->colors[index] = (t_rgb){(unsigned char)rgb_val[RGB_R],
		(unsigned char)rgb_val[RGB_G], (unsigned char)rgb_val[RGB_B], true};
	return (0);
}
