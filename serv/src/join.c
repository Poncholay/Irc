/*
** join.c for join in /Users/noboud_n/Documents/Share/PSU_2015_myirc/serv/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Wed May 18 17:43:49 2016 Nyrandone Noboud-Inpeng
** Last update Tue May 24 19:20:53 2016 Nyrandone Noboud-Inpeng
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "serv.h"
#include "errors.h"
#include "replies.h"

t_list		*create_first_channel(const int fd, char *command,
				      t_list *new_user, int len)
{
  t_udata	*udata;
  t_cdata	*cdata;
  t_list	*channel;
  char		*names_list;

  if ((cdata = malloc(sizeof(t_cdata))) == NULL)
    return (puterr(ERR_MALLOC, NULL));
  udata = ((t_udata *)new_user->struc);
  if (udata->current_channel != NULL)
    free(udata->current_channel);
  if ((udata->current_channel = strdup(command)) == NULL)
    return (puterr(ERR_STRDUP, NULL));
  if ((cdata->users = create_list(udata, NULL)) == NULL)
    return (NULL);
  if ((cdata->name = strdup(command)) == NULL)
    return (puterr(ERR_STRDUP, NULL));
  if ((channel = create_list(cdata, NULL)) == NULL
      || join_succeed(fd, channel) == -1
      || (names_list =
    	   get_all_names(&len, NULL, NULL,
			 ((t_cdata *)(channel->struc))->users)) == NULL
      || final_answer(fd, len, names_list, channel) == -1)
    return (NULL);
  return (channel);
}

int		add_user_to_channel(const int fd, t_list *new_user,
				    t_list *current_channel, int len)
{
  t_udata	*udata;
  char		*names_list;

  udata = ((t_udata *)new_user->struc);
  if (udata->current_channel != NULL)
    free(udata->current_channel);
  udata->current_channel = strdup(((t_cdata *)(current_channel->struc))->name);
  if (udata->current_channel == NULL)
    return (puterr_int(ERR_STRDUP, -1));
  if (!((t_cdata *)(current_channel->struc))->users)
    {
      ((t_cdata *)(current_channel->struc))->users = create_list(udata, NULL);
      if (!((t_cdata *)(current_channel->struc))->users)
	return (-1);
    }
  else if (((t_cdata *)(current_channel->struc))->users->push_back
	   (((t_cdata *)(current_channel->struc))->users, udata) == NULL)
    return (puterr_int("Error: push back of users failed.\n", -1));
  if (join_succeed(fd, current_channel) == -1
      || (names_list =
	  get_all_names(&len, NULL, NULL,
			 ((t_cdata *)(current_channel->struc))->users)) == NULL
      || final_answer(fd, len, names_list, current_channel) == -1)
    return (-1);
  return (0);
}

int		add_new_channel(const int fd, char *command,
				t_list *new_user, t_list **channel)
{
  t_cdata	*cdata;
  t_udata	*udata;
  char		*names_list;
  int		len;
  t_list	*last;

  len = 0;
  if ((cdata = malloc(sizeof(t_cdata))) == NULL)
    return (puterr_int(ERR_MALLOC, -1));
  udata = ((t_udata *)new_user->struc);
  udata->current_channel != NULL ? free(udata->current_channel) : 0;
  if ((udata->current_channel = strdup(command)) == NULL
      || (cdata->users = create_list(udata, NULL)) == NULL
      || (cdata->name = strdup(command)) == NULL
      || ((*channel)->push_back(*channel, cdata)) == NULL)
    return (puterr_int(ERR_INTERNALJOIN, -1));
  last = *(*channel)->last;
  if (join_succeed(fd, *(*channel)->last) == -1
      || (names_list =
       get_all_names(&len, NULL, NULL,
                     ((t_cdata *)(last->struc))->users)) == NULL
      || final_answer(fd, len, names_list, last) == -1)
    return (-1);
  return (0);
}

int		edit_channels(const int fd, char *command,
			   t_list **channel, t_list *users)
{
  t_list	*tmp;
  t_list	*new_user;

  if ((new_user = get_user(users, fd)) == NULL)
    return (puterr_int(ERR_UNKNOWNUSER, -1));
  if (*channel == NULL)
    {
      if ((*channel = create_first_channel(fd, command, new_user, 0)) == NULL)
	return (-1);
      return (0);
    }
  else if ((tmp = search_channel_by_name(*channel, command)) != NULL
	   && search_channel_by_user_fd(tmp, fd) == -1)
    return (add_user_to_channel(fd, new_user, tmp, 0));
  else if (*channel != NULL
	   && (tmp = search_channel_by_name(*channel, command)) == NULL)
    return (add_new_channel(fd, command, new_user, channel));
  return (already_in_channel(fd, search_channel_by_name(*channel, command)));
}

int		join(const int fd, char *command,
		     t_list **channel, t_list **users)
{
  char		buffer[4096];
  int		ret_value;

  if ((ret_value = take_first_arg(fd, &command, *users, "JOIN")) != 0)
    return (ret_value);
  if ((command && command[0] != '#') || strlen(command) > 50)
    {
      if (memset(buffer, 0, 4096) == NULL)
	return (puterr_int(ERR_MEMSET, -1));
      if (snprintf(buffer, 4096, strlen(command) > 50 ?
		   ERR_UNAVAILRESOURCE : ERR_NOSUCHCHANNEL, command) == -1)
	return (puterr_int(ERR_SNPRINTF, -1));
      return (store_answer(get_user(*users, fd), buffer, -2));
    }
  if (edit_channels(fd, command, channel, *users) == -1)
    return (-1);
  return (0);
}
