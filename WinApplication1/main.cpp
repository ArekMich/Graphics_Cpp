#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "font.h"
#include <iostream>
#include <vector>

class Menu : public sf::Drawable,public sf::Image
{
private:
	sf::Font font;
	sf::Text *text;
	sf::RectangleShape *rectangle;
	sf::RectangleShape *FirstRectangle;
	sf::RectangleShape *SecoundRectangle;

	wchar_t * flag;

	sf::Texture *colors_texture;
	sf::Sprite *colors_sprite;
	sf::Uint8 *colors_pixels;
	sf::Color line;
	sf::Color fill;

	const unsigned int colors_size_x = 765;
	const unsigned int colors_size_y = 60;
	inline void draw_to_color_pixels(unsigned int x, unsigned int y, unsigned char r, unsigned char g, unsigned char b)
	{
		colors_pixels[4 * (y * colors_size_x + x) + 0] = r;
		colors_pixels[4 * (y * colors_size_x + x) + 1] = g;
		colors_pixels[4 * (y * colors_size_x + x) + 2] = b;
		colors_pixels[4 * (y * colors_size_x + x) + 3] = 255;
	}

public:
	Menu()
	{
		font.loadFromMemory(font_data, font_data_size);
		text = new sf::Text;
		text->setFont(font);
		text->setCharacterSize(12);
		text->setFillColor(sf::Color::White);

		rectangle = new sf::RectangleShape(sf::Vector2f(796, 536));
		rectangle->setFillColor(sf::Color::Transparent);
		rectangle->setOutlineColor(sf::Color::White);
		rectangle->setOutlineThickness(1.0f);
		rectangle->setPosition(2, 62);

		FirstRectangle = new sf::RectangleShape(sf::Vector2f(35, 30));
		FirstRectangle->setFillColor(sf::Color::Transparent);
		FirstRectangle->setPosition(766, 1);
		SecoundRectangle = new sf::RectangleShape(sf::Vector2f(35, 30));
		SecoundRectangle->setFillColor(sf::Color::Transparent);
		SecoundRectangle->setPosition(766, 31);

		line = sf::Color(0, 0, 0, 255);
		fill = sf::Color(0, 0, 0, 255);

		unsigned int x, y;
		colors_pixels = new sf::Uint8[colors_size_x * colors_size_y * 4];
		for (x = 0; x<255; x++)
			for (y = 0; y < 30; y++)
			{
				draw_to_color_pixels(x, y, x, 255, 0);
				draw_to_color_pixels(x + 255, y, 255, 255 - x, 0);
				draw_to_color_pixels(x + 510, y, 255, 0, x);
				draw_to_color_pixels(254 - x, y + 30, 0, 255, 255 - x);
				draw_to_color_pixels(509 - x, y + 30, 0, x, 255);
				draw_to_color_pixels(764 - x, y + 30, 255 - x, 0, 255);
			}

		colors_texture = new sf::Texture();
		colors_texture->create(colors_size_x, colors_size_y);
		colors_texture->update(colors_pixels);

		colors_sprite = new sf::Sprite();
		colors_sprite->setTexture(*colors_texture);
		colors_sprite->setPosition(1, 1);

		flag = L"";
	}

	void outtextxy(sf::RenderTarget& target, float x, float y, wchar_t *str) const
	{
		text->setPosition(x, y);
		text->setString(str);
		target.draw(*text);
	}

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		outtextxy(target, 5, 600, L"f - wybór koloru rysowania");
		outtextxy(target, 5, 615, L"b - wybór koloru wype³niania");
		outtextxy(target, 5, 630, L"l - rysowanie linii");

		outtextxy(target, 200, 600, L"r - rysowanie prostok¹ta");
		outtextxy(target, 200, 615, L"a - rysowanie wype³nionego prostok¹ta");
		outtextxy(target, 200, 630, L"c - rysowanie okrêgu");

		outtextxy(target, 470, 600, L"w - zapis do pliku");
		outtextxy(target, 470, 615, L"o - odczyt z pliku");
		outtextxy(target, 470, 630, L"esc - wyjœcie");

		outtextxy(target, 650, 615, L"Aktualne:");
		outtextxy(target, 745, 620, getchar());

