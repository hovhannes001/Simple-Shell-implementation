#include "my_libararys.h"
char* promt_name = NULL;
char **matrix;
int main(){
    promt_name = malloc(sizeof(char) * SIZE);
    if(promt_name == NULL) {
        perror("malloc failed: ");
        exit(EXIT_FAILURE);
    }
    matrix = malloc(sizeof(char*) * HISTORY);
    if(matrix == NULL) {
        perror("malloc failed: ");
        exit(EXIT_FAILURE);
    }
    for(int i = 0;i <= HISTORY;i++) {
        matrix[i] = malloc(sizeof(char) * SIZE);
        if(matrix[i] == NULL) {
            perror("malloc failed: ");
            exit(EXIT_FAILURE);
        }
    }
    if(promt_name == NULL) {
        perror("malloc failed: ");
        exit(EXIT_FAILURE);
    }
    strcpy(promt_name,"picsart@academy$");
    char * command = malloc(sizeof(char) * SIZE);
    if(command == NULL) {
        perror("malloc failed: ");
        exit(EXIT_FAILURE);
    }
    int i = 0;
    while(true) {
        printf("%s ",promt_name);
        memset(command,0,SIZE);
        fgets(command,SIZE,stdin); //SIZE - 2 for newline and /0
        remove_newline(command);
        strcpy(matrix[HISTORY - i],command);
        
        check(command);
        i++;
    }
    return 0;
}
