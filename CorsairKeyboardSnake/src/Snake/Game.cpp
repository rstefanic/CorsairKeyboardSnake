#include "Game.h"

Snake::Game::Game(Display& display) : m_display(display) {
    srand(time(NULL)); // Set random seed for game

    // First Initialize and place the snake on the
    // board so we what spaces are unoccupied when
    // randomizing the food location.
    m_gameboard = new Board(gameboardColor);
    m_snake = new Snake(4 + 10 * 4, SnakeDirection::Right, m_gameboard->getWidth(), m_gameboard->getHeight());

    addSnakeBodyToBoard();
    addSnakeHeadToBoard();
    createNewFood();
}

Snake::Game::~Game()
{
    free(m_snake);
    free(m_food);
    free(m_gameboard);
}

void Snake::Game::run()
{
    while (m_isRunning) {
        auto command = getUserInput();
        update(command);
        draw();
    }
}

Controls::Command Snake::Game::getUserInput()
{
    Controls::Command command = Controls::Command::NONE;

    auto inputStartTime = std::chrono::system_clock::now();
    while ((std::chrono::system_clock::now() - inputStartTime) < std::chrono::milliseconds(500)) {
        command = m_userInput.getInput();
    }

    return command;
}

void Snake::Game::update(Controls::Command command)
{
    translateCommandToSnakeDirection(command);
    m_snake->move();

    if (m_snake->snakeHasCollidedWith(m_food->getX(), m_food->getY())) {
        m_snake->growSnake();
        createNewFood();
    }

    if (m_snake->snakeHasCollidedWithSelf() || m_snake->snakeLength() == Constants::maxSnakeLength) {
        m_isRunning = false;
    }

}

void Snake::Game::draw()
{
    m_gameboard->clear();
    addSnakeBodyToBoard();
    addSnakeHeadToBoard();
    addFoodToBoard();

    m_display.render(*m_gameboard);
}

void Snake::Game::translateCommandToSnakeDirection(Controls::Command command)
{
    SnakeDirection currentDirection = m_snake->getSnakeDirection();

    switch (command) {
    case Controls::Command::LEFT:
    {
        switch (currentDirection) {
        case SnakeDirection::Up:
            m_snake->changeDirection(SnakeDirection::Left);
            break;
        case SnakeDirection::Left:
            m_snake->changeDirection(SnakeDirection::Down);
            break;
        case SnakeDirection::Down:
            m_snake->changeDirection(SnakeDirection::Right);
            break;
        case SnakeDirection::Right:
            m_snake->changeDirection(SnakeDirection::Up);
            break;
        default:
            break;
        }
        break;
    }
    case Controls::Command::RIGHT:
    {
        switch (currentDirection) {
        case SnakeDirection::Up:
            m_snake->changeDirection(SnakeDirection::Right);
            break;
        case SnakeDirection::Right:
            m_snake->changeDirection(SnakeDirection::Down);
            break;
        case SnakeDirection::Down:
            m_snake->changeDirection(SnakeDirection::Left);
            break;
        case SnakeDirection::Left:
            m_snake->changeDirection(SnakeDirection::Up);
            break;
        default:
            break;
        }
    }
    default:
        break;
    }
}

void Snake::Game::createNewFood()
{
    if (m_food != nullptr) {
        free(m_food);
    }

    auto foodLocation = findLocationForNewFood();
    m_food = new Food(foodLocation.x, foodLocation.y);
}

Snake::FoodSegment Snake::Game::findLocationForNewFood()
{
    int x = 0;
    int y = 0;

    do {
        x = rand() % m_gameboard->getWidth();
        y = rand() % m_gameboard->getHeight();
    } while (!m_gameboard->isBlank(x, y));

    return { x, y };
}

void Snake::Game::addSnakeBodyToBoard()
{
    auto snake = m_snake->getSnake();
    std::for_each(snake.begin(), snake.end(),
        [this](const SnakeSegment segment) {
            m_gameboard->addSnakeBodyTo(segment.x, segment.y);
        });
}

void Snake::Game::addSnakeHeadToBoard()
{
    auto head = m_snake->getSnake().front();
    m_gameboard->addSnakeHeadTo(head.x, head.y);
}

void Snake::Game::addFoodToBoard()
{
    m_gameboard->addFoodTo(m_food->getX(), m_food->getY());
}

