#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define eps 1e-15

int sign (double);

int check1 (double* , int);

int check2 (double*, int, int , int );

int solution(int size, double* M, double* V, double* X, double* Xn){


    int i = 0;
    int j = 0;
    int k = 0;

    double temp1 = 0;


    X[0] = sign(M[0]);

    if(fabs(M[0]) < eps) {

           // printf("0\n");

            return 5;

        }

    M[0] = sqrtf(std::fabs(M[0]));

    for(i=1; i<size; i++){

        M[i*size] = M[i*size]/(M[0]*X[0]);

    }

    for(i=1; i<size; i++){

        temp1 = M[i*size + i];

        for(j = 0; j < i; j++){

            temp1 -= M[i*size + j]*M[i*size + j]*X[j];

        }

        if(std::fabs(temp1/M[i*size + i]) < eps*size){


            return 5;

        }

        X[i] = sign(temp1);

        M[i*size + i] = sqrtf(fabs(temp1));

        if(std::fabs(M[i*size + i]) < eps*size){

            return 5;

        }

        temp1 = 0;

        for(j=i+1; j<size; j++){

            for(k=0; k<i; k++){

                temp1 += M[i*size + k]*M[j*size + k]*X[k];
            }

            M[j*size + i] = ((M[j*size + i] - temp1)/(M[i*size + i]*X[i]));

            temp1 = 0;
        }

        temp1 = 0;
    }

    for(i=0; i<size-1; i++){

        for (j=i+1; j<size; j++){

            M[i*size + j] = 0;

        }
    }


    /*printf("The L-matrix is:\n");

    for(i=0; i<4; i++){

        for (j=0; j<4; j++){

            printf("%10.3e ", M[i*size + j]);

        }

        printf("\n");
    }
    printf("\n"); */


    for(i=0; i < size; i++){

        for (j = 0; j<i; j++){

            V[i] -= M[i*size + j]*Xn[j];

        }

        Xn[i] = V[i]/M[i*size + i];
    }

    /*printf("\n\nVector is:\n");

    for(i = 0; i<size; i++)
        printf("%.2f ", Xn[i]);

    printf("\n\n"); */




     for(i=0; i<size; i++){

        for ( j=0; j<size; j++){

            M[i*size + j] = M[j*size + i];
        }
    }



    for(j=0; j<size-1; j++){

        for (i=j+1; i<size; i++){

            M[i*size + j] = 0;

        }
    }



    /*printf("\n\n");
    printf("Trans:\n");

    for(i=0; i<size; i++){

        for (j=0; j<size; j++){

            printf("%.2f ", M[i*size + j]);
        }

        printf("\n");
    }

    printf("\n\n"); */

    for(i=0; i<size; i++)
        Xn[i] *= X[i];


    for(i=0; i<size; i++)
        X[i] = 0;

    for (i = size-1; i>=0; i--){

        for( j = size-1; j>i; j--){

            Xn[i] -= M[i*size + j]*X[j];

        }

        X[i] = Xn[i]/M[i*size + i];
    }

    return 0;
}

int sign(double x){

    if (x > 0.0) return 1;
    if (x < 0.0) return -1;

    return 0;
}



