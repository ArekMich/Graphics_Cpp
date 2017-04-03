#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <vector>
#include <math.h>
#include <sstream>
#include <string>
#include "font.h"

int * hsl2rgb(int *, float, float, float);
int * hsv2rgb(int *, float, float, float);

class drawer: public sf::Drawable 
{

private:
	sf::Text *text;
	sf::Font *font;
	float myValue;
	int myNum;
	unsigned int myFps;

public:
	drawer() {
		text = new sf::Text;
		font = new sf::Font();
		font->loadFromMemory(font_data, font_data_size);
		text->setFont(*font);
		text->setCharacterSize(14);
		text->setFillColor(sf::Color::Black);
		myValue = 0.5;
		myNum = 128;
		myFps = 0;
	}

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		add_text(target, 50, 50, L"HSL");
		add_text(target, 400, 50, L"RGB");
		add_text(target, 50, 340, L"HSV");
		add_text(target, 400, 340, L"CMY");
		add_text(target, 240, 280, L"L=");
		add_text(target, 260, 280, std::to_string(myValue));
		add_text(target, 590, 280, L"B=");
		add_text(target, 610, 280, std::to_string(myNum));
		add_text(target, 240, 570, L"V=");
		add_text(target, 260, 570, std::to_string(myValue));
		add_text(target, 590, 570, L"Y=");
		add_text(target, 610, 570, std::to_string(myValue) + "%");
		add_text(target, 688, 490, L"RefreshTime:");
		add_text(target, 724, 510, std::to_string(myFps));
	}

	void add_text(sf::RenderTarget& target, float x, float y, wchar_t *str) const {
		text->setPosition(x, y);
		text->setString(str);
		target.draw(*text);
	}

	void add_text(sf::RenderTarget& target, float x, float y, std::string str) const {
		text->setPosition(x, y);
		text->setString(str);
		target.draw(*text);
	}

	void setValue(float val) {
		myValue = val;
	}

	void setNum(int val) {
		myNum = val;
	}

	void setFPS(unsigned int val) {
		myFps = val;
	}
};


