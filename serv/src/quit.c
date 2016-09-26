/*
** quit.c for quit in /Users/noboud_n/Documents/Share/PSU_2015_myirc/serv/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Fri May 20 13:49:39 2016 Nyrandone Noboud-Inpeng
** Last update Sat May 21 02:21:37 2016 Nyrandone Noboud-Inpeng
*/

#include <stdio.h>
#include <unistd.h>
#include "serv.h"
#include "errors.h"

int		quit(const int fd, UNUSED char *command,
		     t_list **channel, t_list **users)
{
  delete_user_from_channels(fd, channel);
  delete_user_from_users_list(fd, users);
  if (close(fd) == -1)
    {
      fprintf(stderr, ERR_CLOSEQUIT);
      return (-1);
    }
  return (0);
}
