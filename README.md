
# LINUX MINI SHELL USING C

## Building and Running

        make;
        ./terminal;
## To clear all unnecessary files
-	make clean

## Features
- C code implementation of
   a)cd  b)pinfo  c)echo  d)ls [al]  e)pwd.
- Rest all basic commands implementation similar to terminal.
- semicolon separated multiple commands
- Foreground and Background implementations
- quit command for exiting the shell
- ls.c contains implementation of ls command, pinfo.c of pinfo command, built_in_commands contains implemtation of cd ,pwd and echo  command.
- terminal.c takes line as input and prints username and host and gives all commands to execute.c.
- execute.c is for background processing
- environment.c is for set and unset
