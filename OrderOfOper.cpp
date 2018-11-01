#include <iostream>
#include "Parser.h"

int getRightBracket(int** arr, int index, int op);

int getType(int** arr, int i)
{
    for(int index = 0; index < 12; index++)
    {
       if(arr[i][index] != 0)
       {
           return index;
       }
    }
}

orderExp* OrderOfOper(int** ExpString)
{
    int remainingRightb = 0;

    int count = 0; //counts of all operators
    for(int i = 0; i < 256; i++)
    {
        int type = getType(ExpString, i);
        
        if(type >= plus && type <= power) //without functions - not yet implemented anywhere
            count += 3; //if there's operator, counts it as 3 symbols as good rule of thumb(adding brackets to the count)
        else
            count += 1;
    }

    int** orderedExp = new int*[count]; 
    int index = 0;

    int rightBracketIn = -1;
    for(int i = 0; i < count; i++)
    {
        //std::cout << "old array index(256): " << index << std::endl;
        orderedExp[i] = new int[12]; //new sub-array for each element of this array(will hold type of element)

        for(int j = 0; j < 12; j++)
        {
            orderedExp[i][j] = 0; //sets every element of subarray to zero, for each subarray of ordered expression array
        }

        if(index == rightBracketIn || (index == 255 && remainingRightb != 0)) //if index corresponding to "without-brackets" array is equal to one we found
        {
            orderedExp[i][rightb] = 1; //creates right bracket at corresponding pos
            rightBracketIn = -1;
            remainingRightb -= 1;

            continue;
        }

        int type = getType(ExpString, index);
        int next_op = 0;

        if(type >= plus && type <= power) //if type of current element is operator
        {
            orderedExp[i][type] = ExpString[index][type];

            int next_i = 0;

            for(int j = index+1; j < 256; j++) //tries to find next operator
            {
                int t = getType(ExpString, j);
                if(t >= leftb && t <= power) // if some future element is operator, saves its type and index
                {
                    if(t >= leftb && t <= rightb)
                        break;
                    
                    next_op = t;
                    next_i = j;

                    break;
                }
                    
            }

            if(next_op > type)
            { 
                orderedExp[++i] = new int[12]; //creates subarray for the left bracket
                orderedExp[i][leftb] = 1; //creates left bracket

                rightBracketIn = getRightBracket(ExpString, next_i, next_op); //predicts the position of rightb in regard to "old" array
                remainingRightb += 1;
            }
        }
        else
        {
            orderedExp[i][type] = ExpString[index][type]; 
            //assigns type of element of "old" array 
            //to corres. element of "new" one
        }
        if(index < 255)
            index++;
        else
            orderedExp[i][0] = 1;
    }

    return new orderExp(orderedExp, count);
}

int getRightBracket(int** arr, int index, int op)
{
    int m = index; //index of "old" array we will be iterating with 
    for(;m < 256; m++)
    {
        int type = getType(arr, m);

        if(type >= leftb && type <= power) //if found element is of type operator
        {
            if(type < op) //if value(significance) of next operator is less
            {
                //predicts right bracket position
                return m;
            }
        }
    }
    return 255;
}