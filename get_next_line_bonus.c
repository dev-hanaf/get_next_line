/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 04:19:01 by aylamgha          #+#    #+#             */
/*   Updated: 2023/12/14 08:35:34 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	cleanin(t_list **lst)
{
	t_list	*last_node;
	t_list	*clean_node;
	int		i;
	int		k;
	char	*buf;

	buf = malloc(BUFFER_SIZE + 1);
	clean_node = malloc(sizeof(t_list));
	if (NULL == buf || NULL == clean_node)
		return ;
	last_node = find_last_node(*lst);
	i = 0;
	k = 0;
	while (last_node->str_buf[i] && last_node->str_buf[i] != '\n')
		++i;
	while (last_node->str_buf[i] && last_node->str_buf[++i])
		buf[k++] = last_node->str_buf[i];
	buf[k] = '\0';
	clean_node->str_buf = buf;
	clean_node->next = NULL;
	dealloc(lst, clean_node, buf);
}

char	*get_the_line(t_list *lst)
{
	int		str_len;
	char	*next_str;

	if (NULL == lst)
		return (NULL);
	str_len = len_to_newline(lst);
	next_str = malloc(str_len + 1);
	if (NULL == next_str)
		return (NULL);
	copy(lst, next_str);
	return (next_str);
}

void	append(t_list **lst, char *buf)
{
	t_list	*new_node;
	t_list	*last_node;

	last_node = find_last_node(*lst);
	new_node = malloc(sizeof(t_list));
	if (new_node == NULL)
		return ;
	if (last_node == NULL)
		*lst = new_node;
	else
		last_node->next = new_node;
	new_node->str_buf = buf;
	new_node->next = NULL;
}

void	create_list(t_list **lst, int fd)
{
	ssize_t		char_read;	
	char		*buf;

	while (!found_newline(*lst))
	{
		buf = malloc(BUFFER_SIZE + 1);
		if (NULL == buf)
			return ;
		char_read = read(fd, buf, BUFFER_SIZE);
		if (!char_read || char_read == -1)
		{
			free(buf);
			return ;
		}
		buf[char_read] = '\0';
		append(lst, buf);
	}
}

char	*get_next_line(int fd)
{
	static t_list	*lst[1024];
	char			*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	create_list(&lst[fd], fd);
	if (lst[fd] == NULL)
		return (NULL);
	next_line = get_the_line(lst[fd]);
	cleanin(&lst[fd]);
	return (next_line);
}
#include  <stdio.h>

int main(){
int fd = open("text.txt", O_RDONLY);
int fd2 = open("text2.txt", O_RDONLY);

printf("%s",get_next_line(fd));
printf("%s",get_next_line(fd2));
printf("%s",get_next_line(fd));
printf("%s",get_next_line(fd2));
printf("%s",get_next_line(fd));
printf("%s",get_next_line(fd2));
printf("%s",get_next_line(fd));
printf("%s",get_next_line(fd2));
close(fd);
}