int main()
{

	float qual = 0.5;
	int color_blue = 128;
	int rgb[3];

	//_____________________________________FONT_______________________________________


	sf::Font * myFont;
	myFont = new sf::Font();
	myFont->loadFromMemory(font_data, font_data_size);


	
	//____________________________________OBJECTS______________________________________

	sf::RenderWindow window(sf::VideoMode(800, 650), "GFK Lab 02", sf::Style::Titlebar | sf::Style::Close);
	sf::Clock clock;
	sf::Time time = sf::Time::Zero;
	unsigned int FPS = 0, frame_counter = 0;
	drawer windowText;

	//_____________________________________________________Circles Lines_________________________________________________
	//Menu:
	//	1.HSL
	//	2.HSV
	//	3.RGB
	//  4.CMY

	float deg[1440];
	float rad = 120.0;
	for (int i = 0; i < 1440; i++) {
		deg[i] = 2.0 * (float)i*3.14159265 / 1440.0;
	}
	

	//______________________________HSL__________________________________________________

	sf::VertexArray hslcir(sf::Lines, 2880);

	for (int i = 0; i < 1440; i++) {



		hslcir[2 * i].position = sf::Vector2f(170, 170);
		hslcir[2 * i + 1].position = sf::Vector2f(170 + rad*cos(deg[i]), 170 + rad*sin(deg[i]));
		hsl2rgb(rgb, deg[i] / (2 * 3.14159265), 0.0, qual);
		hslcir[2 * i].color = sf::Color(rgb[0], rgb[1], rgb[2]);
		hsl2rgb(rgb, deg[i] / (2 * 3.14159265), 1.0, qual);
		hslcir[2 * i + 1].color = sf::Color(rgb[0], rgb[1], rgb[2]);
	}

	//______________________________HSV__________________________________________________

	sf::VertexArray hsvcir(sf::Lines, 2880);

	for (int i = 0; i < 1440; i++) {

		hsvcir[2 * i].position = sf::Vector2f(170, 460);
		hsvcir[2 * i + 1].position = sf::Vector2f(170 + rad*cos(deg[i]), 460 + rad*sin(deg[i]));
		hsv2rgb(rgb, deg[i] * 360.0 / (2 * 3.14159265), 0.0, qual);
		hsvcir[2 * i].color = sf::Color(rgb[0], rgb[1], rgb[2]);
		hsv2rgb(rgb, deg[i] * 360.0 / (2 * 3.14159265), 1.0, qual);
		hsvcir[2 * i + 1].color = sf::Color(rgb[0], rgb[1], rgb[2]);
	}

	//______________________________________RGB_______________________________________________

	sf::VertexArray rgbcir(sf::Lines, 2880);

	for (int i = 0; i < 1440; i++) {
		rgbcir[2 * i].position = sf::Vector2f(520, 170);
		rgbcir[2 * i + 1].position = sf::Vector2f(520 + rad*cos(deg[i]), 170 + rad*sin(deg[i]));
		rgbcir[2 * i].color = sf::Color(0, deg[i] * (255.0 / (2 * 3.14159265)), color_blue);
		rgbcir[2 * i + 1].color = sf::Color(rad*255.0 / 120.0, deg[i] * (255.0 / (2 * 3.14159265)), color_blue);
	}

	

	//____________________________CMY__________________________________________________

	sf::VertexArray cmycir(sf::Lines, 2880);

	for (int i = 0; i < 1440; i++) {
		cmycir[2 * i].position = sf::Vector2f(520, 460);
		cmycir[2 * i + 1].position = sf::Vector2f(520 + rad*cos(deg[i]), 460 + rad*sin(deg[i]));
		cmycir[2 * i].color = sf::Color(255, 255 - deg[i] * (255.0 / (2 * 3.14159265)), 255 - color_blue);
		cmycir[2 * i + 1].color = sf::Color(255 - rad*255.0 / 120.0, 255 - deg[i] * (255.0 / (2 * 3.14159265)), 255 - color_blue);
	}


	//_______________________________________SHORT LINE__________________________________

	sf::VertexArray shrt_line(sf::Lines, 2);
	shrt_line[0].position = sf::Vector2f(670, 325);
	shrt_line[1].position = sf::Vector2f(760, 325);
	shrt_line[0].color = sf::Color::Blue;
	shrt_line[1].color = sf::Color::Blue;

	//_______________________________________RECTANGLE PICK______________________________

	sf::VertexArray rec_pick(sf::Quads, 4);

	rec_pick[0].position = sf::Vector2f(690, 197);
	rec_pick[1].position = sf::Vector2f(740, 197);
	rec_pick[2].position = sf::Vector2f(740, 453);
	rec_pick[3].position = sf::Vector2f(690, 453);

	rec_pick[0].color = sf::Color::Black;
	rec_pick[1].color = sf::Color::Black;
	rec_pick[2].color = sf::Color::White;
	rec_pick[3].color = sf::Color::White;

	//__________________________________PICK BOARD________________________________

	sf::RectangleShape setRect;
	setRect.setSize(sf::Vector2f(54, 264));
	setRect.setPosition(sf::Vector2f(688, 193));
	setRect.setFillColor(sf::Color::White);
	setRect.setOutlineColor(sf::Color::Black);
	setRect.setOutlineThickness(2.0f);


	//________________________________START WINDOW________________________________________________
	clock.restart().asMilliseconds();
	while (window.isOpen())
	{
		sf::Event event;
		window.clear(sf::Color::White);

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) window.close();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

				sf::Vector2i position = sf::Mouse::getPosition(window);

				if ((196 < position.y && position.y < 453) && (690 <= position.x && position.x <= 740)) {
					shrt_line[0].position = sf::Vector2f(670, position.y);
					shrt_line[1].position = sf::Vector2f(760, position.y);
					qual = ((float)position.y - 196.0) / 256;
					color_blue = position.y - 197;
					windowText.setValue(qual);
					windowText.setNum(color_blue);
					for (int i = 0; i < 1440; i++) {

						rgbcir[2 * i].color = sf::Color(0, deg[i] * (255.0 / (2 * 3.14159265)), color_blue);
						rgbcir[2 * i + 1].color = sf::Color(rad*255.0 / 120.0, deg[i] * (255.0 / (2 * 3.14159265)), color_blue);

						cmycir[2 * i].color = sf::Color(255, 255 - deg[i] * (255.0 / (2 * 3.14159265)), 255 - color_blue);
						cmycir[2 * i + 1].color = sf::Color(255 - rad*255.0 / 120.0, 255 - deg[i] * (255.0 / (2 * 3.14159265)), 255 - color_blue);

						hsv2rgb(rgb, deg[i] * 360.0 / (2 * 3.14159265), 0.0, qual);
						hsvcir[2 * i].color = sf::Color(rgb[0], rgb[1], rgb[2]);
						hsv2rgb(rgb, deg[i] * 360.0 / (2 * 3.14159265), 1.0, qual);
						hsvcir[2 * i + 1].color = sf::Color(rgb[0], rgb[1], rgb[2]);

						hsl2rgb(rgb, deg[i] / (2 * 3.14159265), 0.0, qual);
						hslcir[2 * i].color = sf::Color(rgb[0], rgb[1], rgb[2]);
						hsl2rgb(rgb, deg[i] / (2 * 3.14159265), 1.0, qual);
						hslcir[2 * i + 1].color = sf::Color(rgb[0], rgb[1], rgb[2]);


					}
				}

			}
		}
	
		window.draw(rgbcir);
		window.draw(cmycir);
		window.draw(hslcir);
		window.draw(hsvcir);
		window.draw(shrt_line);
		window.draw(setRect);
		window.draw(rec_pick);
		window.draw(windowText);

		if (clock.getElapsedTime().asSeconds() >= 1.0f)
		{
			FPS = (unsigned int)((float)frame_counter / clock.getElapsedTime().asSeconds());
			clock.restart();
			frame_counter = 0;
		}
		frame_counter++;
		windowText.setFPS(FPS);
		window.display();
	}
}

