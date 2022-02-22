#pragma once
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <vector>
#include <ctime>
using namespace sf;
class Game {
private:
	void InicializarVariaveis();
	void InicializarJanela();

	unsigned points;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;
	int health;
	bool endGame;
	sf::RenderWindow* window;
	sf::Event ev;
	sf::VideoMode videoMode;
	std::vector<RectangleShape> enemies;
	//objetos do jogo
	sf::RectangleShape enemy;
	
	//Posiçoes do mouse
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	
	
public:
	Game();//construtor
	virtual ~Game();//destrutor
	void InitEnemys();
	//funçoes
	const bool getEndGame() const;
	void spawnEnemies();
	void updateEnemies();
	void renderEnemies();
	void update();
	void render();
	const bool running() const;
	void pollEvents();
	void updateMousePositions();
};
