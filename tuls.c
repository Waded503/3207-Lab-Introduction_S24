#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  // Get the directory to list.
  char *dirname;
  if (argc == 1) {
    dirname = ".";
  } else if (argc == 2) {
    dirname = argv[1];
  } else {
    fprintf(stderr, "Usage: %s [dirname]\n", argv[0]);
    exit(1);
  }

  // Open the directory.
  DIR *dirp = opendir(dirname);
  if (dirp == NULL) {
    perror("opendir");
    exit(1);
  }

  // Scan the directory.
  struct dirent **namelist;
  int n = scandir(dirname, &namelist, NULL, alphasort);
  if (n == -1) {
    perror("scandir");
    exit(1);
  }

  // Print the directory contents.
  for (int i = 0; i < n; i++) {
    printf("%s\n", namelist[i]->d_name);
  }

  // Free the memory allocated by scandir().
  for (int i = 0; i < n; i++) {
    free(namelist[i]);
  }
  free(namelist);

  // Close the directory.
  closedir(dirp);

  return 0;
}
