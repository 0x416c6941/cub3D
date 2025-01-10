/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 12:17:35 by asagymba          #+#    #+#             */
/*   Updated: 2024/11/30 01:18:31 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

int		ft_isspace(int c);
int		ft_isupper(int c);
int		ft_islower(int c);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);

size_t	ft_strlen(const char *s);
size_t	ft_strnlen(const char *s, size_t maxlen);

void	*ft_memset(void *s, int c, size_t n);

void	ft_bzero(void *s, size_t n);

void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);

size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);

int		ft_toupper(int c);
int		ft_tolower(int c);

char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);

int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);

char	*ft_strnstr(const char *big, const char *little, size_t len);

int		ft_atoi(const char *nptr);

void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strdup(const char *s);

char	*ft_substr(const char *s, unsigned int start, size_t len);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_strtrim(const char *s1, const char *set);
char	*ft_strtok_r(char *str, const char *delim, char **saveptr);
/**
 * Free result of ft_split().
 * @param	strs	A result of ft_split().
 */
void	ft_split_free(char **strs);
char	**ft_split(const char *s, char c);
char	*ft_itoa(int n);

char	*ft_strmapi(const char *s, char (*f)(unsigned int i, char c));
void	ft_striteri(char *s, void (*f)(unsigned int i, char *s));

void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/**
 * Swaps nodes 'x' and 'y' in 'lst'.
 * @param	lst	Pointer to a list.
 * @param	x	Node x.
 * @param	y	Node y.
 */
void	ft_lstswap(t_list **lst, t_list *x, t_list *y);

/**
 * Gets element with index 'at' from 'lst'.
 * @param	lst	List.
 * @param	at	Index of the element.
 * @return	Some element from 'lst' at index 'at', if exists;
 * 			NULL otherwise.
 */
t_list	*ft_lstat(t_list *lst, size_t at);

/**
 * Remove element in '*lst' with index 'at'.
 * @param	lst	A pointer to list.
 * @param	del	A function to remove content of the node.
 * @param	at	Index of the element.
 */
void	ft_lstremove_at(t_list **lst, void (*del)(void *), size_t at);
/**
 * Remove element 'node' in '*lst'.
 * @param	lst		A pointer to list.
 * @param	del		A function to remove content of the node.
 * @param	node	Element to remove.
 */
void	ft_lstremove_node(t_list **lst, void (*del)(void *), t_list *node);

/**
 * Inserts 'node' to '*lst' to index 'at'.
 * @param	lst		A pointer to list.
 * @param	at		Index at '*lst', where to insert 'node'.
 * @param	node	Node to insert.
 */
void	ft_lstinsert_at(t_list **lst, size_t at, t_list *node);

size_t	ft_strcspn(const char *s, const char *reject);
char	*get_next_line(int fd);

int		ft_printf(const char *format, ...);

#endif	/* LIBFT_H */
