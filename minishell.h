/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ildaboun <ildaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:20:33 by ildaboun          #+#    #+#             */
/*   Updated: 2025/07/15 22:17:09 by ildaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef MAX_FD
#  define MAX_FD 10240
# endif

# ifndef MAX_PROCESS
#  define MAX_PROCESS 10240
# endif

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/stat.h>
# include <termios.h>

/* ************************************************************************** */
/*                                  GC Types                                  */
/* ************************************************************************** */

typedef struct s_gc_node
{
	void				*ptr;
	struct s_gc_node	*next;
}	t_gc_node;

typedef struct s_gc_double
{
	void				**d_ptr;
	struct s_gc_double	*next;
}	t_gc_double;

typedef struct s_garbage
{
	t_gc_node			*head;
	t_gc_double			*d_head;
}	t_garbage;

/* ************************************************************************** */
/*                                Token Types                                 */
/* ************************************************************************** */

typedef enum e_token_type
{
	TOKEN_STRING,
	TOKEN_OPTION,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_REDIR_HEREDOC,
	TOKEN_HEREDOC_DELIMITER,
	TOKEN_OUTFILE,
	TOKEN_INFILE,
	TOKEN_ENV_VAR,
	TOKEN_ALREADY_EXPANDED
}	t_token_type;

typedef struct s_token
{
	char				*value;
	t_token_type		type;
	bool				need_expans;
	bool				expanded;
	bool				was_quoted;
	bool				deli_quoted;
	bool				dont_split_quoted;
	struct s_token		*next;
}	t_token;

typedef struct s_env
{
	char				*key;
	char				*value;
	int					exported;
	struct s_env		*next;
}	t_env;

typedef struct s_free_env
{
	void				*ptr;
	struct s_free_env	*next;
}	t_free_env;

typedef struct s_d_free_env
{
	void				**d_ptr;
	struct s_d_free_env	*next;
}	t_d_free_env;

typedef struct s_env_gc
{
	t_free_env			*head;
	t_d_free_env		*d_head;
}	t_env_gc;

/* ************************************************************************** */
/*                               Command Struct                               */
/* ************************************************************************** */

typedef struct s_command
{
	char				*cmd;
	char				**args;
	char				*infile;
	char				*outfile;
	int					append;
	char				*heredoc;
	bool				herdoc_live;
	char				**quote_split;
	char				**heredocers;
	int					nbr_heroc;
	bool				is_herdoc_quoted;
	bool				should_we_expand_herdoc;
	int					*herdoc_fd;
	char				**env_args;
	bool				there_is_outfile;
	bool				there_is_infile;
	bool				there_is_heredoc;
	bool				quoted_delim;
	t_token_type		stdin_type;
	bool				dont_split_cmd;
	bool				i_removed_quotes;
	bool				export_append_case;
	struct s_command	*next;
}	t_command;

/* ************************************************************************** */
/*                                Parser Struct                               */
/* ************************************************************************** */

typedef struct s_parser
{
	t_token				*token_head;
	t_garbage			*gc;
	t_env_gc			*env_gc;
	t_command			*command;
	int					j;
	char				*input;
	int					start;
	bool				needs_expansion;
	bool				in_single_quote;
	bool				in_double_quote;
	int					quoted;
	int					k;
	int					g;
	int					last_cmd;
	int					stdin_backup;
	int					stdout_backup;
	int					max_fd;
	char				**heredocers;
	int					*fds;
	int					c_fd;
	t_env				*env;
	char				**my_strenv;
	bool				belong_to_export;
	bool				dollar_before;
	bool				itoa_done;
	bool				in_quotes;
	bool				empty_after_expand;
	bool				no_buffer_needed;
	bool				dont_expand_delimiter;
	char				**split_later;
	int					track_split;
	bool				in_expand;
	bool				delimiter;
	bool				dollar;
	bool				herdoc_loop;
	bool				dont_split;
	bool				cmd_export;
	bool				quotes;
	bool				closed_quotes;
	bool				redir_out;
	bool				redir_in;
	int					save_k;
	int					track_ambiguous;
	char				**buffers;
	int					index;
	pid_t				shell_pgid;
	bool				stop_heredoc;
	int					save_j;
	char				*buffer;
	int					save_h;
	int					save_i;
	int					i_doc;
	int					i_env;
	bool				gc_already_allocated;
	struct termios		term;
}	t_parser;

/* ************************************************************************** */
/*                              Execution Struct                              */
/* ************************************************************************** */

typedef struct s_info
{
	int					cmd_nbr;
	int					argcc;
	int					pipe_nbr;
	int					outfile;
	char				**envpp;
	int					psplit;
	int					csplit;
	int					infile;
	int					lst_argm;
	int					a;
	bool				outfile_already_open;
	bool				infile_already_open;
	bool				open_outfile;
	bool				over_large_nbr;
	bool				in_no_export;
	int					nbr_heroc;
	bool				dont_open_herdoc;
	pid_t				proc;
	pid_t				*process;
	int					track_process;
	t_parser			*parser;
	t_env				*envp;
	int					dup;
}	t_info;

