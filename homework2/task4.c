#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char necword[1001], badword[1001], wholefile[500001], masterline[1001], line[1001], title[1001], *k, *start, *end, cline[1001], input[1001], words[101][101], *fnd;
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
    int checksum; // found key
    int key; // official key
} bruh;

bruh bd[1001], bd2[1001], aux;

int rotr(char x, int k) // rotr function, as requested in task4
{
    if(k == 0 || x == 0) return x;
    char c[8], d[8];
    for(int i=7; i>=0; i--) // from b10 to b2
    {
        c[i] = x%2;
        x/=2;
    }
    for(int i = 0; i <= 7; i++) // move the bits
    {
        d[i] = c[(i - k + 8) % 8];
    }
    int lv = 1, n = 0;
    for(int i=7; i>=0; i--) // from b2 to b10
    {
        n += lv * d[i];
        lv*=2;
    }
    return n;
}

int rotl(char x, int k) // rotl function, as requested in task4
{
    if(k == 0 || x == 0) return x;
    char c[8], d[8];
    for(int i=7; i>=0; i--) // from b10 to b2
    {
        c[i] = x%2;
        x/=2;
    }
    for(int i = 0; i <= 7; i++) // move the bits
    {
        d[i] = c[(i + k + 8) % 8];
    }
    int lv = 1, n = 0;
    for(int i=7; i>=0; i--) // from b2 to b10
    {
        n += lv * d[i];
        lv*=2;
    }
    return n;
}

int hash(char s[]) // hash function to calculate keys
{
    int a = 0;
    for (int i = 0; i < strlen(s); i ++)
    {
        if(i%2 == 0) a = a ^ rotl(s[i], i%8); // xorsum calculation
        else a = a ^ rotr(s[i], i%8);
    }
    return a;
}

int cmp(int va, int vb) // unused
{
    return va < vb;
}

void sortare(bruh b[], int cnt, int(*cr)(int va, int vb)) // unused
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

            k = strtok(NULL, " ");

            bd[masterlinecount].key = atoi(k); // get key as int

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
                    if(end == NULL) strcat(bd[masterlinecount].content, start + 1);
                    else
                    {
                        inp = false;
                        memset(cline, '\0', 1000);
                        strncpy(cline, start + 1, strlen(start) - 6);
                        strcat(bd[masterlinecount].content, cline);
                        strcat(bd[masterlinecount].content, "\n");
                    }
                }
                else if(inp)
                {
                    if(end == NULL) strcat(bd[masterlinecount].content, line);
                    else
                    {
                        inp = false;
                        memset(cline, '\0', 1000);
                        strncpy(cline, line, strlen(line) - 5);
                        strcat(bd[masterlinecount].content, cline);
                        strcat(bd[masterlinecount].content, "\n");
                    }
                }
            }

            bd[masterlinecount].checksum = hash(wholefile); // calculate hash of content

        }
        fclose(site);
    }
    while(gets(input))
    {
        bool websitefound = false;
        for(int i = 1; i <= masterlinecount; i ++)
        {
            if(!strcmp(input, bd[i].link)) // check if filename matches input
            {
                websitefound = true;
                if(bd[i].key == bd[i].checksum) printf("Website safe!\n"); // compare keys
                else printf("Malicious website! Official key: %d. Found key: %d\n",bd[i].key, bd[i].checksum);
            }
        }
        if(!websitefound) printf("Website not found!\n"); // if no site matches input
    }

    fclose(f);
    return 0;
}
