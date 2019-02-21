#include <iostream>
#include <string.h>

int main()
{
    // SIMPLE TEST
    // Input string to split
    char str[] = "on|AXY768|bedroom|#fff123";

    char *nstate = strtok(str, "|");
    char *nid = strtok(NULL, "|");
    char *name = strtok(NULL, "|");
    char *color = strtok(NULL, "|");

    std::cout << "State: " << nstate << "\n";
    std::cout << "ID: " << nid << "\n";
    std::cout << "Name: " << name << "\n";
    std::cout << "Color: " << color << "\n";

    // ADVANCED TEST
    // Input string to split
    char str[] = "state=on&id=AXY768&name=bedroom&color=#fff123";
}
