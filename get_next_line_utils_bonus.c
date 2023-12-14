/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aylamgha <aylamgha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 04:19:08 by aylamgha          #+#    #+#             */
/*   Updated: 2023/12/12 04:32:08 by aylamgha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	found_newline(t_list *lst)
{
	long	i;

	if (NULL == lst)
		return (0);
	while (lst)
	{
		i = 0;
		while (lst->str_buf[i] && i < (long)BUFFER_SIZE)
		{
			if (lst->str_buf[i] == '\n')
				return (1);
			++i;
		}
		lst = lst->next;
	}
	return (0);
}

t_list	*find_last_node(t_list *lst)
{
	if (NULL == lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	copy(t_list *lst, char *str)
{
	int	i;
	int	k;

	if (NULL == lst)
		return ;
	k = 0;
	while (lst)
	{
		i = 0;
		while (lst->str_buf[i])
		{
			if (lst->str_buf[i] == '\n')
			{
				str[k++] = '\n';
				str[k] = '\0';
				return ;
			}
			str[k++] = lst->str_buf[i++];
		}
		lst = lst->next;
	}
	str[k] = '\0';
}

int	len_to_newline(t_list *lst)
{
	int	i;
	int	len;

	if (NULL == lst)
		return (0);
	len = 0;
	while (lst)
	{
		i = 0;
		while (lst->str_buf[i])
		{
			if (lst->str_buf[i] == '\n')
			{
				++len;
				return (len);
			}
			++i;
			++len;
		}
		lst = lst->next;
	}
	return (len);
}

void	dealloc(t_list **lst, t_list *clean_node, char *buf)
{
	t_list	*tmp;

	if (NULL == *lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		free((*lst)->str_buf);
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
	if (clean_node->str_buf[0])
		*lst = clean_node;
	else
	{
		free(buf);
		free(clean_node);
	}
}
