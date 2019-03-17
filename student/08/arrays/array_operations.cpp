#include "array_operations.hh"



int greatest_v1(int* itemptr, int size){

    int number = 0;
    for ( int i = 0; i < size; i++)
    {

        if (number < *(itemptr+i)){
            number = *(itemptr+i);
        }
    }

    return number;
}


int greatest_v2(int* itemptr, int* endptr)
{
    int i = 0;
    int luku = 0;
    while ((itemptr+i) != endptr)
    {
        if (luku < *(itemptr+i))
        {
            luku = *(itemptr+i);
        }
        i++;

    }
    return luku;
}

void copy(int* itemptr, int* endptr, int* targetptr)
{
    int i = 0;
    while ((itemptr+i) != endptr)
    {
        *(targetptr+i) = *(itemptr+i);
        i++;
    }
}


void reverse(int* leftptr, int* rightptr)
{
    int i = 0;
    int temp = *leftptr;
    int *old_right = (rightptr-1);
    int size = 0;
    while ((leftptr+size) != old_right){
        size++;
    }

    while (i < size/2)
    {


        temp = *(leftptr+i);
        *(leftptr+i) = *(rightptr-i-1);
        *(rightptr-i-1) = temp;



        i++;
    }
}
