/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rizz <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 11:55:23 by rizz              #+#    #+#             */
/*   Updated: 2024/05/19 11:55:24 by rizz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

typedef struct s_node
{
	char			*str;
	struct s_node	*next;
}	t_node;
char	*get_next_line(int fd);
t_node	*new_node(unsigned int content_size, char *content);
void	create_list(int fd, t_node **list, char *buffer);
t_node	*lstadd_back(t_node **head, t_node *new_node);
char	*join_list(t_node **list, char *buffer);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
size_t	ft_strlen(const char *s);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strchr(const char *s, char c);
void	split_result(char *line, char *buffer);

#endif
