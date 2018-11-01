/*
----- My try at doing parser for mathematical expressions -----
	version: v 0.1

	CHANGE_LOG:
	different from debug version(v 0.1.d):
		-function OOP renamed to OrderOfOper
		-same for the file OOP.cpp, renamed to OrderOfOper.cpp
		-updated comments
	----------


*/


#include <iostream>
#include "Parser.h"

int main()
{
  std::cout << "Function(256): ";

  char cstring[256]={};
  int** ExpString = new int*[256];

	for(int i = 0; i < 256; i++)
	{
		ExpString[i] = new int[12]; //creates subarrays for every type of element for each element
		for(int j = 0; j < 12; j++)
		{
					ExpString[i][j] = 0; //sets every element of expression array to(across all subarrays) 0
		}
	}

  std::cin.getline(cstring, 256);

  for(int i = 0; i < sizeof(cstring); i++)
  {
    int type = parseToType(cstring[i]); //gets the type of the current element
    ExpString[i][type] = parse(cstring[i], type); 
		//puts them to two dimensional array, with values at correspoding "slots"
		//e.g. plus will be in "second dimension" at index 7, etc.
  }

	orderExp* orderedExp = OrderOfOper(ExpString); //"orders" the expression string -> puts there additional brackets for order of operations

  EndRes* end = result(orderedExp->arr, 0, false, orderedExp->count); //calculates the actual result of the ordered expression
  
  std::cout << "After: "<< end->result << std::endl;


	//deleting all dynamically created arrays
	delete[] ExpString; //deletes unordered expresion array
	for(int i = 0; i < orderedExp->count; i++)
	{
		delete[] orderedExp->arr[i]; //deletes every subarray of ordered expression array
	}
	delete[] orderedExp->arr; //deletes ordered expression array itself

  return 0;
}