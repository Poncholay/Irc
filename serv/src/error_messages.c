/*
** error_messages.c for error_messages.c in /Users/noboud_n/Documents/Share/PSU_2015_myirc/serv/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Sat May 21 14:43:25 2016 Nyrandone Noboud-Inpeng
** Last update Mon May 23 16:36:13 2016 Nyrandone Noboud-Inpeng
*/

#include <string.h>
#include <stdio.h>
#include "serv.h"
#include "errors.h"
#include "replies.h"

int		unknown_command(const char *command, t_list *user)
{
  char		buffer[4096];

  if (user == NULL)
    return (puterr_int(ERR_UNKNOWNUSER, -1));
  if (memset(buffer, 0, 4096) == NULL)
    return (puterr_int(ERR_MEMSET, -1));
  if (snprintf(buffer, 4096, ERR_UNKNOWNCMD, command) == -1)
    return (puterr_int(ERR_SNPRINTF, -1));
  return (store_answer(user, buffer, -2));
}

int		not_enough_params(t_list *user, const char *command)
{
  char		buffer[4096];
  char		*name;

  if (user == NULL)
    return (puterr_int(ERR_UNKNOWNUSER, -1));
  if (memset(buffer, 0, 4096) == NULL)
    return (puterr_int(ERR_MEMSET, -1));
  name = ((t_udata *)(user->struc))->name;
  if (snprintf(buffer, 4096, ERR_NEEDMOREPARAMS,
	       name == NULL ? "\0" : name, command) == -1)
    return (puterr_int(ERR_SNPRINTF, -1));
  return (store_answer(user, buffer, -2));
}

int		no_such_channel(t_list *user, const char *channel)
{
  char		buffer[4096];

  if (user == NULL)
    return (puterr_int(ERR_UNKNOWNUSER, -1));
  if (memset(buffer, 0, 4096) == NULL)
    return (puterr_int(ERR_MEMSET, -1));
  if (snprintf(buffer, 4096, ERR_NOSUCHCHANNEL, channel) == -1)
    return (puterr_int(ERR_SNPRINTF, -1));
  return (store_answer(user, buffer, -2));
}

int		cannot_send_to_chan(t_list *user, const char *channel)
{
  char		buffer[4096];

  if (user == NULL)
    return (puterr_int(ERR_UNKNOWNUSER, -1));
  if (memset(buffer, 0, 4096) == NULL)
    return (puterr_int(ERR_MEMSET, -1));
  if (snprintf(buffer, 4096, ERR_CANNOTSENDTOCHAN, channel) == -1)
    return (puterr_int(ERR_SNPRINTF, -1));
  return (store_answer(user, buffer, -2));
}
