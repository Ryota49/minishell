# ----------------------------------
# PROJECT NAME
# ----------------------------------
NAME = minishell
# ----------------------------------
# COMPILATION AND FLAGS
# ----------------------------------
CC     = cc
CCFLAGS= -Wall -Wextra -Werror -g -I ./

# ----------------------------------
# PATH
# ----------------------------------
PARS_DIR	= prepare_input
UTILS_DIR	= utils
EXEC_DIR	= exec
BUILTIN_DIR	= builtin
OBJ_DIR    = obj
EXEC_DIR = pipe_and_exec

# ----------------------------------
# COLORS
# ----------------------------------
RESET       = \033[0m
BLACK       = \033[0;30m
RED         = \033[0;31m
GREEN       = \033[0;32m
YELLOW      = \033[0;33m
BLUE        = \033[0;34m
MAGENTA     = \033[0;35m
CYAN        = \033[0;36m
WHITE       = \033[0;37m

# ----------------------------------
# SOURCES
# ----------------------------------
SRCS    = minishell.c \
		exit_def.c \
		$(PARS_DIR)/read_input.c \
		$(PARS_DIR)/signals.c \
		$(PARS_DIR)/tokenize.c \
		$(PARS_DIR)/free.c \
		$(PARS_DIR)/parser.c \
		$(PARS_DIR)/expansion.c \
		$(BUILTIN_DIR)/cd.c \
		$(BUILTIN_DIR)/echo.c \
		$(BUILTIN_DIR)/env.c \
		$(BUILTIN_DIR)/exit.c \
		$(BUILTIN_DIR)/export.c \
		$(BUILTIN_DIR)/pwd.c \
		$(BUILTIN_DIR)/unset.c \
		$(UTILS_DIR)/utils_libft1.c \
		$(UTILS_DIR)/utils_libft2.c \
		$(UTILS_DIR)/utils_tab.c \
		$(UTILS_DIR)/ft_split.c \
		$(UTILS_DIR)/ft_strjoin.c \
		$(UTILS_DIR)/ft_itoa.c \
		$(UTILS_DIR)/ft_atol.c \
		$(UTILS_DIR)/utils_token.c \
		$(UTILS_DIR)/utils_cmd.c \
		$(UTILS_DIR)/utils_expansion.c \
		$(UTILS_DIR)/utils_exec.c \
		$(UTILS_DIR)/utils_builtin.c \
		$(EXEC_DIR)/check_builtins.c \
		$(EXEC_DIR)/execution.c \
		$(EXEC_DIR)/execution_utils.c \
		$(EXEC_DIR)/count_cmds_and_pipes.c \
		$(EXEC_DIR)/access_and_path.c \
		$(EXEC_DIR)/dup_and_redir.c \
		$(EXEC_DIR)/child_process.c \
		$(EXEC_DIR)/heredoc.c 

OBJS    = $(SRCS:.c=.o)

# ----------------------------------
# RULES
# ----------------------------------

all: $(NAME)

# Final link
$(NAME): $(OBJS)
	@echo "\033[1;34m[LINK] -> Creating $(NAME)...\033[0m"
	@$(CC) $(CCFLAGS) $(OBJS) -o $(NAME) -lreadline
	@echo "\033[1;32m[OK] -> $(NAME) ready!\033[0m"

# Compilation of .c in .o
%.o: %.c
	@echo "$(CYAN)[COMPILING]$(RESET) $<"
# 	@sleep 0.02
	@$(CC) $(CCFLAGS) -c $< -o $@

# Clean
clean:
	@echo "$(RED)[CLEAN]$(RESET) Removing object files..."
	@for file in $(OBJS); do \
		if [ -f $$file ]; then \
			echo "  $(YELLOW)→ removing$(RESET) $$file"; \
			rm -f $$file; \
			sleep 0.02; \
		fi \
	done

# Full Clean
fclean: clean
	@echo "$(RED)[FCLEAN]$(RESET) Removing executable..."
	@echo "  $(YELLOW)→ removing$(RESET) $(NAME)";
	@sleep 0.03
	@rm -f $(NAME)

# Rebuild
re: fclean all

# ----------------------------------
# PHONY
# ----------------------------------
.PHONY: all clean fclean re