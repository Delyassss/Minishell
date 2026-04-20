NAME    = minishell
CC      = cc
CFLAGS  = -Wall -Wextra -Werror -I$(HOME)/local/include
LDFLAGS = -L$(HOME)/local/lib -lreadline
SRCS    =	minishell.c parsing/list_utils1.c utils/utils2.c \
            parsing/parse_helper.c parsing/parse_tokens.c parsing/parser_helper2.c\
            parsing/token_quotes.c parsing/syntax_error.c parsing/token_helper.c \
            parsing/token_loop.c utils/utils1.c utils/util3.c parsing/expanding2.c \
			parsing/expanding.c parsing/free_functions.c parsing/init_all.c \
			utils/ft_strtrim.c utils/ft_split.c utils/utils5.c parsing/token_utils.c \
			utils/utils4.c parsing/parse_redirection.c parsing/handle_signals.c \
			parsing/exporting.c parsing/herdoc_expanding.c parsing/main_helper.c\
			execution/ft_strnstr_bonus.c execution/get_env_bonus.c execution/pipex_bonus.c \
			execution/append_access_bonus.c execution/utils1_bonus.c execution/maloc_fd_fail.c \
			execution/utils2_bonus.c execution/utils3_bonus.c execution/utils4_bonus.c \
			execution/get_next_line_utils_bonus.c \
			execution/create_env.c execution/built_in.c execution/ft_pwdecho.c \
			execution/env_helper.c execution/ft_export.c execution/ft_cd.c parsing/parse_redirection2.c\
			execution/env_helper2.c execution/ft_unset.c execution/beta_export.c \
			execution/ft_env_exit.c execution/is_directory.c execution/the_herdoc.c \
			utils/safe_malloc.c utils/exit_status.c utils/malloc_helper.c utils/env_malloc.c \
			execution/ft_cd_helper.c execution/when_to_dup.c parsing/spliting_in_export.c \
			execution/redirections.c parsing/split_tricks.c parsing/split_tricks2.c \


OBJS   = $(SRCS:.c=.o)

HEADER = minishell.h

all: $(NAME)

$(NAME): $(OBJS)
		@echo "\033[1;32m✅ Compiling complete source code into executable...\033[0m"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)
	@echo "\033[1;32m🎉 Build successful! You can now run ./minishell\033[0m"
	@echo "\033[1;31m"
	@echo "███╗   ███╗ ██╗███╗   ██╗ ██╗███████╗██╗  ██╗██████╗  ██╗ ██╗"
	@echo "████╗ ████║███║████╗  ██║███║██╔════╝██║  ██║╚════██╗███║███║"
	@echo "██╔████╔██║╚██║██╔██╗ ██║╚██║███████╗███████║ █████╔╝╚██║╚██║"
	@echo "██║╚██╔╝██║ ██║██║╚██╗██║ ██║╚════██║██╔══██║ ╚═══██╗ ██║ ██║"
	@echo "██║ ╚═╝ ██║ ██║██║ ╚████║ ██║███████║██║  ██║██████╔╝ ██║ ██║"
	@echo "╚═╝     ╚═╝ ╚═╝╚═╝  ╚═══╝ ╚═╝╚══════╝╚═╝  ╚═╝╚═════╝  ╚═╝ ╚═╝"
	@echo "\033[0m"

%.o: %.c $(HEADER)
	$(CC)  $(CFLAGS) -c $< -o $@
	@echo "\033[1;34m🔹 Compiling: $< -> $@\033[0m"

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
