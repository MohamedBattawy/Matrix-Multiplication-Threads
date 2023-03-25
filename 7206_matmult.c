#include<stdlib.h>
#include<pthread.h>

#define Item(X, I, J, NCOL)      X[((J) + (I) * (NCOL))]

typedef struct{
    int l;
    int m;
    int n;
    int *A;
    int *B;
    int *C;
    int i;
    int j;
}data;

/*
 * matrix multiplication
 *     C = A*B
 *     A has l rows and m cols
 *     B has m rows and n cols
 *     C has l rows and n cols
 */
void matmult(int* A, int* B, int* C, int l, int m, int n)
{
    for(int i=0; i<l; i++)
        for(int j=0; j<n; j++)
        {
            int sum = 0;
            for(int k=0; k<m; k++)
                sum += Item(A, i, k, m) * Item(B, k, j, n);
            Item(C, i, j, n) = sum;
        }
}



/*
 * matrix multiplication
 *     C = A*B
 *     A has l rows and m cols
 *     B has m rows and n cols
 *     C has l rows and n cols
 */

 void * rowmultiply(void* arg){
    data *d=(data*)arg;
        for(int j=0; j<d->n; j++)
        {
            int sum = 0;
            for(int k=0; k<d->m; k++)
                sum += Item(d->A,d->i,k,d->m) * Item(d->B, k, j, d->n);
            Item(d->C, d->i, j, d->n) = sum;
        }

 }
  void * multiply(void* arg){
data *d=(data*)arg;
                int sum = 0;
                int k;
            for(k=0; k<d->m; k++)
                sum += Item(d->A,d->i,k,d->m) * Item(d->B, k, d->j, d->n);
            Item(d->C, d->i, d->j, d->n) = sum;
            //printf("i=%d  j=%d  value=%d\n",d->i,d->j,Item(d->C, d->i, d->j, d->n));

 }
void matmult_v1(int* A, int* B, int* C, int l, int m, int n)
{
    pthread_t threads[l][n];

    int i,j,z,y;
    for(i=0;i<l;i++){
    for(j=0;j<n; j++){
    data *temp=malloc(sizeof(data));
    temp->A=A;
    temp->B=B;
    temp->C=C;
    temp->l=l;
    temp->m=m;
    temp->n=n;
    temp->i=i;
    temp->j=j;
    //printf("BEFORE THREAD I=%d  J=%d\n",i,j);
    pthread_create(&threads[i][j],NULL,multiply,temp);
    }
    }
    for(z=0;z<l;z++){
    for(y=0;y<n; y++){
    pthread_join(threads[z][y],NULL);
    //if((pthread_join(threads[z][y],NULL)!=0)){
    //printf("Failed");
    //}
    }
    }
}




/*
 * matrix multiplication
 *     C = A*B
 *     A has l rows and m cols
 *     B has m rows and n cols
 *     C has l rows and n cols
 */
void matmult_v2(int* A, int* B, int* C, int l, int m, int n)
{
    pthread_t threads[l];
    int i,y;
    for(i=0;i<l;i++){
    data *temp=malloc(sizeof(data));
    temp->A=A;
    temp->B=B;
    temp->C=C;
    temp->l=l;
    temp->m=m;
    temp->n=n;
    temp->i=i;
    //printf("BEFORE THREAD I=%d  J=%d\n",i,j);
    pthread_create(&threads[i],NULL,rowmultiply,temp);
    }
    for(y=0;y<l; y++){
    pthread_join(threads[y],NULL);
}
}

//int main()
//{

//    return 0;
//}
