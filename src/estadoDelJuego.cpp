#include "../estadoDelJuego.h"
estadoDelJuego::estadoDelJuego()
{

}
int estadoDelJuego::vidas = 5;
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


void estadoDelJuego::continuarPartida()
{
    estadoDelJuego::tipoPartida=true;
}

void estadoDelJuego::modificarEstadosPersonaje(std::string personaje)
{
    if (personaje == "Mabbel")
    {
        estadoDelJuego::_debeDesaparecerMabel=true;
    }
    else if(personaje == "Soos")
    {
       estadoDelJuego::_debeDesaparecerSoos=true;
    }
    else if (personaje == "Stan")
    {
         estadoDelJuego::_debeDesaparecerStan=true;
    }
    else if (personaje =="Wendy" )
    {
        estadoDelJuego::_debeDesaparecerWendy=true;
    }

}

void estadoDelJuego::modificarEstadosLibros(int numero)
{
    switch(numero)
    {
    case 1:
        estadoDelJuego::agarrado1=true;
        break;
    case 2:
         estadoDelJuego::agarrado2=true;
         break;
    case 3:
         estadoDelJuego::agarrado3= true;
         break;

    }
}

void estadoDelJuego::modificarEstadosCofres(int numeroCofres)
{
    estadoDelJuego::cofresAbiertos [numeroCofres]= true;
}

void estadoDelJuego::modificarEstadosBebidas(int numeroBebidas)
{
    estadoDelJuego::estadoBebidasDeVida[numeroBebidas]= true;
}

void estadoDelJuego::modificarEstadosPociones(int numeroPociones)
{
    estadoDelJuego::estadoPocionesVelocidad[numeroPociones]=true;
}

void estadoDelJuego::modificarEstadosItems(std::string items)
{
    if (items == "Cuchillo")
    {
          estadoDelJuego::cuchilloAgarrado= true;
    }
    else if (items =="Gancho")
    {
        estadoDelJuego::ganchoAgarrado= true;
    }
    else if (items == "Linterna")
    {
       estadoDelJuego::linternaAgarrado = true;
    }
}

bool estadoDelJuego::getEstadoLibros(int numero)
{
    switch(numero)
    {
    case 1:
        return estadoDelJuego::agarrado1;
        break;
    case 2:
         return estadoDelJuego::agarrado2;
         break;
    case 3:
         return estadoDelJuego::agarrado3;
    }
}

bool estadoDelJuego::getEstadoCofres(int numeroCofre)
{
     return estadoDelJuego::cofresAbiertos [numeroCofre];
}

bool estadoDelJuego::getEstadoBebidas (int numeroBebidas)
{
    return estadoDelJuego::estadoBebidasDeVida[numeroBebidas];
}

bool estadoDelJuego::getEstadoPociones(int numeroPociones)
{
    return estadoDelJuego::estadoPocionesVelocidad[numeroPociones];
}

bool estadoDelJuego::getEstadosItems (std::string items)
{
    if (items == "Cuchillo")
    {
         return estadoDelJuego::cuchilloAgarrado;
    }
    else if (items =="Gancho")
    {
        return estadoDelJuego::ganchoAgarrado;
    }
    else if (items == "Linterna")
    {
        return estadoDelJuego::linternaAgarrado;
    }
}

bool estadoDelJuego::getEstadoPersonajes (std::string personaje)
{
    if (personaje == "Mabbel")
    {
       return estadoDelJuego::_debeDesaparecerMabel;
    }
    else if(personaje == "Soos")
    {
      return estadoDelJuego::_debeDesaparecerSoos;
    }
    else if (personaje == "Stan")
    {
        return estadoDelJuego::_debeDesaparecerStan;
    }
    else if (personaje =="Wendy" )
    {
       return estadoDelJuego::_debeDesaparecerWendy;
    }
}






