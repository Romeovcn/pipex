SRCS_DIR = srcs

OBJS_DIR = objs

OBJSBONUS_DIR = objs_bonus

SRCSBONUS_DIR = srcs_bonus

SRCS	=	pipex.c \
			get_path.c \
			free_and_exit.c \
			error.c

SRCS_BONUS =	pipex_bonus.c \
				get_path_bonus.c \
				free_and_exit_bonus.c \
				error_bonus.c \
				utils_bonus.c

LIB = ./libft/libft.a

OBJS = ${patsubst %.c,${OBJS_DIR}/%.o,${SRCS}}

OBJS_BONUS = ${patsubst %.c,${OBJSBONUS_DIR}/%.o,${SRCS_BONUS}}

HEADERS = pipex.h

HEADERS_BONUS = pipex_bonus.h

NAME = pipex

NAME_BONUS = pipex

CC = gcc

CFLAGS = 

# -- RULES -- #

${NAME}: ${OBJS_DIR} ${OBJS} ${HEADERS} ${LIB}
	@${CC} ${CFLAGS} ${OBJS} ${LIB} -o ${NAME}
	@echo "\033[32mPipex compiled !"
	@echo "----------------------------\033[0m"

all: ${NAME}

${OBJS_DIR}:
	@mkdir -p ${OBJS_DIR}
	@echo "\033[33mCompiling Pipex..."

${OBJSBONUS_DIR}:
	@mkdir -p ${OBJSBONUS_DIR}
	@echo "\033[33mCompiling Pipex..."

${LIB}:
	@make -sC ./libft

${OBJS_DIR}/%.o: ${SRCS_DIR}/%.c
	@${CC} ${CFLAGS} -I. -c $< -o $@

${OBJSBONUS_DIR}/%.o: ${SRCSBONUS_DIR}/%.c
	@${CC} ${CFLAGS} -I. -c $< -o $@

clean:
	@make clean -sC ./libft
	@rm -rf ${OBJSBONUS_DIR}
	@rm -rf ${OBJS_DIR}

fclean: clean
	@make fclean -sC ./libft
	@rm -f ${NAME} ${NAME_BONUS}

re: fclean all

bonus: ${OBJSBONUS_DIR} ${OBJS_BONUS} ${HEADERS_BONUS} ${LIB}
	@rm -rf ${OBJS_DIR}
	@${CC} ${CFLAGS} ${OBJS_BONUS} ${LIB} -o ${NAME_BONUS}
	@echo "\033[32mBonus compiled !"
	@echo "----------------------------\033[0m"

.PHONY:	all clean fclean re bonus