/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazrael <aazrael@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 22:17:20 by mlatashi          #+#    #+#             */
/*   Updated: 2022/02/10 11:52:34 by aazrael          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/errno.h>
# include <readline/readline.h>
# include <readline/history.h>

# define TRUE 1
# define FALSE 0

# define CMD 0
# define ARG 1
# define BUILTIN 2
# define PIPE 3
# define REDIR_OUT 4
# define REDIR_OUT_2 5
# define REDIR_IN 6
# define REDIR_HEREDOC 7

# define FALSE	0
# define TRUE	1

# define STDIN	0
# define STDOUT	1
# define STDERR	2

# define ERROR_STATUS 127
# define WIFSIGNALED_SIGINT 2
# define SIGINT_STATUS 130
# define WIFSIGNALED_SIGQUIT 3
# define SIGQUIT_STATUS 131

typedef struct s_token
{
	int				type;
	char			*str;
	struct s_token	*next;
	struct s_token	*prev;
	int				skip;
}	t_token;

typedef struct s_pid_t
{
	pid_t			pid;
	struct s_pid_t	*next;
}	t_pid_t;

typedef struct s_main
{
	t_pid_t	*childs;
	char	*message;
	int		exit;
	int		fds[1024][2];
	int		ret;
	int		error;
	int		in;
	int		out;
	int		fd_in;
	int		fd_out;
	t_token	*tokens;
}	t_main;

typedef struct s_global
{
	int	g_return;
	int	g_run;
	int	g_here_doc;
}	t_global;

t_global    g_main;

typedef struct s_env
{
	char			*str;
	struct s_env	*next;
}	t_env;

typedef struct s_parser
{
	int			i;
	int			j;
	int			last_space;
}				t_parser;

void		ft_sig(int code);
void		ft_signal_doc(int code);
void		on_eof(t_main *shell);
void		init0_shell(t_main *shell, char ***arr);
void		init1_shell(t_main *shell);
void		shell_err(t_main *shell);
void		free_data(t_token *a_tokens, t_token *b_tokens);
void		execution(t_main *shell);

void	simple_cmd(char **argv);
int		imple_cmd(char **argv);
void	free_char_list(char **list);
void	execute_last_cmd(t_token *token);
int		return_shell_err(t_main *shell);

void	exit_shell_err(t_main *shell);
int		fatal_error(t_main *shell);
void	malloc_err(void);
int		set_redirection(t_main *shell);

int		execute_builtin(t_main *shell, t_token *token);
t_token	*get_prev_input(t_token *token);

void	exec_here_doc(t_main *shell, t_token *token);
int		redirect_heredoc(t_main *shell, t_token *token, int *new_input);
int		get_next_line(int fd, char **line);
size_t	gnl_strlen(const char *s);
char	*gnl_strchr(const char *s, int c);
char	*gnl_strjoin(char *s1, char const *s2);
size_t	gnl_strlcpy(char *dst, const char *src, size_t dstsize);

void	execute_token(t_main *shell, t_token *token);
void	execv_cmd(t_token *token);
t_token	*get_prev_token(t_token *token);

void	free_tokens(t_token **token);
void	split_free(char **paths);
void	execute_pipe(t_main *shell, t_token *token, int *curr_pipe);

int		redirect_out(t_main *shell, t_token *token, int *new_output);

int		first_pipe(t_main *shell, t_token *token, int fd);
int		mid_pipe(t_main *shell, t_token *token, int fd);
int		last_pipe(t_main *shell, t_token *token, int fd);
int		the_only_pipe(t_main *shell, t_token *token, int fd);

void	struct_pid_clear(t_pid_t **head);
void	struct_pid_add(t_pid_t **head, t_pid_t *new);
t_pid_t	*struct_pid_new(pid_t value);
int		ctrl_d(t_main *shell, char *input);
void	close_fd_save(int fd);
void	handle_return_value(int *return_value);
void	set_io_first(t_main *shell, t_token *token, int fd);
void	set_io_last(t_main *shell, t_token *token, int fd);
int		pipes_count(t_main *shell);
int		token_has_redir_out(t_main *shell, t_token *token);
int		token_has_redir_in(t_main *shell, t_token *token);
void	execute_child_first(t_main *shell, t_token *token, int fd);
void	execute_child_right(t_main *shell, t_token *token, int fd);

//parser
char	*parser0(t_token **token, char *str);
char	*parser1(char *str, char **array, int token_ct);
int		parser2(char *str, int *sep_ct);
int		check_leading_pipe(char *str);
int		ft_isspace(int c);
int		parser_error(int type, char ch);
int		ft_issep(int c);
int		handle_sep(char *str, int i, int *sep_ct);
int		handle_pipe(char *str, int i, int *sep_ct);
int		handle_redirection(char *str, int i, int *sep_ct);
char	*handle_quotes(char *str, int *start);
char	*handle_double_quotes(char *str, int *start);
void	remove_quotes(char *str, int start, int end);
char	*handle_bucks(char *str, int *start);
char	*replace_bucks(char *str, int i, int *start, char *var_value);
char	*remove_invalid_var_name(char *str, char *var_name, int *start);
void	free_intermediate_strings(char *temp, char *part_1, char *part_2);
char	*handle_invalid_name(char *str, int *start);
void	add_to_array(char *str, char **array, t_parser *vars);

//tokens
void	create_tokens(t_token **token, char **array, int token_ct);
void	ft_add_token(t_token **lst, t_token *new);
t_token	*ft_new_token(void);
t_token	*ft_last_token(t_token *lst);
void	assign_type(t_token *token, char *str);
int		is_builtin(char *str);

//builtins
int		ft_echo(t_token *token);
int		ft_env(void);
int		ft_pwd(void);
int		ft_exit(t_token *token, t_main *shell);
int		ft_export(t_token *token);
int		ft_unset(t_token *token);
int		ft_cd(t_token *token);

//builtins_utils
int		is_arg_numeric(char *str);
void	insertion_sort(char **arr, int size);
void	print_sorted_env(void);
int		check_var_name(char *str);
int		print_export_or_unset_error(char *str, int type);
char	*get_var_name(char *str);
void	add_var(char *var_name, char *str);
int		is_name_valid(char *str);
int		ft_is_in_env(char *var_name);
int		print_cd_error(char *str, int type);
int		change_dir_to_home_or_oldpwd(char *var);
void	update_pwd(char *pwd);
void	update_oldpwd(char *oldpwd);

//environ
char	**m_environ(void);
//int		env_size(char **arr);
char	**r_environ(int diff, char *str);
void	handle_negative_diff(char **arr, char *str, int size);
void	free_env(void);
void	save_exit_child(void);

//utils
int		ft_strcmp(const char *s1, const char *s2);
void	free_on_exit(char **input);
char	*return_path(char **paths, char **ret_char);

#endif