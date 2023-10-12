#include <iostream>
#include <SFML/Graphics.hpp>

const float windowLength = 800.0f;
const float indentPercent = 0.05;
const float indentWidth = windowLength * indentPercent; // 40
const float lineWidth = 1.0f;
const float gridLength = windowLength - (2*indentWidth); // 720
const int gridSize = 8; // 40 to 760
const float squareLength = gridLength / gridSize; // 22.5
const float paletteLength = 200;
const float paletteHeight = 400;
int tileMap[gridSize][gridSize] = {};
std::map<int, sf::Texture> paletteMap;

sf::RenderWindow window(sf::VideoMode(windowLength, windowLength), "Tilemap :)");
sf::RenderWindow palette(sf::VideoMode(paletteLength, paletteHeight), "Palette :I");

void drawGrid()
{
    sf::RectangleShape line(sf::Vector2f(gridLength, lineWidth));

    for (int i=0; i <= gridSize; i++)
    {
        // draw a horizontal line
        line.setRotation(0);
        line.setPosition(0, gridLength/gridSize * i);
        line.move(indentWidth, indentWidth);
        window.draw(line);

        // draw a vertical line
        line.setRotation(90);
        line.setPosition(gridLength/gridSize * i, 0);
        line.move(indentWidth, indentWidth);
        window.draw(line);
    }
}

std::tuple<int, int> getTilePosition()
{
    float gridPosX = sf::Mouse::getPosition(window).x - indentWidth;
    float gridPosY = sf::Mouse::getPosition(window).y - indentWidth;
    // if mouse is not within grid, don't give a tile position
    if (gridPosX < 0 || gridPosX > gridLength || gridPosY < 0 || gridPosY > gridLength)
    {
        return std::make_tuple(-1,-1);
    }
    return std::make_tuple(gridPosX / squareLength, gridPosY / squareLength);
}

void drawIndicator()
{
    std::tuple<int, int> tilePosition = getTilePosition();
    if (std::get<0>(tilePosition) >= 0)
    {
        sf::RectangleShape hoverIndicator(sf::Vector2f(squareLength-lineWidth, squareLength-lineWidth));
        hoverIndicator.setPosition(indentWidth+(std::get<0>(tilePosition)*squareLength), indentWidth+lineWidth+(std::get<1>(tilePosition)*squareLength));
        hoverIndicator.setFillColor(sf::Color(255, 255, 255, 100)); // transparent gray
        window.draw(hoverIndicator);
    }
}

int main()
{
    window.setPosition(sf::Vector2i(200, 0));
    palette.setPosition(sf::Vector2i(window.getPosition().x+windowLength+indentWidth, windowLength*0.25));

    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                // for (int i=0;i<gridSize;i++)
                // {
                //     for (int j=0;j<gridSize;j++)
                //     {
                //         std::cout << tileMap[i][j] << "  ";
                //     }
                //     std::cout << "\n";
                // }
                window.close();
            }
        }

        window.clear();
        palette.clear();

        //drawing stuff here

        //draw grid
        drawGrid();

        //draw transparent gray box over selected tile
        drawIndicator();

        window.display();
        palette.display();
    }
}