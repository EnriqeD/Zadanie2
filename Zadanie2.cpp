/**
 * @file main.cpp
 * @brief Glowny plik aplikacji obslugujacy menu uzytkownika dla drzewa BST.
 */

#include <iostream>
#include <string>
#include <limits>
#include "BST.h"
#include "BSTFileManager.h"

using namespace std;

/**
 * @brief Czysci bufor wejsciowy (stdin).
 *
 * Pomija wszystkie pozostale znaki w buforze az do napotkania znaku nowej linii,
 * aby zapobiec bledom przy kolejnych operacjach wejscia.
 */
void clearInputBuffer() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

/**
 * @brief Bezpiecznie pobiera liczbe calkowita od uzytkownika.
 *
 * Wyswietla komunikat i ponawia probe az do podania prawidlowej liczby calkowitej.
 * @param prompt Komunikat wyswietlany uzytkownikowi.
 * @return Prawidlowa liczba calkowita wprowadzona przez uzytkownika.
 */
int getIntInput(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            clearInputBuffer();
            return value;
        }
        else {
            cout << "Nieprawidlowa wartosc. Prosze podac liczbe calkowita.\n";
            cin.clear();
            clearInputBuffer();
        }
    }
}

/**
 * @brief Pobiera linie tekstu (string) od uzytkownika.
 * @param prompt Komunikat wyswietlany uzytkownikowi.
 * @return Lancuch znakow wprowadzony przez uzytkownika.
 */
string getStringInput(const string& prompt) {
    string value;
    cout << prompt;
    getline(cin, value);
    return value;
}

/**
 * @brief Wyswietla glowne menu programu na konsoli.
 */
void printMenu() {
    cout << "\n--- MENU DRZEWA BST ---\n";
    cout << "1. Dodaj element\n";
    cout << "2. Usun element\n";
    cout << "3. Wyczysc cale drzewo\n";
    cout << "4. Znajdz sciezke do elementu\n";
    cout << "5. Wyswietl drzewo graficznie\n";
    cout << "6. Wyswietl (Preorder)\n";
    cout << "7. Wyswietl (Inorder)\n";
    cout << "8. Wyswietl (Postorder)\n";
    cout << "--- SPOSOB ZAPISU---\n";
    cout << "9. Zapisz do pliku tekstowego (metoda BST)\n";
    cout << "10. Wczytaj z pliku tekstowego (metoda FileManager)\n";
    cout << "11. Zapisz do pliku binarnego (metoda FileManager)\n";
    cout << "12. Wczytaj z pliku binarnego (metoda FileManager)\n";
    cout << "0. Wyjscie\n";
    cout << "------------------------\n";
}

/**
 * @brief Glowna funkcja programu (petla aplikacji).
 *
 * Inicjalizuje drzewo BST i obsluguje petle zdarzen menu,
 * wywolujac odpowiednie metody na podstawie wyboru uzytkownika.
 * @return 0 po pomyslnym zakonczeniu (wybranie opcji 0).
 */
int main() {
    BST myTree;
    int choice;

    while (true) {
        printMenu();
        choice = getIntInput("Wybierz opcje: ");

        switch (choice) {
        case 1: {
            int val = getIntInput("Podaj wartosc do dodania: ");
            myTree.insert(val);
            cout << "Dodano " << val << endl;
            break;
        }
        case 2: {
            int val = getIntInput("Podaj wartosc do usuniecia: ");
            myTree.remove(val);
            cout << "Usunieto " << val << endl;
            break;
        }
        case 3: {
            myTree.clear();
            cout << "Drzewo zostalo wyczyszczone.\n";
            break;
        }
        case 4: {
            int val = getIntInput("Podaj wartosc do znalezienia: ");
            vector<int> path = myTree.findPath(val);
            if (path.empty()) {
                cout << "Element " << val << " nie zostal znaleziony.\n";
            }
            else {
                cout << "Sciezka do " << val << ": ";
                for (size_t i = 0; i < path.size(); ++i) {
                    cout << path[i] << (i == path.size() - 1 ? "" : " -> ");
                }
                cout << endl;
            }
            break;
        }
        case 5: {
            cout << "Drzewo (graficznie, obrocone o 90 stopni):\n";
            myTree.displayGraphical();
            break;
        }
        case 6: {
            cout << "Preorder: ";
            myTree.displayPreorder();
            break;
        }
        case 7: {
            cout << "Inorder: ";
            myTree.displayInorder();
            break;
        }
        case 8: {
            cout << "Postorder: ";
            myTree.displayPostorder();
            break;
        }
        case 9: {
            string filename = getStringInput("Podaj nazwe pliku tekstowego do zapisu (np. tree.txt): ");
            myTree.saveToText(filename);
            break;
        }
        case 10: {
            string filename = getStringInput("Podaj nazwe pliku tekstowego do odczytu (np. numbers.txt): ");
            BSTFileManager::loadFromText(myTree, filename);
            break;
        }
        case 11: {
            string filename = getStringInput("Podaj nazwe pliku binarnego do zapisu (np. tree.bin): ");
            BSTFileManager::saveBinary(myTree, filename);
            break;
        }
        case 12: {
            string filename = getStringInput("Podaj nazwe pliku binarnego do odczytu (np. tree.bin): ");
            myTree.clear();
            myTree = BSTFileManager::loadBinary(filename);
            break;
        }
        case 0: {
            cout << "Zamykanie programu...\n";
            return 0;
        }
        default: {
            cout << "Nieznana opcja. Sproboj ponownie.\n";
            break;
        }
        }
    }
}