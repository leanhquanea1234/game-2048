#include "rendering.h"

// -----GETERS-----

sf::Color getTileColor(const unsigned int& tileValue) {
    switch (tileValue) {
    case 0: 
        return sf::Color(189, 172, 151);
    case 1:
        return sf::Color(238, 228, 218);
    case 2:
        return sf::Color(235, 216, 182);
    case 3:
        return sf::Color(242, 176, 117);
    case 4:
        return sf::Color(245, 142, 90);
    case 5:
        return sf::Color(247, 126, 99);
    case 6:
        return sf::Color(245, 91, 55);
    case 7:
        return sf::Color(242, 208, 90);
    }
    if(tileValue > 30) return sf::Color(150, 0, 0);
    else return sf::Color(255, 150 - 5 * tileValue, 150 - 5 * tileValue);
}

int getTextTileSize(const unsigned int& tileValue) {
    if(tileValue >= 17) return 36;
    else if(tileValue >= 14) return 26;
    else if(tileValue >= 10) return 32;
    else if(tileValue >= 7) return 34;
    else return 39;
}

std::string getValueString(const unsigned int& tileValue) {
    if(tileValue < 17) return std::to_string(1 << tileValue);
    else return "2^" + std::to_string(tileValue);
}





// -----DRAWING TO THE WINDOW-----

void drawBoard(sf::RenderWindow& window, const sf::Font& font, const Board& gameBoard) {
    float tileSize = (WINDOW_HEIGHT - 2 * BOARD_MARGIN) / GAME_SIZE; 
    
    sf::RectangleShape tile(sf::Vector2f(tileSize, tileSize));
    tile.setOutlineThickness(BOARD_BORDER);
    tile.setOutlineColor(sf::Color(156, 138, 122)); 

    sf::Text tileText;
    tileText.setFont(font);

    for(int i = 0; i < GAME_SIZE; i++)
        for(int j = 0; j < GAME_SIZE; j++) {
            sf::Vector2f tilePosition(BOARD_MARGIN + j * tileSize, BOARD_MARGIN + i * tileSize);
            tile.setFillColor(getTileColor(gameBoard.value[i][j]));
            tile.setPosition(tilePosition);
            window.draw(tile);

            if(!gameBoard.value[i][j]) continue;


            if(gameBoard.value[i][j] <= 2) 
                tileText.setFillColor(sf::Color(117, 100, 82));
            else tileText.setFillColor(sf::Color::White);

            tileText.setCharacterSize(getTextTileSize(gameBoard.value[i][j]));
            tileText.setString(getValueString(gameBoard.value[i][j]));
            tileText.setPosition(tilePosition.x + TILE_MARGIN, tilePosition.y + tileSize / 2 - getTextTileSize(gameBoard.value[i][j]));
            window.draw(tileText);
        }
}

void drawSidebar(sf::RenderWindow& window, const sf::Font& font, const Board& gameBoard) {
    sf::Vector2i statsPosition(WINDOW_HEIGHT - BOARD_MARGIN + LINE_WIDTH, BOARD_MARGIN);
    sf::Text text;
    text.setFont(font);
    if(gameBoard.score >= 1000000000) text.setCharacterSize(22);
    else if(gameBoard.score > (1 << 26)) text.setCharacterSize(27);
    else text.setCharacterSize(31);
    text.setFillColor(sf::Color(117, 100, 82));


    text.setString("Score: " + std::to_string(gameBoard.score));
    text.setPosition(statsPosition.x, statsPosition.y);
    window.draw(text);

    text.setString("Steps: " + std::to_string(gameBoard.step));
    text.setPosition(statsPosition.x, statsPosition.y + 50);
    window.draw(text);

    text.setCharacterSize(25);
    text.setString("Keymap:\n W/A/S/D: Move\n (or arrow keys)\n U: Undo\n R: Redo\n Y: Restart\n Esc: Quit");
    text.setPosition(statsPosition.x + 20, WINDOW_HEIGHT - BOARD_BORDER - 280);
    window.draw(text);
}

