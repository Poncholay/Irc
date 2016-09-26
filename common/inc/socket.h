/*
** socket.h for myftp in /home/wilmot_g/Rendu/PSU_2015_myftp
**
** Made by guillaume wilmot
** Login   <wilmot_g@epitech.net>
**
** Started on  Mon May  2 11:11:18 2016 guillaume wilmot
** Last update Mon May  2 14:00:35 2016 guillaume wilmot
*/

#ifndef SOCKET_H_
# define SOCKET_H_

#include <netdb.h>

typedef struct		s_socket
{
  struct protoent	*pe;
  struct sockaddr_in	s_in;
  int			fd;
  int			port;
  int			(*init)(struct s_socket *, int, const char *,
				in_addr_t);
  int			(*close)(struct s_socket *);
  int			(*listen)(struct s_socket *);
  int			(*accept)(struct s_socket *, struct sockaddr_in *);
  int			(*bind)(struct s_socket *);
  int			(*connect)(struct s_socket *);
}			t_socket;

t_socket		*create_socket();
int			init_socket(t_socket *, int, const char *, in_addr_t);
int			close_socket(t_socket *);
int			listen_socket(t_socket *);
int			accept_socket(t_socket *, struct sockaddr_in *);
int			bind_socket(t_socket *);
int			connect_socket(t_socket *);

#endif /* !SOCKET_H_ */
