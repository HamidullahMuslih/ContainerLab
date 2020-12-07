#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static char child_stack[1048576];

static int child_fn() {
  printf("New Container's PID: %ld\n", (long)getpid());
  printf("Parent PID: %ld\n", (long)getppid());
  printf("New (container) `data structure` Namespace:\n");
  system("ls /");
  printf("\n\n");
  return 0;
}

int main() {
  printf("New Container's PID: %ld\n", (long)getpid());
  printf("Original (Host) `data structure` Namespace:\n");
  system("ls /");
  printf("\n\n");


  pid_t child_pid = clone(child_fn, child_stack+1048576, CLONE_NEWPID | CLONE_NEWNET | CLONE_NEWNS | SIGCHLD, NULL);
  printf("clone() = %ld\n", (long)child_pid);

  waitpid(child_pid, NULL, 0);
  return 0;
}
