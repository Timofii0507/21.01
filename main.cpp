#include "dai.h"
#include <Windows.h>

using namespace std;


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