void drawMainMenu(sf::RenderWindow& window, const sf::Font& font) {
    sf::RectangleShape box(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    box.setFillColor(sf::Color(187, 169, 155));
    box.setPosition(0, 0);
    window.draw(box);

    sf::Text text;
    text.setFont(font);
    text.setColor(sf::Color::White);

    text.setPosition(BOARD_MARGIN, BOARD_MARGIN);
    text.setCharacterSize(70);
    text.setString("GAME 2048");
    window.draw(text);

    text.setPosition(BOARD_MARGIN, WINDOW_HEIGHT - 200);
    text.setCharacterSize(45);
    text.setString("Made by Le Anh Quan - 24120217");
    window.draw(text);

    text.setPosition(BOARD_MARGIN, WINDOW_HEIGHT - 100);
    text.setCharacterSize(40);
    text.setString("Press any key to start.");
    window.draw(text);
}

void drawEndScreen(sf::RenderWindow& window, const sf::Font& font, const Board& gameBoard, short& flag) {
    sf::RectangleShape box(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    box.setFillColor(sf::Color(187, 169, 155, 150));
    box.setPosition(0, 0);
    window.draw(box);

    sf::Text text;
    text.setFont(font);
    text.setColor(sf::Color::White);

    text.setPosition(BOARD_MARGIN, BOARD_MARGIN);
    text.setCharacterSize(70);
    if(flag == OVERFLOWED) text.setString("YOU WIN!");
    else text.setString("YOU LOSE!");
    window.draw(text);

    if(flag == OVERFLOWED) {
        text.setPosition(BOARD_MARGIN, BOARD_MARGIN + 100);
        text.setCharacterSize(50);
        text.setString("Woa, I'm impressed (@.@)");
        window.draw(text);
    }

    text.setPosition(BOARD_MARGIN, WINDOW_HEIGHT - 300);
    text.setCharacterSize(35);
    text.setString("Steps: " + std::to_string(gameBoard.step));
    window.draw(text);

    text.setPosition(BOARD_MARGIN, WINDOW_HEIGHT - 350);
    text.setCharacterSize(35);
    if(flag == OVERFLOWED) text.setString("Score: INF");
    else text.setString("Score: " + std::to_string(gameBoard.score));
    window.draw(text);

    text.setPosition(BOARD_MARGIN, WINDOW_HEIGHT - 100);
    text.setCharacterSize(35);
    text.setString("Press <Esc> to quit or <Space> to play again.");
    window.draw(text);
}



//--------------------------

// only save when user in the middle of the game and exit it
void closeGame(sf::RenderWindow& window, const Board& gameBoard, const SavedBoard &savedBoard) {
    saveGame("2048_save.bin", gameBoard, savedBoard);
    window.close();
}

short processEvents(sf::RenderWindow& window, Board& gameBoard, SavedBoard &savedBoard) {
    for(auto event = sf::Event{}; window.pollEvent(event);) {
        if(event.type == sf::Event::Closed)
            closeGame(window, gameBoard, savedBoard);
        else if(event.type == sf::Event::KeyPressed) {
            char direction = 0;
            switch (event.key.code) {
            case sf::Keyboard::Escape:
                closeGame(window, gameBoard, savedBoard);
                break;
            case sf::Keyboard::Y:
                return RESTART;
            case sf::Keyboard::Left:
            case sf::Keyboard::A:
                direction = LEFT;
                break;
            case sf::Keyboard::Right:
            case sf::Keyboard::D:
                direction = RIGHT;
                break;
            case sf::Keyboard::Up:
            case sf::Keyboard::W:
                direction = UP;
                break;
            case sf::Keyboard::Down:
            case sf::Keyboard::S:
                direction = DOWN;
                break;
            case sf::Keyboard::U:
                undoGame(gameBoard, savedBoard);
                break;
            case sf::Keyboard::R:
                redoGame(gameBoard, savedBoard);
                break;
            }
            if(direction) {
                updateUndoList(gameBoard, savedBoard);
	            if(!moveTile(gameBoard, direction)) return OVERFLOWED;
                if(checkValidMovement(gameBoard, savedBoard)) {
                    gameBoard.step++;
	                resetRedoList(savedBoard);
	                addRandomTile(gameBoard);
                }
                else savedBoard.undoList.popHead();
            }
        }
    }
    return CONTINUE;
}

// -----APPLYING-----

void runMenu(sf::RenderWindow& window, const sf::Font& font, short& flag) {
    for(auto event = sf::Event{}; window.pollEvent(event);) {
        if(event.type == sf::Event::Closed) window.close();
        else if(event.type == sf::Event::KeyPressed) {
            flag = IN_SESSION;
            return;
        }
    }
    window.clear();
    drawMainMenu(window, font);
    window.display();
}

void runEndScreen(sf::RenderWindow& window, const sf::Font& font, Board &gameBoard, short& flag) {
    for(auto event = sf::Event{}; window.pollEvent(event);) {
        if(event.type == sf::Event::Closed) window.close();
        else if(event.type == sf::Event::KeyPressed) {
        if(event.key.code == sf::Keyboard::Escape) 
                window.close();
            if(event.key.code == sf::Keyboard::Space) {
                clearGameBoard(gameBoard);
                addRandomTile(gameBoard);
                flag = IN_SESSION;
                return;
            }
        }
    }
    window.clear(sf::Color(250, 248, 240));
    drawBoard(window, font, gameBoard);
    drawSidebar(window, font, gameBoard);
    drawEndScreen(window, font, gameBoard, flag);
    window.display();
}

void runSession(sf::RenderWindow& window, const sf::Font& font, Board &gameBoard, SavedBoard &savedBoard, short& flag) {
    short state = processEvents(window, gameBoard, savedBoard);

    if(state == OVERFLOWED) {
        flag = OVERFLOWED;
        return;
    }
    else if(state == RESTART || !checkPossibleMove(gameBoard)) {
        flag = END_SESSION;
        return;
    } 

    window.clear(sf::Color(250, 248, 240));
    drawBoard(window, font, gameBoard);
    drawSidebar(window, font, gameBoard);
    window.display();
}


void runGame(Board &gameBoard, SavedBoard &savedBoard) {
    auto window = sf::RenderWindow(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Game 2048", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);

    sf::Font font;
    // may bug cauze this path is different
    if (!font.loadFromFile("../assets/RussoOne-Regular.ttf"))
        printf("Failed to load font.\n");


    std::ifstream file("2048_save.bin", std::ios::binary);
    // check if is there a save or not
    if(file.is_open()) {
        file.close();
        loadGame("2048_save.bin", gameBoard, savedBoard);
    }
    else {
        initializeGameBoard(gameBoard);
        addRandomTile(gameBoard);
    }


    short flag = MENU;
    while (window.isOpen()) {
        if(flag == MENU) runMenu(window, font, flag);
        else if(flag == IN_SESSION)
            runSession(window, font, gameBoard, savedBoard, flag);
        else runEndScreen(window, font, gameBoard, flag);
    }
    deleteGameBoard(gameBoard);
	resetSavedBoard(savedBoard);
}