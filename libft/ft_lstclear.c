/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 18:41:22 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/09/05 18:41:23 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*ptr;
	t_list	*next;

	if (!*lst)
		return ;
	next = *lst;
	while (next)
	{
		ptr = next;
		(*del)(ptr->content);
		next = ptr->next;
		free(ptr);
	}
	*lst = NULL;
}