//_______________________________HSL ----> RGB_______________________________________________

int* hsl2rgb(int * result, float H, float S, float L) {

	float tmp1, tmp2;
	float tab[3];
	if (reinterpret_cast <int&> (S) == 0) {
		result[0] = L * 255;
		result[1] = L * 255;
		result[2] = L * 255;
		return result;
	}

	if (L < 0.5) { tmp1 = L*(1.0 + S); }
	else { tmp1 = L + S - L * S; }

	tmp2 = 2.0 * L - tmp1;

	tab[0] = H + 0.333;
	tab[1] = H;
	tab[2] = H - 0.333;

	if (tab[0] > 1.0) { tab[0] -= 1; }
	if (tab[2] < 0.0) { tab[2] += 1; }

	for (int i = 0; i < 3; i++) {
		if (6 * tab[i] < 1.0) { tab[i] = tmp2 + (tmp1 - tmp2) * 6 * tab[i]; continue; }
		if (2 * tab[i] < 1.0) { tab[i] = tmp1; continue; }
		if (3 * tab[i] < 2.0) { tab[i] = tmp2 + (tmp1 - tmp2)*(0.666 - tab[i]) * 6; continue; }
		tab[i] = tmp2;
	}

	result[0] = (int)(tab[0] * 255.0);
	result[1] = (int)(tab[1] * 255.0);
	result[2] = (int)(tab[2] * 255.0);
	return result;

};


//_______________________________HSV ----> RGB_______________________________________________


int* hsv2rgb(int * result, float H, float S, float V) {
	float tab[3];
	int check;
	float f, p, q, t;

	if (reinterpret_cast <int&> (S) == 0) {
		tab[0] = (int)(V * 255.0);
		tab[1] = (int)(V * 255.0);
		tab[2] = (int)(V * 255.0);
	}

	H /= 60;

	check = floor(H);

	f = H - check;
	p = V*(1 - S);
	q = V*(1 - S*f);
	t = V*(1 - S*(1 - f));

	if (check == 0) {
		tab[0] = (int)(V * 255.0);
		tab[1] = (int)(t * 255.0);
		tab[2] = (int)(p * 255.0);
	}
	else if (check == 1) {
		tab[0] = (int)(q * 255.0);
		tab[1] = (int)(V * 255.0);
		tab[2] = (int)(p * 255.0);
	}
	else if (check == 2) {
		tab[0] = (int)(p * 255.0);
		tab[1] = (int)(V * 255.0);
		tab[2] = (int)(t * 255.0);
	}
	else if (check == 3) {
		tab[0] = (int)(p * 255.0);
		tab[1] = (int)(q * 255.0);
		tab[2] = (int)(V * 255.0);
	}
	else if (check == 4) {
		tab[0] = (int)(t * 255.0);
		tab[1] = (int)(p * 255.0);
		tab[2] = (int)(V * 255.0);
	}
	else if (check == 5) {
		tab[0] = (int)(V * 255.0);
		tab[1] = (int)(p * 255.0);
		tab[2] = (int)(q * 255.0);
	}

	result[0] = (int)(tab[0]);
	result[1] = (int)(tab[1]);
	result[2] = (int)(tab[2]);

	return result;

}