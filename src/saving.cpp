#include "saving.h"


void saveBoard(const Board& gameBoard, std::ofstream& file) {
    file.write(reinterpret_cast<const char*>(&gameBoard.score), sizeof(gameBoard.score));
    file.write(reinterpret_cast<const char*>(&gameBoard.step), sizeof(gameBoard.step));

    for(int i = 0; i < GAME_SIZE; i++)
        for(int j = 0; j < GAME_SIZE; j++)
            file.write(reinterpret_cast<const char*>(&gameBoard.value[i][j]), sizeof(unsigned int));
}

void saveList(const List<Board*>& list, std::ofstream& file) {
    file.write(reinterpret_cast<const char*>(&list.size), sizeof(list.size));
    
     for(Node<Board*> *i = list.pHead; i != nullptr; i = i->pNext)
          if (i->value != nullptr)
            saveBoard(*i->value, file);
}

void saveGame(const char* filename, const Board& gameBoard, const SavedBoard& savedBoard) {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cout << "Could not open file!\n";
        return;
    }

    saveBoard(gameBoard, file);

    saveList(savedBoard.undoList, file);
    saveList(savedBoard.redoList, file);
    file.close();
}

void loadBoard(Board& gameBoard, std::ifstream& file) {
    file.read(reinterpret_cast<char*>(&gameBoard.score), sizeof(gameBoard.score));
    file.read(reinterpret_cast<char*>(&gameBoard.step), sizeof(gameBoard.step));

    for(int i = 0; i < GAME_SIZE; i++)
        for(int j = 0; j < GAME_SIZE; j++)
            file.read(reinterpret_cast<char*>(&gameBoard.value[i][j]), sizeof(unsigned int));
}

void loadList(List<Board*>& list, std::ifstream& file) {
    file.read(reinterpret_cast<char*>(&list.size), sizeof(list.size));
    
    Board *temp;
    for(int i = 0; i < list.size; i++) {
        temp = new Board;
        initializeGameBoard(*temp);
        loadBoard(*temp, file);
        Node<Board*> *newNode = new Node(temp);
        
        // not using addTail func here because list.size is currently unsync with the list
        if(list.pHead == nullptr) list.pHead = list.pTail = newNode;
        else {
            list.pTail->pNext = newNode;
            list.pTail = newNode;
        }
    }
}

void loadGame(const char* filename, Board& gameBoard, SavedBoard& savedBoard) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cout << "Could not open file!\n";
        return;
    }

    initializeGameBoard(gameBoard);
    loadBoard(gameBoard, file);

    loadList(savedBoard.undoList, file);
    loadList(savedBoard.redoList, file);
    file.close();
}