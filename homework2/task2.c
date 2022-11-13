#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char wholefile[500001], masterline[1001], line[1001], title[1001], *k, *start, *end, cline[1001], input[1001], words[1001][1001], *fnd, *fnd1, *fnd2, *fnd3;
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

int hash(char s[]) // not implemented
{
    return 0;
}

int cmp(int va, int vb, char ca[], char cb[]) // compare function, as requested in task 2
{
    int l = strcmp(ca, cb);
    if (l == 0) return va > vb;
    else return l > 0;
}


void sortare(bruh b[], int cnt, int(*cr)(int va, int vb, char ca[], char cb[])) // bubble sort function using pointer to cmp, as requested in task 2
{
    for(int i = 1; i <= cnt; i ++)
        for(int j = cnt; j > i; j --)
        {
            if(cr(b[j-1].views, b[j].views, b[j-1].p, b[j].p))
            {
                aux = b[j-1];
                b[j-1] = b[j];
                b[j] = aux;
            }
        }
    return;
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
    if (!f)
    {
        printf("Error opening master file!\n");
        return 0;
    }

    while(fgets(masterline, sizeof(masterline), f)) // commented in task 1, mostly the same
    {
        masterlinecount ++;

        masterline[strlen(masterline) - 1] = '\0';
        FILE *site = fopen(masterline, "r");

        if (!file_exists(masterline))
        {
            printf("Error opening %s\n", masterline);
            return 0;
        }

        else
        {
            memset(wholefile, '\0', 500000);

            strcpy(bd[masterlinecount].file, masterline);

            fgets(line, sizeof(line), site);

            k = strtok(line, " ");

            strcpy(bd[masterlinecount].link, k);

            k = strtok(NULL, " "); // skip one
            k = strtok(NULL, " ");

            bd[masterlinecount].views = atoi(k);

            inp = false;

            while(fgets(line, sizeof(line), site))
            {
                strcat(wholefile, line);

                start = strstr(line, "<title>"); 
                end = strstr(line, "</title>");
                if(start != NULL)
                {
                    strncpy(title, line + 7, strlen(line) - 16);
                    title[strlen(line) - 16] = '\0';
                    strcpy(bd[masterlinecount].title, title);
                }
                start = strstr(line, "<p");
                end = strstr(line, "</p"); // get what is inside paragraph, used for comparison later

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
                    //printf(cline);
                    //printf("\n");
                }

            }
            strcpy(bd[masterlinecount].content, wholefile);
            bd[masterlinecount].checksum = hash(wholefile);

        }

        fclose(site);
    }
    gets(input); 

    k = strtok(input, " ");
    while(k != NULL) // split input into words
    {
        wordcnt++;
        strcpy(words[wordcnt], k);
        k = strtok(NULL, " ");
    }

    for (int i = 1; i <= masterlinecount; i ++)
    {
        char spaces[10001];
        strcpy(spaces, " ");
        for(int j = 0; j < strlen(bd[i].content); j ++)
            if(strchr(",?!;<>\'\"\\\n()[]{}",bd[i].content[j])) strcat(spaces, " ");
                else {
                        char auxc[2];
                        auxc[0] = bd[i].content[j];
                        auxc[1] = '\0';
                        strcat(spaces, auxc);
                } 
        strcat(spaces, " \0");

        // spaces is the content, but modified to replace characters in the string ",?!;<>\'\"\\\n()[]{}" with " " for an easier search
        for(int j = 1; j <= wordcnt; j++) 
        {
            char wordspc[1001], worddotend[1001], worddotstart[1001], colonend[1001];

            // creating modified versions of the word we're looking for in order to avoid a 'subword' that is part of a bigger word
            // instead of this I should have checked if character to the left is a letter and character to the right is a letter

            strcpy(wordspc, " ");
            strcat(wordspc, words[j]);
            strcat(wordspc, " ");

            strcpy(worddotend, " ");
            strcat(worddotend, words[j]);
            strcat(worddotend, ".");

            strcpy(worddotstart, ".");
            strcat(worddotstart, words[j]);
            strcat(worddotstart, " ");

            strcpy(colonend, " ");
            strcat(colonend, words[j]);
            strcat(colonend, ":");

            fnd = strstr(spaces, wordspc);
            fnd1 = strstr(spaces, worddotend);
            fnd2 = strstr(spaces, worddotstart);
            fnd3 = strstr(spaces, colonend);
            if(fnd != NULL || fnd1 != NULL || fnd2 != NULL || fnd3 != NULL)
            {
                bd2[++goodwords] = bd[i]; // store sites that have at least one of the words in them in bd2
                //printf("%d\n", bd2[goodwords].checksum);
                break; // break so sites don't get added twice
            }
        }
    }

    int (*cmpc)(const int, const int, const char[], const char[]) = {cmp};
    sortare(&bd2, goodwords, cmpc); // sort the sites

    for(int i = 1; i <= goodwords; i ++) // print links in sorted order
        printf("%s\n", bd2[i].link);

    fclose(f);
    return 0;
}
