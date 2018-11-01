#pragma once
enum Exp
{
    function = 1,
    var,
    number,
    dot,
    leftb,
    rightb,
    plus, 
    minus,
    times,
    over,
    power

};

int parseToType(char character);

int parse(char c, int type);

struct EndRes
{
public:
    double result;
    int index;
    EndRes(double res, int i);
};

struct orderExp
{
public:
    int** arr;
    int count;
    orderExp(int ** array, int countOfElements);
};

EndRes* result(int** ptr, int start, bool bracket, int lenght);

orderExp* OrderOfOper(int** ExpString);