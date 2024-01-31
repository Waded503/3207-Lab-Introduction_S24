#include <dirent.h>
#include <stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#define MAX_LEN 10000


int isDirectory(char* location) {
    // opening the directory
    DIR* directory = opendir(location);
    // if directory is not null, then it is a valid directory
    if (directory != NULL) {
        // close the directory and return 1
        closedir(directory);
        return 1;
    } else if (errno == ENOTDIR) {
        // not a directory, so return 0
        return 0;
    }
    // else return -1
    return -1;
}

void printDirectories(char* directoryName, int tabCount) {
    int result = isDirectory(directoryName);    // checking the directory
    if (result != -1) {
        // the directory possibly exists
        if (result == 1) {
            // it is a directory
            // scan the directory for the file contents
            struct dirent **namelist;
            int n = scandir(directoryName, &namelist, NULL, alphasort);
            if (n == -1) {
                // directory could not be opened, return with exit status of 1
                perror("directory cannot be opened.");
                exit(1);
            }
            while (n--) {
                // printing the contents of the directory
                // tabCount for visual hierarchy
                for (int i = 0; i < tabCount; i += 1) {
                    printf("\t");
                }
                // display the name
                printf("%s\n", namelist[n]->d_name);
                // getting the relative location of the file/directory in the current directory
                char currentFileLocation[MAX_LEN] = "";
                // current File location = "directoryName/currentName"
                strcpy(currentFileLocation, directoryName);
                strcat(currentFileLocation, "/");
                strcat(currentFileLocation, namelist[n]->d_name);
                if (strcmp(namelist[n]->d_name, ".") != 0 && strcmp(namelist[n]->d_name, "..") != 0) {
                    // if it is a directory, recursively call printDirectories function
                    // for the currentFileLocation, with increment in tabCount for visual hierarchy
                    if (isDirectory(currentFileLocation) == 1)
                        printDirectories(currentFileLocation, tabCount+1);
                }
                // free the pointer
                free(namelist[n]);
            }
        } else {
            // display error
            perror("The given location is not a directory");
            exit(1);
}
    } else {
        // display error
        perror("Directory doesn't exist.");
        exit(1);
    }
}

int main(int argc, char** argv) {

    // getting the arguments
    if (argc > 2) {
        perror("Wrong number of arguments.\n");
        exit(1);
    } else {
        // if argc = 1, then no directory location was sent, so set default location to "."
        if (argc == 1) {
            // print using default location
            printDirectories(".", 0);
        } else {
            // print directories with the location provided
            printDirectories(argv[1], 0);
        }
    }

}
