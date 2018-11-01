/*

CPP file for Parser.h header, includes some function definitions

*/

#include "Parser.h"

int parseToType(char character)
{
   switch ((int)character) //gets int for every type of symbol
   {
    case (int)'+':
    return plus;

    case (int)'-':
    return minus;

    case (int)'*':
    return times;

    case (int)'/':
    return over;

    case (int)'^':
    return power;

    case (int)'(':
    return leftb;

    case (int)')':
    return rightb;

    case (int)'.':
    return dot;

    case(int)',':
    return dot;

    default:
    break;
   }

   if(((int)character >= 48 && (int)character <= 57)) //if number
   {
   	return number;
   }
   //if char
   else if(((int)character >= 65 && (int)character <= 90)||((int)character >= 97 && (int)character <= 122))
   {
   	return var;
   }
   else
   {
   	return 0;
   }

}

int parse(char c, int type) //if element has a type, puts value into corresponding element of subarray
{
  switch (type)
  {
   	case number:
   	return ((int)c - 48);

   	default:
   	return 1; 
  }

}

EndRes::EndRes(double res, int i)
{
	index = i;
	result = res;
}

orderExp::orderExp(int** array, int countOfElements)
{
	arr = array;
	count = countOfElements;
}