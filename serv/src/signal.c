/*
** signal.c for signal in /Users/noboud_n/Documents/Share/PSU_2015_myirc/serv/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Thu May 19 02:12:34 2016 Nyrandone Noboud-Inpeng
** Last update Mon May 23 14:43:24 2016 Nyrandone Noboud-Inpeng
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "serv.h"

t_socket		*save_socket(t_socket *server, const int force)
{
  static t_socket	*tmp = NULL;

  if (server != NULL || force == 1)
    tmp = server;
  return (tmp);
}

t_list			*save_users(t_list *users, const int force)
{
  static t_list		*tmp = NULL;

  if (users != NULL || force == 1)
    tmp = users;
  return (tmp);
}

t_list			*save_channels(t_list *channels, const int force)
{
  static t_list		*tmp = NULL;

  if (channels != NULL || force == 1)
    tmp = channels;
  return (tmp);
}

void			clean_socket()
{
  close_and_free(save_socket(NULL, 0),
		 save_users(NULL, 0),
		 save_channels(NULL, 0),
		 0);
  exit(0);
}
