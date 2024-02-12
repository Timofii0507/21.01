#ifndef DAI_H
#define DAI_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Node {
public:
    string carNumber;
    vector<string> violations;
    Node* left;
    Node* right;

    Node(string carNumber);
};

class BinarySearchTree {
public:
    Node* root;

    BinarySearchTree();

    void insert(string carNumber, string violation);
    void printAll();
    void printByCarNumber(string carNumber);
    void printByRange(string carNumber1, string carNumber2);
    void saveToFile(ofstream& file);
    void loadFromFile(ifstream& file);
    void handleUserChoice();

private:
    void printAll(Node* node);
    Node* findNode(string carNumber);
    void printByRange(Node* node, string carNumber1, string carNumber2);
    void saveToFile(Node* node, ofstream& file);
    void loadFromFile(Node*& node, ifstream& file);
    void insertNode(Node*& node, Node* newNode);
};

#endif 
