#include <stdio.h>

int main(int argc, char* argv[])
{
    char* rotor;
    char* rotor1 = "rotor 1";
    char* rotor2 = "rotor 2";
    char* print = "";
    sprintf(print, rotor"%i", argv[1]);
    printf(print);
}