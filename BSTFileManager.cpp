/**
 * @file BSTFileManager.cpp
 * @brief Plik implementacyjny dla klasy BSTFileManager.
 */

#include "BSTFileManager.h"
#include <fstream>
#include <iostream>

using namespace std;

/**
 * @brief Implementacja publicznej metody statycznej loadFromText.
 */
void BSTFileManager::loadFromText(BST& tree, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Blad: Nie mozna otworzyc pliku do odczytu: " << filename << endl;
        return;
    }

    int number;
    int count = 0;
    while (file >> number) {
        tree.insert(number);
        count++;
    }

    file.close();
    cout << "Wczytano i dodano " << count << " liczb z pliku: " << filename << endl;
}

/**
 * @brief Implementacja publicznej metody statycznej saveBinary.
 */
void BSTFileManager::saveBinary(const BST& tree, const string& filename) {
    ofstream file(filename, ios::binary);
    if (!file.is_open()) {
        cerr << "Blad: Nie mozna otworzyc pliku do zapisu binarnego: " << filename << endl;
        return;
    }

    // Dostep do tree.root jest mozliwy dzieki 'friend class'
    saveBinaryHelper(tree.root, file);

    file.close();
    cout << "Drzewo zapisano (binarnie) do pliku: " << filename << endl;
}

/**
 * @brief Implementacja publicznej metody statycznej loadBinary.
 */
BST BSTFileManager::loadBinary(const string& filename) {
    ifstream file(filename, ios::binary);
    if (!file.is_open()) {
        cerr << "Blad: Nie mozna otworzyc pliku do odczytu binarnego: " << filename << endl;
        return BST();
    }

    BST tree;
    // Dostep do tree.root jest mozliwy dzieki 'friend class'
    tree.root = loadBinaryHelper(file);

    file.close();
    cout << "Drzewo wczytano (binarnie) z pliku: " << filename << endl;
    return tree;
}

/**
 * @brief Implementacja prywatnej metody statycznej saveBinaryHelper.
 */
void BSTFileManager::saveBinaryHelper(BST::Node* node, ostream& out) {
    if (node == nullptr) {
        bool hasNode = false;
        out.write(reinterpret_cast<const char*>(&hasNode), sizeof(bool));
    }
    else {
        bool hasNode = true;
        out.write(reinterpret_cast<const char*>(&hasNode), sizeof(bool));
        out.write(reinterpret_cast<const char*>(&node->data), sizeof(int));
        saveBinaryHelper(node->left, out);
        saveBinaryHelper(node->right, out);
    }
}

/**
 * @brief Implementacja prywatnej metody statycznej loadBinaryHelper.
 */
BST::Node* BSTFileManager::loadBinaryHelper(istream& in) {
    bool hasNode;
    in.read(reinterpret_cast<char*>(&hasNode), sizeof(bool));

    if (in.eof() || !hasNode) {
        return nullptr;
    }

    int data;
    in.read(reinterpret_cast<char*>(&data), sizeof(int));

    BST::Node* node = new BST::Node(data);
    node->left = loadBinaryHelper(in);
    node->right = loadBinaryHelper(in);

    return node;
}