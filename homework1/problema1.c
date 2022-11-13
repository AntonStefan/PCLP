#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int is_anagram(char *s1,char *s2)
{
    int v1[26]= {0},v2[26]= {0};
    if(strlen(s1)!=strlen(s2))
        return 0;
    for(int i=0; i<strlen(s1); i++)
    {
        v1[s1[i]-'a']++;
        v2[s2[i]-'a']++;
    }
    for(int i=0; i<=25; i++)
        if(v1[i]!=v2[i])
            return 0;
    return 1;
}

double compute_grade(char *s1,char *s2)
{
    if(is_anagram(s1,s2)==0)
        return -1;
    int i;
    double grad=0;
    for(i=0; i<strlen(s1); i++)
        if(s2[i]!=s1[i])
            grad++;
    return grad/(double)(strlen(s1));
}

int main()
{
    int n;
    char s1[51],s2[51],v[1001][2][51];
    scanf("%d",&n);
    for(int i=0; i<n; i++)
        scanf("%s%s",&v[i][0],&v[i][1]);
    for(int i=0; i<n; i++)
        for(int m=i+1; m<n; m++)
        {
            if(compute_grade(v[i][0],v[i][1])<compute_grade(v[m][0],v[m][1]))
            {
                char aux[51];
                strcpy(aux,v[i][0]);
                strcpy(v[i][0],v[m][0]);
                strcpy(v[m][0],aux);
                strcpy(aux,v[i][1]);
                strcpy(v[i][1],v[m][1]);
                strcpy(v[m][1],aux);
            }
             if(compute_grade(v[i][0],v[i][1])==compute_grade(v[m][0],v[m][1]))
                if(strcmp(v[i][0],v[m][0])<0)
            {
                char aux[51];
                strcpy(aux,v[i][0]);
                strcpy(v[i][0],v[m][0]);
                strcpy(v[m][0],aux);
                strcpy(aux,v[i][1]);
                strcpy(v[i][1],v[m][1]);
                strcpy(v[m][1],aux);
            }

        }

    for(int i=0; i<n; i++)
    {
        printf("%s %s",v[i][0],v[i][1]);
        printf("\n");
    }
    return 0;
}