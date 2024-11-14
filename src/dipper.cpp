#include "../dipper.h"

// Constructor de la clase Dipper
Dipper::Dipper()
    : _frame(0), _velocity(4, 4), _direccionMirada(0, 1), incremento (false), cambio(false), cambioItem(1)
{
    // Carga la textura del personaje desde un archivo
    if(!_texture.loadFromFile("./Imagenes/Personajes/dipper.png"))
    {
        throw std::runtime_error("Error al cargar la imagen del personaje");
    }

    if (!sonidoBebida.openFromFile("./Imagenes/Sonidos/sonidoBebida.wav"))
    {
        throw std::runtime_error("Error al cargar el sonido de la bebida");
    }
    sonidoBebida.setVolume(30);

    // Asigna la textura al sprite
    _sprite.setTexture(_texture);

    // Define el rectángulo de textura inicial (primer frame de animación)
    _sprite.setTextureRect({0, 0, 50, 55});

    // Centra el origen del sprite en la base del personaje
    _sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height);

}
//int Dipper::vidas = 5;


void Dipper::update()
{
    // Reinicia la velocidad a cero en cada frame
    _velocity = {0, 0};


    //El timer lo utilizamos para poder controlar el tiempo en el incremento de velocidad
    if(timer>0)
    {
        timer--;
    }

    if(timer == 0)
    {
        incremento = false;
    }

    if(estadoDelJuego.contadorDePociones() > 0)
    {
        if (timer == 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::X))
        {
            incremento = true;
            estadoDelJuego.restarPociones();
            timer= 400;
        }
    }

    if(estadoDelJuego.contadorDeBebidas() >0 && estadoDelJuego.getVidasDipper() < 5)
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
        {
            sonidoBebida.play();
            estadoDelJuego.modificarVidasDipper(1);
            estadoDelJuego.restarBebidas();
        }
    }



    // Reinicia la animación si se ha completado un ciclo
    if (_frame >= 2) _frame = 0;

    // Comprueba la entrada del teclado para el movimiento hacia arriba
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        if (incremento)
        {
            _velocity.y = -6;
        }
        else
        {
            _velocity.y = -4;
        }
        // Establece la velocidad vertical negativa (hacia arriba)
        _frame += 0.2f;    // Avanza la animación
        _sprite.setTextureRect({int(_frame) * 50, 169, 50, 55});  // Actualiza el rectángulo de textura para la animación hacia arriba
        _direccionMirada = {0, -1};  // Actualiza la dirección de la mirada
    }

    // Comprueba la entrada del teclado para el movimiento hacia abajo
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        if (incremento)
        {
            _velocity.y = 6;
        }
        else
        {
            _velocity.y = 4;
        }  // Establece la velocidad vertical positiva (hacia abajo)
        _frame += 0.2f;   // Avanza la animación
        _sprite.setTextureRect({0 + int(_frame) * 50, 0, 50, 55});  // Actualiza el rectángulo de textura para la animación hacia abajo
        _direccionMirada = {0, 1};  // Actualiza la dirección de la mirada
    }

    // Comprueba la entrada del teclado para el movimiento hacia la izquierda
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        if (incremento)
        {
            _velocity.x = -6;
        }
        else
        {
            _velocity.x = -4;
        }  // Establece la velocidad horizontal negativa (hacia la izquierda)
        _frame += 0.2f;    // Avanza la animación
        _sprite.setTextureRect({0 + int(_frame) * 50, 57, 50, 55});  // Actualiza el rectángulo de textura para la animación hacia la izquierda
        _direccionMirada = {-1, 0};  // Actualiza la dirección de la mirada
    }

    // Comprueba la entrada del teclado para el movimiento hacia la derecha
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        if (incremento)
        {
            _velocity.x = 6;
        }
        else
        {
            _velocity.x = 4;
        }  // Establece la velocidad horizontal positiva (hacia la derecha)
        _frame += 0.2f;   // Avanza la animación
        _sprite.setTextureRect({0 + int(_frame) * 50, 113, 50, 55});  // Actualiza el rectángulo de textura para la animación hacia la derecha
        _direccionMirada = {1, 0};  // Actualiza la dirección de la mirada
    }

    // Aplica el movimiento al sprite
    _sprite.move(_velocity);


    //accion de dispara
    // Disparo con la tecla Space
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
{
        disparar();
    }

    // Cambiar tipo de disparo con la tecla C
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::C) && !cambio)   //cambio debe ser falso para disparar
    {
        cambio = true;   //una vez que presiona la tecla, el bool cambia y nos obliga a preionar de nuevo
        cambiarTipoDisparo();
    }
    else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::C))   //en caso de que dejemos de presionar la tecla
    {
        cambio= false;   //el bool vuelve a ser falso
    }

    // Actualizar disparos existentes
    for (auto it = _disparos.begin(); it != _disparos.end();)
    {
        it->update();
        if (!it->isAlive())
        {
            it = _disparos.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

// Método para obtener la posición actual del personaje
sf::Vector2f Dipper::getPosition() const
{
    return _sprite.getPosition();
}

// Método para dibujar el personaje en la ventana
void Dipper::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

    target.draw(_sprite, states);
    // Dibuja todos los disparos activos
    for (const auto& disparo : _disparos)
    {
        target.draw(disparo, states);
    }
}

// Método para obtener los límites globales del sprite del personaje
sf::FloatRect Dipper::getBounds() const
{
    return _sprite.getGlobalBounds();
}

// Método para establecer la posición del personaje
void Dipper::setPosition(const sf::Vector2f& position)
{
    _sprite.setPosition(position);
}

void Dipper::setInitialTextureRect(int row)
{
    _sprite.setTextureRect({50, row * 0, 50, 55});
}


void Dipper::disparar()
{
    if (!estadoDelJuego.getEstadosItems("cuchillo"))
    {
        return;
    }
    else
    {
        if (_disparoCooldown.getElapsedTime() >= _tiempoEntreDisparos)
        {
            sf::Vector2f posicionDisparo = _sprite.getPosition();
            // Ajusta la posición inicial del disparo según la dirección
            posicionDisparo.y -= _sprite.getGlobalBounds().height / 2;

            _disparos.emplace_back(posicionDisparo, _direccionMirada, cambioItem); //agregamos cambioItem para cambiar de disparo en el switch
            _disparoCooldown.restart();
        }
    }

}


void Dipper::cambiarTipoDisparo()
{

    int itemDisponible=0;


    // Comprobamos los ítems disponibles
    if (estadoDelJuego.getEstadosItems("cuchillo"))
    {
        itemDisponible++;

    }
    if(estadoDelJuego.getEstadosItems("gancho"))
    {
        itemDisponible++;
    }
    if(estadoDelJuego.getEstadosItems("linterna"))
    {
        itemDisponible++;
    }

    cambioItem++;

    // Si el cambioItem supera el número de ítems disponibles, reiniciamos
    if(cambioItem > itemDisponible )
    {
        cambioItem = 1;
    }
}












