all: terminal

terminal: terminal.o built_in_commands.o execute.o ls.o pinfo.o jobs.o overkill.o fg_bg.o signal_handlers.o
	gcc terminal.o built_in_commands.o execute.o ls.o pinfo.o jobs.o overkill.o fg_bg.o signal_handlers.o -o terminal
terminal.o: terminal.c
	gcc -c terminal.c
built_in_commands.o: built_in_commands.c
	gcc -c built_in_commands.c
execute.o: execute.c
	gcc -c execute.c
ls.o: ls.c
	gcc -c ls.c
pinfo.o: pinfo.c
	gcc -c pinfo.c
jobs.o: jobs.c
	gcc -c jobs.c
overkill.o: overkill.c
	gcc -c overkill.c
fg_bg.o: fg_bg.c
	gcc -c fg_bg.c
signal_handlers.o: signal_handlers.c
	gcc -c signal_handlers.c
clean:
	rm -rf terminal signal_handlers.o terminal.o built_in_commands.o execute.o ls.o pinfo.o jobs.o overkill.o fg_bg.o
