/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchen <jchen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 12:08:59 by jchen             #+#    #+#             */
/*   Updated: 2024/09/04 15:21:22 by jchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Itère sur la liste ’lst’ et applique la fonction ’f’
// au contenu de chaque élément. Crée une nouvelle liste résultant
// des applications successives de ’f’. La fonction ’del’ est là pour détruire
// le contenu d’un élément si nécessaire
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*nlist;
	t_list	*nelem;

	nlist = NULL;
	nelem = NULL;
	if (lst == NULL || f == NULL || del == NULL)
		return (NULL);
	while (lst)
	{
		nelem = ft_lstnew(f(lst->content));
		if (nelem == NULL)
		{
			if (del)
				del(lst->content);
			ft_lstclear(&nlist, del);
			return (NULL);
		}
		ft_lstadd_back(&nlist, nelem);
		lst = lst->next;
	}
	return (nlist);
}
