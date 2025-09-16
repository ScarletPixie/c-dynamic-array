NAME := test_array
CFLGS := -Wall -Wextra -Werror -Wno-unused-function -ggdb3 -MP -MMD
BUILD := ./build/

SRCS := main.c tests.c
OBJS := $(SRCS:.c=.o)
OBJS := $(addprefix $(BUILD), $(OBJS))
DEPS := $(OBJS:.o=.d)

all: $(NAME)

test: all
	./$(NAME)

$(NAME): $(OBJS) $(TEST_SUBJ)
	$(CC) $(CFLGS) $(TEST_SUBJ) $^ -o $@

$(BUILD)%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLGS) -c $< -o $@

-include $(DEPS)

clean:
	rm -rf $(BUILD)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
