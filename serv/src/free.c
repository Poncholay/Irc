/*
** free.c for free in /Users/noboud_n/Documents/Share/PSU_2015_myirc/serv/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Fri May 20 13:35:19 2016 Nyrandone Noboud-Inpeng
** Last update Sun May 22 18:55:46 2016 guillaume wilmot
*/

#include <stdlib.h>
#include <unistd.h>
#include "errors.h"
#include "serv.h"

void		free_channels_structures(t_list *channels)
{
  t_list	*tmp;
  t_list	*tmp_cdata;

  tmp = channels;
  while (tmp != NULL)
    {
      tmp_cdata = ((t_cdata *)(tmp->struc))->users;
      tmp_cdata->destroy(tmp_cdata);
      if (tmp->struc != NULL)
	{
	  free(((t_cdata *)(tmp->struc))->name);
	  free(tmp->struc);
	  tmp->struc = NULL;
	}
      tmp = tmp->next;
    }
}

int		close_and_free(t_socket *socket, t_list *users,
			       t_list *channels, int ret_value)
{
  t_list	*tmp;
  t_list	*tmp_free;

  tmp = users;
  if (socket && socket->fd != -1)
    {
      if (socket->close(socket) == -1)
	return (-1);
    }
  while (tmp != NULL)
    {
      if (((t_udata *)(tmp->struc))->fd != -1)
	{
	  if (close(((t_udata *)(tmp->struc))->fd) == -1)
	    return (puterr_int(ERR_CLOSE, -1));
	}
      tmp_free = tmp;
      tmp = tmp->next;
      delete_user_from_users_list(((t_udata *)(tmp_free->struc))->fd,
				  &tmp_free);
    }
  channels ? free_channels_structures(channels) : 0;
  channels ? channels->destroy(channels) : 0;
  return (socket ? free(socket) : 0, ret_value);
}
