/*
** replace_eol.c for myIRC in /home/wilmot_g/Rendu/PSU_2015_myirc
**
** Made by guillaume wilmot
** Login   <wilmot_g@epitech.net>
**
** Started on  Sat May 21 23:10:59 2016 guillaume wilmot
** Last update Sat May 21 23:21:10 2016 guillaume wilmot
*/

#include <string.h>

void		replace_end_of_string(char *string)
{
  int		i;

  if (!string)
    return ;
  i = strlen(string);
  if (i > 1 && string[i - 1] == '\n' && string[i - 2] == '\r')
    string[i - 2] = '\0';
}
