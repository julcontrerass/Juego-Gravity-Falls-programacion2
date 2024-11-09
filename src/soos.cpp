#include "../soos.h"
#include <cmath>
Soos::Soos()
    : _fotograma(0), _velocidad(4, 4), _direccionMirada(0, 1),
      _moviendoseAutomaticamente(false), _puntoActual(0),
      _velocidadAutomatica(2.0f),_mostrarDialogo(false), _dialogoActual(0),
      _dialogoCompletado(false), _tiempoDialogo(0),
      _dialogoPermanentementeCompletado(false)
{
    _textura.loadFromFile("./Imagenes/Personajes/soos.png");
    _sprite.setTexture(_textura);
    _sprite.setTextureRect({50, 0, 50, 60});
    _sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height);

    // Definir los puntos de ruta para el movimiento automático
    _puntosDeRuta = {
        sf::Vector2f(78,207),  // Primer destino
        sf::Vector2f(380, 207),  // Segundo destino
        sf::Vector2f(380, 400),  // Segundo destino
        sf::Vector2f(697, 265)  // Destino final
    };

    // FONT DEL DIALGOO
    if (!_fuente.loadFromFile("./font/numeros.ttf")) {
        throw std::runtime_error("No se pudo cargar la fuente para el diálogo");
    }

    //DIALOGO
    _textoDialogo.setFont(_fuente);
    _textoDialogo.setCharacterSize(18);
    _textoDialogo.setFillColor(sf::Color::Black);

    _burbujaDialogo.setFillColor(sf::Color(255, 255, 255, 230));
    _burbujaDialogo.setOutlineColor(sf::Color::Black);
    _burbujaDialogo.setOutlineThickness(2);

    // Inicializar los diálogos directamente
    _dialogos = {
        " Ayuda dipper!"
    };

    _dialogos2 = {
        " Gracias por salvarme",
        " Abri el cofre que tiene",
        " Cosas importantes",
        " Me voy a la cabaña"
    };
}

void Soos::iniciarMovimientoAutomatico()
{
    if (!_moviendoseAutomaticamente)
    {
        _moviendoseAutomaticamente = true;
        _puntoActual = 0;
    }
}

void Soos::actualizarMovimientoAutomatico()
{
    if (!_moviendoseAutomaticamente || estadoDelJuego.getEstadoPersonajes("soos")) return;

    if (_puntoActual >= _puntosDeRuta.size())
    {
        estadoDelJuego.modificarEstadosPersonaje("soos");
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
            _sprite.setTextureRect({0 + int(_fotograma) * 50, 139, 50, 72});  // Derecha
            _direccionMirada = {1, 0};
        }
        else
        {
            _sprite.setTextureRect({0 + int(_fotograma) * 50, 70, 50, 72});   // Izquierda
            _direccionMirada = {-1, 0};
        }
    }
    else
    {
        if (direccion.y > 0)
        {
            _sprite.setTextureRect({0 + int(_fotograma) * 50, 0, 50, 72});    // Abajo
            _direccionMirada = {0, 1};
        }
        else
        {
            _sprite.setTextureRect({0 + int(_fotograma) * 50, 210, 50, 72});  // Arriba
            _direccionMirada = {0, -1};
        }
    }
}

void Soos::update()
{
    if (_moviendoseAutomaticamente)
    {
        actualizarMovimientoAutomatico();
        return;
    }
}

void Soos::draw(sf::RenderTarget& objetivo, sf::RenderStates estados) const
{
    objetivo.draw(_sprite, estados);

    // Selecciona el vector de diálogos según la condición
    const std::vector<std::string>& dialogosActuales = !minotauro.estaVivo() ? _dialogos2 : _dialogos;

    if (_mostrarDialogo && _dialogoActual < static_cast<int>(dialogosActuales.size())) {
        objetivo.draw(_burbujaDialogo, estados);
        objetivo.draw(_textoDialogo, estados);
    }
}

sf::FloatRect Soos::obtenerLimites() const
{
    return _sprite.getGlobalBounds();
}

sf::Vector2f Soos::obtenerPosicion() const
{
    return _sprite.getPosition();
}

void Soos::establecerPosicion(const sf::Vector2f& posicion)
{
    _sprite.setPosition(posicion);
}


// Método para establecer la posición del personaje
void Soos::setPosition(const sf::Vector2f& position)
{
    _sprite.setPosition(position);
    actualizarPosicionDialogo();
}


///DIALOGOS
void Soos::actualizarPosicionDialogo() {
    const std::vector<std::string>& dialogosActuales = !minotauro.estaVivo() ? _dialogos2 : _dialogos;

    if (_mostrarDialogo && _dialogoActual < static_cast<int>(dialogosActuales.size())) {
        _textoDialogo.setString(dialogosActuales[_dialogoActual]);

        // Ajustar el tamaño de la burbuja basado en el texto
        sf::FloatRect textoBounds = _textoDialogo.getLocalBounds();
        _burbujaDialogo.setSize(sf::Vector2f(textoBounds.width + 20, textoBounds.height + 20));

        // Posicionar la burbuja arriba del personaje
        sf::Vector2f posPersonaje = _sprite.getPosition();
        _burbujaDialogo.setPosition(
            posPersonaje.x - _burbujaDialogo.getSize().x/2,
            posPersonaje.y - _sprite.getGlobalBounds().height - _burbujaDialogo.getSize().y - 10
        );

        // Posicionar el texto dentro de la burbuja
        _textoDialogo.setPosition(
            _burbujaDialogo.getPosition().x + 10,
            _burbujaDialogo.getPosition().y + 5
        );
    }
}

void Soos::actualizarDialogo(float deltaTime) {
    if (!_mostrarDialogo || _dialogoCompletado || _dialogoPermanentementeCompletado) return;

    _tiempoDialogo += deltaTime;

    if (_tiempoDialogo >= TIEMPO_ENTRE_DIALOGOS) {
        _tiempoDialogo = 0;
        _dialogoActual++;

        if (_dialogoActual >= static_cast<int>(_dialogos.size())) {
            _mostrarDialogo = false;
            _dialogoCompletado = true;
            _dialogoPermanentementeCompletado = true;
        } else {
            actualizarPosicionDialogo();
        }
    }
}

void Soos::iniciarDialogo() {
    if (!_dialogoCompletado) {
        _mostrarDialogo = true;
        _dialogoActual = 0;
        _tiempoDialogo = 0;
        _dialogoCompletado = false;
        actualizarPosicionDialogo();
    }
}

sf::Vector2f Soos::getPosition() const {
    return _sprite.getPosition();
}


