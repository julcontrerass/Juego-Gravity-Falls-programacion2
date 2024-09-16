#include "PrimerMapa.h"
#include "segundoMapa.h"  // Incluimos la cabecera de SegundoMapa

PrimerMapa::PrimerMapa()
    : libroRecogido(false), libroVisible(false), vidas(20), invulnerableTime(sf::Time::Zero), invulnerableDuration(sf::seconds(1)),
      currentSpeechBubblePhase(0)
{
    // Inicializamos las zonas bloqueadas (árboles y agua)
    zonasBloqueadas.push_back(sf::FloatRect(0, 0, 1147, 100));
    zonasBloqueadas.push_back(sf::FloatRect(734, 100, 250, 63));
    zonasBloqueadas.push_back(sf::FloatRect(1140, 0, 89, 33));
    zonasBloqueadas.push_back(sf::FloatRect(1229, 0, 317, 117));
    zonasBloqueadas.push_back(sf::FloatRect(0, 0, 102, 1020));
    zonasBloqueadas.push_back(sf::FloatRect(1400, 0, 155, 780));
    zonasBloqueadas.push_back(sf::FloatRect(1330, 350, 65, 300));
    zonasBloqueadas.push_back(sf::FloatRect(330, 370, 160, 95));
    zonasBloqueadas.push_back(sf::FloatRect(1470, 767, 51, 200));
    zonasBloqueadas.push_back(sf::FloatRect(1444, 900, 102, 45));
    zonasBloqueadas.push_back(sf::FloatRect(0, 1000, 1546, 111));
    zonasBloqueadas.push_back(sf::FloatRect(320, 930, 200, 65));
    zonasBloqueadas.push_back(sf::FloatRect(832, 930, 700, 80));
    zonasBloqueadas.push_back(sf::FloatRect(300, 670, 400, 80));
    zonasBloqueadas.push_back(sf::FloatRect(700, 480, 129, 300));
    zonasBloqueadas.push_back(sf::FloatRect(812, 357, 210, 330));
    zonasBloqueadas.push_back(sf::FloatRect(694, 475, 169, 205));
    zonasBloqueadas.push_back(sf::FloatRect(1000, 410, 263, 230));
    zonasBloqueadas.push_back(sf::FloatRect(833, 687, 79, 100));

    // Cargar música de fondo
    if (!music.openFromFile("musicaFondoJuego.wav"))
    {
        throw std::runtime_error("No se pudo cargar la música de fondo.");
    }
    music.setLoop(true);
    music.setVolume(5.f);
    music.play();

    // Música del cofre
    if (!musicCofre.openFromFile("images/cofreAbriendo.wav"))
    {
        throw std::runtime_error("No se pudo cargar la música del cofre.");
    }

    // Agregar tipo de letra
    if (!font.loadFromFile("font/letragravityFalls.ttf") || !font2.loadFromFile("font/numeros.ttf"))
    {
        throw std::runtime_error("No se pudo cargar la fuente.");
    }

    // Configurar textos
    text.setFont(font);
    text.setString("Materiales: ");
    text.setCharacterSize(24);
    text.setPosition(10, 10);
    text.setFillColor(sf::Color::Black);

    textVidas.setFont(font2);
    textVidas.setPosition(10, 70);
    textVidas.setFillColor(sf::Color::Black);

    // Cargar la textura del libro para la interfaz
    sf::Texture libroTextureUI;
    if (!libroTextureUI.loadFromFile("images/Libro1.png"))
    {
        throw std::runtime_error("No se pudo cargar la textura del libro.");
    }

    libroSpriteUI.setTexture(libroTextureUI);
    libroSpriteUI.setPosition(170, 0);

    // Cargar la textura de fondo
    if (!tex.loadFromFile("images/mapa.png"))
    {
        throw std::runtime_error("No se pudo cargar la textura del mapa.");
    }

    imagen.setTexture(tex);

    // Crear una vista que actúa como cámara
    camera.setSize(sf::Vector2f(800, 600));

    // Initialize the speech bubble phases
    speechBubblePhases = {
        {"Hola soy dipper!", sf::seconds(4.0f)},
        {"Me ayudas a rescatar a mabel?", sf::seconds(4.0f)},
        {"Debemos encontrar al gnomo!", sf::seconds(4.0f)},
        {"Luego abrir el cofre \n para encontrar el libro", sf::seconds(4.0f)},
        {"", sf::seconds(0.0f)}

    };

    // Inicializar el globo de diálogo
    speechBubble.setFont(font2);
    speechBubble.setString(speechBubblePhases[currentSpeechBubblePhase].text);
    speechBubble.setCharacterSize(18);
    speechBubble.setFillColor(sf::Color::Black);

    // Crear fondo para el globo de diálogo
    speechBubbleBackground.setFillColor(sf::Color(255, 255, 255, 200));
    speechBubbleBackground.setOutlineColor(sf::Color::Black);
    speechBubbleBackground.setOutlineThickness(2.f);

    // Iniciar el temporizador del globo de diálogo
    speechBubbleTimer.restart();
}

