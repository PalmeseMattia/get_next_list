/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rizz <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 12:05:56 by rizz              #+#    #+#             */
/*   Updated: 2024/05/18 12:05:59 by rizz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

t_node	*new_node(unsigned int content_size, char *content)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node -> next = NULL;
	if (content_size != 0)
	{
		node -> str = ft_calloc(content_size, sizeof(char));
		if (!node -> str)
		{
			free(node);
			return (NULL);
		}
		if (content != NULL && *content)
			ft_strlcpy(node -> str, content, content_size);
	}
	else
		node -> str = NULL;
	return (node);
}


size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = -1;
	while (src[++i] && (i + 1) < size)
		dest[i] = src[i];
	if (size)
		dest[i] = '\0';
	return (ft_strlen(src));
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	if (*s)
	{
		while (*s)
		{
			len++;
			s++;
		}
	}
	return (len);
}

 void    *ft_calloc(size_t nmemb, size_t size)
 {
	void    		*p;
	unsigned char	*p_copy;
	size_t  bytes;

	if (nmemb == 0 || size == 0)
	{
		nmemb = 1;
		size = 1;
	}
	bytes = nmemb * size;
	if (bytes / size != nmemb)
		return (NULL);
	p = malloc(bytes);
	if (!p)
		return (NULL);
	p_copy = p;
	while(bytes--)
		*p_copy++ = 0;
	return (p);
}

char	*ft_strchr(const char *s, char c)
{
	char	*str;

	str = (char *)s;
	while(*str)
	{
		if (*str == c)
			return str;
		str++;
	}
	return (NULL);
}
