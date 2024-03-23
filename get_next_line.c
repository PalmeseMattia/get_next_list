#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 10

typedef struct s_list {
	char			*content;
	struct s_list	*next;
}	t_list;

t_list	*new_node();
char	*ft_strchr(char *str, char c);
char	*get_next_line(int fd);
char	*get_nl_eof(char *str);
char	*create_string(t_list *parent_node);
void	clean_string(char *str);

int main()
{
	int	fd;

	printf(">> get_next_line list version!\n");
	fd = open("file.txt", O_RDONLY);
	if (fd < 0) {
		perror("Error while opening file");
		exit(EXIT_FAILURE);
	}
	printf("----- LINES -----\n\n");
	char *result;
	while((result = get_next_line(fd)))
		printf("%s", result);
	close (fd);
	return (0);
}

char	*get_next_line(int fd)
{
	static t_list	*parent_node = NULL;
	t_list			*current_node;
	int				chars_read;

	if (fd < 0)
		return NULL;
	if (parent_node == NULL)
		parent_node = new_node();
	current_node = parent_node;
	if(!get_nl_eof(current_node -> content)) {
		if (current_node -> content != NULL) {
		current_node -> next = new_node();
		current_node = current_node -> next;
		}
		current_node -> content = calloc(BUFFER_SIZE + 1, sizeof(char));
		chars_read = read(fd, current_node -> content, BUFFER_SIZE);
		if (chars_read <= 0)
			return NULL;
		while(chars_read > 0) {
			if (ft_strchr(current_node -> content, '\n') 
					|| ft_strchr(current_node -> content, EOF)) {
				break;
			}
			current_node -> next = new_node();
			current_node = current_node -> next;
			current_node -> content = calloc(BUFFER_SIZE + 1, sizeof(char));
			chars_read = read(fd, current_node -> content, BUFFER_SIZE);	
		}
	}
	char *result = create_string(parent_node);	//Create the final string
	parent_node = current_node;					//Set the last node as the new parent
	clean_string(parent_node -> content);
	return (result); 
}
/* Removes everything before new line
 * and prepares the node for the next iteration
 */
void clean_string(char *str)
{
	char *eol = get_nl_eof(str) + 1;
	int len = strlen(eol) + 1;
	memmove(str, eol, len);
}

/* Create the result string traversing the list to find the size
 * and then traversing again to copy the content of the nodes
 */
char	*create_string(t_list *parent_node)
{
	int		size;
	char	*eol;
	char	*result;
	t_list	*current_node;

	size = 0;
	current_node = parent_node;
	//Get size TODO: in another separate function
	while (1) {
		eol = get_nl_eof(current_node -> content);
		if (eol) {
			size += eol - current_node -> content;
			break;
		}
		size += strlen(current_node -> content);
		current_node = current_node -> next;
	}
	result = calloc(size + 1, sizeof(char));
	//Copy string
	current_node = parent_node;
	while(current_node -> next) {
		strncpy(result + strlen(result), current_node -> content, strlen(current_node -> content));
		current_node = current_node -> next;
	}
	strncpy(result + strlen(result), current_node -> content, eol - current_node -> content + 1);
	return result;
}

char	*get_nl_eof(char *str)
{
	if (!str)
		return NULL;
	while (*str) {
		if (*str == '\n' || *str == EOF)
			return str;
		str++;
	}
	return NULL;
}

/* Creates a new node for our linked list
 */
t_list	*new_node()
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (node == NULL)
		return NULL;
	node -> content = NULL;
	node -> next = NULL;
	return (node);
}

char	*ft_strchr(char *str, char c) {
	while(*str) {
		if (*str == c)
			return str;
		str++;
	}
	return NULL;
}
