#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int **M;
int max(int a, int b) { return a > b ? a : b; };

int bottom_up_dp(int n, int *s, int *v, int C)
{
    int i, j;
    M = (int **)malloc(sizeof(int *) * (n+1));
    for(int i=0; i<=n; i++){
        M[i] = (int*)malloc(sizeof(int)* (C+1));
    }
    for(int i=0; i<=n; i++){
        for(int j=0; j<=C; j++){
            M[i][j] = 0;
        }
    }
    for(i=1; i<=n; i++){
        for(j=1; j<=C; j++){
            if(j >= s[i]){
                M[i][j] = max(M[i-1][j], (M[i-1][j-s[i]]+v[i]));
            }
            else{
                M[i][j] = M[i-1][j];
            }
        }
    }
    return M[n][C];
}


int main ()
{
    int n,C;
    int function;
    int *s;
    int *v;
    int i,j;
    printf("Enter the number of items n:\n");
    scanf("%d",&n);
    printf("Enter the capacity C:\n");
    scanf("%d",&C);
    s = (int *) malloc(sizeof(int) * (n+1));
    v = (int *) malloc(sizeof(int) * (n+1));

    printf("Enter the sizes of items (as a list, separate by spacing:\n");
    for (i=1;i<=n;i++)
        scanf("%d",&s[i]);

    printf("Enter the values of items (as a list, separate by spacing:\n");
    for (i=1;i<=n;i++)
        scanf("%d",&v[i]);

    printf("The maximum value is: %d \n", bottom_up_dp(n,s,v,C));

}
