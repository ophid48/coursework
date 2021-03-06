#include "Game.h"



Game::Game()
{
	restart = 1;
}

void Game::start() {

	// setup ////////////////////////////////////////////////////////////
	Texture texture_of_wolf_w;
	texture_of_wolf_w.loadFromFile("images/wolf_1.png");
	wolfW.getSprite().setTexture(texture_of_wolf_w);
	wolfW.setScore(1);

	Texture texture_of_wolf_m;
	texture_of_wolf_m.loadFromFile("images/wolf_2.png");
	wolfM.getSprite().setTexture(texture_of_wolf_m);
	wolfM.setScore(1);

	Sprite background;
	Texture texture_of_setup;
	texture_of_setup.loadFromFile("images/background_3.png");
	background.setTexture(texture_of_setup);

	rabbits.setTexture();

	string button;


	RenderWindow window_setup(sf::VideoMode(1000, 1050), "Island", Style::None);
	window_setup.setPosition(Vector2i(500, 0));
	while (window_setup.isOpen()) {
		Event event;
		Vector2i pos = Mouse::getPosition(window_setup);//забираем координаты курсора
		while (window_setup.pollEvent(event))
		{

			if (event.type == Event::MouseButtonPressed)//если нажата клавиша мыши
			{
				if (pos.x >= 701 && pos.x <= 749 && pos.y >= 1 && pos.y <= 48 && event.key.code == Mouse::Left) {
					button = "rabbit";
					texture_of_setup.loadFromFile("images/background_3_1.png");
					background.setTexture(texture_of_setup);
					cout << "Select rabbit" << endl;
				}
				else if (pos.x >= 751 && pos.x <= 799 && pos.y >= 1 && pos.y <= 48 && event.key.code == Mouse::Left) {
					button = "wolf_w";
					texture_of_setup.loadFromFile("images/background_3_2.png");
					background.setTexture(texture_of_setup);
					cout << "Select wolf_w" << endl;
				}
				else if (pos.x >= 801 && pos.x <= 849 && pos.y >= 1 && pos.y <= 48 && event.key.code == Mouse::Left) {
					button = "wolf_m";
					texture_of_setup.loadFromFile("images/background_3_3.png");
					background.setTexture(texture_of_setup);
					cout << "Select wolf_m" << endl;
				}
				else if (pos.x >= 950 && pos.x <= 999 && pos.y >= 0 && pos.y <= 49 && event.key.code == Mouse::Left) {
					system("start inst.txt");
				}
				else if (pos.x >= 400 && pos.y >= 0 && pos.x <= 499 && pos.y <= 49 && event.key.code == Mouse::Left) {
					window_setup.close();
				}
				//else if (button != "") {
				//	texture_of_setup.loadFromFile("images/background_3.png");
				//	background.setTexture(texture_of_setup);
				//}

				int dx, dy{ 1 };
				for (int i = 0; i < 20; i++) {
					dx = 1;
					dy += 50;
					for (int j = 0; j < 20; j++) {
						if (pos.x >= dx && pos.x <= dx + 47 && pos.y >= dy && pos.y <= dy + 47 && event.key.code == Mouse::Left)
						{
							if (button == "rabbit") {
								rabbits.addRabbit();
								rabbits.getVectorOfRabbits()[0].setPosition(dx, dy);
							}
							if (button == "wolf_w") {
								wolfWs.insert(wolfWs.begin(), wolfW);
								wolfWs[0].getSprite().setPosition(dx, dy);
							}
							if (button == "wolf_m") {
								wolfMs.insert(wolfMs.begin(), wolfM);
								wolfMs[0].getSprite().setPosition(dx, dy);

							}
						}
						else if (pos.x >= dx && pos.x <= dx + 47 && pos.y >= dy && pos.y <= dy + 47 && event.key.code == Mouse::Right) {
							if (button == "rabbit" && rabbits.getVectorOfRabbits().size() > 0) {
								rabbits.deleteAnimal(rabbits.getVectorOfRabbits(), dx, dy);
							}
							if (button == "wolf_w" && wolfWs.size() > 0) {
								wolfW.deleteAnimal(wolfWs, dx, dy);
							}
							if (button == "wolf_m" && wolfMs.size() > 0) {
								wolfM.deleteAnimal(wolfMs, dx, dy);
							}
						}
						dx += 50;
					}

				}
			}


			if (event.type == sf::Event::KeyPressed &&
				event.key.code == sf::Keyboard::Escape ||
				event.type == event.Closed)
				window_setup.close();
		}
		window_setup.clear();
		window_setup.draw(background);
		for (int i = 0; i < rabbits.getVectorOfRabbits().size(); i++) {
			window_setup.draw(rabbits.getVectorOfRabbits()[i]);
		}
		for (int i = 0; i < wolfWs.size(); i++) {
			window_setup.draw(wolfWs[i].getSprite());
		}
		for (int i = 0; i < wolfMs.size(); i++) {
			window_setup.draw(wolfMs[i].getSprite());
		}
		window_setup.display();
	}

	restart = 0;
	////////////////////////////////////////////////////////////////////

	srand(time(NULL));
	Texture texture_of_background;
	texture_of_background.loadFromFile("images/background_2.png");
	background.setTexture(texture_of_background);

	Font font;//шрифт 
	font.loadFromFile("font/arial.ttf");//передаем нашему шрифту файл шрифта
	Text text(to_string(speed), font, 16);
	text.setPosition(71, 15);//задаем позицию текста

	RenderWindow window(sf::VideoMode(1000, 1050), "Island", Style::None);
	window.setPosition(Vector2i(500, 0));

	while (window.isOpen()) {
		Event event;
		Vector2i pos = Mouse::getPosition(window);//забираем координаты курсора
		while (window.pollEvent(event))
		{
			// кнопки старт и стоп
			if (event.type == Event::MouseButtonPressed)//если нажата клавиша мыши
				if (event.key.code == Mouse::Left)//а именно левая
					if (pos.x >= 350 && pos.x <= 450 && pos.y >= 0 && pos.y <= 50) {
						isStart = 1;
					}
					else if (pos.x >= 550 && pos.x <= 650 && pos.y >= 0 && pos.y <= 50) {
						isStart = 0;
					}

			// кнопки регулирования скорости
			if (event.type == Event::MouseButtonPressed)//если нажата клавиша мыши
				if (event.key.code == Mouse::Left)//а именно левая
					if (pos.x >= 110 && pos.x <= 129 && pos.y >= 16 && pos.y <= 35 && speed < 900) {
						speed += 100;
						// обновляем строку со скоростью
						text.setString(to_string(speed));
						cout << speed << endl;
					}
					else if (pos.x >= 140 && pos.x <= 159 && pos.y >= 16 && pos.y <= 35 && speed > 0) {
						speed -= 100;
						// обновляем строку со скоростью
						text.setString(to_string(speed));
						cout << speed << endl;
					}

			// кнопка рестарта
			if (event.type == Event::MouseButtonPressed)//если нажата клавиша мыши
				if (event.key.code == Mouse::Left)//а именно левая
				{
					if (pos.x >= 899 && pos.x <= 948 && pos.y >= 0 && pos.y <= 49) {
						rabbits.clearRabbits();
						wolfMs.clear();
						wolfWs.clear();
						button = "";
						restart = 1;
						isStart = 0;
						return;
					}
				}

			// кнопка закрытия окна
			if (event.type == Event::MouseButtonPressed)//если нажата клавиша мыши
				if (event.key.code == Mouse::Left)//а именно левая
				{
					if (pos.x >= 950 && pos.x <= 999 && pos.y >= 0 && pos.y <= 49) {
						restart = 0;
						return;
					}
				}


			// для дебага
			if (event.type == Event::KeyPressed &&
				event.key.code == Keyboard::F) {
				cout << "Rabbits:" << endl;
				rabbits.getCoord();
				cout << "Wolf_ws:" << endl;
				wolfW.getCoord(wolfWs);
				cout << "Wolf_ms:" << endl;
				wolfM.getCoord(wolfMs);
			}
		}

		// если не была нажата кнопка "стоп"
		if (isStart) {
			for (int i = 0; i < wolfMs.size(); i++) {
				Vector2f hunt = wolfMs[i].Hunting(rabbits.getVectorOfRabbits(), wolfMs[i].getSprite().getPosition().x,
					wolfMs[i].getSprite().getPosition().y);
				if (hunt != Vector2f(-1, -1)) {
					wolfMs[i].getSprite().setPosition(hunt);
					wolfMs[i].setHunt(1);
					//cout << "Hunt search" << endl;
				}
				else {
					wolfMs[i].decScore();
					Vector2f pos_of_wolfW = wolfMs[i].getPosOfWolfW(wolfW.getVectorOfSprite(wolfWs), wolfMs[i].getSprite().getPosition().x,
						wolfMs[i].getSprite().getPosition().y);
					if (pos_of_wolfW != Vector2f(-1, -1)) {
						wolfMs[i].getSprite().setPosition(pos_of_wolfW);
						//cout << "wolf search" << endl;

					}
					else {
						int random = rand() % 8 + 1;
						wolfMs[i].move(wolfMs[i].getSprite(), random);
					}
				}
			}
			for (int i = 0; i < wolfWs.size(); i++) {
				Vector2f hunt = wolfWs[i].Hunting(rabbits.getVectorOfRabbits(), wolfWs[i].getSprite().getPosition().x,
					wolfWs[i].getSprite().getPosition().y);
				if (hunt != Vector2f(-1, -1)) {
					wolfWs[i].getSprite().setPosition(hunt);
					//cout << "Hunt search" << endl;
				}
				else {
					int random = rand() % 8 + 1;
					wolfWs[i].move(wolfWs[i].getSprite(), random);
				}
			}
			for (int i = 0; i < rabbits.getVectorOfRabbits().size(); i++) {
				int random = rand() % 9 + 1;
				rabbits.move(rabbits.getVectorOfRabbits()[i], random);
			}

			// eat rabbits and die if not enough scores
			for (int i = 0; i < wolfMs.size(); i++) {
				if (wolfMs[i].getHunt())
					hunt_ = !wolfMs[i].eatRabbits(rabbits.getVectorOfRabbits(), wolfMs[i].getSprite().getPosition().x,
						wolfMs[i].getSprite().getPosition().y);
				else {
					wolfMs[i].decScore();
					if (wolfMs[i].birth(wolfW.getVectorOfSprite(wolfWs), wolfMs[i].getSprite().getPosition().x,
						wolfMs[i].getSprite().getPosition().y)) {
						if (wolfMs.size() < 100 && wolfWs.size() < 100) {
							int random = rand() % 2;
							if (random) {
								wolfMs.insert(wolfMs.begin(), wolfM);
								i++;
								wolfMs[0].getSprite().setPosition(wolfMs[i].getSprite().getPosition().x,
									wolfMs[i].getSprite().getPosition().y);
							}
							else {
								wolfWs.insert(wolfWs.begin(), wolfW);
								wolfWs[0].getSprite().setPosition(wolfMs[i].getSprite().getPosition().x,
									wolfMs[i].getSprite().getPosition().y);

							}
						}
						else if (wolfMs.size() < 100) {
							wolfMs.insert(wolfMs.begin(), wolfM);
							i++;
							wolfMs[0].getSprite().setPosition(wolfMs[i].getSprite().getPosition().x,
								wolfMs[i].getSprite().getPosition().y);
						}
						else if (wolfWs.size() < 100) {
							wolfWs.insert(wolfWs.begin(), wolfW);
							wolfWs[0].getSprite().setPosition(wolfMs[i].getSprite().getPosition().x,
								wolfMs[i].getSprite().getPosition().y);
						}
					}
				}
				//cout << "wolf_m:\n " << i << ":\n  " << wolfMs[i].getScore() << endl;
				if (wolfMs[i].getScore() < 0.1) {
					wolfMs.erase(wolfMs.begin() + i);
				}
			}
			for (int i = 0; i < wolfWs.size(); i++) {
				wolfWs[i].eatRabbits(rabbits.getVectorOfRabbits(), wolfWs[i].getSprite().getPosition().x,
					wolfWs[i].getSprite().getPosition().y);
				//cout << "wolf_w:\n " << i << ":\n  " << wolfWs[i].getScore() << endl;
				if (wolfWs[i].getScore() < 0.1) {
					wolfWs.erase(wolfWs.begin() + i);
				}
			}


			sleep(milliseconds(900 - speed));
			rabbits.birth();
		}
		window.clear();
		window.draw(background);
		window.draw(text);
		for (int i = 0; i < rabbits.getVectorOfRabbits().size(); i++) {
			window.draw(rabbits.getVectorOfRabbits()[i]);
		}
		for (int i = 0; i < wolfWs.size(); i++) {
			window.draw(wolfWs[i].getSprite());
		}
		for (int i = 0; i < wolfMs.size(); i++) {
			window.draw(wolfMs[i].getSprite());
		}
		window.display();
	}
}

Game::~Game()
{
}

