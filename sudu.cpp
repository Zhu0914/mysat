//
// Created by lenovo on 2021/9/9.
//
#include "global.h"
using namespace std;
int a[15][15],ans_pre,ans[15][15],b[15][15];
bool square[10][10],lie[10][10],hang[10][10],flag[15][15];
bool check;
bool f[15];
int c[15];
int difficult;

void SetColor(unsigned short ForeColor=7,unsigned short BackGroundColor=0)
{
    HANDLE hCon=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hCon,ForeColor|BackGroundColor);
}
int ge(int x,int y)
{
    return(((x-1)/3)*3+(y-1)/3+1);
}

int print(){
    SetColor(15);
    printf("╔━━━┳━━━┳━━━");
    SetColor(9);
    printf("┳");
    SetColor(15);
    printf("━━━┳━━━┳━━━");
    SetColor(9);
    printf("┳");
    SetColor(15);
    printf("━━━┳━━━┳━━━┓\n");
    for(int i=1;i<=9;i++)
    {
        for(int j=1;j<=9;j++)
        {
            if(a[i][j]==0)
            {
                if(j==4||j==7) SetColor(9);
                cout<<"┃   ";
                SetColor(15);
                if (j==9)  cout<<"┃";
            }else
            {
                if(j==4||j==7) SetColor(9);
                cout<<"┃ ";
                SetColor(15);
                if(b[i][j]==0) SetColor(4);
                cout<<a[i][j]<<" ";
                SetColor(15);
                if (j==9) cout<<"┃";
            }
        }
        cout<<endl;
        if(i==3||i==6)
        {
            SetColor(9);
            cout<<"┣━━━╋━━━╋━━━";
            cout<<"╋";
            cout<<"━━━╋━━━╋━━━";
            cout<<"╋" ;
            cout<<"━━━╋━━━╋━━━┫";
            cout<<endl;
            continue;
        }
        if(i!=9)
        {
            cout<<"┣━━━╋━━━╋━━━";
            SetColor(9);
            cout<<"╋";
            SetColor(15);
            cout<<"━━━╋━━━╋━━━";
            SetColor(9);
            cout<<"╋" ;
            SetColor(15);
            cout<<"━━━╋━━━╋━━━┫";
            cout<<endl;
        }

        else
        {
            SetColor(15);
            printf("┗━━━┻━━━┻━━━");
            SetColor(9);
            printf("┻");
            SetColor(15);
            printf("━━━┻━━━┻━━━");
            SetColor(9);
            printf("┻");
            SetColor(15);
            printf("━━━┻━━━┻━━━┛\n");
        }
        SetColor(15);
    }
}

