# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <time.h>
//int matrix1[10][10];
//int matrix2[10][10];
//int matrix3[10][10];

int **matrix1;
int **matrix2;
int **matrix3;

int row1, col1, row2, col2;
int row_i, col_j;
int get_i, get_j;
void *Multiplication();

int main()
{
    float start_time, end_time, elapsed;

	FILE *f1;
    f1 = fopen("test2.txt", "r");


    int i, j, k;
    fscanf(f1,"%d %d",&row1,&col1);//getting size of matrices


    matrix1 = malloc(row1 * sizeof(int *));
    for(i = 0; i < row1; i++){
        matrix1[i] = malloc(col1 * sizeof(int));
    }//creating memory space for matrix1

    for(i=0;i<row1;i++)
    {
        for(j=0;j<col1;j++)
        {

            fscanf(f1,"%d",&matrix1[i][j]);
        }
    }//initialize matrix1

	fscanf(f1,"%d %d",&row2,&col2);
    //row2 = col1;
    //col2 = row1;


    matrix2 = malloc(row2 * sizeof(int *));
    for(i = 0; i < row2; i++){
        matrix2[i] = malloc(col2 * sizeof(int));
    }//creating memory space for matrix2


    for(i=0;i<row2;i++)
    {
        for(j=0;j<col2;j++)
        {
            fscanf(f1,"%d",&matrix2[i][j]);
        }
    }//initialize matrix2

    start_time = clock();
    pthread_t tid[row2][col1];
printf("123\n");

    matrix3 = malloc(row1 * sizeof(int *));
    for(i = 0; i < row1; i++){
        matrix3[i] = malloc(col2 * sizeof(int));
    }//creating memory space for matrix3

    for(i=0;i<row1;i++)
    {
        for(j=0;j<col2;j++)
        {
            matrix3[i][j]=0;
        }
    }//initialize matrix3
printf("a\n");
	for(i=0; i<row1; i++){
            for(j=0; j<col2; j++){
                row_i=i;
                col_j=j;
                pthread_create(&tid[i][j],NULL,Multiplication,NULL);
                pthread_join(tid[i][j],NULL);
            }
    }//computing...
    printf("b\n");
    end_time = clock();
    elapsed = (end_time - start_time) / CLOCKS_PER_SEC * 1000;
    printf("%.30lf\n", elapsed);
    FILE *file;
    file = fopen("output.txt", "w");


    printf("done\n");
    //fprintf(file, "Output:\n");
    for(i=0;i<row1;i++)
    {
        for(j=0;j<col2;j++)
        {
            fprintf(file, "%d ",matrix3[i][j]);//1111111111111111111111111111111111111111111
        }
        fprintf(file, "\n");
    }//printing matrix3 into "output.txt"

    fclose(file);

    while(1){
        printf("\n");

        scanf("%d %d",&get_i,&get_j);
        get_i--;
        get_j--;
        if((get_i >= row1) || (get_j >= col2)){
            printf("out of range\n");
        }else{
            printf("%d\n", matrix3[get_i][get_j]);
        }
    }//getting the (i,j) element of matrix3

    for(i = 0; i < row1; i++){
        free(matrix1[i]);
        free(matrix3[i]);
    }
    for(i = 0; i < row2; i++){
        free(matrix2[i]);
    }
    free(matrix1);
    free(matrix2);
    free(matrix3);



    //system("PAUSE");
    return 0;
}

void *Multiplication()
{
    int k;
    for(k=0;k<col1;k++)
    {
         matrix3[row_i][col_j]+=matrix1[row_i][k] * matrix2[k][col_j];
     }

    pthread_exit(NULL);
}
