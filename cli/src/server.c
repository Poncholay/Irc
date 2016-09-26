/*
** server.c for server in /Users/noboud_n/Documents/Share/PSU_2015_myirc/cli/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Mon May 16 23:22:26 2016 Nyrandone Noboud-Inpeng
** Last update Tue May 24 13:37:03 2016 guillaume wilmot
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "socket.h"
#include "circular_buffer.h"
#include "errors.h"

static int	after_connection(t_buffs *buffs)
{
  char		cmd[4097];
  char		name[1025];

  if (!memset(cmd, 0, sizeof(cmd)) ||
      !memset(name, 0, sizeof(name)) ||
      gethostname(name, 1024) ||
      snprintf(cmd, 4096, "NICK %s\r\n", name) == -1)
    return (puterr_int(ERR_MEMSET, -1));
  if (write_to_buffer(cmd, &buffs->out, strlen(cmd)) == -1)
    return (puterr_int("Error: Buffer overflow\n", -2));
  if (!memset(cmd, 0, sizeof(cmd)) ||
      snprintf(cmd, 4096, "USER %s %s %s %s\r\n", name, name,
	       "127.0.0.1", "FooBar") == -1)
    return (puterr_int("Error: Buffer overflow\n", -2));
  if (write_to_buffer(cmd, &buffs->out, strlen(cmd)) == -1)
    return (puterr_int("Error: Buffer overflow\n", -2));
  return (0);
}

int		server(t_socket *socket, t_buffs *buffs, char *cmdf)
{
  char		*ip;
  char		*port;

  if (!strtok(cmdf, " ") || !(ip = strtok(NULL, ":")))
    return (puterr_int("Error: /server ip port\n", -2));
  port = strtok(NULL, "");
  if (init_socket(socket, port == NULL ? 6667 : atoi(port), "TCP",
		  inet_addr(ip)) == -1)
      return (puterr_int("Error: Unable to initiate connection\n", -2));
  if (connect_socket(socket) == -1)
    return (puterr_int("Error: Unable to connect\n", -2));
  printf("Trying to connect to %s:%d\n", ip, port == NULL ? 6667 : atoi(port));
  return (after_connection(buffs));
}
