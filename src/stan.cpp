#include "../stan.h"
#include <iostream>
#include <cmath>

Stan::Stan()
    : _frame(0), _velocity(4, 4), _direccionMirada(0, 1),
      _mostrarDialogo(false), _dialogoActual(0),
      _dialogoCompletado(false), _tiempoDialogo(0),
      _moviendoseAutomaticamente(false), _puntoActual(0),
      _velocidadAutomatica(2.0f), _fotograma(0),
      _segundoDialogoCompletado(false),
      _primerDialogoCompletado(false),
      _dialogoActualmenteActivo(false)
{
    // Carga la textura del personaje
    if (!_texture.loadFromFile("./Imagenes/Personajes/stan.png"))
    {
        throw std::runtime_error("No se pudo cargar la textura de Stan");
    }

    // Configura el sprite inicial
    _sprite.setTexture(_texture);
    _sprite.setTextureRect({56, 140, 67, 67});
    _sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height);

    // FONT DEL DIALOGO
    if (!_fuente.loadFromFile("./font/numeros.ttf"))
    {
        throw std::runtime_error("No se pudo cargar la fuente para el diálogo");
    }

    // Configuración inicial del texto y burbuja de diálogo
    _textoDialogo.setFont(_fuente);
    _textoDialogo.setCharacterSize(18);
    _textoDialogo.setFillColor(sf::Color::Black);

    _burbujaDialogo.setFillColor(sf::Color(255, 255, 255, 230));
    _burbujaDialogo.setOutlineColor(sf::Color::Black);
    _burbujaDialogo.setOutlineThickness(2);

    // Inicializar los diálogos
    _dialogos = {
        " Hola Dipper!",
        " Bill atrapo a todo el pueblo!",
        " Necesito que rescates a",
        "Mabbel , Wendy y Soos!",
        " Y para salvar al pueblo",
        " Traeme los tres libros!",
        " Con ellos podemos ir a pelear",
        " Contra bill y salvar a todos",
        " Toma este cuchillo para que",
        " Puedas pelear"
    };

    _dialogos2 = {
        " Bien! Salvaste a los chicos",
        " Ahora con los tres libros",
        " Vamos a buscar a Bill",
        " Sigueme a la heladera",
        " Que te muestro un secreto"
    };

    _dialogos3 = {
        " Parate en la plataforma",
        " y preciona espacio cuando",
        " Estes preparado para pelear"
    };

    _puntosDeRuta = {
        sf::Vector2f(120, 270),
        sf::Vector2f(230, 270),
        sf::Vector2f(230, 170)
    };
}

void Stan::actualizarPosicionDialogo()
{
    const std::vector<std::string>& dialogosActuales = estadoDelJuego.getEstadoPersonajes("stan") ? _dialogos3 :
                                                      estadoDelJuego.tresLibros() ? _dialogos2 :
                                                      _dialogos;

    if (_mostrarDialogo && _dialogoActual < static_cast<int>(dialogosActuales.size()))
    {
        _textoDialogo.setString(dialogosActuales[_dialogoActual]);

        sf::FloatRect textoBounds = _textoDialogo.getLocalBounds();
        _burbujaDialogo.setSize(sf::Vector2f(textoBounds.width + 20, textoBounds.height + 20));

        sf::Vector2f posPersonaje = _sprite.getPosition();
        _burbujaDialogo.setPosition(
            posPersonaje.x - _burbujaDialogo.getSize().x/2 + 50,
            posPersonaje.y - _sprite.getGlobalBounds().height - _burbujaDialogo.getSize().y - 10
        );

        _textoDialogo.setPosition(
            _burbujaDialogo.getPosition().x + 10,
            _burbujaDialogo.getPosition().y + 5
        );
    }
}

//bool Stan::_debeDesaparecer = false;


void Stan::actualizarDialogo(float deltaTime)
{
    if (!_mostrarDialogo || _dialogoCompletado) return;

    _tiempoDialogo += deltaTime;

    if (_tiempoDialogo >= TIEMPO_ENTRE_DIALOGOS)
    {
        _tiempoDialogo = 0;
        _dialogoActual++;

        const std::vector<std::string>& dialogosActuales =
            estadoDelJuego.getEstadoPersonajes("stan") ? _dialogos3 :
            estadoDelJuego.tresLibros() ? _dialogos2 :
            _dialogos;

        if (_dialogoActual >= static_cast<int>(dialogosActuales.size()))
        {
            _mostrarDialogo = false;
            _dialogoCompletado = true;
            _dialogoActualmenteActivo = false;

            if (!estadoDelJuego.getEstadoPersonajes("stan") && estadoDelJuego.tresLibros()) {
                _segundoDialogoCompletado = true;
            } else if (!estadoDelJuego.getEstadoPersonajes("stan") && !estadoDelJuego.tresLibros()) {
                _primerDialogoCompletado = true;
                estadoDelJuego.cambiarEstadoDialogoStan(true);
            }
        }
        else
        {
            actualizarPosicionDialogo();
        }
    }
}


