/*
** create_socket.c for myftp in /home/wilmot_g/Rendu/PSU_2015_myftp
**
** Made by guillaume wilmot
** Login   <wilmot_g@epitech.net>
**
** Started on  Mon May  2 13:54:29 2016 guillaume wilmot
** Last update Tue May 17 09:26:23 2016 Nyrandone Noboud-Inpeng
*/

#include <stdlib.h>
#include <unistd.h>
#include "socket.h"
#include "errors.h"

t_socket		*create_socket()
{
  t_socket		*socket;

  if (!(socket = malloc(sizeof(*socket))))
    return (puterr(ERR_MALLOC, NULL));
  socket->pe = NULL;
  socket->fd = -1;
  socket->port = -1;
  socket->init = &init_socket;
  socket->close = &close_socket;
  socket->listen = &listen_socket;
  socket->accept = &accept_socket;
  socket->connect = &connect_socket;
  socket->bind = &bind_socket;
  return (socket);
}

int			close_socket(t_socket *this)
{
  if (close(this->fd) == -1)
    return (puterr_int(ERR_CLOSE, -1));
  this->fd = -1;
  return (0);
}

int			init_socket(t_socket *this, int port, const char *proto,
				    in_addr_t addr)
{
  this->port = port;
  if (!(this->pe = getprotobyname(proto)))
    return (puterr_int(ERR_GETPROTOBYNAME, -1));
  if ((this->fd = socket(AF_INET, SOCK_STREAM, this->pe->p_proto)) == -1)
    return (puterr_int(ERR_SOCKET, -1));
  this->s_in.sin_family = AF_INET;
  this->s_in.sin_port = htons(port);
  this->s_in.sin_addr.s_addr = addr;
  return (0);
}
