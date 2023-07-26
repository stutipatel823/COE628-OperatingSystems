/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: s364pate
 *
 * Created on February 10, 2023, 2:29 PM
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<sys/wait.h> 
#include <unistd.h> 
#include <stdbool.h>
 
/*
 * 
 */
int main(int argc, char** argv) {
    char *user_input;
    do{
        char *new_argv[15];
        user_input=(char *)malloc(20*sizeof(char));
        
        int cntr=0,argument_cntr=0, ch, fork_boolean;
        printf("Your Command>");
        while((ch=getchar()) != '\n'){
            if(cntr==0){
                new_argv[argument_cntr]=user_input+cntr;
                *(user_input+cntr)=ch;
                cntr++;
                argument_cntr++;
            }else if(ch==' '){
                new_argv[argument_cntr]=user_input+cntr+1;
                *(user_input+cntr)='\0';
                cntr++;
                argument_cntr++;
            }else{
                *(user_input+cntr)=ch;
                cntr++;
            }
        }
        *(user_input+cntr)='\0';
        new_argv[argument_cntr]=NULL;
        if(*(user_input+cntr-1)=='&'){
            //*(user_input+cntr-1)='\0';
            fork_boolean=1;
        }else{
            fork_boolean=0;
        }
        
        
        int parent_id;
        parent_id = fork();
        
        if(parent_id<0){
            printf("Error in creating child process.\n");
            exit(1);
        }
        else if(parent_id>0){
            //parent process
            if(fork_boolean == 0){
               
                while(wait(NULL)>0);  
                printf("Parent will wait, with ID: %d\n", getpid);
            }
            else if (fork_boolean == 1){
                printf("Parent will not waiting, with ID: %d\n", getpid);
            }
            //go to outside_fork;
        }
        else if (parent_id == 0){
            printf("Child Process with ID: %d\n", getpid);
            //child process
            int NoS = argument_cntr;
            char * args[NoS+2];
            int k;
            for (k=0; k<NoS; k++){
                args[k]= new_argv[k];
            }
            args[NoS+1]= NULL;
            printf("child executed\n");


            execvp(args[0],args);
        }
        
    } 
     while(strncmp(user_input,"exit",4)!=0);
    printf("GoodBye");
    return (EXIT_SUCCESS);
}

