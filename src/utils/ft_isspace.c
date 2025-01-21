/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlyshchu <hlyshchu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:53:49 by hlyshchu          #+#    #+#             */
/*   Updated: 2025/01/21 15:00:29 by hlyshchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <utils.h>

/**
 * Returns true if the character `c` is a whitespace, otherwise false.
 */
bool ft_isspace(char c)
{
    return (c == ' ' || (c >= 9 && c <= 13));
}
