/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-bou <hben-bou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 23:14:14 by hben-bou          #+#    #+#             */
/*   Updated: 2023/08/02 01:36:44 by hben-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#define FD_ERROR "ERROR INITIALIZING FILE DESCIPTOR\n"
#define DUP_ERROR "ERROR DUPLICATING FILE\n"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <limits.h>
#include <signal.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

#define ENVIRON 1
#define EXPORT 2

#define IN_FILE 1
#define APPEND_FILE 2
#define OUT_FILE 3
#define HERE_FILE 4


extern char **environ;

typedef struct s_list
{
    char *file;
	char *str;
	int type;
    struct s_list *next;
} t_list;

typedef struct s_struct
{
	char **expor;
    char *PATH;
	char *buff;
    int pid;
	int exit_status;
} t_struct;

typedef struct data_struct
{
	char 	**parsed;
	int	k;
	int  sub_a;
	int  sub_b;
	int		cursh;
	int		paran;
}			t_parsing;

// --error checker
int error(char *str);
// --likatssb lik >,>>,<,<<
int redirect_count(char *str);
char **ft_spliting(char *str);
char	*ft_substr(char *s, int start, int len);
// --hada lparser
char **parser(char *str);
// --ft_split--
char **ft_split(char *str, char c);
// --utils--
void free_nodes(t_list **ls);
void my_free(char **str);
int is_alpha(int c);
int ft_strlen(char *str);
int ptr_len(char **str);
int ft_strcmp(char *s1, char *s2, int len);
int builtins(char **str, t_struct *s, int fd);
char *ft_strdup(char *str);
void ft_putchar(int c, int fd);
void ft_putstr(char *str);
void ft_putnbr(int nbr, int fd);
// --redirection
int redirection(char **ptr, t_struct *s);
// --main--
int commands(char **str);
// --environment--
void export(char *str, t_struct *s);
int till_equal(char *str);
void unset(char *str);
void declare_x(t_struct *s, int fd);
// --path--
char *path(char *str);
char *remove_nl(char *str);
// --parser--
int redirection_counter(char **str);
char **no_redir(char **parsed);
char **parser(char *str);
// --heredoc--
char *heredoc(char *str);
void delete_file(void);
char **herereturn(char **ptr, int trigger);
char *ft_strjoin(char *s1, char *s2, int type);
// --left_direct--
char *read_file(int fd);
char **direct_cmd(char **ptr);
// --create_files--
int *create_files(char **ptr);
int *create_file2(char **ptr, t_struct *s);
// --old_pwd--
void old_pwd(void);
void new_pwd(void);
// --echo--
void pwd(int fd);
void echo(char **str, t_struct *s, int fd);
int flag(char *str);
void cd(char **str);
void print_env(int type, t_struct *s, int fd);
// --builtins--
void dollar(char **ptr);
// --redirections
int redirections(char **str, t_struct *s);
int redirect(char **str, t_struct *s);
// --ft_atoi--
int ft_atoi(char *str);
// --pipes--
int pipe_counter(char **str);
int operator(char **str, char *str1);
int pipes(char **str, t_struct *s, int trigger);
char ***pipe_cmd(char **str);
char **xd(char **ptr);
int create_files11(t_list **linked, char **str);
#endif
