/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 10:45:59 by asagymba          #+#    #+#             */
/*   Updated: 2024/11/23 20:11:11 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stddef.h>
#include <stdlib.h>

#define OUT	0
#define IN	1

/**
 * Counts amount of strings in 'str',
 * all of which are divided by charset in 'delim'.
 * @param	str		String, which will later be divided into strings,
 * 					with delimiter character provided in 'delim'.
 * @param	delim	A delimiter charset.
 * @return	Amount of those strings in 'str'.
 */
static size_t	ft_count_strings(char *str, const char *delim)
{
	size_t	cnt;
	int		state;

	cnt = 0;
	state = OUT;
	while (*str != '\0')
	{
		if (ft_strchr(delim, *str) == NULL)
		{
			if (state == OUT)
				cnt++;
			state = IN;
		}
		else
			state = OUT;
		str++;
	}
	return (cnt);
}

#undef IN
#undef OUT

/**
 * Saves the result of division of 'str' by charset provided in 'delim'
 * to 'res'.
 * If some allocation fails, also free()'s everything allocated.
 * @param	res		Where to store the result.
 * @param	str		A string to divide.
 * @param	delim	A delimiter charset.
 * @return	Some non-negative value, if everything went alright;
 * 			(-1) otherwise.
 */
static int	ft_split_populate_res(char **res, char *str, const char *delim)
{
	size_t	strduped_cnt;
	char	*last;
	char	*token;

	strduped_cnt = 0;
	token = ft_strtok_r(str, delim, &last);
	while (token != NULL)
	{
		res[strduped_cnt] = ft_strdup(token);
		if (res[strduped_cnt] == NULL)
		{
			while (42)
			{
				free(res[strduped_cnt]);
				res[strduped_cnt] = NULL;
				if (!(strduped_cnt-- > 0))
					break ;
			}
			return (-1);
		}
		token = ft_strtok_r(NULL, delim, &last);
		strduped_cnt++;
	}
	return (0);
}

#define FOR_TRAILING_NULL	1

/**
 * A second stage of ft_split().
 * @param	str		A string to split.
 * @param	delim	A delimiter charset.
 * @return	An array of split characters, if everything went fine;
 * 			NULL otherwise.
 */
static char	**ft_split_finish(char *str, const char *delim)
{
	char	**res;
	size_t	res_size;

	res_size = ft_count_strings(str, delim) + FOR_TRAILING_NULL;
	res = (char **)malloc(res_size * sizeof(char *));
	if (res == NULL || ft_split_populate_res(res, str, delim) == -1)
	{
		free(res);
		return (NULL);
	}
	res[res_size - FOR_TRAILING_NULL] = NULL;
	return (res);
}

#undef FOR_TRAILING_NULL

/**
 * For the character itself and trailing '\0'.
 */
#define DELIM_SIZE	2

/**
 * Basically does all preparations for ft_split_finish().
 */
char	**ft_split(const char *s, char c)
{
	char	*s_dup;
	char	delim[DELIM_SIZE];
	char	**ret;

	if (s == NULL)
		return (NULL);
	s_dup = ft_strdup(s);
	if (s_dup == NULL)
		return (NULL);
	(void) ft_memset(delim, '\0', DELIM_SIZE);
	*delim = c;
	ret = ft_split_finish(s_dup, (const char *)delim);
	free(s_dup);
	return (ret);
}
