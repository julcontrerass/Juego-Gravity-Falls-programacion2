#include "../estadoDelJuego.h"
#include <vector>
#include <iostream>
#include <sstream>
estadoDelJuego::estadoDelJuego()
{

}
int estadoDelJuego::vidasDipper = 5;
bool estadoDelJuego::tipoPartida=false;   //siempre arranca en nueva partida
bool estadoDelJuego::cofresAbiertos[3]= {false};
bool estadoDelJuego::agarrado1=false;
bool estadoDelJuego::agarrado2=false;
bool estadoDelJuego::agarrado3=false;
bool estadoDelJuego::cuchilloAgarrado = false;
bool estadoDelJuego::ganchoAgarrado= false;
bool estadoDelJuego::linternaAgarrado= false;
bool estadoDelJuego::estadoBebidasDeVida[3]= {false};
bool estadoDelJuego::estadoPocionesVelocidad[3]= {false};
bool estadoDelJuego::_debeDesaparecerMabel=false;
bool estadoDelJuego::_debeDesaparecerSoos=false;
bool estadoDelJuego::_debeDesaparecerStan=false;
bool estadoDelJuego::_debeDesaparecerWendy=false;
int estadoDelJuego::vidasBill =5;
int estadoDelJuego::vidasGideon =5;
int estadoDelJuego::vidasGnomo =5;
int estadoDelJuego::vidasMinotauro =5;
int estadoDelJuego::cantidadBebidas=0;
int estadoDelJuego::cantidadPociones=0;
int estadoDelJuego::decremento=0;
int estadoDelJuego::decrementoPociones=0;
bool estadoDelJuego::muerto=false;
std::string estadoDelJuego::jugadorActual = "";
int estadoDelJuego::mapaActual = 0;


void estadoDelJuego::continuarPartida()
{
    tipoPartida=true;
}

void estadoDelJuego::modificarEstadosPersonaje(std::string personaje)
{
    if (personaje == "mabbel")
    {
        _debeDesaparecerMabel=true;
    }
    else if(personaje == "soos")
    {
        _debeDesaparecerSoos=true;
    }
    else if (personaje == "stan")
    {
        _debeDesaparecerStan=true;
    }
    else if (personaje =="wendy" )
    {
        _debeDesaparecerWendy=true;
    }

}

void estadoDelJuego::modificarEstadosLibros(int numero)
{
    switch(numero)
    {
    case 1:
        agarrado1=true;
        break;
    case 2:
        agarrado2=true;
        break;
    case 3:
        agarrado3= true;
        break;

    }
}

void estadoDelJuego::modificarEstadosCofres(int numeroCofres)
{
    cofresAbiertos [numeroCofres]= true;
}

void estadoDelJuego::modificarEstadosBebidas(int numeroBebidas)
{
    estadoBebidasDeVida[numeroBebidas]= true;
}

void estadoDelJuego::modificarEstadosPociones(int numeroPociones)
{
    estadoPocionesVelocidad[numeroPociones]=true;
}

void estadoDelJuego::modificarEstadosItems(std::string items)
{
    if (items == "cuchillo")
    {
        cuchilloAgarrado= true;
    }
    else if (items =="gancho")
    {
        ganchoAgarrado= true;
    }
    else if (items == "linterna")
    {
        linternaAgarrado = true;
    }
}

bool estadoDelJuego::getEstadoLibros(int numero) const
{
    switch(numero)
    {
    case 1:
        return agarrado1;
        break;
    case 2:
        return agarrado2;
        break;
    case 3:
        return agarrado3;
        break;
    }
}

bool estadoDelJuego::getEstadoCofres(int numeroCofre)
{
    return cofresAbiertos [numeroCofre];
}

bool estadoDelJuego::getEstadoBebidas (int numeroBebidas)
{
    return estadoBebidasDeVida[numeroBebidas];
}

bool estadoDelJuego::getEstadoPociones(int numeroPociones)
{
    return estadoPocionesVelocidad[numeroPociones];
}

