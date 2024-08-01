
OBJDIR = obj/
SRCDIR = src/
HELPERDIR = helper_functions/
DEBUGDIR = debug_functions/
ENV_DIR = environment/
BUILTINS_DIR = builtins/
EXECUTOR_DIR = executor/
LEXER_DIR = lexer/
PARSER_DIR = parser/
EXPANDER_DIR = expander/
WILDCARD_DIR = wildcard/

COLOUR_GREEN=\033[0;32m
COLOUR_END=\033[0m

SRC = $(addprefix $(SRCDIR), main.c \
	cleaner.c \
	signals.c)
HELPERSRC = $(addprefix $(SRCDIR), $(addprefix $(HELPERDIR), \
	general_helpers.c \
	parser_helper_functions.c \
	set_error_and_message.c \
	strpart_helpers.c))
DEBUGSRC = $(addprefix $(SRCDIR), $(addprefix $(DEBUGDIR), \
	debug_functions.c \
	print_cmd_lst.c))
ENV_SRC = $(addprefix $(SRCDIR), $(addprefix $(ENV_DIR), \
	env_create_and_change.c \
	env_delete_and_free.c \
	env_get.c \
	init_environment.c \
	shlvl.c))
BUILTINS_SRC = $(addprefix $(SRCDIR), $(addprefix $(BUILTINS_DIR), \
	b_cd.c \
	b_export.c \
	builtins_others.c \
	builtins_utils.c))
EXECUTOR_SRC = $(addprefix $(SRCDIR), $(addprefix $(EXECUTOR_DIR), \
	command_execute.c \
	command_prepare.c \
	executor_main.c \
	executor_utils.c \
	heredoc.c \
	input_output.c))
LEXER_SRC = $(addprefix $(SRCDIR), $(addprefix $(LEXER_DIR), \
	lexer_main.c \
	try_word_parsing.c \
	try_tokens.c \
	env_expansion_tools.c \
	normal_lex_strparts_build.c \
	str_part_joining.c \
	str_part_joining_helpers.c \
	lex_lst_std_functions.c \
	lexer_helper_functions.c \
	lexer_helper_functions_2.c))
EXPANDER_SRC = $(addprefix $(SRCDIR), $(addprefix $(EXPANDER_DIR), \
	expander.c \
	expand_home.c \
	eetl.c \
	eetl_build_first_lex.c \
	eetl_build_first_lex_p2.c \
	eetl_create_cutoff_new_env.c \
	eetl_tools1.c \
	eetl_tools2.c \
	expander_helper_functions.c \
	expander_helper_functions2.c \
	build_tools.c \
	build_env_expansion.c \
	build_env_expansion_p2.c))
PARSER_SRC = $(addprefix $(SRCDIR), $(addprefix $(PARSER_DIR), \
	parser.c \
	parser_parenthesis_logic.c \
	parser_parenthesis_logic_p2.c \
	parser_helpers.c \
	parser_helpers2.c))
WILDCARD_SRC = $(addprefix $(SRCDIR), $(addprefix $(WILDCARD_DIR), \
	wildcard.c \
	read_directory.c \
	scan_and_store_matching.c \
	scan_helpers.c \
	wildcard_cleaner.c \
	wildcard_helpers.c \
	sorting_list.c \
	determine_pattern.c \
	determine_pattern_build.c))

OBJ = $(addprefix $(OBJDIR), $(notdir $(SRC:.c=.o)))
HELPEROBJ = $(addprefix $(OBJDIR), $(notdir $(HELPERSRC:.c=.o)))
DEBUGOBJ = $(addprefix $(OBJDIR), $(notdir $(DEBUGSRC:.c=.o)))
ENV_OBJ = $(addprefix $(OBJDIR), $(notdir $(ENV_SRC:.c=.o)))
BUILTINS_OBJ = $(addprefix $(OBJDIR), $(notdir $(BUILTINS_SRC:.c=.o)))
EXECUTOR_OBJ = $(addprefix $(OBJDIR), $(notdir $(EXECUTOR_SRC:.c=.o)))
LEXER_OBJ = $(addprefix $(OBJDIR), $(notdir $(LEXER_SRC:.c=.o)))
EXPANDER_OBJ = $(addprefix $(OBJDIR), $(notdir $(EXPANDER_SRC:.c=.o)))
PARSER_OBJ = $(addprefix $(OBJDIR), $(notdir $(PARSER_SRC:.c=.o)))
WILDCARD_OBJ = $(addprefix $(OBJDIR), $(notdir $(WILDCARD_SRC:.c=.o)))

NAME = minishell

# INCLUDES = -I./src/lexer/lexer.h
LINKING = #-fsanitize=address

FLAGS = -g $(LINKING) \
	-Wall -Werror -Wextra

all: $(OBJDIR) $(NAME)

LIBFTLIB = Libft/
LIBFTA = $(LIBFTLIB)libft.a

$(OBJDIR):
	@if test -d $(OBJDIR); then echo $(OBJDIR) exists; \
		else mkdir $(OBJDIR); \
		fi

$(NAME): $(OBJ) $(HELPEROBJ) $(DEBUGOBJ) $(ENV_OBJ) $(BUILTINS_OBJ) $(EXECUTOR_OBJ) $(LEXER_OBJ) $(EXPANDER_OBJ) $(PARSER_OBJ) $(WILDCARD_OBJ)
	make -C $(LIBFTLIB)
	cc $(OBJ) $(HELPEROBJ) $(DEBUGOBJ) $(ENV_OBJ) $(BUILTINS_OBJ) $(EXECUTOR_OBJ) $(LEXER_OBJ) $(EXPANDER_OBJ) $(PARSER_OBJ) $(WILDCARD_OBJ)\
		$(LIBFTA) -lreadline $(FLAGS) -o $(NAME)

$(OBJ): $(OBJDIR)%.o: $(SRCDIR)%.c
		cc $(FLAGS) -c  $(INCLUDES) $< -o $@
$(HELPEROBJ): $(OBJDIR)%.o: $(SRCDIR)$(HELPERDIR)%.c
		cc $(FLAGS) -c  $(INCLUDES) $< -o $@
$(DEBUGOBJ): $(OBJDIR)%.o: $(SRCDIR)$(DEBUGDIR)%.c
		cc $(FLAGS) -c  $(INCLUDES) $< -o $@
$(ENV_OBJ): $(OBJDIR)%.o: $(SRCDIR)$(ENV_DIR)%.c
		cc $(FLAGS) -c  $(INCLUDES) $< -o $@
$(BUILTINS_OBJ): $(OBJDIR)%.o: $(SRCDIR)$(BUILTINS_DIR)%.c
		cc $(FLAGS) -c  $(INCLUDES) $< -o $@
$(EXECUTOR_OBJ): $(OBJDIR)%.o: $(SRCDIR)$(EXECUTOR_DIR)%.c
		cc $(FLAGS) -c  $(INCLUDES) $< -o $@
$(LEXER_OBJ): $(OBJDIR)%.o: $(SRCDIR)$(LEXER_DIR)%.c
		cc $(FLAGS) -c  $(INCLUDES) $< -o $@
$(EXPANDER_OBJ): $(OBJDIR)%.o: $(SRCDIR)$(EXPANDER_DIR)%.c
		cc $(FLAGS) -c  $(INCLUDES) $< -o $@
$(PARSER_OBJ): $(OBJDIR)%.o: $(SRCDIR)$(PARSER_DIR)%.c
		cc $(FLAGS) -c  $(INCLUDES) $< -o $@
$(WILDCARD_OBJ): $(OBJDIR)%.o: $(SRCDIR)$(WILDCARD_DIR)%.c
		cc $(FLAGS) -c  $(INCLUDES) $< -o $@

clean:
	rm -f $(OBJ) $(HELPEROBJ) $(DEBUGOBJ) $(ENV_OBJ) $(BUILTINS_OBJ) $(EXECUTOR_OBJ) $(LEXER_OBJ) $(EXPANDER_OBJ) $(PARSER_OBJ) $(WILDCARD_OBJ)
	if test -d $(OBJDIR); then echo $(OBJDIR) exists; fi

fclean: clean
	make fclean -C $(LIBFTLIB)
	rm $(NAME)

bonus: all

re:
	make clean
	make
