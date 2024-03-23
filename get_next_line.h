#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef struct s_list {
	char			*content;
	struct s_list	*next;
}	t_list;

t_list	*new_node();
char	*ft_strchr(char *str, char c);
char	*get_next_line(int fd);
char	*get_eol(char *str);
char	*create_string_from_list(t_list *parent_node);
void	clean_string(char *str);
t_list	*create_list(int fd, t_list *parent_node);
int		get_string_size(t_list *parent_node);
t_list	*free_list(t_list *parent_node);

#endif
