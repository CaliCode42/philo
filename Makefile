NAME = philo

# Directories
SRC_DIR = src
DBG_DIR  = debug
LIBFT_DIR = libft
OBJ_DIR = obj
INCLUDE_DIR = includes

# Sources
SRC := \
	main.c \
	parse_args.c \
	create_philos.c \
	threads.c \

DBG := \
	debug.c \
#Path to sources
VPATH = $(SRC_DIR) $(DBG_DIR)

# Objects
OBJ_FILES := $(addprefix $(OBJ_DIR)/$(SRC_DIR)/, $(SRC:.c=.o)) \
	$(addprefix $(OBJ_DIR)/$(DBG_DIR)/, $(DBG:.c=.o))

# Compilation
CC := cc
CFLAGS := -Wall -Wextra -Werror -I$(INCLUDE_DIR) -I$(LIBFT_DIR)

#Libraries
LIBFT = $(LIBFT_DIR)/libft.a

#Objects directory
OBJDIRS := $(sort $(dir $(OBJ_FILES)))

# Rules
all: $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(NAME): $(OBJ_FILES) $(LIBFT)
	$(CC) $(OBJ_FILES) -o $(NAME) -L$(LIBFT_DIR) -lft

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

debug : CFLAGS += -g
debug : $(NAME)

.PHONY: all clean fclean re debug