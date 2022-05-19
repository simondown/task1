#include<new>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"head.h"



int main (int argc, char **argv){

    int size;
    int res;
    int formula;
    double N = 0;
    double P = 0;
    char file[50];
    clock_t start, stop;



    if(argc< 4 || argc>5){

        printf("\nWrong parameters\n\n");
        return 1;

    }

    sscanf(argv[1], "%d", &size);
    printf("\nThe size of the matrix: %d\n\n", size);


    sscanf(argv[2], "%d", &res);

    if(res > size){

        printf("Wrong parameters\n");

        return 1;

    }

    double* M = 0;

    try {

    M = new double[size*size];

    } catch (std::bad_alloc &e) {

        printf("Can't allocate memory");
        return 2;


    }

    sscanf(argv[3], "%d", &formula);

    if(formula < 0 || formula > 4){

        printf("Wrong formula\n\n");
        delete[] M;

        return 3;
    }


    if(formula != 0){

        printf("You chose formula №%d\n\n", formula);

        input(size, formula, M);
    }

    else{

        if(argc < 5) {

            printf("Please, enter the file\n");
            delete[] M;
            return 4;

        }

        sscanf(argv[4], "%s", file);

        printf("From the file: %s\n\n", file);

        if (text(size, file, M) != 0) {

            delete[] M;

            return 5;
        }

    }

    printf("The matrix A is:\n");

    print(res, size, 1, M);


    double* V = new double[size];

    vector(size, M, V);

    printf("The vector b is:\n");

    print(res,size, 2, V);


    double* X = new double[size];
    double* Xn = new double[size];



    start = clock();

    if (solution(size, M, V, X, Xn) == 5){

        printf("Non-zero minors of the matrix are required\n");

        delete[] M;
        delete[] V;
        delete[] Xn;
        delete[] X;
        return 5;
    }

    stop = clock();

    if(formula == 0)
        text(size, file, M);

    if(formula != 0)
        input(size, formula, M);

    vector(size, M, V);

    for(int i=0; i<size; i++)
        Xn[i] = 0;


    norma(size, M, V, X, Xn, &N);

    for(int i=0; i<size; i++)
        Xn[i] = 0;

    accuracy(size, X, Xn, &P);

    if(P > 1){

        printf("Non-zero minors of the matrix are required\n");

        delete[] M;
        delete[] V;
        delete[] Xn;
        delete[] X;
        return 5;


    }


    printf("The solution is:\n");

    print(res, size, 2, X);


    printf("Time required: %lf seconds\n", ((double)(stop-start))/CLOCKS_PER_SEC);


    printf("Norma: %10.3e\n", N);


    printf("Accuracy: %10.3e\n", P);


    delete[] M;
    delete[] V;
    delete[] X;
    delete[] Xn;

    return 0;
}
