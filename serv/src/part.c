/*
** part.c for part in /Users/noboud_n/Documents/Share/PSU_2015_myirc/serv/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Wed May 18 17:45:56 2016 Nyrandone Noboud-Inpeng
** Last update Sat May 21 23:36:44 2016 Nyrandone Noboud-Inpeng
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "serv.h"
#include "replies.h"
#include "errors.h"

int		part_succeed(const int fd, t_list *current_channel,
			     const char *user_name, const char *channel_name)
{
  char		buffer[4096];
  t_list	*users;
  t_list	*user_to_answer;

  if (user_name == NULL)
    return (puterr_int(ERR_INTERNALPART, -1));
  if (current_channel)
    users = ((t_cdata *)(current_channel->struc))->users;
  else
    users = NULL;
  if (memset(buffer, 0, 4096) == NULL)
    return (puterr_int(ERR_MEMSET, -1));
  if (snprintf(buffer, 4096, RPL_PARTOK, user_name, channel_name) == -1)
    return (puterr_int(ERR_SNPRINTF, -1));
  while (users != NULL)
    {
      if (((t_udata *)(users->struc))->fd != -1)
	{
	  if (store_answer(users, buffer, 0) == -1)
	    return (-1);
	}
      users = users->next;
    }
  user_to_answer = save_users(NULL, 0);
  return (store_answer(get_user(user_to_answer, fd), buffer, 0));
}

int		not_on_channel(t_list *user, const char *channel_name)
{
  char		buffer[4096];

  if (memset(buffer, 0, 4096) == NULL)
    return (puterr_int(ERR_MEMSET, -1));
  if (snprintf(buffer, 4096, ERR_NOTONCHANNEL, channel_name) == -1)
    return (puterr_int(ERR_SNPRINTF, -1));
  return (store_answer(user, buffer, -2));
}

int		part(const int fd, char *command,
		     t_list **channels, t_list **users)
{
  int		ret_value;
  t_list	*channel;
  int		index;
  char		buffer[4096];

  if ((ret_value = take_first_arg(fd, &command, *users, "PART")) != 0)
    return (ret_value);
  if ((channel = search_channel_by_name(*channels, command)) == NULL)
    {
      if (memset(buffer, 0, 4096) == NULL)
	return (puterr_int(ERR_MEMSET, -1));
      if (snprintf(buffer, 4096, ERR_NOSUCHCHANNEL, command) == -1)
	return (puterr_int(ERR_SNPRINTF, -1));
      return (store_answer(get_user(*users, fd), buffer, -2));
    }
  if ((get_index_user_from_channel(channel, fd)) != -1 &&
      (index = get_index_channel_from_channels_list(channel, command) != -1))
    {
      delete_user_from_channel(fd, index, channels, channel);
      channel = search_channel_by_name(*channels, command);
      if (change_current_channel(fd, users, NULL) == -1)
	return (-1);
      return (part_succeed(fd, channel, get_user_name(*users, fd), command));
    }
  return (not_on_channel(get_user(*users, fd), command));
}
