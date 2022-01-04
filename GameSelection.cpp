#include"GameSelection.h"
#include<string>

float fr;
int Quad::maxLevel = 0;

GameSelection::GameSelection(GameDataRef data) : _data(data), technique(new NaiveTechnique())
{
	_data->font.LoadFont("Oswald-Bold", "../Fonts/Oswald-Bold.ttf");
	approachSelectionText.setFont(_data->font.GetFont("Oswald-Bold"));
	NaiveApproach.setFont(_data->font.GetFont("Oswald-Bold"));
	QuadtreeApproach.setFont(_data->font.GetFont("Oswald-Bold"));
	SpatialHashApproach.setFont(_data->font.GetFont("Oswald-Bold"));
	totalnumberOfShapes.setFont(_data->font.GetFont("Oswald-Bold"));
	framerate.setFont(_data->font.GetFont("Oswald-Bold"));
	totalnumberOfShapesValue.setFont(_data->font.GetFont("Oswald-Bold"));
	frameRateValue.setFont(_data->font.GetFont("Oswald-Bold"));

	approachSelectionText.setString("Select the approach");
	NaiveApproach.setString("Press N for Naive approach");
	QuadtreeApproach.setString("Press J for Quadtree approach");
	SpatialHashApproach.setString("Press I for spatial hash approach");
	totalnumberOfShapes.setString("TotalNumberOfShapes: ");
	framerate.setString("Framerate: ");

	approachSelectionText.setCharacterSize(20);
	NaiveApproach.setCharacterSize(20);
	QuadtreeApproach.setCharacterSize(20);
	SpatialHashApproach.setCharacterSize(20);
	totalnumberOfShapes.setCharacterSize(20);
	framerate.setCharacterSize(20);
	totalnumberOfShapesValue.setCharacterSize(20);
	frameRateValue.setCharacterSize(20);

	approachSelectionText.setPosition(sf::Vector2f(30, 20));
	NaiveApproach.setPosition(sf::Vector2f(30, 50));
	QuadtreeApproach.setPosition(sf::Vector2f(30, 80));
	SpatialHashApproach.setPosition(sf::Vector2f(30, 110));

	totalnumberOfShapes.setPosition(sf::Vector2f(900,20));
	framerate.setPosition(sf::Vector2f(900,50));
	totalnumberOfShapesValue.setPosition(sf::Vector2f(1110, 20));
	frameRateValue.setPosition(sf::Vector2f(1050, 50));

	for (int i = 0; i < 100; ++i)
	{
		CircleShape* cs = new CircleShape(data, sf::Vector2f(rand() % 1200 + 1, rand() % 800 + 1));

		float num = ((float)rand()) / (float)RAND_MAX;
		int r = rand() % 2;
		if (r == 0) r = -1;
		else r = 1;

		float x = num * r;

		float num2 = ((float)rand()) / (float)RAND_MAX;
		int r2 = rand() % 2;
		if (r2 == 0) r2 = -1;
		else r2 = 1;
		float y = num2 * r2;

		cs->SetDirection(sf::Vector2f(x,y));
		allshapes.push_back(cs);
	}

	totalnumberOfShapesValue.setString(std::to_string(allshapes.size()));
}

void GameSelection::Init()
{

}

void GameSelection::HandleInput()
{
	sf::Event event;

	while (_data->window.pollEvent(event))
	{
		if (event.type == sf::Event::EventType::Closed)
		{
			_data->window.close();
		}

		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Up) {
				for (int i = 0; i < 100; ++i)
				{
					CircleShape* cs = new CircleShape(_data, sf::Vector2f(rand() % 1200 + 1, rand() % 800 + 1));

					float num = ((float)rand()) / (float)RAND_MAX;
					int r = rand() % 2;
					if (r == 0) r = -1;
					else r = 1;

					float x = num * r;

					float num2 = ((float)rand()) / (float)RAND_MAX;
					int r2 = rand() % 2;
					if (r2 == 0) r2 = -1;
					else r2 = 1;
					float y = num2 * r2;

					cs->SetDirection(sf::Vector2f(x, y));
					allshapes.push_back(cs);
				}

				totalnumberOfShapesValue.setString(std::to_string(allshapes.size()));
			}

			else if (event.key.code == sf::Keyboard::Down)
			{
				int size = allshapes.size();
				for (size_t i = size; i > (size_t)size - 100; --i)
				{
					delete allshapes[(int)i-1];
					allshapes.erase(allshapes.begin() + i - 1);
				}
				totalnumberOfShapesValue.setString(std::to_string(allshapes.size()));
			}
			
			else if (event.key.code == sf::Keyboard::J)
			{
				technique = &quadTree;
			}

			else if (event.key.code == sf::Keyboard::I)
			{
				technique = &sptHsh;
			}
			
		}

	}
}


void GameSelection::Update(float dt)
{
	frameRateValue.setString(std::to_string(fr));
	technique->Setup(allshapes);

	for (int i = 0; i < allshapes.size(); ++i)
	{
		allshapes[i]->Update(dt);
	}

	for (int i = 0; i < allshapes.size(); ++i)
	{
		std::vector<CircleShape*> shapesInRange = technique->findShapesInRange(30, allshapes[i]);

		for (int j = 0; j < shapesInRange.size(); ++j)
		{
			bool isColliding = CheckCollision(*allshapes[i], *shapesInRange[j]);
			if (isColliding)
			{
				sf::Vector2f newDirection  = sf::Vector2f(allshapes[i]->GetDirection().x*-1, allshapes[i]->GetDirection().y* -1);
				sf::Vector2f newDirection2 = sf::Vector2f(shapesInRange[j]->GetDirection().x *-1, shapesInRange[j]->GetDirection().y* -1);

				float num = ((float)rand()) / (float)RAND_MAX;
				int r = rand() % 2;
				if (r == 0) r = -1;
				else r = 1;

				float x = num * r;

				float num2 = ((float)rand()) / (float)RAND_MAX;
				int r2 = rand() % 2;
				if (r2 == 0) r2 = -1;
				else r2 = 1;
				float y = num2 * r2;

				shapesInRange[j]->SetDirection(sf::Vector2f(x,y));

				float num1 = ((float)rand()) / (float)RAND_MAX;
				int r1 = rand() % 2;
				if (r1 == 0) r1 = -1;
				else r1 = 1;

				float x1 = num1 * r1;

				float num21 = ((float)rand()) / (float)RAND_MAX;
				int r21 = rand() % 2;
				if (r21 == 0) r21 = -1;
				else r21 = 1;
				float y1 = num21 * r21;

				allshapes[i]->SetDirection(sf::Vector2f(x1,y1));
			}
		}
	}

    
}

void GameSelection::Draw(float dt)
{
	_data->window.clear();

	for (int i = 0; i < allshapes.size(); ++i)
	{
		allshapes[i]->Draw();
	}

	_data->window.draw(approachSelectionText);
	_data->window.draw(NaiveApproach);
	_data->window.draw(QuadtreeApproach);
	_data->window.draw(SpatialHashApproach);
	_data->window.draw(framerate);
	_data->window.draw(frameRateValue);
	_data->window.draw(totalnumberOfShapes);
	_data->window.draw(totalnumberOfShapesValue);
	_data->window.display();
}

