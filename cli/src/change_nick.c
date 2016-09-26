/*
** change_nick.c for myIRC in /home/wilmot_g/Rendu/PSU_2015_myirc
**
** Made by guillaume wilmot
** Login   <wilmot_g@epitech.net>
**
** Started on  Tue May 24 12:07:30 2016 guillaume wilmot
** Last update Tue May 24 13:08:42 2016 guillaume wilmot
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void		 	change_nick(char *cmd, char *nick)
{
  char			*tmp;

  if ((tmp = strtok(cmd, " ")))
    {
      if (tmp[0] == ':')
	tmp = strtok(NULL, " ");
      if (!tmp || strcmp(tmp, "NICK") || !(tmp = strtok(NULL, "")) ||
	  !memset(nick, 0, 4097) || !strncat(nick, tmp, 4096))
	{
	  free(cmd);
	  return ;
	}
    }
  free(cmd);
}