bool estadoDelJuego::getEstadosItems (std::string items)
{
    if (items == "cuchillo")
    {
        return cuchilloAgarrado;
    }
    else if (items =="gancho")
    {
        return ganchoAgarrado;
    }
    else if (items == "linterna")
    {
        return linternaAgarrado;
    }
}

bool estadoDelJuego::getEstadoPersonajes (std::string personaje) const
{
    if (personaje == "mabbel")
    {
        return _debeDesaparecerMabel;
    }
    else if(personaje == "soos")
    {
        return _debeDesaparecerSoos;
    }
    else if (personaje == "stan")
    {
        return _debeDesaparecerStan;
    }
    else if (personaje =="wendy" )
    {
        return _debeDesaparecerWendy;
    }
}

void estadoDelJuego::modificarVidasDipper(int vida)
{
    if(vidasDipper < 5 && vida == 1)
    {
        vidasDipper++;
    }
    else if(vidasDipper > 0 && vida == -1)
    {
        vidasDipper--;
    }
}

int estadoDelJuego::getVidasDipper()
{
    return vidasDipper;
}

int estadoDelJuego::contadorDePociones()
{
    int cantPociones =0;
    for(int i=0; i<3; i++)
    {
        if (getEstadoPociones(i))
        {
            cantPociones ++;
        }
    }
    cantPociones = cantPociones-decrementoPociones;
    return cantPociones;
}

int estadoDelJuego::contadorDeBebidas()
{
    int cantBebidas =0;
    for(int i=0; i<3; i++)
    {
        if (getEstadoBebidas(i))
        {
            cantBebidas ++;
        }
    }
    cantBebidas = cantBebidas-decremento;
    return cantBebidas;
}

void estadoDelJuego::restarBebidas()
{
    decremento++;
}

void estadoDelJuego::restarPociones()
{
    decrementoPociones++;
}

void estadoDelJuego::modificarVidasEnemigos(std::string enemigo, int vida)
{
    if(enemigo == "gnomo")
    {
        if(vidasGnomo < 5 && vida == 1)
        {
            vidasGnomo++;
        }
        else if(vidasGnomo > 0 && vida == -1)
        {
            vidasGnomo--;
        }
    }
    else if(enemigo == "gideon")
    {
        if(vidasGideon < 5 && vida == 1)
        {
            vidasGideon++;
        }
        else if(vidasGideon > 0 && vida == -1)
        {
            vidasGideon--;
        }
    }
    else if(enemigo == "minotauro")
    {
        if(vidasMinotauro < 5 && vida == 1)
        {
            vidasMinotauro++;
        }
        else if(vidasMinotauro > 0 && vida == -1)
        {
            vidasMinotauro--;
        }
    }
    else if(enemigo == "bill")
    {
        if(vidasBill < 5 && vida == 1)
        {
            vidasBill++;
        }
        else if(vidasBill > 0 && vida == -1)
        {
            vidasBill--;
        }
    }
}

int estadoDelJuego::getVidasEnemigos(std::string enemigos)
{
    if(enemigos == "gnomo")
    {
        return vidasGnomo;
    }
    else if(enemigos == "gideon")
    {
        return vidasGideon;
    }
    else if(enemigos == "minotauro")
    {
        return vidasMinotauro;
    }
    else if(enemigos == "bill")
    {
        return vidasBill;
    }
}

int estadoDelJuego::getCantidadPociones()
{
    return cantidadPociones;
}

int estadoDelJuego::getCantidadBebidas()
{
    return cantidadBebidas;
}

bool estadoDelJuego::tresLibros() const
{
    bool libros = false;
    if ( getEstadoLibros(1) && getEstadoLibros(2) && getEstadoLibros(3))
    {
        libros = true;
    }
    return libros;
}

