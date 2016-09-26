/*
** process.c fr process in /Users/noboud_n/Documents/Share/PSU_2015_myirc/serv/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Thu May 19 02:24:12 2016 Nyrandone Noboud-Inpeng
** Last update Tue May 24 01:57:45 2016 guillaume wilmot
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "serv.h"
#include "socket.h"
#include "errors.h"
#include "replies.h"

static int		process(t_processdata *pdata,
				t_list **channels, t_list **users)
{
  char			*code[11];
  int			(*func[11])(const int, char *, t_list **, t_list **);
  int			i;
  char			*function_to_call;
  t_udata		*user_data;

  i = -1;
  init_code(code);
  init_ptrfunc(func);
  if (get_user(*users, pdata->fd) == NULL
      || (user_data = (t_udata *)(get_user(*users, pdata->fd)->struc)) == NULL)
    return (puterr_int(ERR_UNKNOWNUSER, -1));
  if ((function_to_call = strtok(pdata->command, " ")) == NULL)
    return (puterr_int(ERR_SYNTAX, -2));
  while (user_data->is_registered == 0 || user_data->name == NULL ?
	 ++i < 3 : code[++i] != NULL)
    if (!strcmp(code[i], function_to_call))
      {
	if (func[i](pdata->fd, strtok(NULL, ""), channels, users) == -1)
	  return (-1);
	save_users(*users, 1);
	save_channels(*channels, 1);
	return (0);
      }
  return (unknown_command(function_to_call, get_user(*users, pdata->fd)));
}

static int		process_all(t_list **channels, t_list **users)
{
  t_list		*tmp;
  t_list		*tmp_cmd;
  t_list		*next;
  t_list		*next_cmd;
  t_processdata		pdata;

  tmp = *users;
  while (tmp)
    {
      tmp_cmd = ((t_udata *)(tmp->struc))->buffs.cmds;
      next = tmp->next;
      while (tmp_cmd)
	{
	  pdata.fd = ((t_udata *)(tmp->struc))->fd;
	  pdata.command = tmp_cmd->struc;
	  fprintf(stderr, "%s\n", pdata.command);
	  next_cmd = tmp_cmd->next;
	  if (process(&pdata, channels, users) == -1)
	    return (-1);
	  tmp_cmd = *users ? next_cmd : NULL;
	}
      tmp = *users ? next : NULL;
    }
  return (0);
}

int			core(t_socket *socket, t_list *channels, t_list *users)
{
  fd_set		readf;
  fd_set		writef;
  struct timeval	tv;
  int			higher_fd;

  while (1)
    {
      tv.tv_sec = 5;
      tv.tv_usec = 0;
      FD_ZERO(&readf);
      FD_ZERO(&writef);
      higher_fd = set_select_fd(socket, users, &readf, &writef);
      if (select(higher_fd + 1, &readf, &writef, NULL, &tv) == -1)
	return (puterr_int(ERR_SELECT, -1));
      if (FD_ISSET(socket->fd, &readf))
	{
	  if ((users = add_new_user(socket, users)) == NULL)
	    return (close_and_free(socket, users, channels, -1));
	  save_users(users, 1);
	}
      if (check_and_read(&readf, &users) == -1 ||
	  process_all(&channels, &users) == -1 ||
	  check_and_write(&writef, &users) == -1)
	return (close_and_free(socket, users, channels, -1));
    }
}
