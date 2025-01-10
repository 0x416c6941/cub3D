/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 20:05:33 by asagymba          #+#    #+#             */
/*   Updated: 2024/11/23 20:05:48 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_isspace(int c)
{
	const char	*ws_chars = " \f\n\r\t\v";

	while (*ws_chars != '\0')
		if (*ws_chars++ == c)
			return (1);
	return (0);
}
