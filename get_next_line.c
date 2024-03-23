#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_list	*parent_node = NULL;
	t_list			*tmp_node;

	if (fd < 0)
		return NULL;
	if (parent_node == NULL)
		parent_node = new_node();
	tmp_node = create_list(fd, parent_node);
	if (tmp_node == NULL)
	{
		free(parent_node);
		return (NULL);
	}
	char *result = create_string_from_list(tmp_node);	//Create the final string
	while(tmp_node -> next)
		tmp_node = tmp_node-> next;
	clean_string(tmp_node -> content);
	parent_node = free_list(parent_node);
	return (result); 
}

t_list	*free_list(t_list *parent_node) {
    t_list *current_node = parent_node;
    while (current_node -> next) {
        t_list *next = current_node->next;
        free(current_node->content);
        free(current_node);
        current_node = next;
    }
	return (current_node);
}

t_list	*create_list(int fd, t_list *parent_node)
{
	t_list	*current_node;
	int		chars_read;

	if (get_eol(parent_node -> content))
		return (parent_node);
	current_node = parent_node;
	if (current_node -> content != NULL)
	{
		current_node -> next = new_node();
		current_node = current_node -> next;
	}
	chars_read = read(fd, current_node -> content, BUFFER_SIZE);
	if (chars_read <= 0)
		return NULL;
	while (chars_read > 0)
	{
		if (get_eol(current_node -> content)) {
			break;
		}
		current_node -> next = new_node();
		current_node = current_node -> next;
		chars_read = read(fd, current_node -> content, BUFFER_SIZE);	
	}
	return parent_node;
}


/* Removes everything before new line
 * and prepares the node for the next iteration
 */
void clean_string(char *str)
{
	char *eol = get_eol(str) + 1;
	int len = strlen(eol) + 1;
	memmove(str, eol, len);
}

/* Create the result string traversing the list
*/
char	*create_string_from_list(t_list *parent_node)
{
	int		size;
	char	*eol;
	char	*result;
	t_list	*current_node;

	current_node = parent_node;
	size = get_string_size(current_node);
	result = calloc(size + 1, sizeof(char));
	while(current_node -> next) {
		strncpy(result + strlen(result), current_node -> content, strlen(current_node -> content));
		current_node = current_node -> next;
	}
	eol = get_eol(current_node -> content);
	strncpy(result + strlen(result), current_node -> content, eol - current_node -> content + 1);
	return (result);
}

/* Returns the size of the string created by the nodes
 * of a linked list.
 */
int	get_string_size(t_list *parent_node)
{
	t_list	*current_node;
	char	*eol;
	int size;

	size = 0;
	current_node = parent_node;
	while (1) {
		eol = get_eol(current_node -> content);
		if (eol) {
			size += eol - current_node -> content;
			break;
		}
		size += strlen(current_node -> content);
		current_node = current_node -> next;
	}
	return (size);
}

/* Returns the first occurence of newline or EOF
 * Returns NULL if string is null
 */
char	*get_eol(char *str)
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
		return (NULL);
	node -> content = calloc(BUFFER_SIZE + 1, sizeof(char));
	if (node -> content == NULL)
		return (NULL);
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
