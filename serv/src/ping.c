/*
** ping.c for ping in /Pings/noboud_n/Documents/Share/PSU_2015_myirc/serv/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Sun May 22 16:47:22 2016 Nyrandone Noboud-Inpeng
** Last update Mon May 23 15:27:56 2016 guillaume wilmot
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "serv.h"
#include "errors.h"
#include "replies.h"

int		ping(const int fd, char *command,
		     UNUSED t_list **channels, t_list **users)
{
  t_list	*user;
  t_udata	*data;
  char		buff[4096];

  if ((user = get_user(*users, fd)) == NULL || (data = user->struc) == NULL)
    return (puterr_int(ERR_UNKNOWNUSER, -1));
  if (!memset(buff, 0, sizeof(buff)))
    return (puterr_int(ERR_MEMSET, -1));
  if (snprintf(buff, 4096, "PONG %s\r\n", command) == -1)
    return (puterr_int(ERR_SNPRINTF, -1));
  store_answer(user, buff, 0);
  return (0);
}