bool estadoDelJuego::estaVivo(std::string nombre)
{
    if (nombre == "bill")
    {
        return vidasBill > 0;
    }
    else if (nombre == "gideon")
    {
        return vidasGideon > 0;
    }
    else if (nombre == "minotauro")
    {
        return vidasMinotauro > 0;
    }
    else if (nombre == "gnomo")
    {
        return vidasGnomo > 0;
    }
}

void estadoDelJuego::guardarPartida() {
    if (jugadorActual.empty()) {
        std::cerr << "Error: No se puede guardar partida sin nombre de jugador" << std::endl;
        return;
    }

    // Primero intentamos crear/abrir el archivo temporal
    std::ofstream archivoTemp("datosPartidas.tmp", std::ios::binary);
    if (!archivoTemp) {
        std::cerr << "Error: No se pudo crear el archivo temporal" << std::endl;
        return;
    }

    // Leemos todas las partidas existentes
    std::vector<std::string> partidas;
    cargarPartida(partidas);

    // Verificamos si ya existe una partida con este nombre
    bool partidaExistente = false;
    for (const auto& nombre : partidas) {
        if (nombre == jugadorActual) {
            partidaExistente = true;
            break;
        }
    }

    try {
        // Si existen partidas previas, las copiamos excepto la que vamos a actualizar
        if (!partidas.empty()) {
            std::ifstream archivoOriginal("datosPartidas.dat", std::ios::binary);
            if (archivoOriginal) {
                while (archivoOriginal) {
                    size_t nombreLength;
                    if (!archivoOriginal.read(reinterpret_cast<char*>(&nombreLength), sizeof(nombreLength))) {
                        break;
                    }

                    std::string nombre(nombreLength, '\0');
                    archivoOriginal.read(&nombre[0], nombreLength);

                    // Calcular el tamaño de los datos de la partida
                    size_t dataSize = sizeof(vidasDipper) + sizeof(tipoPartida) +
                                    sizeof(cofresAbiertos) + sizeof(agarrado1) +
                                    sizeof(agarrado2) + sizeof(agarrado3) +
                                    sizeof(cuchilloAgarrado) + sizeof(ganchoAgarrado) +
                                    sizeof(linternaAgarrado) + sizeof(estadoBebidasDeVida) +
                                    sizeof(estadoPocionesVelocidad) + sizeof(_debeDesaparecerMabel) +
                                    sizeof(_debeDesaparecerSoos) + sizeof(_debeDesaparecerStan) +
                                    sizeof(_debeDesaparecerWendy) + sizeof(vidasBill) +
                                    sizeof(vidasGideon) + sizeof(vidasGnomo) +
                                    sizeof(vidasMinotauro) + sizeof(cantidadPociones) +
                                    sizeof(cantidadBebidas) + sizeof(decremento) +
                                    sizeof(decrementoPociones) + sizeof(muerto);

                    std::vector<char> data(dataSize);
                    archivoOriginal.read(data.data(), dataSize);

                    if (nombre != jugadorActual) {
                        // Copiar partida al archivo temporal
                        archivoTemp.write(reinterpret_cast<const char*>(&nombreLength), sizeof(nombreLength));
                        archivoTemp.write(nombre.c_str(), nombreLength);
                        archivoTemp.write(data.data(), dataSize);

                        if (!archivoTemp.good()) {
                            throw std::runtime_error("Error al escribir partida existente");
                        }
                    }
                }
                archivoOriginal.close();
            }
        }

        // Escribir la nueva partida
        size_t nombreLength = jugadorActual.length();
        archivoTemp.write(reinterpret_cast<const char*>(&nombreLength), sizeof(nombreLength));
        archivoTemp.write(jugadorActual.c_str(), nombreLength);

        // Escribir todos los datos del estado
        archivoTemp.write(reinterpret_cast<const char*>(&vidasDipper), sizeof(vidasDipper));
        archivoTemp.write(reinterpret_cast<const char*>(&tipoPartida), sizeof(tipoPartida));
        archivoTemp.write(reinterpret_cast<const char*>(cofresAbiertos), sizeof(cofresAbiertos));
        archivoTemp.write(reinterpret_cast<const char*>(&agarrado1), sizeof(agarrado1));
        archivoTemp.write(reinterpret_cast<const char*>(&agarrado2), sizeof(agarrado2));
        archivoTemp.write(reinterpret_cast<const char*>(&agarrado3), sizeof(agarrado3));
        archivoTemp.write(reinterpret_cast<const char*>(&cuchilloAgarrado), sizeof(cuchilloAgarrado));
        archivoTemp.write(reinterpret_cast<const char*>(&ganchoAgarrado), sizeof(ganchoAgarrado));
        archivoTemp.write(reinterpret_cast<const char*>(&linternaAgarrado), sizeof(linternaAgarrado));
        archivoTemp.write(reinterpret_cast<const char*>(estadoBebidasDeVida), sizeof(estadoBebidasDeVida));
        archivoTemp.write(reinterpret_cast<const char*>(estadoPocionesVelocidad), sizeof(estadoPocionesVelocidad));
        archivoTemp.write(reinterpret_cast<const char*>(&_debeDesaparecerMabel), sizeof(_debeDesaparecerMabel));
        archivoTemp.write(reinterpret_cast<const char*>(&_debeDesaparecerSoos), sizeof(_debeDesaparecerSoos));
        archivoTemp.write(reinterpret_cast<const char*>(&_debeDesaparecerStan), sizeof(_debeDesaparecerStan));
        archivoTemp.write(reinterpret_cast<const char*>(&_debeDesaparecerWendy), sizeof(_debeDesaparecerWendy));
        archivoTemp.write(reinterpret_cast<const char*>(&vidasBill), sizeof(vidasBill));
        archivoTemp.write(reinterpret_cast<const char*>(&vidasGideon), sizeof(vidasGideon));
        archivoTemp.write(reinterpret_cast<const char*>(&vidasGnomo), sizeof(vidasGnomo));
        archivoTemp.write(reinterpret_cast<const char*>(&vidasMinotauro), sizeof(vidasMinotauro));
        archivoTemp.write(reinterpret_cast<const char*>(&cantidadPociones), sizeof(cantidadPociones));
        archivoTemp.write(reinterpret_cast<const char*>(&cantidadBebidas), sizeof(cantidadBebidas));
        archivoTemp.write(reinterpret_cast<const char*>(&decremento), sizeof(decremento));
        archivoTemp.write(reinterpret_cast<const char*>(&decrementoPociones), sizeof(decrementoPociones));
        archivoTemp.write(reinterpret_cast<const char*>(&muerto), sizeof(muerto));

        if (!archivoTemp.good()) {
            throw std::runtime_error("Error al escribir nueva partida");
        }

        archivoTemp.close();

        // Reemplazar el archivo original con el temporal
        if (std::remove("datosPartidas.dat") != 0 && std::ifstream("datosPartidas.dat").good()) {
            throw std::runtime_error("No se pudo eliminar el archivo original");
        }
        if (std::rename("datosPartidas.tmp", "datosPartidas.dat") != 0) {
            throw std::runtime_error("No se pudo renombrar el archivo temporal");
        }

        std::cout << "Partida guardada exitosamente para " << jugadorActual << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error durante el guardado: " << e.what() << std::endl;
        archivoTemp.close();
        std::remove("datosPartidas.tmp");  // Limpiamos el archivo temporal en caso de error
    }
}
void estadoDelJuego::cargarPartida(std::vector<std::string>& nombresGuardados)
{
    nombresGuardados.clear();
    std::ifstream archivo("datosPartidas.dat", std::ios::binary);

    if (!archivo)
    {
        std::cerr << "No se encontró archivo de partidas guardadas." << std::endl;
        return;
    }

    try
    {
        while (archivo && !archivo.eof())
        {
            size_t nombreLength;
            if (!archivo.read(reinterpret_cast<char*>(&nombreLength), sizeof(nombreLength)))
            {
                break;
            }

            // Verificar longitud del nombre válida
            if (nombreLength > 1000 || nombreLength == 0)
            {
                std::cerr << "Nombre de longitud inválida detectado." << std::endl;
                break;
            }

            std::string nombre(nombreLength, '\0');
            if (!archivo.read(&nombre[0], nombreLength))
            {
                break;
            }

            // Verificar si el nombre ya existe en la lista
            bool nombreDuplicado = false;
            for (const auto& nombreGuardado : nombresGuardados)
            {
                if (nombreGuardado == nombre)
                {
                    nombreDuplicado = true;
                    break;
                }
            }

            if (!nombreDuplicado)
            {
                nombresGuardados.push_back(nombre);
            }

            // Saltar el resto de los datos para esta partida
            size_t dataSize = sizeof(vidasDipper) + sizeof(tipoPartida) +
                              sizeof(cofresAbiertos) + sizeof(agarrado1) +
                              sizeof(agarrado2) + sizeof(agarrado3) +
                              sizeof(cuchilloAgarrado) + sizeof(ganchoAgarrado) +
                              sizeof(linternaAgarrado) + sizeof(estadoBebidasDeVida) +
                              sizeof(estadoPocionesVelocidad) + sizeof(_debeDesaparecerMabel) +
                              sizeof(_debeDesaparecerSoos) + sizeof(_debeDesaparecerStan) +
                              sizeof(_debeDesaparecerWendy) + sizeof(vidasBill) +
                              sizeof(vidasGideon) + sizeof(vidasGnomo) +
                              sizeof(vidasMinotauro) + sizeof(cantidadPociones) +
                              sizeof(cantidadBebidas) + sizeof(decremento) +
                              sizeof(decrementoPociones) + sizeof(muerto);

            if (!archivo.seekg(dataSize, std::ios::cur))
            {
                break; // Si no se puede mover el puntero, salimos del bucle
            }

            // Verificar si hemos llegado al final del archivo
            archivo.peek();
            if (archivo.eof())
            {
                break;
            }
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error al cargar nombres de partidas: " << e.what() << std::endl;
    }

    archivo.close();
}

void estadoDelJuego::cargarPartida(const std::string& nombreJugador)
{
    std::ifstream archivo("datosPartidas.dat", std::ios::binary);
    if (!archivo)
    {
        std::cerr << "Error al abrir el archivo para cargar." << std::endl;
        return;
    }

    try
    {
        while (archivo && !archivo.eof())
        {
            size_t nombreLength;
            if (!archivo.read(reinterpret_cast<char*>(&nombreLength), sizeof(nombreLength)))
            {
                break;
            }

            // Verificar longitud del nombre válida
            if (nombreLength > 1000)
            {
                std::cerr << "Nombre de longitud inválida detectado." << std::endl;
                break;
            }

            std::string nombre(nombreLength, '\0');
            if (!archivo.read(&nombre[0], nombreLength))
            {
                break;
            }

            if (nombre == nombreJugador)
            {
                // Encontramos la partida correcta, cargarla
                jugadorActual = nombre;

                // Cargar todas las variables de estado del juego
                archivo.read(reinterpret_cast<char*>(&vidasDipper), sizeof(vidasDipper));
                archivo.read(reinterpret_cast<char*>(&tipoPartida), sizeof(tipoPartida));
                archivo.read(reinterpret_cast<char*>(cofresAbiertos), sizeof(cofresAbiertos));
                archivo.read(reinterpret_cast<char*>(&agarrado1), sizeof(agarrado1));
                archivo.read(reinterpret_cast<char*>(&agarrado2), sizeof(agarrado2));
                archivo.read(reinterpret_cast<char*>(&agarrado3), sizeof(agarrado3));
                archivo.read(reinterpret_cast<char*>(&cuchilloAgarrado), sizeof(cuchilloAgarrado));
                archivo.read(reinterpret_cast<char*>(&ganchoAgarrado), sizeof(ganchoAgarrado));
                archivo.read(reinterpret_cast<char*>(&linternaAgarrado), sizeof(linternaAgarrado));
                archivo.read(reinterpret_cast<char*>(estadoBebidasDeVida), sizeof(estadoBebidasDeVida));
                archivo.read(reinterpret_cast<char*>(estadoPocionesVelocidad), sizeof(estadoPocionesVelocidad));
                archivo.read(reinterpret_cast<char*>(&_debeDesaparecerMabel), sizeof(_debeDesaparecerMabel));
                archivo.read(reinterpret_cast<char*>(&_debeDesaparecerSoos), sizeof(_debeDesaparecerSoos));
                archivo.read(reinterpret_cast<char*>(&_debeDesaparecerStan), sizeof(_debeDesaparecerStan));
                archivo.read(reinterpret_cast<char*>(&_debeDesaparecerWendy), sizeof(_debeDesaparecerWendy));
                archivo.read(reinterpret_cast<char*>(&vidasBill), sizeof(vidasBill));
                archivo.read(reinterpret_cast<char*>(&vidasGideon), sizeof(vidasGideon));
                archivo.read(reinterpret_cast<char*>(&vidasGnomo), sizeof(vidasGnomo));
                archivo.read(reinterpret_cast<char*>(&vidasMinotauro), sizeof(vidasMinotauro));
                archivo.read(reinterpret_cast<char*>(&cantidadPociones), sizeof(cantidadPociones));
                archivo.read(reinterpret_cast<char*>(&cantidadBebidas), sizeof(cantidadBebidas));
                archivo.read(reinterpret_cast<char*>(&decremento), sizeof(decremento));
                archivo.read(reinterpret_cast<char*>(&decrementoPociones), sizeof(decrementoPociones));
                archivo.read(reinterpret_cast<char*>(&muerto), sizeof(muerto));

                archivo.close();
                return;
            }
            else
            {
                // Saltar los datos de esta partida
                size_t dataSize = sizeof(vidasDipper) + sizeof(tipoPartida) +
                                  sizeof(cofresAbiertos) + sizeof(agarrado1) +
                                  sizeof(agarrado2) + sizeof(agarrado3) +
                                  sizeof(cuchilloAgarrado) + sizeof(ganchoAgarrado) +
                                  sizeof(linternaAgarrado) + sizeof(estadoBebidasDeVida) +
                                  sizeof(estadoPocionesVelocidad) + sizeof(_debeDesaparecerMabel) +
                                  sizeof(_debeDesaparecerSoos) + sizeof(_debeDesaparecerStan) +
                                  sizeof(_debeDesaparecerWendy) + sizeof(vidasBill) +
                                  sizeof(vidasGideon) + sizeof(vidasGnomo) +
                                  sizeof(vidasMinotauro) + sizeof(cantidadPociones) +
                                  sizeof(cantidadBebidas) + sizeof(decremento) +
                                  sizeof(decrementoPociones) + sizeof(muerto);

                archivo.seekg(dataSize, std::ios::cur);
            }
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error al cargar partida: " << e.what() << std::endl;
    }

    archivo.close();
}


void estadoDelJuego::borrarPartida(const std::string& nombrePartida)
{
    std::ifstream archivoLectura("datosPartidas.dat", std::ios::binary);
    if (!archivoLectura)
    {
        std::cerr << "Error al abrir el archivo de partidas." << std::endl;
        return;
    }

    // Crear un archivo temporal para almacenar las partidas restantes
    std::ofstream archivoTemporal("temp.dat", std::ios::binary);
    if (!archivoTemporal)
    {
        std::cerr << "Error al crear el archivo temporal." << std::endl;
        archivoLectura.close();
        return;
    }

    bool partidaEncontrada = false;

    // Leer todas las partidas y copiar las que no sean la seleccionada al archivo temporal
    while (archivoLectura && !archivoLectura.eof())
    {
        size_t nombreLength;
        if (!archivoLectura.read(reinterpret_cast<char*>(&nombreLength), sizeof(nombreLength)))
            break;

        if (nombreLength > 1000 || nombreLength == 0)
        {
            archivoLectura.seekg(nombreLength, std::ios::cur);
            continue;
        }

        std::string nombre(nombreLength, '\0');
        if (!archivoLectura.read(&nombre[0], nombreLength))
            break;

        size_t dataSize = sizeof(vidasDipper) + sizeof(tipoPartida) +
                                  sizeof(cofresAbiertos) + sizeof(agarrado1) +
                                  sizeof(agarrado2) + sizeof(agarrado3) +
                                  sizeof(cuchilloAgarrado) + sizeof(ganchoAgarrado) +
                                  sizeof(linternaAgarrado) + sizeof(estadoBebidasDeVida) +
                                  sizeof(estadoPocionesVelocidad) + sizeof(_debeDesaparecerMabel) +
                                  sizeof(_debeDesaparecerSoos) + sizeof(_debeDesaparecerStan) +
                                  sizeof(_debeDesaparecerWendy) + sizeof(vidasBill) +
                                  sizeof(vidasGideon) + sizeof(vidasGnomo) +
                                  sizeof(vidasMinotauro) + sizeof(cantidadPociones) +
                                  sizeof(cantidadBebidas) + sizeof(decremento) +
                                  sizeof(decrementoPociones) + sizeof(muerto);

        std::vector<char> data(dataSize);
        archivoLectura.read(data.data(), dataSize);

        // Si el nombre no coincide, escribir en el archivo temporal
        if (nombre != nombrePartida)
        {
            archivoTemporal.write(reinterpret_cast<const char*>(&nombreLength), sizeof(nombreLength));
            archivoTemporal.write(nombre.data(), nombreLength);
            archivoTemporal.write(data.data(), dataSize);
        }
        else
        {
            partidaEncontrada = true;
        }
    }

    archivoLectura.close();
    archivoTemporal.close();

    // Reemplazar el archivo original por el temporal
    if (partidaEncontrada)
    {
        std::remove("datosPartidas.dat");
        std::rename("temp.dat", "datosPartidas.dat");
    }
    else
    {
        std::remove("temp.dat");
        std::cerr << "No se encontró la partida a borrar." << std::endl;
    }
}


void estadoDelJuego::nuevaPartida()
{
    vidasDipper = 5;
    tipoPartida = false;
    std::fill(std::begin(cofresAbiertos), std::end(cofresAbiertos), false);
    agarrado1 = false;
    agarrado2 = false;
    agarrado3 = false;
    cuchilloAgarrado = false;
    ganchoAgarrado = false;
    linternaAgarrado = false;
    std::fill(std::begin(estadoBebidasDeVida), std::end(estadoBebidasDeVida), false);
    std::fill(std::begin(estadoPocionesVelocidad), std::end(estadoPocionesVelocidad), false);
    _debeDesaparecerMabel = false;
    _debeDesaparecerSoos = false;
    _debeDesaparecerStan = false;
    _debeDesaparecerWendy = false;
    vidasBill = 5;
    vidasGideon = 5;
    vidasGnomo = 5;
    vidasMinotauro = 5;
    cantidadBebidas = 0;
    cantidadPociones = 0;
    decremento = 0;
    decrementoPociones = 0;
    muerto = false;
    mapaActual = 0;
}

void estadoDelJuego::setJugadorActual(const std::string& nombre)
{
    if (nombre.empty())
    {
        std::cerr << "Error: No se puede establecer un nombre de jugador vacío" << std::endl;
        return;
    }
    jugadorActual = nombre;
    std::cout << "Nombre de jugador establecido: " << jugadorActual << std::endl;
}

void estadoDelJuego::modificarMapa(int mapa){
    mapaActual = mapa;
}


