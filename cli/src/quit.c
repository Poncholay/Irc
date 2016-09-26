/*
** quit.c for myIRC in /home/wilmot_g/Rendu/PSU_2015_myirc
**
** Made by guillaume wilmot
** Login   <wilmot_g@epitech.net>
**
** Started on  Thu May 19 18:16:23 2016 guillaume wilmot
** Last update Tue May 24 13:19:04 2016 guillaume wilmot
*/

#include <string.h>
#include <unistd.h>
#include "circular_buffer.h"
#include "socket.h"
#include "errors.h"

int		quit(t_socket *socket, t_buffs *buffs, char *cmd)
{
  (void)buffs;
  (void)cmd;
  (void)socket;
  return (-1);
}
