/*
** list_all.c for list_all in /Users/noboud_n/Documents/Share/PSU_2015_myirc/serv/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Sun May 22 00:17:31 2016 Nyrandone Noboud-Inpeng
** Last update Sun May 22 00:43:12 2016 Nyrandone Noboud-Inpeng
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "serv.h"
#include "errors.h"
#include "replies.h"

void		store_data_for_list(const char *name, char **answer,
				    int *len, t_list *tmp)
{
  int		i;

  i = 0;
  while (RPL_LIST[i])
    (*answer)[(*len)++] = RPL_LIST[i++];
  i = 0;
  while (name[i])
    (*answer)[(*len)++] = name[i++];
  (*answer)[(*len)++] = ' ';
  store_nbr(answer, len, count_users_in_channel(tmp));
  (*answer)[(*len)++] = ' ';
  (*answer)[(*len)++] = ':';
  i = 0;
  while (name[i])
    (*answer)[(*len)++] = name[i++];
  if (tmp->next)
    (*answer)[(*len)++] = '\n';
  else
    {
      (*answer)[(*len)++] = '\r';
      (*answer)[(*len)++] = '\n';
      (*answer)[(*len)++] = '\0';
    }
}

int		store_and_print_list(const int fd,
				     t_list *channels, t_list *users)
{
  char		*answer;
  char		*name;
  t_list	*tmp;
  int		len;

  answer = NULL;
  tmp = channels;
  len = 0;
  if (tmp != NULL)
    {
      while (tmp != NULL)
	{
	  name = ((t_cdata *)(tmp->struc))->name;
	  if ((tmp == channels && !(answer = malloc(50 + strlen(name))))
	      || (tmp != channels && !(answer = realloc(answer,
      						  len + 50 + (strlen(name) * 2)))))
      	    return (puterr_int(ERR_MALLOC, -1));
	  store_data_for_list(name, &answer, &len, tmp);
	  tmp = tmp->next;
	}
      if (store_answer(get_user(users, fd), answer, 0) == -1)
	return (-1);
      free(answer);
    }
  return (0);
}

int		list_all(const int fd, t_list **channels, t_list **users)
{
  char		buffer[4096];

  if (memset(buffer, 0, 4096) == NULL)
    return (puterr_int(ERR_MEMSET, -1));
  if (snprintf(buffer, 4096, RPL_LISTSTART) == -1)
    return (puterr_int(ERR_SNPRINTF, -1));
  if (store_answer(get_user(*users, fd), buffer, 0) == -1)
    return (-1);
  if (store_and_print_list(fd, *channels, *users) == -1)
    return (-1);
  if (memset(buffer, 0, 4096) == NULL)
    return (puterr_int(ERR_MEMSET, -1));
  if (snprintf(buffer, 4096, RPL_LISTEND) == -1)
    return (puterr_int(ERR_SNPRINTF, -1));
  if (store_answer(get_user(*users, fd), buffer, 0) == -1)
    return (-1);
  return (0);
}
