#include<stdio.h>
#include<stdlib.h>

int  text(int size, char* file, double* M ){

    int amount=0;

    FILE *f = fopen(file, "r");

    if(f==NULL){

        printf("No such file\n");
        return 1;

    }
    for (int i = 0; !feof(f) && !ferror(f) && i!= size; i++){

        for (int j = 0; !feof(f) && !ferror(f) && j!=size; j++){

            if (!fscanf(f, "%lf", &M[i*size + j])){

            printf("Wrong data\n");
            return 2;
            }

            if(!feof(f)){
                amount++;
            }
        }
    }

    if (amount < (size*size) ) {

        printf("Add %d more numbers\n", (size*size - amount));
        return 3;
    }

    return 0;

}
