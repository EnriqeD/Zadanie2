/**
 * @file BST.cpp
 * @brief Plik implementacyjny dla klasy BST.
 */

#include "BST.h"
#include <iostream>
#include <iomanip> // Dla std::setw (chociaz nieuzywane, bylo w oryginalnym kodzie)

using namespace std;

/**
 * @brief Konstruktor domyslny. Inicjalizuje korzen jako nullptr.
 */
BST::BST() : root(nullptr) {}

/**
 * @brief Destruktor. Wywoluje metode clear() do zwolnienia pamieci.
 */
BST::~BST() {
    clear();
}

/**
 * @brief Prywatna, rekurencyjna metoda pomocnicza do wstawiania wezla.
 */
void BST::insert(Node*& node, int val) {
    if (node == nullptr) {
        node = new Node(val);
    }
    else if (val < node->data) {
        insert(node->left, val);
    }
    else if (val > node->data) {
        insert(node->right, val);
    }
    // Duplikaty sa ignorowane
}

/**
 * @brief Prywatna, rekurencyjna metoda pomocnicza do usuwania wezla.
 */
void BST::remove(Node*& node, int val) {
    if (node == nullptr) {
        return;
    }

    if (val < node->data) {
        remove(node->left, val);
    }
    else if (val > node->data) {
        remove(node->right, val);
    }
    else {
        // Wezel znaleziony
        if (node->left == nullptr && node->right == nullptr) {
            // Przypadek 0: Lisc
            delete node;
            node = nullptr;
        }
        else if (node->left == nullptr) {
            // Przypadek 1: Tylko prawe dziecko
            Node* temp = node;
            node = node->right;
            delete temp;
        }
        else if (node->right == nullptr) {
            // Przypadek 1: Tylko lewe dziecko
            Node* temp = node;
            node = node->left;
            delete temp;
        }
        else {
            // Przypadek 2: Dwoje dzieci
            Node* temp = findMin(node->right);
            node->data = temp->data;
            remove(node->right, temp->data);
        }
    }
}

/**
 * @brief Prywatna metoda pomocnicza do znalezienia wezla o minimalnej wartosci.
 */
BST::Node* BST::findMin(Node* node) {
    while (node && node->left != nullptr) {
        node = node->left;
    }
    return node;
}

/**
 * @brief Prywatna, rekurencyjna metoda pomocnicza do czyszczenia drzewa (postorder).
 */
void BST::clear(Node* node) {
    if (node != nullptr) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

/**
 * @brief Prywatna, rekurencyjna metoda pomocnicza do szukania sciezki.
 */
bool BST::findPath(Node* node, int val, vector<int>& path) {
    if (node == nullptr) {
        return false;
    }

    path.push_back(node->data);

    if (node->data == val) {
        return true;
    }

    if (val < node->data) {
        if (findPath(node->left, val, path)) {
            return true;
        }
    }
    else {
        if (findPath(node->right, val, path)) {
            return true;
        }
    }

    path.pop_back(); // Cofanie, jesli nie znaleziono
    return false;
}

/**
 * @brief Prywatna, rekurencyjna metoda pomocnicza do wyswietlania graficznego.
 */
void BST::displayGraphical(Node* node, int space, int count) const {
    if (node == nullptr) {
        return;
    }
    space += count;

    displayGraphical(node->right, space, count);

    cout << endl;
    for (int i = count; i < space; i++) {
        cout << " ";
    }
    cout << node->data << "\n";

    displayGraphical(node->left, space, count);
}

/**
 * @brief Prywatna, rekurencyjna metoda pomocnicza dla wyswietlania Preorder.
 */
void BST::printPreorder(Node* node) const {
    if (node != nullptr) {
        cout << node->data << " ";
        printPreorder(node->left);
        printPreorder(node->right);
    }
}

/**
 * @brief Prywatna, rekurencyjna metoda pomocnicza dla wyswietlania Inorder.
 */
void BST::printInorder(Node* node) const {
    if (node != nullptr) {
        printInorder(node->left);
        cout << node->data << " ";
        printInorder(node->right);
    }
}

/**
 * @brief Prywatna, rekurencyjna metoda pomocnicza dla wyswietlania Postorder.
 */
void BST::printPostorder(Node* node) const {
    if (node != nullptr) {
        printPostorder(node->left);
        printPostorder(node->right);
        cout << node->data << " ";
    }
}

/**
 * @brief Prywatna, rekurencyjna metoda pomocnicza do zapisu tekstowego (Inorder).
 */
void BST::saveToText(Node* node, ostream& out) const {
    if (node != nullptr) {
        saveToText(node->left, out);
        out << node->data << "\n";
        saveToText(node->right, out);
    }
}

/**
 * @brief Publiczna metoda wstawiania (opakowanie).
 */
void BST::insert(int val) {
    insert(root, val);
}

/**
 * @brief Publiczna metoda usuwania (opakowanie).
 */
void BST::remove(int val) {
    remove(root, val);
}

/**
 * @brief Publiczna metoda czyszczenia drzewa (opakowanie).
 */
void BST::clear() {
    clear(root);
    root = nullptr;
}

/**
 * @brief Publiczna metoda szukania sciezki (opakowanie).
 */
vector<int> BST::findPath(int val) {
    vector<int> path;
    findPath(root, val, path);
    return path;
}

/**
 * @brief Publiczna metoda wyswietlania graficznego (opakowanie).
 */
void BST::displayGraphical() const {
    if (root == nullptr) {
        cout << "[Drzewo jest puste]" << endl;
        return;
    }
    displayGraphical(root, 0, 10);
}

/**
 * @brief Publiczna metoda wyswietlania Preorder (opakowanie).
 */
void BST::displayPreorder() const {
    if (root == nullptr) {
        cout << "[Drzewo jest puste]";
    }
    printPreorder(root);
    cout << endl;
}

/**
 * @brief Publiczna metoda wyswietlania Inorder (opakowanie).
 */
void BST::displayInorder() const {
    if (root == nullptr) {
        cout << "[Drzewo jest puste]";
    }
    printInorder(root);
    cout << endl;
}

/**
 * @brief Publiczna metoda wyswietlania Postorder (opakowanie).
 */
void BST::displayPostorder() const {
    if (root == nullptr) {
        cout << "[Drzewo jest puste]";
    }
    printPostorder(root);
    cout << endl;
}

/**
 * @brief Publiczna metoda zapisu do pliku tekstowego (opakowanie).
 */
void BST::saveToText(const string& filename) const {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Blad: Nie mozna otworzyc pliku do zapisu: " << filename << endl;
        return;
    }
    saveToText(root, file);
    file.close();
    cout << "Drzewo zapisano (tekstowo) do pliku: " << filename << endl;
}