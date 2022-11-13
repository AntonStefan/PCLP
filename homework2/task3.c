#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char necword[1001], badword[1001], wholefile[500001], masterline[1001], line[1001], title[1001], *k, *start, *end, cline[1001], input[1001], words[101][101], *fnd, *fnd1, *fnd2, *fnd3, *fnd4, *fnd5;
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

int hash(char s[])
{
    return 0;
}

int cmp(int va, int vb) // compare function, as requested in task 3
{
    return va < vb;
}

void sortare(bruh b[], int cnt, int(*cr)(int va, int vb)) // bubble sort function using pointer to cmp, as requested in task 3
{
    for(int i = 1; i <= cnt; i ++)
        for(int j = cnt; j > i; j --)
        {
            if(cr(b[j-1].views, b[j].views))
            {
                aux = b[j-1];
                b[j-1] = b[j];
                b[j] = aux;
            }
        }
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
                end = strstr(line, "</p");

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
            strcpy(bd[masterlinecount].content, wholefile);
            bd[masterlinecount].checksum = hash(wholefile);

        }
        fclose(site);
    }
    gets(input);

    k = strtok(input, " ");
    while(k != NULL)
    {
        if(k[0] == '-') strcpy(badword, k + 1); // bad words strats with '-'
        else if(k[0] == '\"') // for sequences of words starting with '\"'
        {
            if(k[strlen(k) - 1] == '\"') strncpy(necword, k + 1, strlen(k) - 2); // if there is a single word
            char aux2[1001];
            strcpy(aux2, k+1);
            strcpy(k, aux2);
            if(k[strlen(k) - 1] != '\"') while(true)
                {
                    if(k[strlen(k) - 1] == '\"')
                    {
                        char aux[1001];
                        int t = strlen(k);
                        strncpy(aux, k, strlen(k) - 1);
                        aux[t - 1] = '\0';
                        strcat(necword, aux);
                        break;
                    }
                    else
                    {
                        strcat(necword, k);
                        strcat(necword, " ");
                    }
                    k = strtok(NULL, " ");
                }

        }
        else
        {
            wordcnt++;
            strcpy(words[wordcnt], k);
        }
        k = strtok(NULL, " ");
    }
    if(necword[0] != '\0') strncpy(words[++wordcnt], necword, strlen(necword));

    for (int i = 1; i <= masterlinecount; i ++)
    {
        //printf(bd[i].content);
        char spaces[10001];
        strcpy(spaces, " ");
        for(int j = 0; j < strlen(bd[i].content); j ++)
            if(strchr(",?!;<>\'\"\\\n()[]{}",bd[i].content[j])) strcat(spaces, " ");
            else
            {
                char auxc[2];
                auxc[0] = bd[i].content[j];
                auxc[1] = '\0';
                strcat(spaces, auxc);
            }
        strcat(spaces, " \0");
        for(int j = 1; j <= wordcnt; j++)
        {
            char wordspc[1001], worddotend[1001], worddotstart[1001], colonend[1001]; // explained at task 2

            strcpy(wordspc, " ");
            strcat(wordspc, words[j]);
            strcat(wordspc, " \0");

            strcpy(worddotend, " ");
            strcat(worddotend, words[j]);
            strcat(worddotend, ".\0");

            strcpy(worddotstart, ".");
            strcat(worddotstart, words[j]);
            strcat(worddotstart, " \0");

            strcpy(colonend, " ");
            strcat(colonend, words[j]);
            strcat(colonend, ":\0");

            fnd = strstr(spaces, wordspc);
            fnd1 = strstr(spaces, worddotend);
            fnd2 = strstr(spaces, worddotstart);
            fnd3 = strstr(spaces, colonend);
            if(fnd != NULL || fnd1 != NULL || fnd2 != NULL || fnd3 != NULL)
            {
                char badwordspc[1001], badworddotend[1001], badworddotstart[1001], badwordcolonend[1001]; // use the same finding technique for the bad word
                strcpy(badwordspc, " ");
                strcat(badwordspc, badword);
                strcat(badwordspc, " \0");

                strcpy(badworddotend, " ");
                strcat(badworddotend, badword);
                strcat(badworddotend, ".\0");

                strcpy(badworddotstart, ".");
                strcat(badworddotstart, badword);
                strcat(badworddotstart, " \0");

                strcpy(badwordcolonend, " ");
                strcat(badwordcolonend, badword);
                strcat(badwordcolonend, ":\0");

                fnd = strstr(spaces, badwordspc);
                fnd1 = strstr(spaces, badworddotend);
                fnd2 = strstr(spaces, badworddotstart);
                fnd3 = strstr(spaces, badwordcolonend);

                if((fnd == NULL && fnd1 == NULL && fnd2 == NULL && fnd3 == NULL) || badword[0] == '\0') bd2[++goodwords] = bd[i]; // if the bad word isn't found or if there is no bad word, store site in bd2
                break; // break so sites don't get added twice
            }
        }
    }

    int (*cmpc)(const int, const int) = {cmp};
    sortare(&bd2, goodwords, cmpc); // sort the sites

    for(int i = 1; i <= goodwords; i ++) // print links in sorted order
        printf("%s\n", bd2[i].link);

    fclose(f);
    return 0;
}
