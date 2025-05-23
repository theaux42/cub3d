LIBC_FILES = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
	ft_isascii.c ft_isdigit.c ft_isprint.c ft_memchr.c \
	ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_strchr.c \
	ft_strdup.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strncmp.c \
	ft_strnstr.c ft_strrchr.c ft_tolower.c ft_toupper.c ft_strncmp.c \
	ft_strncpy.c ft_strcmp.c ft_strcat.c ft_strncat.c

ADDITIONAL_FILES = ft_itoa.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c \
	ft_split.c ft_strjoin.c ft_strmapi.c ft_strtrim.c ft_substr.c ft_striteri.c \
	ft_isspace.c 

BONUS_FILES = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
	ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

PRINTF_FILES = ft_printf.c print_hexa.c print_nbr.c print_ptr.c \
	print_str.c print_utils.c
	
GNL_FILES = get_next_line.c get_next_line_utils.c \

OTHER_FILES = ft_addchar.c ft_freesplit.c ft_print_split.c ft_split_len.c \
	ft_mstrlcpy.c

MATHS_FILES = ft_pow.c ft_sqrt.c ft_factorial.c ft_fibonacci.c ft_is_prime.c ft_intlen.c \
	ft_atoll.c

STRINGS_FILES = ft_strcap.c ft_strlowcase.c ft_strupcase.c ft_strjoins.c \
	ft_strjoin_double.c ft_strcpy.c ft_edgecmp.c ft_isdigits_str.c \
	ft_isredir.c ft_safecmp.c ft_isemptystr.c

LIBC = $(addprefix basic/, $(LIBC_FILES))
ADDITIONAL = $(addprefix additional/, $(ADDITIONAL_FILES))
PRINTF = $(addprefix printf/, $(PRINTF_FILES))
BONUS = $(addprefix bonus/, $(BONUS_FILES))
GNL = $(addprefix gnl/, $(GNL_FILES))
OTHER = $(addprefix other/, $(OTHER_FILES))
MATHS = $(addprefix maths/, $(MATHS_FILES))
STRINGS = $(addprefix strings/, $(STRINGS_FILES))

SRCS = ${LIBC} ${ADDITIONAL} ${BONUS} ${PRINTF} ${GNL} ${OTHER} ${MATHS} ${STRINGS}

OBJS = ${SRCS:.c=.o}

LIB = libft.a

CC = cc

CFLAGS = -Wall -Werror -Wextra -I ./

TOTAL_FILES := $(words $(SRCS))
COMPILED_COUNT := 0

define progress_message
	$(eval COMPILED_COUNT=$(shell echo $$(($(COMPILED_COUNT)+1))))
	@printf "\033[K⚙️ Compiling %-30s [%0*d/%d]...\r" "$<" $(shell echo $${#TOTAL_FILES}) ${COMPILED_COUNT} ${TOTAL_FILES}
endef

.c.o:
	$(call progress_message)
	@${CC} ${CFLAGS} -c $< -o ${<:.c=.o}
	@printf "\033[K🚀 Compiled %-30s [%0*d/%d]\n" "$<" $(shell echo $${#TOTAL_FILES}) ${COMPILED_COUNT} ${TOTAL_FILES}

${LIB}:	${OBJS}
	@printf "\nCreating library...\r"
	@ar -rsc ${LIB} ${OBJS}
	@printf "\033[K✅ Libft created successfully!\n"

all: 	${LIB}

clean:
	@printf "Cleaning...\r"
	@rm -f ${OBJS}
	@printf "\033[K✅ Cleaned successfully!\n"

fclean:
	@printf "Full cleaning...\r"
	@rm -f ${LIB}
	@rm -f ${OBJS}
	@printf "\033[K✅ Libft fully cleaned successfully!\n"

re:	fclean all

.PHONY: all clean fclean re bonus