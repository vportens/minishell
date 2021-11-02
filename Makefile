NAME = minishell

NAME_B = minishell_bonus

MAC =

MAC_B =

LIBFT = libft

FLAGS 	= -Wall -Wextra

LIB =  -L/usr/include -lreadline

SRCS =  	main_test_2.c						\
			parsing/creat_fill_lst/get_cmd_line.c				\
			parsing/lst_fonction/cmdl_add_back.c				\
			parsing/parsing_utils.c				\
			parsing/free_utils.c				\
			parsing/creat_fill_lst/split_arg.c					\
			parsing/lst_fonction/init_token.c				\
			builtin.c							\
			parsing/expend_word/expend_word.c				\
			parsing/expend_word/devellope_limitor.c			\
			parsing/expend_word/word_will_single.c			\
			parsing/expend_word/word_will_double.c			\
			parsing/expend_word/word_will_unquote.c			\
			parsing/get_env.c					\
			parsing/expend_word/fake_env.c					\
			parsing/expend_word/word_unquote_inter.c		\
			parsing/creat_fill_lst/organise_arg.c				\
			parsing/lst_fonction/token_add_back.c			

SRCS_BONUS =


CC 		= gcc
OBJ 	= ${SRCS:.c=.o}
OBJS 	= *.o
OBJ_B = ${SRCS_BONUS:.c=.o}
OBJS_B = *.o

.c.o:
	${CC} ${FLAGS} -c $< -o ${<:.c=.o} -I include/.

all :
	@make -C $(LIBFT)
	@make $(NAME)

$(NAME)	: $(OBJ)
	$(CC) $(FLAGS) -I libft/includes/ -I include/. $(OBJ) libft/libft.a -o $(NAME) $(LIB)

$(NAME_B) : $(OBJ_B)
	$(CC) $(FLAGS) -I libft/includes/ -I include/. $(OBJ_B) libft/libft.a -o $(NAME_B)

clean :
		@make clean -C $(LIBFT)
		@rm -rf $(OBJ)
		@rm -rf $(OBJ_B)

fclean : clean
		@make fclean -C $(LIBFT)
		@rm -rf $(OBJS)
		@rm -rf $(OBJS_B)
		@rm -rf $(NAME)
		@rm -rf $(NAME_B)

relinux : fclean LINUX

re : fclean all



bonus :
		@make -C $(LIBFT)
		@make ${NAME_B}

rebonus : fclean bonus
