// Santiago Quintero Hincapié.
// Jonathan Stiven Ramírez Fernández

#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
  // Declarations
  time_t start;
  time_t end;
  struct timeval current_time;
  gettimeofday(&current_time, NULL);
  start = current_time.tv_usec;

  // Call to fork()
  int pid = fork();
  if (pid < 0) {
    // Error forking
    fprintf(stderr, "Fork failed\n");
    return 1;
  }
  else if (pid == 0) {
    // Child execution
    char *args[3];
    int aux = 0;
    for(int i = 1; i < argc; i++) {
      args[aux] = argv[i];
      aux++;
    }
    args[aux] = NULL;
    execvp( argv[1], args );
  }
  else {
    // Parent process because return value non-zero.
    wait(NULL);
    gettimeofday(&current_time, NULL);
    end = current_time.tv_usec;
    time_t final_time = end - start;
    printf("Elapsed time: %ld \n", final_time);
  }
  return 0;
}
