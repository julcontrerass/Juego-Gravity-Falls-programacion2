#include "../mochila.h"

Mochila::Mochila()
{
    // Configurar el rectángulo de fondo
    background.setSize(sf::Vector2f(430, 100));
    background.setPosition(200, 470);
    background.setFillColor(sf::Color(143, 159, 97, 192));

    // Cargar la fuente
    if (!font.loadFromFile("./font/numeros.ttf"))
    {
        throw std::runtime_error("No se pudo cargar la fuente");
    }

    // Configurar textos
    // VIDAS
    txtVidas.setFont(font);
    txtVidas.setCharacterSize(20);
    txtVidas.setFillColor(sf::Color::White);
    txtVidas.setPosition(220, 480);

    // ARMAS
    txtArmas.setFont(font);
    txtArmas.setString("ARMAS:");
    txtArmas.setCharacterSize(20);
    txtArmas.setFillColor(sf::Color::White);
    txtArmas.setPosition(430, 480);

    // BEBIDAS
    txtBebidas.setFont(font);
    txtBebidas.setString("BEBIDAS:");
    txtBebidas.setCharacterSize(20);
    txtBebidas.setFillColor(sf::Color::White);
    txtBebidas.setPosition(430, 530);

    cantBebidas.setFont(font);
    cantBebidas.setCharacterSize(20);
    cantBebidas.setFillColor(sf::Color::White);
    cantBebidas.setPosition(610, 530);

    cantPociones.setFont(font);
    cantPociones.setCharacterSize(20);
    cantPociones.setFillColor(sf::Color::White);
    cantPociones.setPosition(550, 530);

    // LIBROS
    txtLibros.setFont(font);
    txtLibros.setString("LIBROS:");
    txtLibros.setCharacterSize(20);
    txtLibros.setFillColor(sf::Color::White);
    txtLibros.setPosition(220, 530);


    libro1.setPosition(sf::Vector2f(320,580));
    libro2.setPosition(sf::Vector2f(360,580));
    libro3.setPosition(sf::Vector2f(400,575));

    posionVelocidad.setPosition(sf::Vector2f(530,580));
    bebidaDeVida.setPosition(sf::Vector2f(590,575));

    cuchillo.setPosition(sf::Vector2f(520,530));
    gancho.setPosition(sf::Vector2f(560,530));
    linterna.setPosition(sf::Vector2f(600,530));

}

void Mochila::draw(sf::RenderWindow& window)
{
    window.draw(background);
    txtVidas.setString("VIDAS: " + std::to_string(dipper.getVidas()));
    window.draw(txtVidas);
    window.draw(txtArmas);
    window.draw(txtBebidas);
    window.draw(txtLibros);
    if(libro1.estadoDelLibro())
    {
        window.draw(libro1);
    }
    if(libro2.estadoDelLibro())
    {
        window.draw(libro2);
    }
    if(libro3.estadoDelLibro())
    {
        window.draw(libro3);
    }
    if(posionVelocidad.cantidadDePociones() > 0)
    {
        cantPociones.setString( std::to_string(posionVelocidad.cantidadDePociones()));
        window.draw(cantPociones);
        window.draw(posionVelocidad);
    }
    if(bebidaDeVida.cantidadDeBebidas() > 0)
    {
        cantBebidas.setString( std::to_string(bebidaDeVida.cantidadDeBebidas()));
        window.draw(bebidaDeVida);
        window.draw(cantBebidas);
    }

    if(cuchillo.estadoDelCuchillo())
    {
        window.draw(cuchillo);
    }
    if(gancho.estadoDelGancho())
    {
        window.draw(gancho);
    }
    if(linterna.estadoDeLaLinterna())
    {
        window.draw(linterna);
    }
}

bool Mochila::tresLibros() const {
    bool libros = false;
    if ( libro1.estadoDelLibro() && libro2.estadoDelLibro() && libro3.estadoDelLibro()){
            libros = true;
    }
    return libros;
}