/* ************************************************************************** */
/*                            Function Prototypes                             */
/* ************************************************************************** */
/* ************************************************************************** */
/*                                PARSING                                     */
/* ************************************************************************** */
void		clear_fd(void);
t_command	*init_command(t_garbage *gc);
void		ft_lstadd_back(t_token **lst, t_token *new);
t_token		*ft_lstnew(void *value, t_token_type type, t_parser *parser);
int			ft_isspace(char c);
int			ft_isalnum(int c);
void		add_token(char *value, t_token_type type, t_parser *parser);
void		ft_putstr_fd(char *s, int fd);
char		*ft_substr(char const *s, int start, int len, t_garbage *gc);
void		handle_quoted_string(int *i, const char *input,
				char *buffer, t_parser *parser);
void		handle_word(int *i, char *input, t_parser *parser);
void		tokenizer_loop(char *input, t_parser *parser);
int			check_syntax_errors(t_token *tokens);
char		*ft_strdup(const char *s1, t_garbage *gc);
void		handle_input_redirection(t_command *cmd, t_token *tokens,
				t_parser *parser);
void		handle_output_redirection(t_command *cmd, t_token *tokens,
				t_parser *parser);
t_command	*parse_tokens(t_token *tokens, t_parser *parser);
t_token		*ft_lstlast(t_token *lst);
void		ft_putchar_fd(char c, int fd);
int			ft_strlen(const char *s);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*get_name_in_envp(char **my_envp, char *var, t_garbage *gc);
char		**my_envp(char **envp, t_garbage *gc);
char		*get_the_expanded_value(char *value, char **envp,
				t_parser *parser);
char		*ft_itoa(int n, t_garbage *gc);
char		**ft_split(const char *s, char *c, t_garbage *gc);
char		*ft_strtrim(const char *s1, const char *set, t_garbage *gc);
void		*ft_memcpy(void *dst, const void *src, size_t n);
char		*ft_strjoin(const char *s1, const char *s2, t_garbage *gc);
int			malloc_fail(char *src);
void		char_vs_char(char a, char b);
char		*ft_strchr(const char *str, int c);
char		*ft_strcat(char *dest, const char *src);
char		*ft_strncpy(char *dest, const char *src, int n);
char		*ft_strncat(char *dest, const char *src, int n);
void		add_arg(t_command *cmd, t_token *start, t_parser *parser);
void		handle_redirection(int *i, char *input, t_parser *parser);
void		setup_signals(void);
void		free_command(t_command *cmd);
void		handle_heredocs(t_token *tokens, t_parser *parser,
				t_command *cmd);
int			malloc_double_fail(char **src);
void		help_cmd(t_parser *parser, t_token *start, t_command *cmd);
int			var_expanding(int *i, const char *input,
				char *buffer, t_parser *parser);
void		fill_word_buffer(int *k, char *str, int *j, t_parser *parser);
char		*herdoc_expansion(char *str, t_parser *parser);
int			exit_code(int set, int value);
void		*ft_memset(void *b, int c, size_t len);
void		end_of_while(t_parser *parser);
void		in_syntax(t_parser *parser, char *input);
void		init_part_one(t_parser *parser, int *a);
t_parser	*init_parser(char **env);
int			redir_helper(int *i, char *input, t_parser *parser);
int			redir_helper_two(int *i, char *input, t_parser *parser);
void		string_by_string(t_parser *parser, char *args);
int			syntax_error(int set, int value);
char		*insert_char_edges(char c, const char *str, t_parser *parser);
int			starts_and_ends_with(char c, char *str);
void		after_split_helper(t_parser *parser, char **res, char **split);
void		fill_quote_split(t_parser *parser, t_command *cmd,
				char *split_equal, int *track);
void		print_ambiguous(t_parser *parser);
void		herdoc_sigint_handler(int sig);
int			the_doc_helper(t_info *info, t_command *cmd, int *i);
int			ft_is_az(int c);
void		append_value(t_env **env, t_info *info, char *arg);
/* ************************************************************************** */
/*                                EXECUTION                                   */
/* ************************************************************************** */

void		full_heredocers(t_info *info, int a);
void		middle_cleanup(t_info *info, int a, int **fd);
void		close_heredocers_fd(t_info *info, int a);
char		*jointree(const char *s1, const char *s2,
				const char *s3, t_garbage *gc);
void		valid_ident(char **args, t_command *cmd);
int			parser_open_file(char *file_name, int file_flag,
				t_parser *parser);
