NAME = minishell

NAME_B = minishell_bonus

MAC =

MAC_B =

LIBFT = libft

FLAGS 	= -Wall -Wextra

LIB =  -L/usr/include -lreadline

SRCS =  	main.c											\
			parsing/ft_is_builtin.c							\
			parsing/creat_fill_lst/get_cmd_line.c			\
			parsing/lst_fonction/cmdl_add_back.c			\
			parsing/lst_fonction/len_cmd.c					\
			parsing/parsing_utils.c							\
			parsing/free_utils.c							\
			parsing/free_utils_2.c							\
			parsing/creat_fill_lst/split_arg.c				\
			parsing/lst_fonction/init_token.c				\
			parsing/expend_word/expend_word.c				\
			parsing/expend_word/expend_word_utils.c			\
			parsing/expend_word/expend_word_utils_two.c		\
			parsing/expend_word/devellope_limitor.c			\
			parsing/expend_word/word_will_single.c			\
			parsing/expend_word/word_will_double.c			\
			parsing/expend_word/word_will_unquote.c			\
			parsing/get_env.c								\
			parsing/expend_word/fake_env.c					\
			parsing/expend_word/word_unquote_inter.c		\
			parsing/creat_fill_lst/organise_arg.c			\
			parsing/lst_fonction/token_add_back.c			\
			built_in/ft_built_in_pwd.c						\
			built_in/ft_built_in_echo.c						\
			built_in/ft_built_in_env.c						\
			built_in/ft_delete_key.c						\
			built_in/ft_env_singletone.c					\
			built_in/ft_built_in.c							\
			built_in/ft_add_value.c							\
			built_in/ft_built_in_cd.c						\
			built_in/ft_push_front.c						\
			built_in/ft_built_in_export.c					\
			built_in/ft_gestion_error.c						\
			built_in/ft_init_env.c							\
			built_in/ft_free_env.c							\
			built_in/ft_get_value.c							\
			built_in/ft_built_in_unset.c					\
			exec/ft_exec.c									\
			exec/ft_exist.c									\
			exec/fill_fd.c									\
			exec/ft_lst_to_str.c

SRCS_BONUS =


CC 		= gcc
OBJ 	= ${SRCS:.c=.o}
OBJS 	= *.o
OBJ_B = ${SRCS_BONUS:.c=.o}
OBJS_B = *.o


all :
	@make -C $(LIBFT)
	@make $(NAME)

.c.o:
	${CC} ${FLAGS} -c $< -o ${<:.c=.o} -I include/

get_src:
	@find built_in -type f -name "*.c" | tr "\n" "|" | sed -r 's/["|"]+/\\ \n/g'

header:
	  @Headermaker built_in include/builtin.h -inc struct 
	  @Headermaker exec include/exec.h -inc struct 

$(NAME)	: $(OBJ)
	$(CC) $(FLAGS) -I libft/includes/ -I include/. $(OBJ) libft/libft.a -o $(NAME) $(LIB)

$(NAME_B) : $(OBJ_B)
	$(CC) $(FLAGS) -I libft/includes/ -I include/. $(OBJ_B) libft/libft.a -o $(NAME_B)

clean :
		@make clean -C $(LIBFT)
		@rm -rf $(OBJ)
		@rm -rf $(OBJ_B)

fclean : clean
		@rm -rf libft.a
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
