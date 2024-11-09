#pragma once
#include <iostream>

class estadoDelJuego{

private:
    static int vidasDipper;
    static bool tipoPartida;
    static bool cofresAbiertos[3];
    static bool agarrado1;  //libros
    static bool agarrado2;
    static bool agarrado3;

    //items
    static bool cuchilloAgarrado;
    static bool ganchoAgarrado;
    static bool linternaAgarrado;
    static bool estadoBebidasDeVida[3];
    static bool estadoPocionesVelocidad[3];

    //personajes
    static bool _debeDesaparecerMabel;
    static bool _debeDesaparecerSoos;
    static bool _debeDesaparecerStan;
    static bool _debeDesaparecerWendy;

    //vidas enemigos
    static int vidasBill;
    static int vidasGideon;
    static int vidasGnomo;
    static int vidasMinotauro;

    static int cantidadPociones;
    static int cantidadBebidas;
    static int decremento;
    static int decrementoPociones;

    static bool muerto;



public:
    estadoDelJuego();
    void continuarPartida();
    void modificarEstadosPersonaje(std::string personaje);
    void modificarEstadosLibros (int numero);
    void modificarEstadosCofres (int numeroCofre);
    void modificarEstadosBebidas(int numeroBebida);
    void modificarEstadosPociones(int numeroPociones);
    void modificarEstadosItems(std::string items);
    bool getEstadoLibros(int numero) const;
    bool getEstadoCofres(int numeroCofre);
    bool getEstadoBebidas(int numeroBebidas);
    bool getEstadoPociones (int numeroPociones);
    bool getEstadosItems (std::string items);
    bool getEstadoPersonajes (std::string personaje) const;
    void modificarVidasDipper(int vida);
    int getVidasDipper();
    int contadorDePociones();
    int contadorDeBebidas();
    void modificarVidasEnemigos (std::string enemigo, int vida);
    int getVidasEnemigos(std::string enemigos);
    int getCantidadPociones();
    int getCantidadBebidas();
    void restarBebidas();
    void restarPociones();
    bool tresLibros() const;
    bool estaVivo(std::string nombre);




};
