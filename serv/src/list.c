/*
** list.c for list in /Users/noboud_n/Documents/Share/PSU_2015_myirc/serv/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Wed May 18 17:44:25 2016 Nyrandone Noboud-Inpeng
** Last update Sun May 22 15:00:46 2016 Nyrandone Noboud-Inpeng
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "serv.h"
#include "replies.h"
#include "errors.h"

char		*lower(char *string)
{
  int		i;

  i = 0;
  while (string[i])
    {
      string[i] = tolower(string[i]);
      ++i;
    }
  return (string);
}

int		get_list_occurencies(char **answer, t_list *tmp,
				     char *command, int pass)
{
  char		*name;
  int		len;

  len = 0;
  while (tmp != NULL)
    {
      name = strdup(((t_cdata *)(tmp->struc))->name);
      if (strstr(lower(name), lower(command)))
	{
	  free(name);
	  name = ((t_cdata *)(tmp->struc))->name;
	  if ((pass == 0 && !(*answer = malloc(50 + strlen(name))))
	      || (pass != 0
		  && !(*answer = realloc(*answer,
					len + 50 + (strlen(name) * 2)))))
	    return (puterr_int(ERR_MALLOC, -1));
	  store_data_for_list(name, answer, &len, tmp);
	  ++pass;
	}
      else
	free(name);
      tmp = tmp->next;
    }
  return (0);
}

int		find_and_print_list(const int fd, t_list *channels,
				    t_list *users, char *command)
{
  t_list	*tmp;
  char		*answer;
  int		ret_value;

  answer = NULL;
  tmp = channels;
  if (tmp != NULL)
    {
      if ((ret_value = get_list_occurencies(&answer, tmp, command, 0)) == 0
	  && answer != NULL)
	{
	  if (store_answer(get_user(users, fd), answer, 0) == -1)
	    return (-1);
	  free(answer);
	}
      else if (ret_value == -1)
	return (-1);
    }
  return (0);
}

int		find_and_list(const int fd, t_list **channels,
			      t_list **users, char *command)
{
  char		buffer[4096];

  if (memset(buffer, 0, 4096) == NULL)
    return (puterr_int(ERR_MEMSET, -1));
  if (snprintf(buffer, 4096, RPL_LISTSTART) == -1)
    return (puterr_int(ERR_SNPRINTF, -1));
  if (store_answer(get_user(*users, fd), buffer, 0) == -1)
    return (-1);
  if (find_and_print_list(fd, *channels, *users, command) == -1)
    return (-1);
  if (memset(buffer, 0, 4096) == NULL)
    return (puterr_int(ERR_MEMSET, -1));
  if (snprintf(buffer, 4096, RPL_LISTEND) == -1)
    return (puterr_int(ERR_SNPRINTF, -1));
  if (store_answer(get_user(*users, fd), buffer, 0) == -1)
    return (-1);
  return (0);
}

int		list(const int fd, char *command,
		     t_list **channels, t_list **users)
{
  if ((command = strtok(command, " ")) == NULL)
    return (list_all(fd, channels, users));
  return (find_and_list(fd, channels, users, command));
}
