/*
** client.c for myIRC in /home/wilmot_g/Rendu/PSU_2015_myirc
**
** Made by guillaume wilmot
** Login   <wilmot_g@epitech.net>
**
** Started on  Thu May 19 17:38:27 2016 guillaume wilmot
** Last update Tue May 24 13:38:55 2016 guillaume wilmot
*/

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "client.h"
#include "errors.h"
#include "socket.h"
#include "circular_buffer.h"

void			set_fds(fd_set *writef, fd_set *readf,
				int fd, t_buffs *buffs)
{
  if (writef)
    FD_ZERO(writef);
  if (readf)
    FD_ZERO(readf);
  if (fd != -1)
    {
      if (buffs->out.start != buffs->out.end)
	writef ? FD_SET(fd, writef) : 0;
      readf ? FD_SET(fd, readf) : 0;
    }
  readf ? FD_SET(0, readf) : 0;
}

void			change_channel(char *cmd, char *channel, char *nick)
{
  char			*tmp;
  char			arg[10];

  change_nick(strdup(cmd), nick);
  if (!memset(arg, 0, sizeof(arg)) ||
      !(tmp = strtok(cmd, " ")) || tmp[0] != ':' ||
      strcmp(&tmp[1], nick) || !(tmp = strtok(NULL, " ")) ||
      (strcmp(tmp, "JOIN") && strcmp(tmp, "PART"))
      || !strncat(arg, tmp, 9) || !(tmp = strtok(NULL, " ")) ||
      tmp[0] != ':' || !memset(channel, 0, 4097))
    return ;
  if (!strcmp(arg, "JOIN"))
    strncat(channel, &tmp[1], 4096);
  else
    memset(channel, 0, 4097);
}

char			*read_all(int fd, fd_set *readf,
				  t_buffs *buffs, char **chan_nick)
{
  t_list                *tmp_cmd;
  int			ret;

  buffs->cmds ? free_content(buffs->cmds) : 0;
  buffs->cmds ? buffs->cmds->destroy(buffs->cmds) : 0;
  buffs->cmds = NULL;
  if (FD_ISSET(fd, readf))
    {
      if ((ret = get_cmd_buff(fd, buffs)) == -1)
	return (NULL);
      else if (ret == -3)
	return (NULL);
      else if (ret == -2)
	puterr("Reply too long\n", 0);
    }
  tmp_cmd = buffs->cmds;
  while (tmp_cmd)
    {
      fprintf(stderr, "%s\n", (char *)tmp_cmd->struc);
      change_channel((char *)tmp_cmd->struc, chan_nick[0], chan_nick[1]);
      tmp_cmd = tmp_cmd->next;
    }
  if (FD_ISSET(0, readf))
    return (get_next_line(0));
  return ("");
}

int			write_all(fd_set *writef, t_buffs *buffs, int fd)
{
  char			*buff;
  int                   ret;

  if (FD_ISSET(fd, writef))
    if ((buff = get_buff_content(&buffs->out)))
      {
	if ((ret = write(fd, buff, strlen(buff)) == -1))
	  return (puterr_int(ERR_ANSWER, -1));
	free(buff);
      }
  return (0);
}

int			wait_for_input(t_socket *socket)
{
  char			*in[2];
  t_buffs		buffs;
  fd_set		fs[2];
  char			*cmd;
  struct timeval	tv;

  if (!create_buffer(&buffs) || !(in[0] = malloc(4097)) ||
      !(in[1] = malloc(4097)) || !memset(in[0], 0, 4097) ||
      !memset(in[1], 0, 4097) || gethostname(in[1], 4096) == -1)
    return (-1);
  while (1)
    {
      tv.tv_sec = 1;
      tv.tv_usec = 0;
      set_fds(&fs[1], &fs[0], socket->fd, &buffs);
      if (select(socket->fd != -1 ? socket->fd + 1 : 1,
		 &fs[0], &fs[1], NULL, &tv) == -1)
	return (puterr_int(ERR_SELECT, -1));
      if (!(cmd = read_all(socket->fd, &fs[0], &buffs, in)) ||
	  write_all(&fs[1], &buffs, socket->fd) == -1 ||
	  (cmd && strcmp(cmd, "") && parse_cmd(cmd, socket,
					       &buffs, in[0]) == -1))
	return (free(in[0]), free(in[1]), -1);
    }
}
