/*
** list.c for myirc in /home/wilmot_g/Rendu/PSU_2015_myirc/common/src
**
** Made by guillaume wilmot
** Login   <wilmot_g@epitech.net>
**
** Started on  Mon May 16 23:49:10 2016 guillaume wilmot
** Last update Sat May 21 03:13:11 2016 Nyrandone Noboud-Inpeng
*/

#include <stdlib.h>
#include "list.h"

t_list		*get_nth_list(t_list *this, unsigned int n)
{
  t_list	*tmp;
  unsigned int	i;

  if (!this || !(tmp = *this->first))
    return (NULL);
  i = 0;
  while (tmp && i < n)
    {
      i++;
      tmp = tmp->next;
    }
  return (tmp);
}

int		make_circular_list(t_list *this)
{
  if (!this || !*this->first || !this->last)
    return (-1);
  (*this->last)->next = *this->first;
  (*this->first)->prev = *this->last;
  return (0);
}

t_list		*insert_at_list(t_list *this, unsigned int n, void *struc)
{
  t_list	*elem;
  t_list	*tmp;
  unsigned int	i;

  if (!this || !(tmp = *this->first))
    return (NULL);
  if (!n)
    return (push_front_list(this, struc));
  if (n >= *this->size - 1)
    return (push_back_list(this, struc));
  if (!(elem = create_list(struc, this)))
    return (NULL);
  i = -1;
  while (tmp && ++i < n - 1)
    if (!(tmp = tmp->next))
      return (NULL);
  elem->next = tmp->next;
  elem->prev = tmp;
  tmp->next ? tmp->next->prev = elem : 0;
  tmp->next = elem;
  return ((*this->size)++, *this->first);
}

int		get_size_list(t_list *this)
{
  if (this)
    return (*this->size);
  return (-1);
}
