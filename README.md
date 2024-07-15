# OS1
This exercise aims to familiarize us with the bash language.
# How to Run
First go to your destination folder and clone the repo:
```
git clone https://github.com/landsboy/OS-Ex1.git
```
## gccfind.sh:
In the file my/gccfind.sh the script receives 2 arguments: a path to the folder and some word, when the file is run it goes over the resulting folder and first deletes all the compiled files from it. After that, reads the c files in the folder, and compiles only the c files in the same folder that contain the given word.

The '-r' flag can be added/dropped, if it appears the same command that is described should be executed only recursively on the given folder.

Run command:
```
sh my/gccfind.sh kslsssss -r
```

## tennis.sh:
In the my/tennis.sh file there is a file that implements the tennis game.

## myshell.c:
This file implements a shell, the program will display a prompt on the screen and allow the user to type commands in Linux (for example sleep, cat, ls). After pressing ENTER, the typed command will be executed, in a separate process.

This exercise also implements the fork principle (creating a child process from a parent process)

### example:

![image](https://github.com/user-attachments/assets/bba02266-93c7-441e-93a6-7a3ba0b0fffa)





