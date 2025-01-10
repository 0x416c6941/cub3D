/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 12:26:38 by asagymba          #+#    #+#             */
/*   Updated: 2024/11/23 20:07:23 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_isprint(int c)
{
	const int	ascii_lower = 0x20;
	const int	ascii_upper = 0x7E;

	return (c >= ascii_lower && c <= ascii_upper);
}
