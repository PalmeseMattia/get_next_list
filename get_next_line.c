/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rizz <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 12:05:26 by rizz              #+#    #+#             */
/*   Updated: 2024/05/18 12:05:51 by rizz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

char	*get_next_line(int fd)
{
	t_node		*list;
	char		*result;
	static char	*buffer = NULL;

	list = NULL;
	if (fd < 0)
		return (NULL);
	if (!buffer)
	{
		buffer = calloc(BUFFER_SIZE + 1, sizeof(char));
		if (!buffer)
			return (NULL);
		buffer[BUFFER_SIZE] = '\0';
	}
	create_list(fd, &list, buffer);
	if (!list)
	{
		free(buffer);
		return (NULL);
	}
	result = join_list(&list);
	split_result(result, buffer);
	free_list(&list);
	return (result);
}

/*
 * Create a linked list with the reads from the file descriptor,
 * until a newline of eof character is found
 */
void	create_list(int fd, t_node **list, char *bf)
{
	char	*buffer;
	t_node	*node;
	int		chars;

	buffer = calloc((BUFFER_SIZE + 1), sizeof(char));
	if (ft_strlen(bf) > 0)
	{
		chars = ft_strlcpy(buffer, bf, ft_strlen(bf) + 1);
		memset(bf, 0, BUFFER_SIZE);
	}
	else
		chars = read(fd, buffer, BUFFER_SIZE);
	while (chars > 0)
	{
		node = new_node(chars + 1);
		strncpy(node -> content, buffer, chars);
		lstadd_back(list, node);
		if (strchr(buffer, '\n') || strchr(buffer, EOF))
			break ;
		chars = read(fd, buffer, BUFFER_SIZE);
	}
	free(buffer);
}

/*
 * Calculate the size of the string composed by the nodes of the list,
 * then alloc and write the result string.
 * Measure, alloc and write :)
 */
char	*join_list(t_node **list)
{
	char	*result;
	int		result_len;
	t_node	*node;
	int		offset;

	result_len = 0;
	offset = 0;
	node = *list;
	while (node -> next)
	{
		result_len += strlen(node -> content);
		node = node -> next;
	}
	result_len += strlen(node -> content);
	node = *list;
	result = calloc(result_len + 1, sizeof(char));
	result[result_len] = '\0';
	while (node -> next)
	{
		strcat(result + offset, node -> content);
		offset += strlen(node -> content);
		node = node -> next;
	}
	strcat(result + offset, node -> content);
	return (result);
}

/*
 * Removes everything after the first newline character and returns the rest
 * of the string
 */
void	split_result(char *line, char *buffer)
{
	char	*nl;

	nl = strchr(line, '\n');
	if (nl)
	{
		if (buffer)
			strcpy(buffer, nl + 1);
		*(nl + 1) = '\0';
	}
}

t_node	*lstadd_back(t_node **head, t_node *new_node)
{
	t_node	*last;

	if (!new_node)
		return (NULL);
	if (!(*head))
		*head = new_node;
	else
	{
		last = *head;
		while (last -> next)
			last = last -> next;
		last -> next = new_node;
	}
	return (new_node);
}
