#include "../estadoDelJuego.h"
estadoDelJuego::estadoDelJuego()
{

}
int estadoDelJuego::vidasDipper = 5;
bool estadoDelJuego::tipoPartida=false;   //siempre arranca en nueva partida
bool estadoDelJuego::cofresAbiertos[3]={false};
bool estadoDelJuego::agarrado1=false;
bool estadoDelJuego::agarrado2=false;
bool estadoDelJuego::agarrado3=false;
bool estadoDelJuego::cuchilloAgarrado = false;
bool estadoDelJuego::ganchoAgarrado= false;
bool estadoDelJuego::linternaAgarrado= false;
bool estadoDelJuego::estadoBebidasDeVida[3]= {false};
bool estadoDelJuego::estadoPocionesVelocidad[3]={false};
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
    for(int i=0; i<3; i++){
        if (getEstadoPociones(i)){
            cantPociones ++;
        }
    }
    cantPociones = cantPociones-decrementoPociones;
    return cantPociones;
}

int estadoDelJuego::contadorDeBebidas()
{
    int cantBebidas =0;
    for(int i=0; i<3; i++){
        if (getEstadoBebidas(i)){
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

bool estadoDelJuego::tresLibros() const{
    bool libros = false;
    if ( getEstadoLibros(1) && getEstadoLibros(2) && getEstadoLibros(3)){
            libros = true;
    }
    return libros;
}

bool estadoDelJuego::estaVivo(std::string nombre){
    if (nombre == "bill"){
        return vidasBill > 0;
    }
    else if (nombre == "gideon"){
        return vidasGideon > 0;
    }
    else if (nombre == "minotauro"){
        return vidasMinotauro > 0;
    }
    else if (nombre == "gnomo"){
        return vidasGnomo > 0;
    }

}




