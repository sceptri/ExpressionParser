#include "Parser.h"
#include <iostream>
#include <math.h>

int getType(int** ptr);
double num(int** ptr);

int i = 0;

EndRes* result(int** ptr, int start, bool bracket, int length)
{
    i = start;

    double res = 0;
    double temp = 0;

    int def = plus;
    int last = plus;

    for(; i < length; i++)
    {   
        //gets type of current element
        def = getType(ptr);

        if(def == 0) continue;

        if(def == leftb) //if left bracket, fire up a new "instance" of this function until rightb or next leftb
        {
            EndRes* end = result(ptr, ++i, true, length);
            temp = end->result;
            i = end->index;
        }

        if(def == number)
        {
            if(ptr[i+1][number] != 0 || ptr[i+1][dot] == 1) // if next element is a number or a floating point
            //executes function, which processes sequence of digits as a number(+floating point)
            {
                temp = num(ptr);
            }
            else
            {
                temp = ptr[i][number];
            }

        }
        if(temp != 0)
        {
            switch(last) //decides what to do with operands, based on current operator
            {
                case plus:
                    res += temp;
                    break;
                case minus:
                    res -= temp;
                    break;
                case times:
                    res *= temp;
                    break;
                case over:
                    res /= temp;
                    break;
                case power:
                    res = pow(res,temp);
                    break;
            }
        }

        if(def == rightb && bracket)
        {
            return new EndRes(res, i);        
        }

        temp = 0;
        last = def;
    }

    return new EndRes(res, i);
}

//gets the type of the element
int getType(int** ptr){
    
    for(int index = 0; index < 12; index++) //checks what kind of element we are dealing with
    {
        if(ptr[i][index] == 1)
        {
            if(index != number)
                return index;
        }
    }

    if(ptr[i][number] != 0) // if it is a number...
    {
        return number;
    }
    else{
        return 0;
    }
}


//checks if next element is also number, if so, then combines them properly
double num(int** ptr)
{
    double res = ptr[i][number];
    int index = i;


    //checks if next element is also number
    if (ptr[++i][number] != 0)
    {
        res = num(ptr);
        res = res + ptr[index][number]*pow(10, (int)log10(res)+1);
    }
    else if(ptr[i][dot] == 1) //checks if there's floating point, if is, treats it as normal number
    //Then, after completing putting together that number behind floating point, multiplies it by number of digits
    {        
        res = num(ptr);

        res = res*pow(10,-((int)log10(res)+1)) + ptr[index][number];
    }
    else //if not, returns current value
    {
        res = ptr[--i][number];
    }

    return res;
}