/*
** circular_buffer.c for myIRC in /home/wilmot_g/Rendu/PSU_2015_myirc/common/src
**
** Made by guillaume wilmot
** Login   <wilmot_g@epitech.net>
**
** Started on  Thu May 19 00:41:38 2016 guillaume wilmot
** Last update Fri May 20 15:02:06 2016 guillaume wilmot
*/

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include "circular_buffer.h"

static int	get_line_buff(t_buff *buff)
{
  while (buff->end && buff->idx < PACKETSIZE)
    {
      buff->check = buff->check ? buff->check - 1 : buff->check;
      buff->cmd[buff->idx++] = buff->buff[buff->start];
      if (buff->buff[buff->start] == '\r')
	buff->check = 2;
      if (buff->buff[buff->start] == '\n' && buff->check == 1)
	buff->check = 3;
      buff->start = buff->start + 1 >= PACKETSIZE * 2 ? 0 : buff->start + 1;
      buff->end--;
      if (buff->check == 3)
	{
	  buff->check = 0;
	  buff->cmd[buff->idx] = 0;
	  return (0);
	}
    }
  return (-1);
}

char		*reinit(t_buff *buff)
{
  if (!memset(buff->final, 0, sizeof(buff->final)) ||
      !strcat(buff->final, buff->cmd) ||
      !memset(buff->cmd, 0, sizeof(buff->cmd)))
    return (NULL);
  buff->idx = 0;
  buff->check = 0;
  return (buff->final);
}

char		*get_cmd_buff(int fd, t_buff *buff)
{
  int		cmd;

  cmd = get_line_buff(buff);
  if (cmd == -1)
    {
      if (buff->idx >= PACKETSIZE)
	return (buff->cmd);
      if ((buff->end = read(fd, &buff->buff[buff->back],
			    PACKETSIZE * 2 - buff->back > PACKETSIZE ?
			    PACKETSIZE : PACKETSIZE * 2 - buff->back)) <= 0)
	return (strncat(buff->cmd, "QUIT", 4), reinit(buff));
      buff->back = buff->back + buff->end >= PACKETSIZE * 2 ?
	buff->back + buff->end - PACKETSIZE * 2 : buff->back + buff->end;
      if ((cmd = get_line_buff(buff)) == -1)
	return (NULL);
    }
  return (reinit(buff));
}

int		send_msg(int fd, char *str)
{
  unsigned int	i;
  unsigned int	len;
  int		ret;

  i = 0;
  len = strlen(str);
  while (i < len)
    {
      if ((ret = write(fd, &str[i], PACKETSIZE / 10 > len - i ?
		       len - i : PACKETSIZE / 10)) == -1)
	return (-1);
      i += ret;
    }
  return (0);
}
