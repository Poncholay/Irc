/*
** client.h for client in /Users/noboud_n/Documents/Share/PSU_2015_myirc/cli/inc/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Mon May 16 23:24:52 2016 Nyrandone Noboud-Inpeng
** Last update Tue May 24 12:46:56 2016 guillaume wilmot
*/

#ifndef CLIENT_H_
# define CLIENT_H_

# include "circular_buffer.h"
# include "socket.h"

/*
** client.c
*/
int		wait_for_input(t_socket *);
void		change_nick(char *, char *);

/*
** exec.c
*/
int		parse_cmd(char *, t_socket *, t_buffs *, char *);
char		*replace(char *);

/*
** get_next_line.c
*/
char		*get_next_line(const int);
/*
** main.c
*/
void		init_code_bis(char **);
void		init_code(char **);
void		init_ptrfunc(int (**)(t_socket *, t_buffs *, char *));

/*
** func.c
*/
int		func_template(t_socket *, t_buffs *, char *);

/*
** server.c
*/
int		server(t_socket *, t_buffs *, char *);

/*
** quit.c
*/
int		quit(t_socket *, t_buffs *, char *);

#endif /* !CLIENT_H_ */
