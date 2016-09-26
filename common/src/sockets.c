/*
** sockets.c for myftp in /home/wilmot_g/Rendu/PSU_2015_myftp
**
** Made by guillaume wilmot
** Login   <wilmot_g@epitech.net>
**
** Started on  Mon May  2 11:06:34 2016 guillaume wilmot
** Last update Tue May 17 00:39:50 2016 Nyrandone Noboud-Inpeng
*/

#include <unistd.h>
#include <stdlib.h>
#include "errors.h"
#include "socket.h"

int			connect_socket(t_socket *this)
{
  if (connect(this->fd, (const struct sockaddr *)&this->s_in,
	      sizeof(this->s_in)) == -1)
    {
      this->close(this);
      return (puterr_int(ERR_CONNECT, -1));
    }
  return (0);
}

int			bind_socket(t_socket *this)
{
  if (bind(this->fd, (const struct sockaddr *)&this->s_in,
           sizeof(this->s_in)) == -1)
    {
      this->close(this);
      return (puterr_int(ERR_BIND, -1));
    }
  return (0);
}

int			listen_socket(t_socket *this)
{
  if (listen(this->fd, SOMAXCONN) == -1)
    {
      this->close(this);
      return (puterr_int(ERR_LISTEN, -1));
    }
  return (0);
}

int			accept_socket(t_socket *this,
				      struct sockaddr_in *s_in_client)
{
  socklen_t		s_in_size;
  int			client_fd;

  s_in_size = sizeof(*s_in_client);
  if ((client_fd = accept(this->fd,
			  (struct sockaddr *)s_in_client, &s_in_size)) == -1)
    {
      this->close(this);
      return (puterr_int(ERR_ACCEPT, -1));
    }
  return (client_fd);
}
