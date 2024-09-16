#ifndef INCIO_H_INCLUDED
#define INCIO_H_INCLUDED
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class StartScreen {
public:
    StartScreen();
    void run(sf::RenderWindow& window);


private:
    void loadResources();
    void draw(sf::RenderWindow& window);
    bool isStartButtonClicked(sf::RenderWindow& window);

    // Recursos gr�ficos
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Font font;
    sf::Text startButtonText;
    sf::Text instructionsText;
    // M�sica para la pantalla de inicio
    sf::Music startScreenMusic;  // Declarar el objeto de m�sica
};



#endif // INCIO_H_INCLUDED