void PrimerMapa::run(sf::RenderWindow &window)
{
    // Game loop (finaliza cuando cierra la ventana)
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
                window.close();  // Cerrar la ventana si se presiona 'Escape' o se cierra la ventana
        }

        update(window);  // Pasamos window a update para poder cambiar de mapa
        handleCollisions();

        if (vidas <= 0)
        {
            GameOver gameOver;
            gameOver.run(window); // Mostrar pantalla de fin de juego
            window.close(); // Cerrar la ventana después de mostrar la pantalla de fin de juego
        }

        window.clear();
        draw(window);
        window.display();
    }
}

void PrimerMapa::update(sf::RenderWindow &window)
{
    sf::Vector2f oldPosition = dipper.getPosition();
    dipper.update();
    sf::Vector2f newPosition = dipper.getPosition();
    sf::FloatRect newBounds = dipper.getBounds();
    newBounds.left = newPosition.x - newBounds.width / 2;
    newBounds.top = newPosition.y - newBounds.height / 2;

    bool collision = false;
    sf::Vector2f correction(0.f, 0.f);

    for (const auto& zona : zonasBloqueadas)
    {
        if (newBounds.intersects(zona))
        {
            collision = true;

            // Calcula la corrección necesaria en cada eje
            if (oldPosition.x < zona.left && newPosition.x + newBounds.width / 2 > zona.left)
                correction.x = zona.left - (newPosition.x + newBounds.width / 2);
            else if (oldPosition.x > zona.left + zona.width && newPosition.x - newBounds.width / 2 < zona.left + zona.width)
                correction.x = (zona.left + zona.width) - (newPosition.x - newBounds.width / 2);

            if (oldPosition.y < zona.top && newPosition.y + newBounds.height / 2 > zona.top)
                correction.y = zona.top - (newPosition.y + newBounds.height / 2);
            else if (oldPosition.y > zona.top + zona.height && newPosition.y - newBounds.height / 2 < zona.top + zona.height)
                correction.y = (zona.top + zona.height) - (newPosition.y - newBounds.height / 2);
        }
    }

    if (collision)
    {
        // Aplica la corrección, priorizando el eje con mayor corrección
        if (std::abs(correction.x) > std::abs(correction.y))
            newPosition.x += correction.x;
        else
            newPosition.y += correction.y;

        dipper.setPosition(newPosition);
    }

    // Actualizar el gnomo y manejar la invulnerabilidad
    gnomo.update(dipper.getPosition());

    if (invulnerableTime > sf::Time::Zero)
    {
        invulnerableTime -= invulnerableClock.restart();
    }
    else
    {
        invulnerableTime = sf::Time::Zero;
        invulnerableClock.restart();
    }

    // Actualizar la cámara
    camera.setCenter(dipper.getPosition());

    // Limitar la cámara a los bordes del mapa
    sf::Vector2f cameraCenter = camera.getCenter();
    cameraCenter.x = std::max(400.f, std::min(cameraCenter.x, static_cast<float>(tex.getSize().x) - 400.f));
    cameraCenter.y = std::max(300.f, std::min(cameraCenter.y, static_cast<float>(tex.getSize().y) - 300.f));
    camera.setCenter(cameraCenter);

    textVidas.setString("Vidas: " + std::to_string(vidas));

    // Verificar si el personaje está en la posición para cambiar al segundo mapa
    sf::Vector2f dipperPos = dipper.getPosition();
    if (dipperPos.x >= 1400 && dipperPos.x <= 1700 && dipperPos.y >= 774 && dipperPos.y <= 870)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            SegundoMapa segundoMapa;
            segundoMapa.setPersonajePosition(sf::Vector2f(1410, 200));
            segundoMapa.run(window);
            return;
        }
    }

    // Update speech bubble
    sf::Time elapsedTime = speechBubbleTimer.getElapsedTime();
    if (elapsedTime >= speechBubblePhases[currentSpeechBubblePhase].duration)
    {
        currentSpeechBubblePhase++;
        if (currentSpeechBubblePhase >= speechBubblePhases.size())
        {
            currentSpeechBubblePhase = speechBubblePhases.size() - 1;  // Stay on the last phase (empty text)
        }
        speechBubble.setString(speechBubblePhases[currentSpeechBubblePhase].text);
        speechBubbleTimer.restart();
    }
}

