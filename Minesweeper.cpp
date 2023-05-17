#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "TextureManager.h"
#include "Board.h"
#include "Extra.h"
#include <fstream>
#include <string>
using namespace std;
using namespace sf;


int main()
{

    cout << "Starting Minesweeper" << endl;
    srand(time(0));
    string name = "boards/config.cfg";
    ifstream file(name);
    int col, row, mines;
    if (file.is_open()) {
        file >> col;
        file >> row;
        file >> mines;
    }
    RenderWindow window(VideoMode(col * 32, row * 32 + 100), "Minesweeper Project");
    Board board(col, row, mines);
    board.InitializeRandom();

    Sprite debugButton(TextureManager::GetTexture("debug"));
    debugButton.setPosition(0, row * 32);
    Sprite test1Button(TextureManager::GetTexture("test_1"));
    test1Button.setPosition((col - 6) * 32, row * 32);
    Sprite test2Button(TextureManager::GetTexture("test_2"));
    test2Button.setPosition((col - 4) * 32, row * 32);
    Sprite test3Button(TextureManager::GetTexture("test_3"));
    test3Button.setPosition((col - 2) * 32, row * 32);
    Sprite face(TextureManager::GetTexture("face_happy"));
    face.setPosition(64, row * 32);
    Texture counterTexture(TextureManager::GetTexture("digits"));
    vector<IntRect> boxes;
    vector<int> numbers = Extra::counter(board.GetMineCount());
    vector<Sprite>digits;
    for (int i = 0; i < 211; i += 21)
        boxes.push_back(IntRect(i, 0, 21, 32));
    int k = (col - 8) * 32;
    for (int j = 0; j < 3; j++)
    {
        
        digits.push_back(Sprite(counterTexture));
        digits[j].setPosition(k, (row + 1) * 32);
        k += 21;
        digits[j].setTextureRect(boxes[numbers[j]]);
    }
        
    while (window.isOpen())
    {
        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();

            else if (e.type == e.MouseButtonPressed) {
                if (e.mouseButton.button == Mouse::Left) {
                    Vector2i pos = Mouse::getPosition(window);

                    if (pos.y < row * 32)
                    {
                        Cell* spot = &board.GetCell(col * (pos.y / 32) + (pos.x / 32));
                        board.RevealCell(spot);
                        board.GetGameOver();
                        if (board.GetVictory()) {
                            for (int a = 0; a < 3; a++) {
                                numbers[a] = 0;
                                digits[a].setTextureRect(boxes[numbers[a]]);
                            }
                            face.setTexture(TextureManager::GetTexture("face_win"));
                        }
                        if (board.GetGameOver())
                            face.setTexture(TextureManager::GetTexture("face_lose"));
                    }
                    else if (pos.x > (col - 6) * 32 && pos.x < (col - 6) * 32 + 64 && pos.y > row * 32 && pos.y < row * 32 + 64) {
                        cout << "Loading Test 1" << endl;
                        for (int a = 0; a < 3; a++)
                            digits[a].setTextureRect(boxes[numbers[a]]);
                        face.setTexture(TextureManager::GetTexture("face_happy"));
                        board.Initialize(1);
                      
                    }
                    else if (pos.x > (col - 4) * 32 && pos.x < (col - 4) * 32 + 64 && pos.y > row * 32 && pos.y < row * 32 + 64) {
                        cout << "Loading Test 2" << endl;
                        for (int a = 0; a < 3; a++)
                            digits[a].setTextureRect(boxes[numbers[a]]);
                        face.setTexture(TextureManager::GetTexture("face_happy"));
                        board.Initialize(2);
                        
                    }
                    else if (pos.x > (col - 2) * 32 && pos.x < (col - 2) * 32 + 64 && pos.y > row * 32 && pos.y < row * 32 + 64) {
                        cout << "Loading Test 3" << endl;
                        for (int a = 0; a < 3; a++)
                            digits[a].setTextureRect(boxes[numbers[a]]);
                        face.setTexture(TextureManager::GetTexture("face_happy"));
                        board.Initialize(3);
                        
                    }
                    else if (pos.x > 64 && pos.x < 128 && pos.y > row * 32 && pos.y < row * 32 + 64) {
                        cout << "New Board Loading" << endl;
                        for (int a = 0; a < 3; a++)
                            digits[a].setTextureRect(boxes[numbers[a]]);
                        face.setTexture(TextureManager::GetTexture("face_happy"));
                        board.InitializeRandom();
                        
                    }
                    else if (pos.x > 0 && pos.x < 64 && pos.y > row * 32 && pos.y < row * 32 + 64)
                        board.ShowHiddenState();
                }
                else if (e.mouseButton.button == Mouse::Right) {
                    Vector2i pos = Mouse::getPosition(window);
                    if (pos.y < row * 32) {
                        Cell* current = &board.GetCell(col * (pos.y / 32) + (pos.x / 32));
                        board.Flag(current);
                        numbers = Extra::counter(board.GetMineCount() - board.GetFlagCount());
                        for (int a = 0; a < 3; a++)
                            digits[a].setTextureRect(boxes[numbers[a]]);
                    }
                }
            }
           
            
        }
        
        window.clear(Color::White);
        window.draw(debugButton);
        window.draw(test1Button);
        window.draw(test2Button);
        window.draw(test3Button);
        window.draw(face);
        for (unsigned int i = 0; i < board.GetSize(); i++) {
            window.draw(board.GetCell(i).GetCellSprite());
        }
        for (int j = 0; j < 3; j++)
            window.draw(digits[j]);
        window.display();
        
    }
    TextureManager::Clear();

}