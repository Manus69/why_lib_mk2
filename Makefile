driver = a.out
driver_name = main.c
lib = libwhy.a
debug_flags = -Wall -Werror -g
release_flags = -O3
driver_flags = debug_flags
flags = $(debug_flags)
obj_dir = objects/
src_dir = ./
include_dir = ./
cc = gcc

headers = $(wildcard $(src_dir)*.h)
source = $(filter-out $(driver_name), $(wildcard $(src_dir)*.c))
# source = $(filter-out($driver), $(source))
objects = $(subst $(src_dir),$(obj_dir),$(source:.c=.o))

all: directory $(objects) $(driver)

directory:
	@mkdir -p $(obj_dir)

release: flags = $(release_flags)
release: driver_flags = $(release_flags) -flto
release: fclean $(driver) $(lib)

$(obj_dir)%.o : $(src_dir)%.c $(headers)
	$(cc) $(flags) $< -I $(include_dir) -c -o $@

$(driver): $(objects)
	$(cc) $(flags) $(driver_name) $(objects) -I $(include_dir) -o $@ -lm

$(lib) : $(objects)
	ar rcs $(lib) $(objects)

clean:
	rm -f $(objects)

fclean: clean
	rm -f $(lib) $(driver)

re: fclean all