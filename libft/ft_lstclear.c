/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvillena <pvillena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 12:52:36 by pvillena          #+#    #+#             */
/*   Updated: 2022/01/25 18:59:24 by pvillena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;
	t_list	*temp2;

	if (!*lst)
		return ;
	temp2 = *lst;
	*lst = NULL;
	while (temp2)
	{
		temp = temp2;
		temp2 = temp2->next;
		del(temp->content);
		free(temp);
	}
}
