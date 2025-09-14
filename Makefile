ENVIRONMENT ?= prod

ifeq ($(ENVIRONMENT), prod)
	NAME := libarray.a
	CFLGS := -Wall -Wextra -Werror -O2 -MP -MMD
	BUILD := ./build/
else
	NAME := libarray-dev.a
	CFLGS := -Wall -Wextra -Werror -O0 -ggdb3 -MP -MMD
	BUILD := ./build-dev/
endif

SRCS := array.c
OBJS := $(SRCS:.c=.o)
OBJS := $(addprefix $(BUILD), $(OBJS))
DEPS := $(OBJS:.o=.d)

all: $(NAME)

$(NAME): $(OBJS)
	ar -rcs $@ $^

$(BUILD)%.o: %.c
	mkdir -p $(@D)
	$(CC) $(CFLGS) -c $< -o $@

-include $(DEPS)

clean:
	rm -rf $(BUILD)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
