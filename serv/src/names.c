/*
** names.c for names in /Users/noboud_n/Documents/Share/PSU_2015_myirc/serv/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Fri May 20 21:36:28 2016 Nyrandone Noboud-Inpeng
** Last update Thu Jun  2 10:35:26 2016 Nyrandone Noboud-Inpeng
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "serv.h"
#include "errors.h"
#include "replies.h"

int		final_answer(const int fd, const int len,
			    char *names_list, t_list *current_channel)
{
  char		*answer;
  char		buffer[4096];
  t_list	*user;

  answer = NULL;
  if ((answer = malloc(50 + len)) == NULL)
    return (puterr_int(ERR_MALLOC, -1));
  if (snprintf(answer,
	       50 + len,
	       RPL_NAMREPLY, ((t_cdata *)(current_channel->struc))->name,
	       len != 0 ? names_list : "\0") == -1)
    return (puterr_int(ERR_SNPRINTF, -1));
  user = get_user(save_users(NULL, 0), fd);
  if (store_answer(user, answer, 0) == -1)
    return (puterr_int(ERR_COMMUNICATE, -1));
  free(names_list);
  free(answer);
  if (memset(buffer, 0, 4096) == NULL)
    return (puterr_int(ERR_MEMSET, -1));
  if (snprintf(buffer, 4096, RPL_ENDOFNAMES,
	       ((t_cdata *)(current_channel->struc))->name) == -1)
    return (puterr_int(ERR_SNPRINTF, -1));
  return (store_answer(user, buffer, 0));
}

int		check_current_channel(t_list **current_channel,
				      t_list *channels, const int fd,
				      const char *command)
{
  char		buffer[4096];
  t_list	*users;

  users = save_users(NULL, 0);
  if ((*current_channel = search_channel_by_name(channels, command)) == NULL)
    {
      if (memset(buffer, 0, 4096) == NULL)
	return (puterr_int(ERR_MEMSET, -1));
      if (snprintf(buffer, 4096, ERR_NOSUCHNICK, command) == -1)
	return (puterr_int(ERR_SNPRINTF, -1));
      return (store_answer(get_user(users, fd), buffer, -2));
    }
  return (0);
}

char		*get_all_names(int *len, char *name,
			       char *names_list, t_list *tmp_users)
{
  while (tmp_users != NULL)
    {
      name = ((t_udata *)(tmp_users->struc))->name;
      if (*len == 0)
	{
	  if ((names_list = malloc(strlen(name) + 2)) == NULL)
	    return (puterr(ERR_MALLOC, NULL));
	  names_list[0] = '\0';
	}
      else if ((names_list = realloc(names_list,
				     *len + strlen(name) + 4)) == NULL)
	return (puterr(ERR_REALLOC, NULL));
      if (*len != 0)
	{
	  names_list[(*len)++] = ' ';
	  names_list[(*len)] = '\0';
	}
      if ((names_list = strcat(names_list, name)) == NULL)
	return (puterr(ERR_STRCAT, NULL));
      (*len) += strlen(name);
      tmp_users = tmp_users->next;
    }
  return (names_list);
}

int		names(const int fd, char *command,
		      t_list **channel, t_list **users)
{
  char		buffer[4096];
  t_list	*current_channel;
  int		ret_value;
  int		len;
  char		*names_list;

  len = 0;
  current_channel = NULL;
  if (memset(buffer, 0, 4096) == NULL)
    return (puterr_int(ERR_MEMSET, -1));
  if (snprintf(buffer, 4096, ERR_NEEDMOREPARAMS,
	      get_user_name(*users, fd), "NAMES") == -1)
    return (puterr_int(ERR_SNPRINTF, -1));
  if (command == NULL)
    return (store_answer(get_user(*users, fd), buffer, -2));
  if ((ret_value = check_current_channel(&current_channel,
					 *channel, fd, command)) != 0)
    return (ret_value);
  if ((names_list =
       get_all_names(&len, NULL, NULL,
		     ((t_cdata *)(current_channel->struc))->users)) == NULL)
    return (-1);
  return (final_answer(fd, len, names_list, current_channel));
}
