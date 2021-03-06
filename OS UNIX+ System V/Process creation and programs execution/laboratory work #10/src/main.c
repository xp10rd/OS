#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <stdlib.h>

void print_error(int status) {
    if(status == -1) {
        perror("Error!");
        exit(-1);
    }
}

int main(int argc, char* argv[]) {
    if(argc < 2) {
        return -1;
    }

    int pid = fork();
    print_error(pid);

    if (pid == 0) {
        int error = execvp(argv[1], argv + 1);
        print_error(error);
    } else {
        int child_exit_code;
        int ret_pid = wait(&child_exit_code);
        print_error(ret_pid);
        printf("Child process %d ", pid);
        if(WIFEXITED(child_exit_code)) {
            printf("exited with code %d\n", WEXITSTATUS(child_exit_code));
        } else if(WIFSIGNALED(child_exit_code)) {
            printf("was interrupted with signal %d\n", WTERMSIG(child_exit_code));
        }
    }
    return 0;
}