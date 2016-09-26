/*
** errors.c for myftp in /home/wilmot_g/Rendu/PSU_2015_myftp
**
** Made by guillaume wilmot
** Login   <wilmot_g@epitech.net>
**
** Started on  Mon May  2 11:16:55 2016 guillaume wilmot
** Last update Mon May  2 12:19:19 2016 guillaume wilmot
*/

#include <unistd.h>
#include <string.h>
#include "errors.h"

int		puterr_int(const char *err, int ret)
{
  if (err)
    write(2, err, strlen(err));
  return (ret);
}

void		*puterr(const char *err, void *ret)
{
  if (err)
    write(2, err, strlen(err));
  return (ret);
}
