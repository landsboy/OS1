// Netanel Landesman 315873588

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

#define MAX_SIZE 100
static int numCommands = 0;

void adding_to_env(int argc, char *argv[]) {
    //Get the enviaroment PATH:
    char *new_path = getenv("PATH"); 
    //Concatenate all user arguments to the enviaroment PATH:
    for(int i = 1 ; i < argc; i++){
    strcat(strcat(new_path, ":"),argv[i]);
    }
    //Initialize the PATH to the new path:
    setenv("PATH", new_path, 1);
}

void parsing_user_command(char *separated_command[], bool *flag) {
    // Maximum command length of 100 characters:
    char new_command[MAX_SIZE]; 
    // Printing the prompt:
    printf("$ ");
    fflush(stdout);
    fgets(new_command, sizeof(new_command), stdin); 
    // replace '\n' at end with '\0':    
    if(new_command[strlen(new_command) - 1] == '\n')
        new_command[strlen(new_command) - 1] = '\0';
    // We will prepare to run the command only if we did not receive an empty command:
    if (new_command[0] != '\0'){
        *flag = true;
        // Splitting the command into components:
        char *single_word = strtok(new_command, " "); 
        // Creating an array with the word-separated command:
        int i = 0;
        while (single_word != NULL) {
            separated_command[i] = malloc(strlen(single_word) + 1); 
            strcpy(separated_command[i], single_word); 
            single_word = strtok(NULL, " "); 
            i += 1;
        }
        //Adding NULL at end of the array to indicate ending:
        separated_command[i] = NULL; 
    } 
}

void add_commants_to_hisory(pid_t pid, char **separated_command, char **command_history, bool print) {
    //First we will convert the PID to string:
    char pid_and_command[MAX_SIZE];
    sprintf(pid_and_command, "%d ", (int) pid);
    // And now we will concatenate the command and the arguments to the PID:
    int i;
    for (i = 0; separated_command[i] != NULL; i++) {
        strcat(pid_and_command, separated_command[i]);
        strcat(pid_and_command, " ");
    }
    // Finally, adding the pid_and_command to the command history list:
    command_history[numCommands] = strdup(pid_and_command); 
    //Adding NULL at end of the array to indicate ending:
    command_history[numCommands + 1] = NULL; 
    // If the user entered the command "history" we will print the history list:
    if (print){
        for (i = 0; command_history[i] != NULL; i++) {
        printf("%s\n", command_history[i]);
        }
    }
    numCommands++;
}

void cd_command(char **separated_command, char **command_history) {
    // First we will check that the user entered path to the command:
    if (separated_command[1] == NULL) { 
        perror("cd failed");
    } else { // Running the command:
        if (chdir(separated_command[1]) != 0) {
            perror("cd failed");
        }
    }
    // Finally we will add the command to the command history:
    add_commants_to_hisory((int) getpid(), separated_command,command_history, false); 
}

void non_builtin_command(char **separated_command, char **command_history) {
    pid_t pid;
    if ((pid = fork()) < 0) { // if creating new process failed:
        perror("fork failed");
    } else { // if fork succed 
        if (pid == 0) { // child process:
            if (execvp(separated_command[0], separated_command) == -1) {
            perror("execvp failed");
            exit(-1);
            } 
        } else { // parent process:
            int status;
            // make parent wait for son to finish
            if (wait(&status) == -1) {
                perror("wait failed");
            }
            // Finally we will add the command to the command history:
            add_commants_to_hisory(pid, separated_command, command_history, false);
        }
    }
}

void run_command(char **separated_command, char **command_history) {
    if (strcmp(separated_command[0], "cd") == 0) {
        cd_command(separated_command, command_history);
    } else if (strcmp(separated_command[0], "history") == 0) {
        add_commants_to_hisory((int) getpid(), separated_command, command_history, true);
    } else if (strcmp(separated_command[0], "exit") == 0) { // We will stop the program without error:
        // Before we exit the program we will release the dynamic memory:
        for (int i = 0; separated_command[i] != NULL; i++) {
            free(separated_command[i]);}
        exit(0);
    } else { // for non-built-in commands:
        non_builtin_command(separated_command, command_history);
    }
}

int main(int argc, char *argv[]) {
    //First we will check if we got a PATH that we will add them to env:
    if (argc > 1) {
        adding_to_env(argc, argv);
    }
    //The length of a command is a maximum 100 and there are at most 100 commands:
    char *separated_command[MAX_SIZE]; 
    char *history[MAX_SIZE];
    bool flag; // A flag that will receive a true value only if we receive a non-empty command
    //It can be assumed that there will be at most 100 commands, so the program will run until the user enters the "exit" command:
    while (true) {
        flag = false;
        parsing_user_command(separated_command, &flag); 
        if (flag){
            run_command(separated_command, history);}
    }
    return 0;
}