/*	Test thu vien winbgim.h	*/
#include <windows.h>
#include <conio.h>
#include <iostream>
#include <time.h>
#include <stack>
#include <winbgim.h>
#include <vector>

using namespace std;

//Console
void gotoxy(int x, int y)
{
    static HANDLE h = NULL;
    if(!h)
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = { x, y };
    SetConsoleCursorPosition(h,c);
}


void textcolor(int x)
{
    HANDLE mau;
    mau=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(mau,x);
}

void XoaManHinh()
{
    HANDLE hOut;
    COORD Position;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    Position.X = 0;
    Position.Y = 0;
    SetConsoleCursorPosition(hOut, Position);
}

//Khai bao
typedef pair<int,int> ii;
typedef pair<ii,ii> iii;

stack<ii> Stack;
vector<iii> SS;


//Game
int Random(int minN, int maxN)
{
    return minN + rand() % (maxN + 1 - minN);
}


void vekhung(int a[][100])
{
    for(int i = 11; i <= 79; i+=2)
    {
        gotoxy(i,10);
        cout << (char)205;
        gotoxy(i,30);
        cout << (char)205;
        if (i+1 <= 79)
        {
            gotoxy(i+1,10);
            cout << (char)209;
            gotoxy(i+1,30);
            cout << (char)207;

        }
        a[10][i]=a[30][i]= 0;
        a[10][i+1]=a[30][i+1]=0;
    }
    for(int i = 11; i <= 29; i+=2)
    {
        gotoxy(10,i);
        cout << (char)186;
        gotoxy(80,i);
        cout << (char)186;
        if (i+1 <= 29)
        {
            gotoxy(10,i+1);
            cout << (char)199;
            gotoxy(80,i+1);
            cout << (char)182;
        }
        a[i][10]=a[i][80]= 0;
        a[i+1][10]=a[i+1][80]=0;
    }
    a[10][10] = 0;
    gotoxy(80,30);
    cout << (char)188;
    gotoxy(10,10);
    cout << (char)201;
    gotoxy(80,10);
    cout << (char)187;
    gotoxy(10,30);
    cout << (char)200;
    for(int i = 11; i <= 29; i++)
        for(int j = 11; j <= 79; j++)
        {
            if (i%2==0)
            {
                gotoxy(j,i);
                if ((j%2==0))
                    cout << (char)197;
                else
                    cout << (char)196;
                a[i][j] = 0;
            }
            else if (j%2==0)
            {
                gotoxy(j,i);
                cout << (char)179;
                a[i][j] = 0;
            }
        }
    gotoxy(0,31);
    textcolor(0);
}

void Init(int a[][100])
{
    for(int i = 0; i < 100; i++)
        for(int j = 0; j < 100; j++)
            a[i][j] = 2;
}

bool check(int i,int j)
{
    bool k = (i>10 && i<30 && j>10 && j<80);
    return k;
}

void Loang(int i,int j,int a[100][100])
{
    if (check(i,j) && a[i][j]==1)
    {
        a[i][j]=3;
        gotoxy(j,i);
        cout << (char)177;
        Loang(i-1,j,a);
        Loang(i,j+1,a);
        Loang(i+1,j,a);
        Loang(i,j-1,a);
        Sleep(10);
    }
}

void xoaTuong(int u,int v,int a[][100])
{
    a[u][v] = 1;
    gotoxy(v,u);
    //cout << (char)177;
    //cout << (char)254;
    cout << '+';
}

void Xaydung(int a[][100])
{
    /*
        Cat dat
        + 1 : O da tham
        + 3 : Wall
        + 2 : O trong
        + 5 : Loi ra
        P/S : Trinh do minh con cui bap nen phai them ham tao vat can
    */
#define p1 first
#define p2 second

//    int x = Random(11,28);
//    int y = Random(11,79);
//    while (a[x][y]!=2)
//    {
//        x = Random(0,28);
//        y = Random(x,79);
//    }
//    cout << x << " " << y << endl;
    Stack.push(ii(11,11)); // day (u,v) vao ngan xep
    a[11][11] = 1;
    gotoxy(11,11);
    //cout << (char)177;
    cout << '+';
    ii tmp;
    while (Stack.empty()==0)
    {
        tmp = Stack.top();
        int u = tmp.p1;
        int v = tmp.p2;
        if (a[u-2][v]==2 && check(u-2,v)) SS.push_back(iii(ii(u-1,v),ii(u-2,v)));
        if (a[u][v+2]==2 && check(u,v+2)) SS.push_back(iii(ii(u,v+1),ii(u,v+2)));
        if (a[u+2][v]==2 && check(u+2,v)) SS.push_back(iii(ii(u+1,v),ii(u+2,v)));
        if (a[u][v-2]==2 && check(u,v-2)) SS.push_back(iii(ii(u,v-1),ii(u,v-2)));
        if (SS.empty()==1) Stack.pop();
        else
        {
            int t = Random(0,(int)SS.size()-1);
            tmp = SS[t].p2;
            Stack.push(tmp);
            tmp = SS[t].p1;
            xoaTuong(tmp.p1,tmp.p2,a);
            SS.erase(SS.begin(),SS.end());
        }
        if (Stack.empty()==0)
        {
            tmp = Stack.top();
            u = tmp.p1;
            v = tmp.p2;
            gotoxy(v,u);
            //cout << (char)177;
            //cout << (char)254;
            cout << '+';
            a[u][v]=1;
        }
        Sleep(5);
    }
    textcolor(10);
    gotoxy(0,31);
}

void mamau()
{
    for(int i = 0; i <= 255; i++)
    {
//        textcolor(15); cout << i << " ";
//        textcolor(i); cout << " " << endl;
    }
}

void outputArr(int a[100][100])
{
    for(int i = 10; i <= 30; i++)
    {
        for(int j = 10; j <= 80; j++)
            cout << a[i][j];
        cout << endl;
    }
}


void khoitao(int a[][100])
{
    int x = Random(11,39);
    int y = Random(11,79);
    while (a[x][y]!=1)
    {
        x = Random(11,39);
        y = Random(11,79);
    }
    a[x][y]=100;
    gotoxy(y,x);
    textcolor(196);
    cout << 'S';
    while (a[x][y]!=1)
    {
        x = Random(11,79);
        y = Random(11,39);
    }
    a[x][y]=200;
    gotoxy(y,x);
    textcolor(19);
    cout << 'F';
    gotoxy(0,31);
}

void Buildhoanchinh(int a[][100])
{
    Init(a);
    textcolor(15);
    vekhung(a);
    textcolor(175);
    //textcolor(10);
    Xaydung(a);
    khoitao(a);
//    for(int i = 11 ; i <= 29; i++)
//        for(int j = 11; j <= 79; j++)
//            if (a[i][j]==1) Loang(i,j,a);
    textcolor(15);
    gotoxy(0,31);
}

void BFS(int a[][100])
{

}

int main()
{
    srand(time(0));
    int a[100][100];
    mamau();
    Buildhoanchinh(a);
    return 0;
}
