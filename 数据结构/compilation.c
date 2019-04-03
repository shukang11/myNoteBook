#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>



int token;

void next() {
    token = 0;
}

void expression(int level) {

}

void statement() {

}

void eval() {
    return 0;
}

int main(int argc, char const *argv[])
{
    next();

    while(token){
        statement();
    }
    eval();

    return 0;
}