		target.draw(*rectangle);
		target.draw(*colors_sprite);
		target.draw(*FirstRectangle);
		target.draw(*SecoundRectangle);
	}

	void setchar(wchar_t * tmp) {
		flag = tmp;
	}

	wchar_t * getchar() const {
		return flag;
	}

	void colorFirstRectangle(sf::Uint8 * color) {
		sf::Color tmp(color[0], color[1], color[2], color[3]);
		FirstRectangle->setFillColor(tmp);
		line = tmp;
	}

	void colorSecoundRectangle(sf::Uint8 *  color) {
		sf::Color tmp(color[0], color[1], color[2], color[3]);
		SecoundRectangle->setFillColor(tmp);
		fill = tmp;
	}

	sf::Color getColorLine() {
		return line;
	}

	sf::Color getColorFill() {
		return fill;
	}

	

	sf::Uint8* colorPixel(unsigned int x, unsigned int y) {
		sf::Uint8 *tmp;
		tmp = new sf::Uint8[4];
		if (x < 0 || x>765) { tmp[0] = 0; tmp[1] = 0; tmp[2] = 0; tmp[3] = 255; return tmp; }
		if (y < 0 || y>60) { tmp[0] = 0; tmp[1] = 0; tmp[2] = 0; tmp[3] = 255; return tmp; }
		tmp[0] = colors_pixels[4 * (y * colors_size_x + x) + 0];
		tmp[1] = colors_pixels[4 * (y * colors_size_x + x) + 1];
		tmp[2] = colors_pixels[4 * (y * colors_size_x + x) + 2];
		tmp[3] = colors_pixels[4 * (y * colors_size_x + x) + 3];
		return tmp;

	}

};

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 650), "GFK Lab 01", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
	sf::Event event;
	sf::Sprite sprite;
	Menu menu;
	std::vector<sf::RectangleShape>rectangles;
	std::vector<sf::CircleShape>circles;
	std::vector<sf::VertexArray>lines;
	sf::VertexArray Line(sf::LineStrip, 2);
	int positionX, positionY;
	char iChar=0;
	sf::Vector2i position;
	sf::Uint8  *color;
	sf::RectangleShape tmpRectangle;
	sf::CircleShape tmpCircle;
	int endPositionX;
	int endPositionY;

	window.setFramerateLimit(60);

	while (window.isOpen())
	{
		window.clear(sf::Color::Black);

		//Przed obs³ugiwaniem wydarzeñ aby móc zapisywaæ uzyskany obraz
		
		for (auto& cir : circles) window.draw(cir);
		for (auto& rec : rectangles) window.draw(rec);
		for (auto& lin : lines) window.draw(lin);
		window.draw(Line);
		window.draw(sprite);
		window.draw(tmpCircle);
		window.draw(tmpRectangle);
		window.draw(menu);
		window.display();

		while (window.pollEvent(event))
		{
			//______________________________ZAYMYKANIE OKNA_______________________________________________

			if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) window.close();

			//_______________________________KOLOR OBRAMÓWEK______________________________________________

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F)
				menu.setchar(L"F");
				
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && menu.getchar() == L"F"){
				position = sf::Mouse::getPosition(window);
				color = menu.colorPixel(position.x, position.y);
				menu.colorFirstRectangle(color);
			}

			//______________________________WYPE£NIENIE_____________________________________________________

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) 
				menu.setchar(L"B");
			
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && menu.getchar() == L"B"){
				position = sf::Mouse::getPosition(window);
				color = menu.colorPixel(position.x, position.y);
				menu.colorSecoundRectangle(color);
			}

			//________________________________________LINIE__________________________________________________

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
				menu.setchar(L"L");
			}
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && menu.getchar() == L"L")
			{
				Line[0].color = menu.getColorLine();
				Line[1].color = menu.getColorFill();
				Line[0].position = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
				iChar = 'l';
				positionX = event.mouseButton.x;
				positionY = event.mouseButton.y;
			}

			if (event.type == sf::Event::MouseMoved && iChar == 'l')
			{
				Line[1].position = sf::Vector2f(event.mouseMove.x, event.mouseMove.y);
			}

			if (event.type == sf::Event::MouseButtonReleased && iChar == 'l')
			{
				Line[1].position = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
				iChar = 0;
				lines.push_back(Line);
			}

			//________________________________PUSTY PROSTOKAT_________________________________________________

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
				menu.setchar(L"R");
			}
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && menu.getchar() == L"R")
			{

				tmpRectangle.setOutlineColor(menu.getColorLine());
				tmpRectangle.setFillColor(sf::Color::Transparent);
				tmpRectangle.setPosition(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
				tmpRectangle.setOutlineThickness(2.0f);
				iChar = 'R';
				positionX = event.mouseButton.x;
				positionY = event.mouseButton.y;
			}
			if (event.type == sf::Event::MouseMoved && iChar == 'R') {
				tmpRectangle.setSize(sf::Vector2f(event.mouseMove.x - positionX, event.mouseMove.y - positionY));

			}
			if (event.type == sf::Event::MouseButtonReleased && iChar == 'R')
			{
				tmpRectangle.setSize(sf::Vector2f(event.mouseButton.x - positionX, event.mouseButton.y - positionY));
				iChar = 0;
				rectangles.push_back(tmpRectangle);
			}

			//_______________________________PELNY PROSTOKAT_________________________________________________


			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				menu.setchar(L"A");

			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && menu.getchar() == L"A")
			{
				tmpRectangle.setOutlineColor(menu.getColorLine());
				tmpRectangle.setFillColor(menu.getColorFill());
				tmpRectangle.setPosition(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
				tmpRectangle.setOutlineThickness(2.0f);
				iChar = 'A';
				positionX = event.mouseButton.x;
				positionY = event.mouseButton.y;
			}
			if (event.type == sf::Event::MouseMoved && iChar == 'A') {
				tmpRectangle.setSize(sf::Vector2f(event.mouseMove.x - positionX, event.mouseMove.y - positionY));

			}
			if (event.type == sf::Event::MouseButtonReleased && iChar == 'A')
			{
				tmpRectangle.setSize(sf::Vector2f(event.mouseButton.x - positionX, event.mouseButton.y - positionY));
				iChar = 0;
				rectangles.push_back(tmpRectangle);
			}

			

			//__________________________________KOLO________________________________________________________

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
				menu.setchar(L"C");
			}
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && menu.getchar() == L"C")
			{
				tmpCircle.setOutlineColor(menu.getColorLine());
				tmpCircle.setFillColor(menu.getColorFill());
				tmpCircle.setPosition(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
				tmpCircle.setOutlineThickness(2.0f);
				iChar = 'C';
				positionX = event.mouseButton.x;
				positionY = event.mouseButton.y;
			}
			if (event.type == sf::Event::MouseMoved && iChar == 'C')
			{
				tmpCircle.setRadius(sqrt((event.mouseMove.x - positionX)*(event.mouseMove.x - positionX) + (event.mouseMove.y - positionY)*(event.mouseMove.y - positionY)));
				tmpCircle.setOrigin(event.mouseMove.x - positionX, event.mouseMove.y - positionY);
			}

			if (event.type == sf::Event::MouseButtonReleased && iChar == 'C')
			{
				endPositionX = event.mouseButton.x;
				endPositionY = event.mouseButton.y;
				tmpCircle.setRadius(sqrt((endPositionX - positionX)*(endPositionX - positionX) + (endPositionY - positionY)*(endPositionY - positionY)));
				iChar = 0;
				circles.push_back(tmpCircle);
			}

		

			//_________________ZAPIS ODCZYT___________________________________________________
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
				menu.setchar(L"W");
				sf::Texture myTexture;
				myTexture.create(800, 650);
				myTexture.update(window);
				sf::Image image;
				image.create(800, 530, sf::Color::Black);
				image.copy(myTexture.copyToImage(), 0, 0, sf::IntRect(0, 60, 800, 530), false);
				if (!image.saveToFile("save.png")) { return -1; };
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) {
				menu.setchar(L"O");
				sf::Texture myTexture;
				myTexture.loadFromFile("save.png");
				sprite.setTexture(myTexture);
				sprite.setTextureRect(sf::IntRect(0, 0, 800, 600));
			}
		}
	
	}
	return 0;
}