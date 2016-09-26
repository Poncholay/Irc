/*
** init.c for init in /Users/noboud_n/Documents/Share/PSU_2015_myirc/serv/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Thu May 19 14:50:18 2016 Nyrandone Noboud-Inpeng
** Last update Tue May 24 01:16:52 2016 Nyrandone Noboud-Inpeng
*/

#include <stdlib.h>
#include "serv.h"

void		init_code(char **code)
{
  code[0] = "NICK";
  code[1] = "USER";
  code[2] = "QUIT";
  code[3] = "LIST";
  code[4] = "JOIN";
  code[5] = "PART";
  code[6] = "USERS";
  code[7] = "NAMES";
  code[8] = "PRIVMSG";
  code[9] = "PING";
  code[10] = NULL;
}

void		init_ptrfunc(int (**func)(const int, char *,
					  t_list **, t_list **))
{
  func[0] = &nick;
  func[1] = &user;
  func[2] = &quit;
  func[3] = &list;
  func[4] = &join;
  func[5] = &part;
  func[6] = &users;
  func[7] = &names;
  func[8] = &msg;
  func[9] = &ping;
  func[10] = NULL;
}
