##
## EPITECH PROJECT, 2019
## CPE_BSQ
## File description:
## Makefile
##

NAME = bsq

FILES = main.c \
	my_read.c

all :	$(NAME)

$(NAME):
	gcc -o $(NAME) $(FILES)
#	gcc -o $(NAME) $(FILES) -Wall -Werror -Ofast

clean:
	rm -f *.o

fclean:	clean
	rm -f $(NAME)

re:	fclean all

prepush:	fclean
	rm -f *# *~ ./*/*# ./*/*~ ./*/*/*# ./*/*/*~
	git add --all
	git status

tree:	prepush
	tree -a -I .git

push:	prepush
	git commit -m 'auto-sync with master'
	git push origin master

pull:
	git pull origin master

sync:	pull	push

debug:
	clear
	gcc -o $(NAME) $(FILES) -Wall -Wextra

valgrind:
	gcc -g3 -o $(NAME) $(FILES)
