/*
** circular_buffer.c for myIRC in /home/wilmot_g/Rendu/PSU_2015_myirc/common/src
**
** Made by guillaume wilmot
** Login   <wilmot_g@epitech.net>
**
** Started on  Thu May 19 00:41:38 2016 guillaume wilmot
** Last update Sat May 28 11:36:12 2016 Nyrandone Noboud-Inpeng
*/

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include "circular_buffer.h"
#include "errors.h"

t_buffs		*create_buffer(t_buffs *buffs)
{
  if (!memset(buffs, 0, sizeof(t_buffs)) ||
      !(buffs->in.buff = malloc(BUFFSIZE_IN * sizeof(char))) ||
      !(buffs->in.cmd = malloc(BUFFSIZE_IN * sizeof(char))) ||
      !(buffs->out.buff = malloc(BUFFSIZE_OUT * sizeof(char))) ||
      !(buffs->out.cmd = malloc(BUFFSIZE_OUT * sizeof(char))) ||
      !memset(buffs->in.buff, 0, BUFFSIZE_IN) ||
      !memset(buffs->in.cmd, 0, BUFFSIZE_IN) ||
      !memset(buffs->out.buff, 0, BUFFSIZE_OUT) ||
      !memset(buffs->out.cmd, 0, BUFFSIZE_OUT))
    return (puterr(ERR_MALLOC, NULL));
  buffs->in.size = BUFFSIZE_IN;
  buffs->out.size = BUFFSIZE_OUT;
  return (buffs);
}

int		write_to_buffer(const char *str, t_buff *buff, int size)
{
  unsigned int	go;
  int		i;

  if (!size)
    return (0);
  i = -1;
  go = buff->start == buff->end ? 1 : 0;
  while (++i < size && ((buff->end + i) % buff->size != buff->start || go--) &&
	 buff->overflow < buff->size)
    buff->buff[(buff->end + i) % buff->size] = str[i];
  if (((buff->end + i) % buff->size == buff->start && i != size) ||
      buff->overflow >= buff->size)
    return (-1);
  buff->end = (buff->end + i) % buff->size;
  buff->overflow += i;
  return (0);
}

static char	*get_next_cmd(t_buff *buff)
{
  char		*cmd;

  while ((buff->start_bis + buff->idx) % buff->size != buff->end)
    {
      buff->found = buff->found ? buff->found - 1 : buff->found;
      buff->cmd[buff->idx] = buff->buff[buff->start];
      buff->buff[buff->start] = '\0';
      buff->found = buff->cmd[buff->idx] == '\r' ? 2 : buff->found;
      if (buff->cmd[buff->idx] == '\n' && buff->found)
	buff->found = 3;
      buff->idx = (buff->idx + 1) % buff->size;
      buff->start = (buff->start + 1) % buff->size;
      buff->overflow--;
     if (buff->found == 3)
	{
	  cmd = strdup(buff->cmd);
	  buff->idx = 0;
	  buff->found = 0;
	  buff->start_bis = buff->start;
	  if (!memset(buff->cmd, 0, buff->size))
	    return (NULL);
	  return (cmd);
	}
    }
  return (NULL);
}

char		*get_buff_content(t_buff *buff)
{
  char		*dup;
  char		*cmd;

  if (!buff || !(dup = malloc(buff->size + 2)) ||
      !memset(dup, 0, buff->size + 2))
    return (NULL);
  cmd = get_next_cmd(buff);
  while (cmd)
    {
      strcat(dup, cmd);
      free(cmd);
      cmd = get_next_cmd(buff);
    }
  return (dup);
}

int		get_cmd_buff(int fd, t_buffs *buffs)
{
  char		tmp[buffs->in.size];
  char		*cmd;
  int		ret;

  if ((ret = read(fd, tmp, buffs->in.size)) <= 0)
    return (!(buffs->cmds = create_list(strdup("QUIT"), NULL)) ? -1 : -3);
  if (write_to_buffer(tmp, &buffs->in, ret) == -1)
    return (!memset(buffs->in.buff, 0, buffs->in.size) ||
	    !memset(buffs->in.cmd, 0, buffs->in.size) ||
	    !memset(&buffs->in.idx, 0, 5 * sizeof(int)
		    + sizeof(char)) ? -1 : -2);
  while ((cmd = get_next_cmd(&buffs->in)))
    {
      replace_end_of_string(cmd);
      if (!buffs->cmds)
	{
	  if (!(buffs->cmds = create_list(cmd, NULL)))
	    return (-1);
	}
      else if (!(buffs->cmds = buffs->cmds->push_back(buffs->cmds, cmd)))
	return (-1);
      if (!strcmp("QUIT", cmd) || !strncmp(cmd, "QUIT ", 5))
	return (0);
    }
  return (0);
}
