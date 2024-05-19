#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
//10000000 BUFF SIZE test
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

typedef struct s_node {
	char			*str;
	struct s_node 	*next;
} t_node;

char *get_next_line(int fd);
t_node *new_node(unsigned int content_size, char *content);
void free_list(t_node **head);
void create_list(int fd, t_node **list, char *buffer);
t_node *lstadd_back(t_node **head, t_node *new_node);
char *join_list(t_node **list, char *buffer);
void split_result(char *line, char *buffer);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
size_t	ft_strlen(const char *s);
void    *ft_calloc(size_t nmemb, size_t size);

#endif
