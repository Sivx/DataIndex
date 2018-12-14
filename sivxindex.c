#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

int main(void)
{
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    
    int h, M, m, s, d, Y;
    char year[5], month[3], day[3], hour[3], minute[3], second[3];
    char *filesname = "/index.log";
    char *filename;
    filename = (char *) malloc(5);
    //2018-04-04 09:00:03 and hard coded filename
    fp = fopen("testfile.log", "r");
    if (fp == NULL)
    exit(EXIT_FAILURE);
    
    while ((read = getline(&line, &len, fp)) != -1) {
        //printf("Retrieved line of length %zu :\n", read);
        sscanf(line, "%d-%d-%d %02d:%02d:%02d", &Y, &M, &d, &h, &m, &s);
        struct stat st = {0};
        sprintf(year,"%ld", Y);
        sprintf(month,"%02d", M);
        sprintf(day,"%02d", d);
        sprintf(hour,"%02d", h);
        sprintf(minute,"%02d", m);
        sprintf(second,"%02d", s);
        
        strcpy (filename,year);
        if (stat(filename, &st) == -1) {
            mkdir(filename, 0777);
        }
        filename = (char *) realloc(filename, sizeof(filename)+sizeof(month));
        strcat(filename, "/");
        strcat(filename, month);
        if (stat(filename, &st) == -1) {
            mkdir(filename, 0777);
        }
        filename = (char *) realloc(filename, sizeof(filename)+sizeof(day));
        strcat(filename, "/");
        strcat(filename, day);
        if (stat(filename, &st) == -1) {
            mkdir(filename, 0777);
        }
        filename = (char *) realloc(filename, sizeof(filename)+sizeof(hour));
        strcat(filename, "/");
        strcat(filename, hour);
        if (stat(filename, &st) == -1) {
            mkdir(filename, 0777);
        }
        filename = (char *) realloc(filename, sizeof(filename)+sizeof(minute));
        strcat(filename, "/");
        strcat(filename, minute);
        if (stat(filename, &st) == -1) {
            mkdir(filename, 0777);
        }
        
        FILE *outFile;
        filename = (char *) realloc(filename, sizeof(filename)+sizeof(filesname));
        strcat(filename, filesname);
        outFile=fopen(filename, "a");
        if(outFile==NULL) {
           perror("Error opening file.");
        }
        else {
           fprintf(outFile, "%s", line);
        }
        fclose(outFile);
    }
    
    fclose(fp);
    if (line)
               free(line);
    exit(EXIT_SUCCESS);
}
