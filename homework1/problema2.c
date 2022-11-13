#include<stdio.h>


int verifica(int M[101][101],int x,int y,int m,int *x1, int *x2, int *y1, int *y2) //Am locatia unui nebun si verific daca exista alti nebuni pe diagonale
{
    int co=0;

    for(int i=x-1,j=y+1;i>=0&&j<m;i--,j++)//diagonala dreapta sus
        if(M[i][j]==1)
            {
                co++;
                *x1 = x; 
                *x2 = i;
                *y1 = y;
                *y2 = j;

                //salvez perechea
            }
    for(int i=x+1,j=y+1;i<m&&j<m;i++,j++)//diagonala dreapta jos
        if(M[i][j]==1)
            {
                co++;
                *x1 = x;
                *x2 = i;
                *y1 = y;
                *y2 = j;

                //salvez perechea
            }

    for(int i=x-1,j=y-1;i>=0&&j>=0;i--,j--)//diagonala stanga sus
        if(M[i][j]==1)
            {
                co++;
                *x1 = x;
                *x2 = i;
                *y1 = y;
                *y2 = j;

                //salvez perechea
            }

    for(int i=x+1,j=y-1;i<m&&j>=0;i++,j--)//diagonala stanga jos
        if(M[i][j]==1)
            {
                co++;
                *x1 = x;
                *x2 = i;
                *y1 = y;
                *y2 = j;

                //salvez perechea
            }

    return co;//scadem 4 deoarece considerram perechea x,y x,y la fiecare for
}

void fill(int N[101][101],int x,int y,int m) //Pun 1 pe diagonale in matricea N
{
    for(int i=x-1,j=y+1;i>=0&&j<m;i--,j++)//diagonala dreapta sus
        N[i][j] = 1;

    for(int i=x+1,j=y+1;i<m&&j<m;i++,j++)//diagonala dreapta jos
        N[i][j] = 1;

    for(int i=x-1,j=y-1;i>=0&&j>=0;i--,j--)//diagonala stanga sus
        N[i][j] = 1;

    for(int i=x,j=y;i<m&&j>=0;i++,j--)//diagonala stanga jos
        N[i][j] = 1;
}

int main()
{
    int m,n,x,y,M[101][101],N[101][101],ans=0,x1=0,x2=0,y1=0,y2=0,freeslot = 0;

    scanf("%d",&m);
    scanf("%d",&n);

    //Initializez cu 0
    for(int i=0;i<m;i++)
        for(int j=0;j<m;j++)
            {
                M[i][j]=0;
                N[i][j]=0;
            }
    
    //"Asez" nebunii pe tabla
    for(int j=0;j<n;j++)
    {
        scanf("%d%d",&x,&y);
        M[x][y]=1;
    }

    //Verific daca exista nebuni care se ataca
    for(int i=0;i<m;i++)
        for(int j=0;j<m;j++)
        {
            if(M[i][j]==1)
                ans+=verifica(M,i,j,m,&x1,&x2,&y1,&y2);
        }

    //printf("%d %d %d %d\n", x1, y1, x2, y2); //DEBUG

    printf("%d\n",ans/2); //Impart la 2 ca sa evitam simetricele

    //Cazul in care avem doar o pereche
    if(ans/2==1)
    {
        //Creez o matrice cu toate spatiile care sunt indisponibile daca elimin nebunul de pe spatiul x1, y1
        M[x1][y1] = 0;

        for(int i=0;i<m;i++)
            for(int j=0;j<m;j++)
                if(M[i][j] == 1)
                    fill(N, i, j, m);

        for(int i=0;i<m;i++)
        {
            for(int j=0;j<m;j++)
            {
                if(!N[i][j]) freeslot = 1; //Verific daca exista spatii goale
                //printf("%d ", N[i][j]); //DEBUG
            }
            //printf("\n"); //DEBUG
        }

        if(freeslot)
        {
            printf("DA\n");
            return 0;
        }

        for(int i=0;i<m;i++)
            for(int j=0;j<m;j++)
            {
                N[i][j]=0;
            }
        
        M[x1][y1] = 1;
        //Creez o matrice cu toate spatiile care sunt indisponibile daca elimin nebunul de pe spatiul x2, y2
        M[x2][y2] = 0;

        for(int i=0;i<m;i++)
            for(int j=0;j<m;j++)
                if(M[i][j] == 1)
                    fill(N, i, j, m);

        for(int i=0;i<m;i++)
        {
            for(int j=0;j<m;j++)
            {
                if(!N[i][j]) freeslot = 1; //Verific daca exista spatii goale
                //printf("%d ", N[i][j]); //DEBUG
            }
            //printf("\n"); //DEBUG
        }

        if(freeslot)
        {
            printf("DA\n");
            return 0;
    }
	}    
    printf("NU\n");
    return 0;
}

