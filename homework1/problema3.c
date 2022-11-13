#include<stdio.h>

void dec_to_bin(int n,char *s) //transforma numarul n din baza 8 in baza 2
{
    int poz=7;
    for(int i=0;i<=7;i++)
        s[i]='0';
    while(n)
    {
        if(n%2==1)
            s[poz]='1';
        n=n/2;
        poz--;
    }
}
void inmultire(int A[8][8],int B[8][8],int rez[8][8])//inmulteste doua matrici
{
     for(int i=0;i<=7;i++)
        for(int j=0;j<=7;j++)
            rez[i][j]=0;
    for(int i=0;i<=7;i++)
        for(int j=0;j<=7;j++)
        {
            for(int t=0;t<=7;t++)
                rez[i][j]|=A[i][t]&B[t][j];
        }

}
void transpus(int A[8][8],int At[8][8])
{
    for(int i=0;i<=7;i++)
        for(int j=0;j<=7;j++)
        At[i][j]=A[j][i];
}
int sum_X_0(int m[][8])
{
    int ans=0,ok=1;
    //matricea stanga sus
    for(int i=0;i<4;i++)//numar liniile
    {
        ok=1;
        for(int j=0;j<=4;j++)
            if(m[i][j]==0)
            ok=0;
        ans+=ok;
        ok=1;
        for(int j=0;j<=4;j++)
            if(m[j][i]==0)//pentru coloane
            ok=0;
        ans+=ok;

    }
    ok=1;
    for(int i=0,j=0;i<4&&j<4;i++,j++)
        if(m[i][j]==0)
        ok=0;
    ans+=ok;
    ok=1;
    for(int i=0,j=3;i<4&&j>=0;i++,j--)
        if(m[i][j]==0)
        ok=0;
    ans+=ok;
    //matricea dreapta sus
    for(int i=0;i<4;i++)//numar liniile
    {
        ok=1;
        for(int j=4;j<=7;j++)
            if(m[i][j]==0)
            ok=0;
        ans+=ok;
        ok=1;
        for(int j=0;j<=4;j++)
            if(m[j][i+4]==0)//pentru coloane
            ok=0;
        ans+=ok;

    }
    ok=1;
    for(int i=0,j=4;i<4&&j<8;i++,j++)
        if(m[i][j]==0)
        ok=0;
    ans+=ok;
    ok=1;
    for(int i=0,j=7;i<4&&j>=4;i++,j--)
        if(m[i][j]==0)
        ok=0;
    ans+=ok;
    //matricea stanga jos
    for(int i=4;i<8;i++)//numar liniile
    {
        ok=1;
        for(int j=0;j<=4;j++)
            if(m[i][j]==0)
            ok=0;
        ans+=ok;
        ok=1;
        for(int j=4;j<=8;j++)
            if(m[j][i-4]==0)//pentru coloane
            ok=0;
        ans+=ok;

    }
    ok=1;
    for(int i=4,j=0;i<8&&j<4;i++,j++)
        if(m[i][j]==0)
        ok=0;
    ans+=ok;
    ok=1;
    for(int i=4,j=3;i<8&&j>=4;i++,j--)
        if(m[i][j]==0)
        ok=0;
    ans+=ok;
    //matricea dreapta jos
    for(int i=4;i<8;i++)//numar liniile
    {
        ok=1;
        for(int j=4;j<8;j++)
            if(m[i][j]==0)
            ok=0;
        ans+=ok;
        ok=1;
        for(int j=4;j<8;j++)
            if(m[j][i]==0)//pentru coloane
            ok=0;
        ans+=ok;
    }
    ok=1;
    for(int i=4,j=4;i<8&&j<8;i++,j++)
        if(m[i][j]==0)
        ok=0;
    ans+=ok;
    ok=1;
    for(int i=4,j=7;i<8&&j>=4;i++,j--)
        if(m[i][j]==0)
        ok=0;
    ans+=ok;
    return ans;
}
int bin_to_dec(char *s)//transforma din baza 2 in baza 8
{
    int x=0,p=1;
    for(int i=7;i>=0;i--)
    {
        if(s[i]=='1')
        x+=p;
    p=p*2;
    }
    return x;
}
int main()
{
    int r1,r2,r3,ok;
    char s[8];
    int A[8][8],At[8][8],A2[8][8],AAt[8][8],i,j,x;
    for(i=0;i<=7;i++)
    {
        scanf("%d",&x);
        dec_to_bin(x,s);
        for (j=0;j<=7;j++)
            if(s[j]=='0')
            A[i][j]=0;
        else
            A[i][j]=1;
    }
    transpus(A,At);
    inmultire(A,A,A2);
    inmultire(A,At,AAt);
    r1=sum_X_0(A);
    r2=sum_X_0(AAt);
    r3=sum_X_0(A2);
    if(r1>=r2&&r1>=r3)
        ok=1;
    if(r2>r1&&r2>=r3)
    ok=2;
        if(r3>r1&&r3>r2)
        ok=3;
    for(int i=0;i<=7;i++)
    {
        for(int j=0;j<=7;j++)
        {
            if(ok==1&&A[i][j]==1)
            s[j]='1';
            else
                if(ok==2&&AAt[i][j]==1)
                s[j]='1';
            else
                if(ok==3&&A2[i][j]==1)
                s[j]='1';
            else
                s[j]='0';


        }
        printf("%d\n",bin_to_dec(s));

    }
    return 0;
}