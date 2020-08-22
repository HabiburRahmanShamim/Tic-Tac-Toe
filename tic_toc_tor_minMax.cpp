#include <bits/stdc++.h>
using namespace std;

char playground[3][3];
void initialize()
{
    int i, j;
    for(i = 0; i < 3; i++){
        for(j = 0; j < 3; j++)
            playground[i][j] = '_';

    }
}
void display()
{
    int i, j;
    for(i = 0; i < 3; i++){
        for(j = 0; j < 3; j++)
            printf("\t%c ", playground[i][j]);
        printf("\n\n\n");
    }
}
void user()
{
    int n, i, j;
    printf("Enter your position: ");
    scanf("%d", &n);
    if(n <= 3){
        i = 0;
        j = n-1;
    }
    else if(n <= 6 && n > 3){
        i = 1;
        j = n - 4;
    }
    else if(n <= 9 && n > 6){
        i = 2;
        j = n - 7;
    }
    if(playground[i][j] != '_'){
        printf("Error position!!!try again.\n\n");
        user();
    }
    else playground[i][j] = 'O';
}

char check(char grid[3][3])
{
    // Check Colum
    for(int i = 0; i < 3; i++)
    {
        if(grid[0][i] == grid[1][i] && grid[0][i] == grid[2][i] && grid[0][i] != '_')
            return grid[0][i];
    }

    // Check Row
    for(int i = 0; i < 3; i++)
    {
        if(grid[i][0] == grid[i][1] && grid[i][0] == grid[i][2] && grid[i][0] != '_')
            return grid[i][0];
    }

    // Check Diagonals
    if(grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2] && grid[0][0] != '_')
        return grid[0][0];
    if(grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0] && grid[0][2] != '_')
        return grid[0][2];
    
    // Check move available
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(grid[i][j] == '_')return '_';
        }
    }
    return 'D';
}

int minMax(char grid[3][3], bool isPc)
{
    char c = check(grid);
    if(c == 'D')return 0;
    if(c == 'X')return 1;
    if(c == 'O')return -1;
    int a;
    (isPc)?a = -100 : a = 100;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (grid[i][j] == '_')
            {
                if(isPc)
                {
                    grid[i][j] = 'X';
                    a = max(a, minMax(grid, !isPc));
                }
                else
                {
                    grid[i][j] = 'O';
                    a = min(a, minMax(grid, !isPc));
                }
                grid[i][j] = '_';
            }
        }
    }
    return a;
}
void cpu()
{
    int pi, pj, mx = -100;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(playground[i][j] == '_') 
            {
                playground[i][j] = 'X';
                int mx_val = minMax(playground, false);
                playground[i][j] = '_';
                if(mx_val > mx)
                {
                    pi = i, pj = j;
                    mx = mx_val;
                }
            }   
        }
    }
    playground[pi][pj] = 'X';
}

int main()
{
    char ch = '_';
    initialize();
    printf("You will be playing with 'O'\n\n");
    while(1){
        display();
        user();
        ch = check(playground);
        if(ch != '_')
            break;
        cpu();
        ch = check(playground);
        if(ch != '_')
            break;
    }

    if(ch == 'O')
        printf("\n\nCongratulation!!You Won!!!\n\n");
    else if(ch == 'X')
        printf("\n\nI Won!!!\n\n");
    else if(ch == 'D')
        printf("\n\nGame Draw!!!\n\n");
    display();

    return 0;
}
