/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 17:16:30 by asagymba          #+#    #+#             */
/*   Updated: 2024/11/23 20:06:15 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdint.h>
#include <stddef.h>

#define DEC_BASE	10

int	ft_atoi(const char *nptr)
{
	int		ret;
	int8_t	sign;

	if (nptr == NULL)
		return (0);
	ret = 0;
	sign = 1;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '+' || *nptr == '-')
		if (*nptr++ == '-')
			sign *= -1;
	while (ft_isdigit(*nptr))
		ret = ret * DEC_BASE + (sign * (*nptr++ - '0'));
	return (ret);
}
