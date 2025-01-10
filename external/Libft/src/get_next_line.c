/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 22:58:14 by asagymba          #+#    #+#             */
/*   Updated: 2024/11/23 20:14:29 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stddef.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <limits.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE	42
#endif	/* BUFFER_SIZE */

#undef NEWLINE_CHARSET
#define NEWLINE_CHARSET	"\n"

/**
 * Tries to add string, stored in 'buffer', to '*last'.
 * If everything went alright, '*last' will point to a new
 * string with updated data, the old one will be free()'d.
 * If anything fails, '*last' will not be changed.
 * @param	buffer	Buffer to append to '*last'.
 * @param	last	String of previously saved data.
 * @return	Some non-negative value, if everything went alright;
 * 			(-1), if got some error.
 */
static int	ft_add_buffer_to_last_read_data(char *buffer, char **last)
{
	char	*res;

	res = ft_strjoin(*last, buffer);
	if (res == NULL)
		return (-1);
	free(*last);
	*last = res;
	return (0);
}

/**
 * Reads file by 'BUFFER_SIZE' bytes until
 * either newline is found or EOF was reached.
 * Remaining part is stored (and also is read from, if it was saved before)
 * 	in '*last'.
 * @param	fd		A file to read from.
 * @param	last	A pointer to a memory, where to read the previous data from
 * 					and where to save a new one.
 * @return	Some non-negative value, if everything went alright;
 * 			(-1), if got some error.
 */
static ssize_t	ft_read_buffer_size_until_newline(int fd, char **last)
{
	char	*buffer;
	ssize_t	read_bytes;

	if (last == NULL)
		return (-1);
	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (buffer == NULL)
		return (-1);
	read_bytes = 0;
	while (*last == NULL || (*last)[ft_strcspn(*last, NEWLINE_CHARSET)] == '\0')
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes <= 0)
			break ;
		buffer[read_bytes] = '\0';
		if (ft_add_buffer_to_last_read_data(buffer, last) == -1)
		{
			free(buffer);
			return (-1);
		}
	}
	free(buffer);
	return (read_bytes);
}

/**
 * Moves '*read_data' up until newline
 * (or null terminator, if no newline there) to line.
 * If there's no other information stored in read_data, then it gets
 * free()'d and set to NULL;
 * otherwise, '*read_data' will point to a shorter buffer with
 * previous information removed.
 * @param	line		A pointer to a place in memory, where to save
 * 						the result of this procession.
 * @param	read_data	A pointer to a string with the previously
 * 						read data.
 * @return	Some non-negative value, if everything went alright;
 * 			-1, if got some error.
 */
static int	ft_process_read_data(char **line, char **read_data)
{
	size_t	line_len;

	if (read_data == NULL || *read_data == NULL
		|| line == NULL || *line != NULL)
		return (-1);
	line_len = ft_strcspn(*read_data, NEWLINE_CHARSET);
	if ((*read_data)[line_len] != '\0')
		line_len++;
	*line = (char *)malloc(line_len + 1);
	if (*line == NULL)
		return (-1);
	(void)ft_strlcpy(*line, *read_data, line_len + 1);
	if ((*read_data)[line_len] == '\0')
	{
		free(*read_data);
		*read_data = NULL;
	}
	else
		(void)ft_strlcpy(*read_data, *read_data + line_len,
			ft_strlen(*read_data + line_len) + 1);
	return (0);
}

#undef NEWLINE_CHARSET

char	*get_next_line(int fd)
{
	static char	*last;
	char		*line;

	if (BUFFER_SIZE <= 0 || BUFFER_SIZE > SSIZE_MAX)
		return (NULL);
	else if (ft_read_buffer_size_until_newline(fd, &last) == -1)
	{
		free(last);
		last = NULL;
		return (NULL);
	}
	line = NULL;
	if (ft_process_read_data(&line, &last) == -1)
	{
		free(last);
		last = NULL;
	}
	return (line);
}
