#ifndef PRIMERMAPA_H
#define PRIMERMAPA_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Personaje.h"
#include "Colisionable.h"
#include "GameOver.h"
#include "Enemigo.h"
#include "Cofre.h"
#include "Item.h"

class PrimerMapa
{
private:
    sf::Sprite imagen;
    sf::Texture tex;
    sf::View camera;
    sf::Music music;
    sf::Music musicCofre;
    sf::Font font, font2;
    sf::Text text, textVidas;
    sf::Sprite libroSpriteUI;
    Personaje dipper;
    Enemigo gnomo;
    Cofre cof;
    Item libro1;

    bool libroRecogido;
    bool libroVisible;
    int vidas;
    sf::Clock invulnerableClock;
    sf::Time invulnerableTime;
    sf::Time invulnerableDuration;
    sf::Text speechBubble;
    sf::RectangleShape speechBubbleBackground;
    sf::Clock speechBubbleTimer;
    const sf::Time speechBubbleDuration = sf::seconds(5.0f);
    struct SpeechBubblePhase
    {
        std::string text;
        sf::Time duration;
    };
    std::vector<SpeechBubblePhase> speechBubblePhases;
    size_t currentSpeechBubblePhase;


    // Nueva variable: zonas bloqueadas
    std::vector<sf::FloatRect> zonasBloqueadas;

public:
    PrimerMapa();
    void run(sf::RenderWindow &window);
    void update(sf::RenderWindow &window);
    void handleCollisions();
    void draw(sf::RenderWindow &window);
};

#endif // PRIMERMAPA_H