void		pipex_b(t_info *info, t_env **env);
char		**get_env(char **env, char *cmd, t_info *info);
char		*append_access(t_info *info, char *cmd, bool flag);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
int			open_file(char *file_name, int file_flag, t_info *info);
void		mid_command(int **fd, t_info *info, int a, t_env *env);
void		last_command(int **fd, t_info *info, int a, t_env *env);
size_t		ft_strlenn(const char *s);
void		fork_error(pid_t i, t_info *info, int **fd);
void		the_doc_thing(t_info *info, t_command *cmd);
void		create_process(int **fd, int a, t_info *info, t_env *env);
void		handle_dup(void);
void		set_info(t_info *info, t_command *cmd);
void		set_info2(t_info *info);
int			**allocate_fd(t_garbage *gc, int rows);
void		pipe_free(t_info *info, int **fd);
void		pipe_failed(t_info *info);
void		create_pipes(int a, int **fd, t_info *info);
void		forking(t_info *info, t_env *env, int **fd);
void		malloc_fd_fail(t_parser *parser);
void		env_fail(t_info *info, int **fd);
void		set_all(t_info *info);
void		when_to_dup(int **fd, t_info *info, int a, char *flag);
void		wait_for_children(t_info *info);
int			arr_len(char **arr);
char		*ft_strjointree(const char *s1, const char *s2,
				const char *s3, t_env_gc *gc);
char		*ft_strcpy(char *dest, const char *src);
t_env		*ft_env(char **env, t_parser *parser);
char		**string_env(t_env *env, t_env_gc *gc);
int			is_built_in(char *cmd, t_command *commands);
int			must_run_in_parent(char *cmd, int pipenbr);
void		add_or_update_env(t_info *info, t_env **env, char *arg);
void		update_env(t_env **env, t_info *info, char *key, char *new_value);
char		*get_value_from_env(t_env *env, char *key);
void		clean_fd(int max_fd, t_parser *parser);
int			ft_cd(t_info *info, t_env *env);
int			ft_echo(t_command *cmd);
int			ft_pwd(void);
t_env		*check_if_exist(t_env *env, char *key);
t_env		*create_env_node(char *key, char *value, t_info *info);
void		print_env(t_env *env);
int			unset_valid_ident(char *str);
void		remove_from_env(t_info *info, t_env **env, char *arg);
int			ft_unset(t_info *info, t_env **env);
int			ft_atoi(const char *str, t_info *info);
int			builtin_env(t_env *env, t_info *info);
int			ft_exit(t_info *info);
void		builtin_exec(t_info *info, t_env **env);
int			ft_export(t_info *info, t_env **env);
void		add_to_env(t_env **env, char *key, t_info *info);
void		check_cmd(char *path);
void		no_export(t_info *info, t_env **env, int i);
int			beta_ident(char *args);
void		run_no_export(t_info *info, t_env **env);
void		advanced_p_error(char *cmd);
int			ft_alpha(int c);

/* ************************************************************************** */
/*                            GC / MEMORY / SIGNALS                           */
/* ************************************************************************** */

void		gc_free_all(t_garbage *gc);
void		**d_gc_malloc(t_garbage *gc, size_t size);
void		*gc_malloc(t_garbage *gc, size_t size);
t_garbage	*gc_init(void);
int			is_d_ptr_tracked(t_garbage *gc, void **d_ptr);
int			is_already_tracked(t_garbage *gc, void *ptr);
t_env_gc	*env_gc_init(void);
void		*env_malloc(t_env_gc *gc, size_t size);
void		**denv_malloc(t_env_gc *gc, size_t size);
void		env_free_all(t_env_gc *gc);
void		env_free_d(t_env_gc *gc);
char		*env_strdup(const char *s1, t_env_gc *gc);
int			env_dtracked(t_env_gc *gc, void **d_ptr);
int			env_ptracked(t_env_gc *gc, void *ptr);
int			reset(int set, int value);
t_info		*init_info(t_parser *parser);
void		execution(t_info *info, t_parser *parser);
char		*ft_strchr_set(const char *s, const char *set);
char		*remove_last_slash(char *old_pwd, t_parser *parser);
int			if_chdir_fail(char **path, char *old_pwd, t_info *info);
char		*cd_edge_case(char *path, t_garbage *gc);
void		p_error(char *str);
char		**goofy(char **array, char *new_elem,
				t_parser *parser, t_command *cmd);
void		for_export(t_parser *parser, t_command *command);
void		for_outfile(t_info *info, char *flag, int **fd, int a);
void		for_infile(t_info *info, int **fd, int a);
void		should_we_split(t_parser *parser,
				t_command *cmd, char *new_elem);
void		kill_all_children(t_info *info);
char		*remove_edge_chars(char c, char *str, t_parser *parser);
void		restore_std_fds(t_parser *parser);
void		splitted(t_command *cmd, t_parser *parser);
void		signals_in_process(void);
void		sig_herdoc(void);
void		f_error(pid_t i, t_info *info, int *fd);
void		update_envvv(t_info *info, t_env *env);
void		end_of_project(t_parser *parser);

#endif
