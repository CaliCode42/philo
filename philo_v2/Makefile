NAME = philo

# Directories
SRC_DIR = src
DBG_DIR  = debug
OBJ_DIR = obj
INCLUDE_DIR = includes

# Sources
SRC := \
	getters_setters.c \
	init.c \
	main.c \
	monitor_routine.c \
	parse.c \
	routine.c \
	safe.c \
	sync_utils.c \
	utils.c \
	write.c \

#Path to sources
VPATH = $(SRC_DIR)

# Objects
OBJ_FILES := $(addprefix $(OBJ_DIR)/$(SRC_DIR)/, $(SRC:.c=.o)) \

# Compilation
CC := cc
CFLAGS := -Wall -Wextra -Werror -I$(INCLUDE_DIR)

#Objects directory
OBJDIRS := $(sort $(dir $(OBJ_FILES)))

# Rules
all: $(NAME)

$(NAME): $(OBJ_FILES)
	$(CC) $(OBJ_FILES) -o $(NAME)

$(OBJ_DIR)/%.o: %.c | $(OBJDIRS)
	$(CC) $(CFLAGS) -c $< -o $@

#Create object directory if doesn't exist
$(OBJDIRS):
	@mkdir -p $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

debug : CFLAGS += -g -DDEBUG_MODE=1
debug : re

.PHONY: all clean fclean re debug