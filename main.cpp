#include <iostream>
#include <Windows.h>
#include "dai.h"

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    BinarySearchTree bst;

    ifstream inputFile("DAI.txt");
    if (inputFile.is_open()) {
        bst.loadFromFile(inputFile);
        inputFile.close();
    }

    bst.handleUserChoice();

    return 0;
}
