
#include "Game.h"
using namespace std;

void Game::InicializarVariaveis()
{
	this->window = nullptr;
    
    
    this->points = 0;
    this->enemySpawnTimerMax = 10.f;
    this->enemySpawnTimer = this->enemySpawnTimerMax;
    
    this->maxEnemies = 5;
    this->health = 10;
    this->endGame = false;
}

void Game::InicializarJanela()
{
    this->videoMode.height = 800;
    this->videoMode.width = 800;
    this->window = new sf::RenderWindow(this->videoMode, "Primeiro Jogo");
    this->window->setFramerateLimit(60);
}

void Game::InitEnemys()
{
    
    this->enemy.setPosition(10.f,10.f);
    this->enemy.setSize(sf::Vector2f(100.f, 100.f));
    this->enemy.setFillColor(sf::Color::Red);
    /*this->enemy.setOutlineColor(sf::Color::Magenta);
    this->enemy.setOutlineThickness(1.f);*/
    
    
   
    
};



Game::Game()
{
	this->InicializarVariaveis();
	this->InicializarJanela();
    this->InitEnemys();
}

Game::~Game()
{
	delete this->window;
}




const bool Game::running() const
{
	return this->window->isOpen();
}

void Game::pollEvents()
{
    while (this->window->pollEvent(this->ev)) {
        
        switch (this->ev.type)
        {
        case sf::Event::Closed:
            this->window->close();
            break;
        case sf::Event::KeyPressed:
            if (this->ev.key.code == sf::Keyboard::Escape)
                this->window->close(); 
                break;
            

        }
    }
}

void Game::updateMousePositions()
{
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);


}

const bool Game::getEndGame() const
{
    return this->endGame;
}

void Game::spawnEnemies()
{
    this->enemy.setPosition(
        static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
        //static_cast<float>(rand() % static_cast<int>(this->window->getSize().y - this->enemy.getSize().y))
        0.f
        
    );
    this->enemy.setFillColor(sf::Color::Green);
    this->enemies.push_back(this->enemy);
}

void Game::updateEnemies()
{
    if (this->enemies.size() < this->maxEnemies) {
        if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
        {
            this->spawnEnemies();
            this->enemySpawnTimer = 0.f;
        }
        else
            this->enemySpawnTimer += 1.f;
    }
    //move the enemies
    for (int i=0; i<enemies.size(); i++)
    {
        enemies[i].move(0.f, 5.f);

        //checar se foi clicado(inimigo)
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if (this->enemies[i].getGlobalBounds().contains(this->mousePosView))
            {
                this->enemies.erase(this->enemies.begin() + i);
                this->points += 1;
                //cout << "PONTOS: " << points << endl;
            }
        }
        if (this->enemies[i].getPosition().y > this->window->getSize().y)
        {
            this->health -= 1;
            this->enemies.erase(this->enemies.begin() + i);
        }
    }
}

void Game::renderEnemies()
{
    for (auto& e : this->enemies)
    {
        this->window->draw(e);
    }
}

void Game::update()
{
    
    this->pollEvents();
    if (this->endGame == false)
    {
        this->updateMousePositions();
        //cout << sf::Mouse::getPosition().x<<" "<<sf::Mouse::getPosition().y << endl;
        this->updateEnemies();
    }
    if(this->health == 0)
    {
        this->endGame = true;
    }
}

void Game::render()
{
    this->window->clear();

    //desenhar o jogo
    this->renderEnemies();

    this->window->display();
}
