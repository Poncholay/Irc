/*
** main.c for main.c in /Users/noboud_n/Documents/Share/PSU_2015_myirc/client/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Mon May 16 11:36:21 2016 Nyrandone Noboud-Inpeng
** Last update Tue May 24 13:18:21 2016 guillaume wilmot
*/

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "errors.h"
#include "client.h"
#include "socket.h"
#include "list.h"

void		init_code_bis(char **code)
{
  code[0] = NULL;
  code[1] = "NICK";
  code[2] = "LIST";
  code[3] = "JOIN";
  code[4] = "PART";
  code[5] = "USERS";
  code[6] = "PRIVMSG";
  code[7] = "NAMES";
  code[8] = NULL;
  code[9] = "PONG";
  code[10] = NULL;
}

void		init_code(char **code)
{
  code[0] = "/server";
  code[1] = "/nick";
  code[2] = "/list";
  code[3] = "/join";
  code[4] = "/part";
  code[5] = "/users";
  code[6] = "/msg";
  code[7] = "/names";
  code[8] = "/quit";
  code[9] = "/pong";
  code[10] = NULL;
}

void		init_ptrfunc(int (**func)(t_socket *, t_buffs *, char *))
{
  func[0] = &server;
  func[1] = &func_template;
  func[2] = &func_template;
  func[3] = &func_template;
  func[4] = &func_template;
  func[5] = &func_template;
  func[6] = &func_template;
  func[7] = &func_template;
  func[8] = &quit;
  func[9] = &func_template;
  func[10] = NULL;
}

int		main()
{
  t_socket	*socket;

  if ((socket = create_socket()) == NULL)
    return (-1);
  return (wait_for_input(socket));
}
