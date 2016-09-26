/*
** nick_messages.c for nick in /Users/noboud_n/Documents/Share/PSU_2015_myirc/serv/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Thu Jun  2 13:09:14 2016 Nyrandone Noboud-Inpeng
** Last update Thu Jun  2 13:14:30 2016 Nyrandone Noboud-Inpeng
*/

#include "serv.h"
#include <stdio.h>
#include <string.h>
#include "errors.h"
#include "replies.h"

int		send_nick_to_all(t_list *user, t_list *tmp,
				const char *new_name)
{
  char		buffer[4096];
  t_list	*users;

  if (memset(buffer, 0, 4096) == NULL
      || snprintf(buffer, 4096, RPL_NICKOKPROP, new_name) == -1)
    return (puterr_int(ERR_INTERNALNICK, -1));
  while (tmp != NULL)
    {
      users = ((t_cdata *)(tmp->struc))->users;
      while (users != NULL)
	{
	  if (get_index_user_from_channel(tmp,
					  ((t_udata *)(user->struc))->fd) != -1
	      && ((t_udata *)(users->struc))->fd !=
	      ((t_udata *)(user->struc))->fd)
	    if (store_answer(users, buffer, 0) == -1)
	      return (-1);
	  users = users->next;
	}
      tmp = tmp->next;
    }
  return (0);
}
