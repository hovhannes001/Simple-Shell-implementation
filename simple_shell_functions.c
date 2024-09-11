#include "my_libararys.h"
void remove_newline(char *str) {
    size_t len = strlen(str);
    
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';  
    }
}
char* argument_from_string(const char *command, int index) {
    int size = strlen(command);
    
    char *argument = malloc(sizeof(char) * (size - index + 1));
    if (argument == NULL) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }

    int j = 0;
    int i = index;
    while (i < size && command[i] == ' ') {
        i++;
    } //you can use string functions like strchr, strcpy ...
    while (i < size && command[i] != ' ') {
        argument[j++] = command[i++];
    }
    argument[j] = '\0';
    //handle the case when commands or argument doesnt exist(print error message for example)
    return argument; 
}
//----------------------------------------------------------cd------------------------------------------
void change_directory(char *command) {
    char *arg = malloc(sizeof(char) * SIZE);
    if(arg == NULL) {
        perror("malloc failed: ");
        exit(EXIT_FAILURE);
    }

    if (chdir(argument_from_string(command,strlen("cd"))) < 0) {
        perror("chdir failed: ");
        return ; 
    }
    
}
//----------------------------------------------------------exit/help------------------------------------------
void my_exit(char* command) {
    exit(EXIT_FAILURE); //not exit_failure, use exit_success
}
void help(char* command){ 
    system("/bin/bash -c 'help'"); //error checking
}
//----------------------------------------------------------chpromt------------------------------------------
void change_promt(char *command){
    strcpy(promt_name,argument_from_string(command,strlen("chpromt"))); 
    strcat(promt_name,"$");
}

//-----------------------------------------------------------clear/pwd------------------------------------------
 void child_function(char *command){

    switch(fork()) {
        case -1:
            perror("fork failed");
            exit(EXIT_FAILURE);
        case 0:
            
            if (execlp(command,command, NULL) == -1) {
                perror("execlp failed");
                exit(EXIT_FAILURE);
            }
            break;
        
        default:   
            wait(NULL); 
            break;
    }
}
void echo_function(char *command){

    switch(fork()) {
        case -1:
            perror("fork failed");
            exit(EXIT_FAILURE);
        case 0:
            
            if (execlp("echo","echo",argument_from_string(command,strlen("echo")), NULL) == -1) {
                perror("execlp failed");
                exit(EXIT_FAILURE);
            }
            break;
        
        default:   
            wait(NULL); 
            break;
    }
}
char* str_name(char* variable){
    char* name = malloc(sizeof(SIZE)); // sizeof(SIZE)?? sizeof(char) * SIZE, error checking
    int i = 0;
    for(;variable[i] != '=';i++) {
        name[i] = variable[i];
    }
    name[i] = '\0';
    return name;
}
char* str_value(char* variable){
    char* value = malloc(sizeof(SIZE)); //the same issue
    variable++; //use tmp char* for  increment operations
    int i = 0;
    while(*variable == '='){
        variable++;
    };
    while(*variable) {
        value[i++] = *variable;
        variable++;
    }
    value[i] = '\0';
    return value;
}
void my_setenv(char *command) { //segmentation fault
    char* variable0; 
    char* variable = argument_from_string(command,strlen("setenv"));
    //variable0 = malloc(strlen(variable) + 1);, check if variable0 is NULL
    strcpy(variable0,variable);
    char *name = str_name(variable);
    char* value = str_value(variable);
    puts(name);
    puts(value);
    if(setenv(name,value,0) < 0) {
        perror("setenv failed: ");
        return;
    }
    //free(name);
    //free(value);
    //free(variable);
    //free(variable0);
}
void my_unsetenv(char *command) {
    if(unsetenv(argument_from_string(command,strlen("unsetenv"))) < 0) {
        perror("unsetenv failed: ");
        return;
    }
}
void history(char* command) {
    int size = atoi(argument_from_string(command,strlen("history")));
    for(int i = HISTORY; i > HISTORY - size;i--){
        puts(matrix[i]);
    }
}
 void check(char *command) {
    if(!strncmp(command,"cd",2)) {
        change_directory(command);
        return ;
    }
    if(!strncmp(command,"exit",4)) {
        my_exit(command);
        return;
    }
    if( !strncmp(command,"help",4)) {
        help(command);
    }
    if(!strncmp(command,"history",strlen("history"))) {
         history(command);
    }
    if(!strncmp(command,"pwd",strlen("pwd")) || !strncmp(command,"clear",strlen("clear"))){
        child_function(command);
        return ;
    }
    if(!strncmp(command,"echo",strlen("echo"))){ 
        echo_function(command);
        return ;
    }
    if(!strncmp(command,"setenv",2)) {
        my_setenv(command); 
    }
    if(!strncmp(command,"unsetenv",strlen("unsetenv"))) {
         unsetenv(command); //my_unsetenv instead of unsetenv
     }
    if(!strncmp(command,"chpromt",strlen("chpromt"))) {
         change_promt(command);
         return;
     }
    
}
