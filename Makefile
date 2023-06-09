NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
RMFLAGS = -f

# file names
MANDA_FILES = philo_init \
			philo_main  \
			philo_utils \
			philo_do	\


# Directories
MANDA_DIR = .
OBJ_DIR = objects
INC_DIR = .
# Object files
MANDA_OBJ = $(addprefix $(OBJ_DIR)/$(MANDA_DIR)/, $(addsuffix .o, $(MANDA_FILES)))

# header files
MANDA_INC = $(INC_DIR)/philo.h


TARGET_OBJ = $(MANDA_OBJ)
TARGET_INC = $(MANDA_INC)
RM_OBJ = $(BONUS_OBJ)


.PHONY : all clean fclean re bonus

all :
	@make $(NAME)

$(NAME) : $(TARGET_OBJ) $(TARGET_INC)
	$(RM) $(RMFLAGS) $(RM_OBJ)
	$(CC) $(CFLAGS) $(TARGET_OBJ) -o $@

$(OBJ_DIR)/$(MANDA_DIR)/%.o : $(MANDA_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)/$(MANDA_DIR)
	$(CC) -c $(CFLAGS) $< -I$(INC_DIR) -o $@

clean :
	$(RM) $(RMFLAGS)r $(OBJ_DIR)

fclean : clean
	$(RM) $(RMFLAGS) $(NAME)

re :
	make fclean
	make all