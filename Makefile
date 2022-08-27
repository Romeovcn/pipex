SRCS_DIR = srcs

OBJS_DIR = objs

SRCSBONUS_DIR = srcs_bonus

SRCS	=	pipex.c

SRCS_BONUS =	checker_bonus.c \
				get_stack_bonus.c \
				check_error_bonus.c \
				utils_bonus.c \
				operations_stack_a_bonus.c \
				operations_stack_b_bonus.c \
				operations_reverse_bonus.c \

LIB = ./libft/libft.a

OBJS = ${patsubst %.c,${OBJS_DIR}/%.o,${SRCS}}

OBJS_BONUS = ${patsubst %.c,${OBJS_DIR}/%.o,${SRCS_BONUS}}

HEADERS = pipex.h

HEADERS_BONUS = pipex_bonus.h

NAME = pipex

NAME_BONUS = pipex_bonus

CC = gcc

CFLAGS =                      

# -- RULES -- #

${NAME}: ${OBJS_DIR} ${OBJS} ${HEADERS} ${LIB}
	@${CC} ${CFLAGS} ${OBJS} ${LIB} -o ${NAME}
	@echo "Pipex compiled !"
	@echo ----------------------------

all: ${NAME}

$(OBJS_DIR):
	@mkdir ${OBJS_DIR}

${LIB}:
	@make -sC ./libft

${OBJS_DIR}/%.o: ${SRCS_DIR}/%.c
	@${CC} ${CFLAGS} -I. -c $< -o $@

${OBJS_DIR}/%.o: ${SRCSBONUS_DIR}/%.c
	@${CC} ${CFLAGS} -I. -c $< -o $@

clean:
	@make clean -sC ./libft
	@rm -rf ${OBJS_DIR}

fclean: clean
	@make fclean -sC ./libft
	@rm -f ${NAME} ${NAME_BONUS}

re: fclean all

${NAME_BONUS}:  ${OBJS_DIR} ${OBJS_BONUS} ${HEADERS_BONUS} ${LIB}
	@${CC} ${CFLAGS} ${OBJS_BONUS} ${LIB} -o ${NAME_BONUS}
	@echo "Bonus compiled !"
	@echo ----------------------------

bonus: ${NAME_BONUS}

.PHONY:	all clean fclean re bonus