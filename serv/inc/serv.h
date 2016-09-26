/*
** serv.h for serv in /Users/noboud_n/Documents/Share/PSU_2015_myirc/serv/inc/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Mon May 16 16:36:15 2016 Nyrandone Noboud-Inpeng
** Last update Thu Jun  2 13:14:00 2016 Nyrandone Noboud-Inpeng
*/

#ifndef SERV_H_
# define SERV_H_

# define UNUSED __attribute__((unused))

# include "list.h"
# include "socket.h"
# include "circular_buffer.h"

typedef struct		s_processdata
{
  int			fd;
  char			*command;
}			t_processdata;

typedef struct		s_cdata
{
  char			*name;
  t_list		*users;
}			t_cdata;

typedef struct		s_udata
{
  int			is_registered;
  int			fd;
  char			*name;
  char			*uname;
  char			*host;
  char			*serv;
  char			*rname;
  char			*current_channel;
  t_buffs		buffs;
}			t_udata;

/*
** delete.c
*/
void		delete_user_from_channel(const int, const int,
					 t_list **, t_list *);
void		delete_user_from_channels(const int, t_list **);
void		delete_user_from_users_list(const int, t_list **);

/*
** error_messages.c
*/
int		unknown_command(const char *, t_list *);
int		not_enough_params(t_list *, const char *);
int		no_such_channel(t_list *, const char *);
int		cannot_send_to_chan(t_list *, const char *);

/*
** free.c
*/
int		close_and_free(t_socket *, t_list *, t_list *, int);

/*
** init.c
*/
void		init_code(char **);
void		init_ptrfunc(int (**)(const int, char *,
				      t_list **, t_list **));

/*
** join.c
*/
int		join(const int, char *, t_list **, t_list **);

/*
** join_messages.c
*/
int		join_succeed(const int, t_list *);
int		already_in_channel(const int, t_list *);

/*
** list.c
*/
int		list(const int, char *, t_list **, t_list **);

/*
** list_all.c
*/
void		store_data_for_list(const char *, char **, int *, t_list *);
int		list_all(const int, t_list **, t_list **);

/*
** msg.c
*/
int		msg(const int, char *, t_list **, t_list **);

/*
** manage_fd.c
*/

int		check_and_read(fd_set *, t_list **);
int		check_and_write(fd_set *, t_list **);
int		set_select_fd(t_socket *, t_list *, fd_set *, fd_set *);

/*
** management.c
*/
int		change_current_channel(const int, t_list **, char *);
int		take_first_arg(const int, char **, t_list *, char *);
int		take_args(char **, char *, const int);
t_list		*add_new_user(t_socket *, t_list *);

/*
** names.c
*/
int		final_answer(const int, const int, char *, t_list *);
char		*get_all_names(int *, char *, char *, t_list *);
int		names(const int, char *, t_list **, t_list **);

/*
** nick.c
*/
int		nick(const int, char *, t_list **, t_list **);

/*
** nick_messages.c
*/
int		send_nick_to_all(t_list *, t_list *, const char *);

/*
** part.c
*/
int		part_succeed(const int, t_list *, const char *, const char *);
int		part(const int, char *, t_list **, t_list **);

/*
** ping.c
*/
int		ping(const int, char *, t_list **, t_list **);

/*
** process.c
*/
int		core(t_socket *, t_list *, t_list *);

/*
** quit.c
*/
int		quit(const int fd, char *, t_list **, t_list **);

/*
** search_channel.c
*/
int		count_users_in_channel(t_list *);
int		get_index_channel_from_channels_list(t_list *, const char *);
t_list		*search_channel_by_name(t_list *, const char *);
int		search_channel_by_user_fd(t_list *, const int);

/*
** search_user.c
*/
int		get_index_user_from_users_list(t_list *, const int);
int		get_index_user_from_channel(t_list *, const int);
t_list		*get_user(t_list *, const int);
char		*get_user_name(t_list *, const int);
t_list		*get_user_by_name(t_list *, const char *);

/*
** server.c
*/
int		server(const int, char *, t_list **, t_list **);

/*
** server_sockets.c
*/
int		store_answer(t_list *, const char *, int);
t_socket	*init_server_socket(const int);

/*
** signal.c
*/
t_socket	*save_socket(t_socket *, const int);
t_list		*save_users(t_list *, const int);
t_list		*save_channels(t_list *, const int);
void		clean_socket();

/*
** store_nbr.c
*/
void		store_nbr(char **, int *, int);

/*
** user.c
*/
int		user(const int, char *, t_list **, t_list **);

/*
** users.c
*/
int		users(const int, char *, t_list **, t_list **);

#endif /* SERV_H_ */
