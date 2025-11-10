#pragma once
#ifndef BSTFILEMANAGER_H
#define BSTFILEMANAGER_H

#include <string>
#include <iostream> // Wymagane dla ostream i istream
#include "BST.h"

/**
 * @class BSTFileManager
 * @brief Klasa narzedziowa do zarzadzania operacjami plikowymi dla klasy BST.
 *
 * Zapewnia statyczne metody do zapisu i odczytu drzewa
 * z/do plikow tekstowych oraz binarnych.
 */
class BSTFileManager {
private:
    /**
     * @brief Rekurencyjna metoda pomocnicza do zapisu binarnego.
     * @param node Aktualny wezel do zapisu.
     * @param out Strumien wyjsciowy pliku binarnego.
     */
    static void saveBinaryHelper(BST::Node* node, std::ostream& out);

    /**
     * @brief Rekurencyjna metoda pomocnicza do odczytu binarnego.
     * @param in Strumien wejsciowy pliku binarnego.
     * @return Wskaznik do nowo utworzonego wezla (lub nullptr).
     */
    static BST::Node* loadBinaryHelper(std::istream& in);

public:
    /**
     * @brief Wczytuje liczby z pliku tekstowego i dodaje je do drzewa.
     * @note Ta metoda DODAJE wezly do istniejacego drzewa.
     * @param tree Referencja do drzewa BST, ktore ma byc zmodyfikowane.
     * @param filename Nazwa pliku tekstowego do odczytu.
     */
    static void loadFromText(BST& tree, const std::string& filename);

    /**
     * @brief Zapisuje cala strukture drzewa BST do pliku binarnego.
     * @param tree Obiekt BST do zapisania.
     * @param filename Nazwa pliku binarnego do utworzenia.
     */
    static void saveBinary(const BST& tree, const std::string& filename);

    /**
     * @brief Wczytuje cala strukture drzewa z pliku binarnego.
     * @note Ta metoda tworzy i zwraca NOWE drzewo.
     * @param filename Nazwa pliku binarnego do odczytu.
     * @return Nowy obiekt BST.
     */
    static BST loadBinary(const std::string& filename);
};

#endif // BSTFILEMANAGER_H