int print_y(){
    SetColor(15);
    printf("╔━━━┳━━━┳━━━");
    SetColor(9);
    printf("┳");
    SetColor(15);
    printf("━━━┳━━━┳━━━");
    SetColor(9);
    printf("┳");
    SetColor(15);
    printf("━━━┳━━━┳━━━┓\n");
    for(int i=1;i<=9;i++)
    {
        for(int j=1;j<=9;j++)
        {
            if(ans[i][j]==0)
            {
                if(j==4||j==7) SetColor(9);
                cout<<"┃   ";
                SetColor(15);
                if (j==9)  cout<<"┃";
            }else
            {
                if(j==4||j==7) SetColor(9);
                cout<<"┃ ";
                SetColor(15);
                if(b[i][j]==0) SetColor(4);
                cout<<ans[i][j]<<" ";
                SetColor(15);
                if (j==9) cout<<"┃";
            }
        }
        cout<<endl;
        if(i==3||i==6)
        {
            SetColor(9);
            cout<<"┣━━━╋━━━╋━━━";
            cout<<"╋";
            cout<<"━━━╋━━━╋━━━";
            cout<<"╋" ;
            cout<<"━━━╋━━━╋━━━┫";
            cout<<endl;
            continue;
        }
        if(i!=9)
        {
            cout<<"┣━━━╋━━━╋━━━";
            SetColor(9);
            cout<<"╋";
            SetColor(15);
            cout<<"━━━╋━━━╋━━━";
            SetColor(9);
            cout<<"╋" ;
            SetColor(15);
            cout<<"━━━╋━━━╋━━━┫";
            cout<<endl;
        }

        else
        {
            SetColor(15);
            printf("┗━━━┻━━━┻━━━");
            SetColor(9);
            printf("┻");
            SetColor(15);
            printf("━━━┻━━━┻━━━");
            SetColor(9);
            printf("┻");
            SetColor(15);
            printf("━━━┻━━━┻━━━┛\n");
        }
        SetColor(15);
    }
}
int dfs(int x,int y)
{
    if(!check) return 0;
    if(x==0&&y==9)
    {
        //   print();
        check=false;
        return 0;
    }
    if(a[x][y]==0)
        for(int j=1;j<=9;j++)
        {
            int i=c[j];
            if(square[ge(x,y)][i]&&lie[y][i]&&hang[x][i])
            {
                square[ge(x,y)][i]=false;
                lie[y][i]=false;
                hang[x][i]=false;
                ans[x][y]=i;

                if(y==1) dfs(x-1,9);else dfs(x,y-1);

                square[ge(x,y)][i]=true;
                lie[y][i]=true;
                hang[x][i]=true;
                if(!check) return 0;
            }
        }
    if(!check) return 0;
    if(a[x][y]!=0) if(y==1) dfs(x-1,9);else dfs(x,y-1);
}

int work(int x){
    if(x==10)
    {
        return 0;
    }
    int i=1;
    int y=rand()%9+1;
    while(!f[y]) y=rand()%9+1;
    f[y]=false;
    c[x]=y;
    work(x+1);
}
void init(){
    srand(time(NULL));
    memset(a,0,sizeof(a));
    memset(lie,true,sizeof(lie));
    memset(hang,true,sizeof(hang));
    memset(square,true,sizeof(square));
    memset(f,true,sizeof(f));
    check=true;
    work(1);
    memset(a,sizeof(a),0);
    check=true;
    dfs(9,9);
    memcpy(a,ans,sizeof(ans));
//    print();
    printf("请输入难度系数 1~3\n");
    difficult=0;
    while(difficult>3||difficult<1) cin>>difficult;
}
void run(){
    int sum=0;
    switch(difficult){
        case 1:sum=20;
            break;
        case 2:sum=40;
            break;
        case 3:sum=60;
            break;

    }
    int i=1;
    while(i<=sum)
    {
        int x,y;
        x=rand()%9+1;
        y=rand()%9+1;
        while(a[x][y]==0)
        {
            x=rand()%9+1;
            y=rand()%9+1;
        }
        a[x][y]=0;
        i++;
    }
}
int sudu(void)
{
    init();
    run();
    system("cls");
    memcpy(b,a,sizeof(a));
    print();
    int xx,yy,zz;


/*	for(int i=1;i<=9;i++)
	{
		for(int j=1;j<=9;j++)
			cout<<a[i][j];
		cout<<endl;
	}*/

    cout<<"请输入如 'x y z' 即可在(x,y) 填入'z' //x,y的范围均为0~9\n\n";
    cout<<"你可以输入 x y 0 以清空(x,y)\n\n";
    cout<<"你可以输入 0 0 0 直接获得正确答案\n\n";
    while(cin>>xx>>yy>>zz)
    {
        if(xx==0&&yy==0&&zz==0)
        {
            system("cls");
            print_y();
            break;
        }
        if(b[xx][yy]==0) a[xx][yy]=zz;
        system("cls");
        print();
        cout<<"请输入如 'x y z' 即可在(x,y) 填入'z' //x,y的范围均为0~9\n\n";
        cout<<"你可以输入 x y 0 以清空(x,y)\n\n";
        cout<<"你可以输入 0 0 0 直接获得正确答案\n\n";
        if(b[xx][yy]!=0)
        {
            SetColor(4);
            cout<<"你填入的格子已被填入\n";
            SetColor(15);
        }
    }


    system("pause");
    return 0;
}