/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: s364pate
 *
 * Created on February 17, 2023
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define CMD_LEN 1024

int main() {
  char input[CMD_LEN];
  char commands[2][CMD_LEN];
  int pipe_fd[2];
  pid_t pid;

  printf("Your command> \n");

  // Read a single line from stdin
  fgets(input, CMD_LEN, stdin);

  int i = 0, j = 0, command_count = 0;

  // Split the input into commands separated by the pipe symbol
  while (input[i] != NULL && command_count < 2) {
    if (input[i] == '|') {
      commands[command_count][j] = NULL;  // Null-terminate the current command
      command_count++;  // Move to the next command
      j = 0;  // Reset the index for the next command
    } 
    else {
      commands[command_count][j] = input[i];  // Add the current character to the current command
      j++;  // Move to the next character in the current command
    }
    i++;  // Move to the next character in the input string
  }

  // Null-terminate the last command
  commands[command_count][j] = NULL;

  // Create a pipe
  if (pipe(pipe_fd) < 0) {
    fprintf(stderr, "Pipe creation failed\n");
    return 1;
  }

  // Fork a child process
  pid = fork();

  if (pid < 0) {
    fprintf(stderr, "Fork failed\n");
    return 1;
  } 
  else if (pid == 0) {// Child process
    // Redirect stdin to the read end of the pipe
    dup2(pipe_fd[0], STDIN_FILENO);
    // Close the write end of the pipe
    close(pipe_fd[1]);
    // Execute the second command
    execlp(commands[1], commands[1], NULL);
    // Should not reach here if execlp() succeeds
    fprintf(stderr, "Command execution failed\n");
    exit(1);
  } 
  else {// Parent process
    // Redirect stdout to the write end of the pipe
    dup2(pipe_fd[1], STDOUT_FILENO);
    // Close the read end of the pipe
    close(pipe_fd[0]);
    // Execute the first command
    execlp(commands[0], commands[0], NULL);
    // Should not reach here if execlp() succeeds
    fprintf(stderr, "Command execution failed\n");
    exit(1);
  }

  return 0;
}

