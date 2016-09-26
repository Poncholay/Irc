/*
** nick.c for nick in /Users/noboud_n/Documents/Share/PSU_2015_myirc/serv/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Wed May 18 17:45:44 2016 Nyrandone Noboud-Inpeng
** Last update Thu Jun  2 13:14:26 2016 Nyrandone Noboud-Inpeng
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <strings.h>
#include "serv.h"
#include "errors.h"
#include "replies.h"

int		already_in_use(t_list *user, const char *command)
{
  char		buffer[4096];

  if (user == NULL)
    return (puterr_int(ERR_UNKNOWNUSER, -1));
  if (memset(buffer, 0, 4096) == NULL)
    return (puterr_int(ERR_MEMSET, -1));
  if (snprintf(buffer, 4096, ERR_NICKNAMEINUSE, command) == -1)
    return (puterr_int(ERR_SNPRINTF, -1));
  return (store_answer(user, buffer, -2));
}

int		erroneus_nickname(t_list *user, const char *command)
{
  char		buffer[4096];

  if (user == NULL)
    return (puterr_int(ERR_UNKNOWNUSER, -1));
  if (memset(buffer, 0, 4096) == NULL)
    return (puterr_int(ERR_MEMSET, -1));
  if (snprintf(buffer, 4096, ERR_ERRONEUSNICKNAME, command) == -1)
    return (puterr_int(ERR_SNPRINTF, -1));
  return (store_answer(user, buffer, -2));
}

int		check_new_name(t_list *user, const char *name)
{
  int		i;

  i = -1;
  if (strlen(name) >= 10)
    return (erroneus_nickname(user, name));
  while (name[++i])
    {
      if ((i == 0 && !isalpha(name[i]))
	  || (i != 0 && (!isalnum(name[i])
			 && name[i] != '-' && name[i] != '['
			 && name[i] != ']' && name[i] != '\\'
			 && name[i] != '`' && name[i] != '^'
			 && name[i] != '{' && name[i] != '}'
			 && name[i] != '_')))
      return (erroneus_nickname(user, name));
    }
  return (0);
}

int		change_nickname(t_list *user, t_list *tmp,
				const char *new_name)
{
  char		buffer[4096];

  if (((t_udata *)(user->struc))->name != NULL)
    free(((t_udata *)(user->struc))->name);
  if ((((t_udata *)(user->struc))->name = strdup(new_name)) == NULL
      || memset(buffer, 0, 4096) == NULL
      || snprintf(buffer, 4096, RPL_NICKOK, new_name) == -1)
    return (puterr_int(ERR_INTERNALNICK, -1));
  if (send_nick_to_all(user, tmp, new_name) == -1)
    return (-1);
  return (store_answer(user, buffer, 0));
}

int		nick(const int fd, char *command,
		     t_list **channel, t_list **users)
{
  t_list	*user;
  t_list	*tmp;
  int		ret_value;
  t_list	*tmp_channels;

  if (command == NULL)
    return (not_enough_params(get_user(*users, fd), "NICK"));
  if ((user = get_user(*users, fd)) == NULL)
    return (puterr_int(ERR_UNKNOWNUSER, -1));
  if ((ret_value = check_new_name(user, command)) != 0)
    return (ret_value);
  tmp = *users;
  while (tmp != NULL)
    {
      if (((t_udata *)(tmp->struc))->name)
	{
	  if (!strcasecmp(((t_udata *)(tmp->struc))->name, command))
	    return (already_in_use(user, command));
	}
      tmp = tmp->next;
    }
  tmp_channels = *channel;
  return (change_nickname(user, tmp_channels, command));
}
