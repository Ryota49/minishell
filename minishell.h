/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfouger <anfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 13:35:28 by anfouger          #+#    #+#             */
/*   Updated: 2026/04/29 10:02:08 by anfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_HEREDOC,
	TOKEN_APPEND
}	t_token_type;

typedef struct s_env
{
	char	**envp;
	int		*has_value;
	int		*exported;
}	t_env;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_redir
{
	int				type;
	char			*filename;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**argv;
	t_redir			*redirs;
	int				has_pipe;
	int				type;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_minish
{
	int		exit_status;
	char	*input;
	t_env	*env;
	t_token	*tokens;
	t_cmd	*cmds;
}	t_minish;

typedef struct s_exec
{
	int		nb_cmds;
	int		**pipes;
}	t_exec;

// --- Utils envp --- //
t_env	*init_envp(char **tab);
int		is_value_empty(char *str);
t_env	sort_env(t_env old_env);

// --- Utils Libft --- //
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);
char	*ft_strndup(const char *s, int start, int end);
char	*add_char(char *str, char c);
int		ft_isspace(const char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_itoa(int n);
int		tab_str_len(char **tab);
long	ft_atol(char *str);
int		verif_long(char *s);
int		ft_isalnum(int x);
int		ft_isalpha(int x);
int		ft_isdigit(int x);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
int		is_used(int *used, int x, int len);

// --- Utils Tab --- //
void	free_str_tab(char **s);
char	**dup_str_tab(char **tab);
void	clean_str_tab(char **tab, int i);
int		*add_value_tab_int(int *tab, int value, int len_tab);
int		*dup_tab_int_less_i(int *tab, int index, int length);

// --- Utils Token --- //
void	add_token(t_token **lst, t_token *new);
t_token	*new_token(t_token_type type, char *value, int is_strndup);

// --- Utils Cmd --- //
t_cmd	*new_cmd(void);
void	add_cmd(t_cmd **lst, t_cmd *new);
void	add_arg(t_cmd *cmd, char *value);
void	add_redir(t_cmd *cmd, t_token_type type, char *filename);

// --- Utils Expansion --- //
int		is_expandable(char c);
int		is_char_var(char c);
char	*get_var(char **envp, char *str, int *i);
char	*remove_quotes(char *str);

// --- Utils Exec --- //
int		is_slash_in(char *str);
int		is_builtin(char *cmd);
void	end_of_exec_single(t_minish *minish, int status);

// --- Utils Builtin --- //
char	*get_env_value(char **envp, char *str);
char	**add_var(t_env *env, char **tab, char *str);
int		change_value(t_env *env, char *key, char *str);
char	*get_key(char *str);
void	print_export(char *str);
int		export_no_args(t_minish *minish);

// --- Signals --- //
void	handle_sigint(int sig);
void	setup_signals(void);

// --- Prepare Input --- //
char	*read_input(void);
t_token	*tokenize(const char *input);
t_cmd	*parser(t_minish *minish, t_token *tokens);
t_cmd	*expansion(t_minish minish, t_cmd *cmds);

// // --- Exec --- // //

// --- Builtin --- //
int		builtin_cd(char **argv, t_env *env);
int		builtin_echo(char **argv);
int		builtin_env(t_env *env, char **argv);
int		builtin_pwd(void);
int		builtin_export(t_minish *minish, char **argv);
int		builtin_unset(t_minish *minish, char **argv);
int		builtin_exit(t_minish *minish, char **argv, int is_child);

/* execve function */
void	execute(t_minish *minish);

/* execution utils */
void	ft_putstr_fd(char *s, int fd);
char	*ft_strjoin_three(char *s1, char *s2, char *s3);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

/* check builtins */
void	exec_single_builtin(t_minish *minish);
int		exec_builtin(t_cmd *cmd, t_minish *minish, int is_child);
int		is_builtin(char *cmd);

/* count_cmds_and_pipes functions */
int		count_cmds(t_cmd *cmds);
int		**create_pipes(int nb_pipes);
void	close_all_pipes(int **pipes, int nb_pipes);
void	free_pipes(int **pipes, int nb_pipes);

/* access_and_path functions */
char	*resolve_cmd(char *cmd, char **envp);
int		access_path(char *cmd);
char	*find_path(char **envp);

/* dup_and_redir functions */
int		apply_redirs(t_redir *redirs);
int		apply_redir_out(t_redir *redir);
int		apply_redir_in(t_redir *redir);

/* child process functions */
void	child_process(t_minish *minish, t_cmd *cmd, int i, t_exec *exec);
void	exec_external(t_minish *minish, t_cmd *cmd, t_exec *exec);
void	setup_pipes_child(int i, int nb_cmds, int **pipes);

// --- Free --- //
void	free_all(t_minish *minish, int end);
void	free_cmds(t_cmd *cmds);
void	ft_free_split(char **split);

// --- Heredoc --- //
void	prepare_heredoc(t_minish *minish, t_cmd *cmds);

/* remove empty argv */

void	remove_empty_argv(t_cmd *cmd);
int		count_non_empty(char **argv);

/* signal for single pid (exec single) */
void	prepare_single_pid(t_minish *minish, t_exec *exec);

/* call free function for pid process */
void	call_free_all(char *path, t_minish *minish, t_exec *exec);
void	free_minish_exit_zero(t_minish *minish, t_exec *exec);
void	free_minish_exit_one(t_minish *minish, t_exec *exec);
void	free_child_pipes(t_exec *exec);

/* error command not found exec external */
void	command_not_found_exit(t_minish *minish, t_exec *exec);

void	exit_minish(void);

/* global variable for SIGNAL */

extern int	g_signal;

#endif