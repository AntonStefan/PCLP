#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char wholefile[500001], masterline[1001], line[1001], title[1001], *k, *start, *end, cline[1001], input[1001], words[1001][1001], *fnd;
size_t linesize, linecount, masterlinecount;
int wordcnt, goodwords;
bool inp, good;

typedef struct
{
    char file[1001]; // filename
    char link[101]; // url
    int views;
    char title[101];
    char p[10001]; // inside p
    char content[10001]; // whole file -first line
    int checksum; // unused
} bruh;

bruh bd[1001], bd2[1001], aux;

int hash(char *s) // not implemented
{
    return 0;
}

bool file_exists(const char *filename) // checks if file exists
{
    FILE *fp = fopen(filename, "r");
    bool is_exist = false;
    if (fp != NULL)
    {
        is_exist = true;
        fclose(fp); // close the file
    }
    return is_exist;
}

int main()
{
    FILE *f = fopen("master.txt", "r");
    if (!file_exists("master.txt"))
    {
        printf("Error opening master file!\n");
        return 0;
    }

    while(fgets(masterline, sizeof(masterline), f))
    {
        masterlinecount ++; // the line number in master.txt file

        masterline[strlen(masterline) - 1] = '\0'; // replaces \n with \0 in the current line
        FILE *site = fopen(masterline, "r"); // opens site from current line 

        if (!file_exists(masterline))
        {
            printf("Error opening %s\n", masterline);
            return 0;
        }

        else // if the file exists
        {
            memset(wholefile, '\0', 500000); // wholefile will contain the content of the site, check line 126

            strcpy(bd[masterlinecount].file, masterline);

            fgets(line, sizeof(line), site); // get first line

            k = strtok(line, " ");

            strcpy(bd[masterlinecount].link, k); // get the link

            k = strtok(NULL, " "); // skip one
            k = strtok(NULL, " ");

            bd[masterlinecount].views = atoi(k); // get the views as int

            inp = false;

            while(fgets(line, sizeof(line), site))
            {
                strcat(wholefile, line); // add current line to content

                start = strstr(line, "<title>"); // title should be on a single line
                if(start != NULL)
                {
                    strncpy(title, line + 7, strlen(line) - 16); // get line without <title>, </title> and newline
                    title[strlen(line) - 16] = '\0';
                    strcpy(bd[masterlinecount].title, title);

                }

                start = strstr(line, "<p"); // used for task 2
                end = strstr(line, "</p");  // gets what is inside paragraph

                if(start != NULL)
                {
                    inp = true;
                    start = strstr(line, ">");
                    if(end == NULL) strcat(bd[masterlinecount].p, start + 1);
                    else
                    {
                        inp = false;
                        memset(cline, '\0', 1000);
                        strncpy(cline, start + 1, strlen(start) - 6);
                        strcat(bd[masterlinecount].p, cline);
                        strcat(bd[masterlinecount].p, "\n");
                    }
                }
                else if(inp)
                {
                    if(end == NULL) strcat(bd[masterlinecount].p, line);
                    else
                    {
                        inp = false;
                        memset(cline, '\0', 1000);
                        strncpy(cline, line, strlen(line) - 5);
                        strcat(bd[masterlinecount].p, cline);
                        strcat(bd[masterlinecount].p, "\n");
                    }
                }

            }
            strcpy(bd[masterlinecount].content, wholefile); // the content of the file is stored
            bd[masterlinecount].checksum = hash(wholefile); // hash is not needed for task 1.

        }
        fclose(site); // close site so I dont get depunctat
    }

    for (int i = 1; i <= masterlinecount; i ++) // print what we need
    {
        printf("%s %d %s\n", bd[i].link, bd[i].views, bd[i].title);
    }

    fclose(f); // close site so I dont get depunctat

    return 0;
}
