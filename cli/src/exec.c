/*
** exec.c for myIRC in /home/wilmot_g/Rendu/PSU_2015_myirc
**
** Made by guillaume wilmot
** Login   <wilmot_g@epitech.net>
**
** Started on  Mon May 23 16:27:27 2016 guillaume wilmot
** Last update Tue May 24 13:46:44 2016 guillaume wilmot
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "client.h"
#include "errors.h"
#include "circular_buffer.h"
#include "socket.h"

int		send_as_message(t_buffs *buffs, char *cmd, char *channel)
{
  char		buff[4097];

  if (!strcmp(channel, ""))
    return (puterr_int("Error: No channel\n", 0));
  if (!memset(buff, 0, sizeof(buff)))
    return (puterr_int(ERR_MEMSET, -1));
  if (snprintf(buff, 4096, "PRIVMSG %s %s\r\n", channel, cmd) == -1 ||
      write_to_buffer(buff, &buffs->out, strlen(buff)) == -1)
    return (puterr_int("Error: message too long", -2));
  return (0);
}

char		*replace(char *fcmd)
{
  char		*code[12];
  char		*bis[12];
  char		*cmd;
  char		*back;
  char		*tmp;
  int		i;

  init_code(code);
  init_code_bis(bis);
  if (!(back = strdup(fcmd)))
    return (puterr(ERR_MALLOC, NULL));
  if (!(cmd = strtok(back, " ")))
    return (free(back), fcmd);
  i = -1;
  while (code[++i])
    if (!strcmp(code[i], cmd))
      {
	tmp = strtok(NULL, "");
	if (!(cmd = malloc(4097)) || !memset(cmd, 0, 4097) ||
	    snprintf(cmd, 4096, "%s%s%s\r\n", bis[i], tmp ? " " : "",
		     tmp ? tmp : "") == -1)
	  return (free(back), NULL);
	return (free(back), free(fcmd), cmd);
      }
  return (free(back), fcmd);
}

int		parse_cmd(char *fcmd, t_socket *socket,
			  t_buffs *buffs, char *channel)
{
  char		*code[12];
  int		(*func[12])(t_socket *, t_buffs *, char *);
  char		*cmd;
  char		*back;
  int		i;

  init_code(code);
  init_ptrfunc(func);
  if (!(back = strdup(fcmd)))
    return (puterr_int(ERR_MALLOC, -1));
  if (!(cmd = strtok(back, " ")))
    return (0);
  i = -1;
  if (cmd[0] == '/')
    while (code[++i])
      if (!strcmp(code[i], cmd))
	return (free(back), func[i](socket, buffs, fcmd));
  if (socket->fd != -1 && cmd[0] != '/')
    send_as_message(buffs, fcmd, channel);
  else
    fprintf(stderr, "No such command\n");
  return (free(back), 0);
}
