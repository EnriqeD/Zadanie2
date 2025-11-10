#pragma once
#ifndef BST_H
#define BST_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

/**
 * @class BST
 * @brief Implementuje strukture danych binarnego drzewa wyszukiwan (BST).
 *
 * Zarzadza wezlami (Node), umozliwia dodawanie, usuwanie,
 * wyszukiwanie oraz rozne metody wyswietlania drzewa.
 */
class BST {
private:
    /**
     * @struct Node
     * @brief Wewnetrzna struktura reprezentujaca pojedynczy wezel drzewa.
     */
    struct Node {
        int data;       ///< Wartosc przechowywana w wezle
        Node* left;     ///< Wskaznik na lewe dziecko
        Node* right;    ///< Wskaznik na prawe dziecko

        /**
         * @brief Konstruktor wezla.
         * @param val Wartosc do przechowania.
         */
        Node(int val) : data(val), left(nullptr), right(nullptr) {}
    };

    Node* root; ///< Wskaznik na korzen drzewa.

    // --- Prywatne metody pomocnicze (rekurencyjne) ---

    void insert(Node*& node, int val);
    void remove(Node*& node, int val);
    Node* findMin(Node* node);
    void clear(Node* node);
    bool findPath(Node* node, int val, std::vector<int>& path);
    void displayGraphical(Node* node, int space, int count) const;

    void printPreorder(Node* node) const;
    void printInorder(Node* node) const;
    void printPostorder(Node* node) const;

    void saveToText(Node* node, std::ostream& out) const;

public:
    /**
     * @brief Konstruktor domyslny. Tworzy puste drzewo.
     */
    BST();

    /**
     * @brief Destruktor. Zwalnia pamiec zajeta przez wszystkie wezly.
     */
    ~BST();

    /**
     * @brief Wstawia nowa wartosc do drzewa.
     * @param val Wartosc do wstawienia.
     */
    void insert(int val);

    /**
     * @brief Usuwa wartosc z drzewa (jesli istnieje).
     * @param val Wartosc do usuniecia.
     */
    void remove(int val);

    /**
     * @brief Usuwa wszystkie wezly z drzewa, czyniac je pustym.
     */
    void clear();

    /**
     * @brief Znajduje sciezke od korzenia do wezla o podanej wartosci.
     * @param val Wartosc do znalezienia.
     * @return Wektor (std::vector) wartosci na sciezce. Pusty, jesli nie znaleziono.
     */
    std::vector<int> findPath(int val);

    /**
     * @brief Wyswietla drzewo w formie graficznej (obroconej o 90 stopni) na konsoli.
     */
    void displayGraphical() const;

    /**
     * @brief Wyswietla drzewo metoda Preorder (korzen, lewy, prawy).
     */
    void displayPreorder() const;

    /**
     * @brief Wyswietla drzewo metoda Inorder (lewy, korzen, prawy).
     */
    void displayInorder() const;

    /**
     * @brief Wyswietla drzewo metoda Postorder (lewy, prawy, korzen).
     */
    void displayPostorder() const;

    /**
     * @brief Zapisuje zawartosc drzewa (w porzadku Inorder) do pliku tekstowego.
     * @param filename Nazwa pliku docelowego.
     */
    void saveToText(const std::string& filename) const;

    /**
     * @brief Zaprzyjazniona klasa do zarzadzania plikami.
     *
     * Pozwala BSTFileManager na bezposredni dostep do 'root'
     * w celu binarnego zapisu/odczytu.
     */
    friend class BSTFileManager;
};

#endif // BST_H