bool Stan::segundoDialogoCompletado() const
{
    return _segundoDialogoCompletado;
}

void Stan::iniciarDialogo()
{
    // Si ya hay un diálogo activo, no iniciar otro
    if (_dialogoActualmenteActivo) return;

    bool puedeIniciar = false;

    if (estadoDelJuego.getEstadoPersonajes("stan")) {
        // Diálogo 3 en el octavo mapa
        puedeIniciar = true;
    } else if (estadoDelJuego.tresLibros() && _primerDialogoCompletado) {
        // Diálogo 2 cuando tiene los tres libros y completó el diálogo 1
        puedeIniciar = true;
        _dialogoCompletado = false;
    } else if (!_primerDialogoCompletado) {
        // Primer diálogo
        puedeIniciar = true;
    }

    if (puedeIniciar) {
        _mostrarDialogo = true;
        _dialogoActualmenteActivo = true;
        _dialogoActual = 0;
        _tiempoDialogo = 0;
        actualizarPosicionDialogo();
    }
}

void Stan::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_sprite, states);

    const std::vector<std::string>& dialogosActuales =
        estadoDelJuego.getEstadoPersonajes("stan") ? _dialogos3 :
        estadoDelJuego.tresLibros() ? _dialogos2 :
        _dialogos;
    if (_mostrarDialogo && _dialogoActual < static_cast<int>(dialogosActuales.size()))
    {
        target.draw(_burbujaDialogo, states);
        target.draw(_textoDialogo, states);
    }
}

sf::Vector2f Stan::getPosition() const
{
    return _sprite.getPosition();
}

sf::FloatRect Stan::getBounds() const
{
    return _sprite.getGlobalBounds();
}

void Stan::setPosition(const sf::Vector2f& position)
{
    _sprite.setPosition(position);
    actualizarPosicionDialogo();
}

void Stan::update()
{
    if (estadoDelJuego.getEstadoPersonajes("stan")) return;

    if (_moviendoseAutomaticamente)
    {
        actualizarMovimientoAutomatico();
        return;
    }
}

void Stan::iniciarMovimientoAutomatico()
{
    if (!_moviendoseAutomaticamente)
    {
        _moviendoseAutomaticamente = true;
        _puntoActual = 0;
    }
}

void Stan::actualizarMovimientoAutomatico()
{
    if (!_moviendoseAutomaticamente || estadoDelJuego.getEstadoPersonajes("stan")) return;

    if (_puntoActual >= _puntosDeRuta.size())
    {
        estadoDelJuego.modificarEstadosPersonaje("stan");
        return;
    }

    sf::Vector2f posicionActual = _sprite.getPosition();
    sf::Vector2f posicionObjetivo = _puntosDeRuta[_puntoActual];
    sf::Vector2f direccion = posicionObjetivo - posicionActual;
    float distancia = std::sqrt(direccion.x * direccion.x + direccion.y * direccion.y);

    if (distancia < 5.0f)  // Si está lo suficientemente cerca del punto
    {
        _puntoActual++;
        return;
    }

    // Normalizar y aplicar velocidad
    direccion /= distancia;
    _sprite.move(direccion * _velocidadAutomatica);

    // Actualizar la animación según la dirección
    _fotograma += 0.2f;
    if (_fotograma >= 2) _fotograma = 0;

    if (std::abs(direccion.x) > std::abs(direccion.y))
    {
        if (direccion.x > 0)
        {
            _sprite.setTextureRect({0 + int(_fotograma) * 56, 138, 67, 67});  // Derecha
            _direccionMirada = {1, 0};
        }
        else
        {
            _sprite.setTextureRect({0 + int(_fotograma) * 56, 68, 67, 67});   // Izquierda
            _direccionMirada = {-1, 0};
        }
    }
    else
    {
        if (direccion.y > 0)
        {
            _sprite.setTextureRect({0 + int(_fotograma) * 56, 0, 67, 67});    // Abajo
            _direccionMirada = {0, 1};
        }
        else
        {
            _sprite.setTextureRect({0 + int(_fotograma) * 56, 210, 67, 67});  // Arriba
            _direccionMirada = {0, -1};
        }
    }
}


