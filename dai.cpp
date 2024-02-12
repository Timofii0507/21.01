#include "dai.h"

void BinarySearchTree::insert(string carNumber, string violation) {
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

void BinarySearchTree::printAll() {
    printAll(root);
}

void BinarySearchTree::printByCarNumber(string carNumber) {
    Node* node = findNode(carNumber);
    if (node != nullptr) {
        cout << "Номер машини: " << node->carNumber << endl;
        cout << "Список правопорушень:" << endl;
        for (string violation : node->violations) {
            cout << " " << violation << endl;
        }
    }
    else {
        cout << "Дані про машину з номером " << carNumber << " не знайдено." << endl;
    }
}

void BinarySearchTree::printByRange(string carNumber1, string carNumber2) {
    printByRange(root, carNumber1, carNumber2);
}

void BinarySearchTree::saveToFile(ofstream& file) {
    saveToFile(root, file);
}

void BinarySearchTree::loadFromFile(ifstream& file) {
    root = nullptr;
    loadFromFile(root, file);
}

void BinarySearchTree::handleUserChoice() {
    int choice;
    do {
        cout << "Меню:" << endl;
        cout << "1. Ввести нове правопорушення" << endl;
        cout << "2. Надрукувати базу даних" << endl;
        cout << "3. Роздруківка даних за заданим номером" << endl;
        cout << "4. Роздруківка даних за діапазоном номерів" << endl;
        cout << "5. Вийти" << endl;
        cout << "Виберіть опцію: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: {
            string carNumber, violation;
            cout << "Введіть номер машини: ";
            getline(cin, carNumber);
            cout << "Введіть опис правопорушення: ";
            getline(cin, violation);
            insert(carNumber, violation);
            break;
        }
        case 2: {
            cout << endl << "**Повний друк бази даних:**" << endl;
            printAll();
            break;
        }
        case 3: {
            string carNumber;
            cout << "Введіть номер машини: ";
            getline(cin, carNumber);
            cout << endl << "**Дані за заданим номером:**" << endl;
            printByCarNumber(carNumber);
            break;
        }
        case 4: {
            string carNumber1, carNumber2;
            cout << "Введіть діапазон номерів для пошуку: ";
            getline(cin, carNumber1);
            getline(cin, carNumber2);
            cout << endl << "**Дані за діапазоном номерів:**" << endl;
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
            cout << "Невірний вибір. Спробуйте ще раз." << endl;
        }
    } while (choice != 5);
}

void BinarySearchTree::printAll(Node* node) {
    if (node == nullptr) {
        return;
    }

    printAll(node->left);
    cout << "Номер машини: " << node->carNumber << endl;
    cout << "Список правопорушень:" << endl;
    for (string violation : node->violations) {
        cout << " " << violation << endl;
    }
    printAll(node->right);
}

Node* BinarySearchTree::findNode(string carNumber) {
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

void BinarySearchTree::printByRange(Node* node, string carNumber1, string carNumber2) {
    if (node == nullptr) {
        return;
    }

    if (carNumber1 < node->carNumber) {
        printByRange(node->left, carNumber1, carNumber2);
    }

    if (carNumber1 <= node->carNumber && carNumber2 >= node->carNumber) {
        cout << "Номер машини: " << node->carNumber << endl;
        cout << "Список правопорушень:" << endl;
        for (string violation : node->violations) {
            cout << " " << violation << endl;
        }
    }

    if (carNumber2 > node->carNumber) {
        printByRange(node->right, carNumber1, carNumber2);
    }
}

void BinarySearchTree::saveToFile(Node* node, ofstream& file) {
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

void BinarySearchTree::loadFromFile(Node*& node, ifstream& file) {
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

void BinarySearchTree::insertNode(Node*& node, Node* newNode) {
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
