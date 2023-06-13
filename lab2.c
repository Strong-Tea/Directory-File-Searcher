#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

long int min, max, counter;
FILE *outFile; 

void _readdir(const char* pathDir) {
    DIR *dir;
    struct dirent *entry;
    struct stat pstatus;

    if ((dir = opendir(pathDir)) == NULL) {
       fprintf(stderr,"%s: %s\n", pathDir, strerror(errno)); 
       return;
    }

    while ((entry = readdir(dir)) != NULL) {
        char path[PATH_MAX];
        snprintf(path, sizeof(path), "%s/%s", pathDir, entry->d_name);

        if (entry->d_type == DT_DIR) {         
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;               
            _readdir(path);    
        } else 
        if (entry->d_type == DT_REG) {
            if (stat(path, &pstatus) == 0) {
                if (pstatus.st_size >= min && pstatus.st_size <= max)
                   fprintf(outFile, "%s %ld\n", path, pstatus.st_size);
                counter++;   
            }
        }
    }

    if (closedir(dir) != 0)
        fprintf(stderr,"%s: %s\n", pathDir, strerror(errno));
}

int main(int argc, char **argv) {

    if(argc < 5){
	fprintf(stderr, "%s: ERROR:not enough arguments\n", basename(argv[0]));
	return -1;
    }

    char *programName = basename(argv[0]);
    char *path = argv[1];
    min = atoi(argv[2]);
    max = atoi(argv[3]);
    char *destFile = basename(argv[4]);

    if (min > max) {
        fprintf(stderr, "%s: ERROR:min is greater than max\n", basename(argv[0]));
	return -1;
    }

    outFile = fopen(destFile, "w");
    if (outFile == NULL) {
        fprintf(stderr,"%s: %s\n", destFile, strerror(errno)); 
	return -1;
    }

    char* fullPath = realpath(path, NULL);
    if (fullPath == NULL) {
        fprintf(stderr,"%s: %s\n", basename(argv[0]), strerror(errno));
        return -1;
    }

    _readdir(fullPath);

    printf( "%ld\n", counter);

    if (fclose(outFile) != 0) {
        fprintf(stderr,"%s: %s\n", destFile, strerror(errno));
    }
    
    return 0;
}
