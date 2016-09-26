/*
** users.c for users in /Users/noboud_n/Documents/Share/PSU_2015_myirc/serv/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Mon May 16 19:13:22 2016 Nyrandone Noboud-Inpeng
** Last update Sun May 22 16:33:02 2016 Nyrandone Noboud-Inpeng
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "serv.h"
#include "errors.h"
#include "replies.h"

int		list_users(t_list *user_to_answer, t_list *users)
{
  t_list	*tmp;
  char		buffer[4096];
  char		*name;

  if (users == NULL)
    return (store_answer(user_to_answer, RPL_NOUSERS, 0));
  tmp = users;
  while (tmp != NULL)
    {
      name = ((t_udata *)(tmp->struc))->name;
      if (memset(buffer, 0, 4096) == NULL)
	return (puterr_int(ERR_MEMSET, -1));
      if (snprintf(buffer, 4096, RPL_USERS, name) == -1)
	return (puterr_int(ERR_SNPRINTF, -1));
      if (store_answer(user_to_answer, buffer, 0) == -1)
	return (-1);
      tmp = tmp->next;
    }
  return (0);
}

int		users(const int fd, UNUSED char *command,
		      UNUSED t_list **channel, t_list **users)
{
  char		buffer[4096];

  if (memset(buffer, 0, 4096) == NULL)
    return (puterr_int(ERR_MEMSET, -1));
  if (snprintf(buffer, 4096, RPL_LISTSTART) == -1)
    return (puterr_int(ERR_SNPRINTF, -1));
  if (store_answer(get_user(*users, fd), buffer, 0) == -1)
    return (-1);
  if (list_users(get_user(*users, fd), *users) == -1)
    return (-1);
  if (memset(buffer, 0, 4096) == NULL)
    return (puterr_int(ERR_MEMSET, -1));
  if (snprintf(buffer, 4096, RPL_LISTEND) == -1)
    return (puterr_int(ERR_SNPRINTF, -1));
  if (store_answer(get_user(*users, fd), buffer, 0) == -1)
    return (-1);
  return (0);
}
