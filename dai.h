#ifndef DAI_H
#define DAI_H

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

    Node(string carNumber) {
        this->carNumber = carNumber;
        left = nullptr;
        right = nullptr;
    }
};

class BinarySearchTree {
public:
    Node* root;

    BinarySearchTree() {
        root = nullptr;
    }

    void insert(string carNumber, string violation) {
        Node* newNode = findNode(carNumber);
        if (newNode != nullptr) {
            newNode->violations.push_back(violation);
        }
        else {
            newNode = new Node(carNumber);
            newNode->violations.push_back(violation);
            if (root == nullptr) {
                root = newNode;
                return;
            }

            Node* current = root;
            while (true) {
                if (carNumber < current->carNumber) {
                    if (current->left == nullptr) {
                        current->left = newNode;
                        return;
                    }
                    else {
                        current = current->left;
                    }
                }
                else {
                    if (current->right == nullptr) {
                        current->right = newNode;
                        return;
                    }
                    else {
                        current = current->right;
                    }
                }
            }
        }
    }

    void printAll() {
        printAll(root);
    }

    void printByCarNumber(string carNumber) {
        Node* node = findNode(carNumber);
        if (node != nullptr) {
            cout << "����� ������: " << node->carNumber << endl;
            cout << "������ �������������:" << endl;
            for (string violation : node->violations) {
                cout << " " << violation << endl;
            }
        }
        else {
            cout << "��� ��� ������ � ������� " << carNumber << " �� ��������." << endl;
        }
    }

    void printByRange(string carNumber1, string carNumber2) {
        printByRange(root, carNumber1, carNumber2);
    }

    void saveToFile(ofstream& file) {
        saveToFile(root, file);
    }

    void loadFromFile(ifstream& file) {
        root = nullptr;
        loadFromFile(root, file);
    }

    void handleUserChoice() {
        int choice;
        do {
            cout << "����:" << endl;
            cout << "1. ������ ���� ��������������" << endl;
            cout << "2. ����������� ���� �����" << endl;
            cout << "3. ���������� ����� �� ������� �������" << endl;
            cout << "4. ���������� ����� �� ��������� ������" << endl;
            cout << "5. �����" << endl;
            cout << "������� �����: ";
            cin >> choice;
            cin.ignore();

            switch (choice) {
            case 1: {
                string carNumber, violation;
                cout << "������ ����� ������: ";
                getline(cin, carNumber);
                cout << "������ ���� ��������������: ";
                getline(cin, violation);
                insert(carNumber, violation);
                break;
            }
            case 2: {
                cout << endl << "**������ ���� ���� �����:**" << endl;
                printAll();
                break;
            }
            case 3: {
                string carNumber;
                cout << "������ ����� ������: ";
                getline(cin, carNumber);
                cout << endl << "**��� �� ������� �������:**" << endl;
                printByCarNumber(carNumber);
                break;
            }
            case 4: {
                string carNumber1, carNumber2;
                cout << "������ ������� ������ ��� ������: ";
                getline(cin, carNumber1);
                getline(cin, carNumber2);
                cout << endl << "**��� �� ��������� ������:**" << endl;
                printByRange(carNumber1, carNumber2);
                break;
            }
            case 5: {
                ofstream outputFile("DAI.txt");
                if (outputFile.is_open()) {
                    saveToFile(outputFile);
                    outputFile.close();
                }
                break;
            }
            default:
                cout << "������� ����. ��������� �� ���." << endl;
            }
        } while (choice != 5);
    }

private:
    void printAll(Node* node) {
        if (node == nullptr) {
            return;
        }

        printAll(node->left);
        cout << "����� ������: " << node->carNumber << endl;
        cout << "������ �������������:" << endl;
        for (string violation : node->violations) {
            cout << " " << violation << endl;
        }
        printAll(node->right);
    }

    Node* findNode(string carNumber) {
        Node* current = root;
        while (current != nullptr) {
            if (carNumber == current->carNumber) {
                return current;
            }
            else if (carNumber < current->carNumber) {
                current = current->left;
            }
            else {
                current = current->right;
            }
        }
        return nullptr;
    }

    void printByRange(Node* node, string carNumber1, string carNumber2) {
        if (node == nullptr) {
            return;
        }

        if (carNumber1 < node->carNumber) {
            printByRange(node->left, carNumber1, carNumber2);
        }

        if (carNumber1 <= node->carNumber && carNumber2 >= node->carNumber) {
            cout << "����� ������: " << node->carNumber << endl;
            cout << "������ �������������:" << endl;
            for (string violation : node->violations) {
                cout << " " << violation << endl;
            }
        }

        if (carNumber2 > node->carNumber) {
            printByRange(node->right, carNumber1, carNumber2);
        }
    }

    void saveToFile(Node* node, ofstream& file) {
        if (node == nullptr) {
            return;
        }

        saveToFile(node->left, file);
        file << node->carNumber << endl;
        for (string violation : node->violations) {
            file << violation << endl;
        }
        saveToFile(node->right, file);
    }

    void loadFromFile(Node*& node, ifstream& file) {
        string line;
        while (getline(file, line)) {
            if (line.empty()) {
                continue;
            }
            string carNumber = line;
            Node* newNode = new Node(carNumber);
            while (getline(file, line)) {
                if (line.empty()) {
                    break;
                }
                newNode->violations.push_back(line);
            }
            insertNode(node, newNode);
        }
    }

    void insertNode(Node*& node, Node* newNode) {
        if (node == nullptr) {
            node = newNode;
        }
        else if (newNode->carNumber < node->carNumber) {
            insertNode(node->left, newNode);
        }
        else {
            insertNode(node->right, newNode);
        }
    }
};

#endif 
