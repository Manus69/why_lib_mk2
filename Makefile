driver = a.out
lib = libwhy.a
debug_flags = -Wall -Werror -g
release_flags = -O3 -flto
flags = $(debug_flags)
obj_dir = objects/
src_dir = ./
include_dir = ./
cc = gcc

headers = $(wildcard $(src_dir)*.h)
source = $(wildcard $(src_dir)*.c)
objects = $(subst $(src_dir),$(obj_dir),$(source:.c=.o))

all: directory $(driver)

directory:
	@mkdir -p $(obj_dir)

release: flags = $(release_flags)
release: fclean $(driver) $(lib)

$(obj_dir)%.o : $(src_dir)%.c $(headers)
	$(cc) $(flags) $< -I $(include_dir) -I. -c -o $@

$(driver): $(objects)
	$(cc) $(flags) $< -I $(include_dir) -o $@

$(lib) : $(objects)
	ar rcs $(lib) $(objects)

clean:
	rm -f $(objects)

fclean: clean
	rm -f $(lib) $(driver)