void PrimerMapa::handleCollisions()
{
    if (dipper.isCollision(libro1))
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && libroVisible)
        {
            libro1.setVisible(false);
            libroRecogido = true;
        }
    }

    if (dipper.isCollision(gnomo) && invulnerableTime == sf::Time::Zero)
    {
        vidas--;
        invulnerableTime = invulnerableDuration;
    }

    if (dipper.isCollision(cof))
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !cof.estaAbierto())
        {
            musicCofre.play();
            cof.cambiarTextura();
            libro1.setVisible(true);
            libroVisible = true;
        }
    }
}

void PrimerMapa::draw(sf::RenderWindow &window)
{
    window.setView(camera);
    window.draw(imagen);
    window.draw(libro1);
    window.draw(cof);
    window.draw(dipper);
    window.draw(gnomo);

    // Draw the speech bubble if it's not the empty phase
    if (currentSpeechBubblePhase < speechBubblePhases.size() - 1)
    {
        sf::Vector2f dipperPosition = dipper.getPosition();

        // Get the bounds of the text
        sf::FloatRect textBounds = speechBubble.getLocalBounds();

        // Calculate the width and height of the dialog box
        float bubbleWidth = std::max(textBounds.width + 20.f, 200.f); // Ensure a minimum width
        float bubbleHeight = textBounds.height + 20.f;

        // Calculate the position of the dialog box
        sf::Vector2f bubblePosition(
            dipperPosition.x - bubbleWidth / 2,
            dipperPosition.y - bubbleHeight - 50.f
        );

        // Adjust the position of the text within the box (centered)
        speechBubble.setPosition(
            bubblePosition.x + (bubbleWidth - textBounds.width) / 2,
            bubblePosition.y + (bubbleHeight - textBounds.height) / 6
        );

        // Adjust the background of the dialog box
        speechBubbleBackground.setSize(sf::Vector2f(bubbleWidth, bubbleHeight));
        speechBubbleBackground.setPosition(bubblePosition);

        window.draw(speechBubbleBackground);
        window.draw(speechBubble);
    }

    // Dibujar elementos de la interfaz de usuario
    window.setView(window.getDefaultView());
    window.draw(text);
    window.draw(textVidas);

    // Si el libro ha sido recogido, dibujamos el icono en la esquina
    if (libroRecogido)
    {
        window.draw(libroSpriteUI);
    }
}




