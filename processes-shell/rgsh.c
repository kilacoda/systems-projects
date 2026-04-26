#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

void handleErrors() {
  char error_message[30] = "An error has occurred\n";
  write(STDERR_FILENO, error_message, strlen(error_message));
}
void handleInteractiveMode() {
  char* input = NULL;
  size_t size = 0;
  char** path = malloc(sizeof(char*));
  int execFound;

  path[0] = "/bin/";

  while (1) {
    execFound = 0;

    printf("rgsh> ");
    ssize_t bytes_read = getline(&input, &size, stdin);

    if (bytes_read != -1) {
      char** commandArgs = malloc(5 * sizeof(char*));
      char* argToken = strsep(&input, " ");
      int argCount = 0;

      while (argToken != NULL) {
        argToken[strcspn(argToken, "\n")] =
            0;  // get rid of newline char, if any
        commandArgs[argCount] = argToken;
        printf("%s\n", argToken);

        argCount++;
        argToken = strsep(&input, " ");
      }

      if (strcmp(commandArgs[0], "exit") == 0) {
        if (argCount > 1) {
          handleErrors();
        }

        exit(0);

      } else if (strcmp(commandArgs[0], "cd") == 0) {
        if ((argCount == 1) || (argCount > 2)) {
          handleErrors();
        }

        if (chdir(commandArgs[1]) == -1) {
          handleErrors();
        };
      } else if (strcmp(commandArgs[0], "path") == 0) {
        free(path);
        char** path = malloc((argCount - 1) * sizeof(char*));
        for (int i = 0; i < argCount - 1; i++) {
          path[i] = commandArgs[i + 1];
          if (path[i][strlen(path[i])-1] != '/') {
            path[i][strlen(path[i])] = '/'; // add slash to make processing paths better.
          }
        }
      } else {
        argCount++;
        commandArgs[argCount] = NULL;  // to make execv happy

        char commandPath[256 + strlen(commandArgs[0])];
        // checking which paths are executable
        for (int i = 0; i < sizeof(path); i++) {
          strcat(strcpy(commandPath, path[i]), commandArgs[0]);

          if (access(commandPath, X_OK) == 0) {
            commandArgs[0] = commandPath;

            perror("access");
            // printf("Can access %s\n", commandArgs[0]);
            execFound = 1;
            break; // don't need to check anymore, found an exec that works.

          }

          memset(commandPath, 0, sizeof commandPath);
        }

        if (!execFound) {
          handleErrors();
        }

        pid_t pid = fork();

        if (pid < 0) {
          // fork failed
          handleErrors();
        } else if (pid == 0) {
          // child process

          execv(commandArgs[0], commandArgs);
          perror("execv");

        } else {
          // parent process
          wait(NULL);
          continue;
        }
      }

    } else {
      handleErrors();
    }
  }
}

int main(int argc, char const* argv[]) {
  if (argc == 1) {
    // interactive mode
    handleInteractiveMode();
  }

  return 0;
}
