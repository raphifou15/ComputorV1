NAME = computor
NAME_BONUS = computorBonus
CC = gcc
FLAGS = -Wall -Wextra -Werror
RM = rm -rf
SRCS = computorV1.c
BONUS = computorV1.c bonus.c
OBJDIR = obj


OBJS = ${SRCS:.c=.o}
BONUS_OBJ = $(BONUS:%.c=$(OBJDIR)/%.o)

.c.o:
	${CC} ${FLAGS} -c $< -o ${<:.c=.o}

$(OBJDIR)/%.o: %.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -DBONUS -c $< -o $@

all: ${NAME}

${NAME}: ${OBJS}
	make -C math
	${CC}  -o ${NAME} ${OBJS} -L math -l:math.a

bonus: ${NAME_BONUS} 
	
${NAME_BONUS}:${BONUS_OBJ}
	make -C math
	${CC} -o ${NAME_BONUS} ${BONUS_OBJ} -L math -l:math.a

clean:
	make clean -C math
	${RM} *.o
	${RM} -R obj

fclean: clean
	make fclean -C math
	${RM} ${NAME}
	${RM} ${NAME_BONUS}
	
re: fclean all