#include "pocionDeVelocidad.h"

PocionDeVelocidad::PocionDeVelocidad() {
    _textur.loadFromFile("./Imagenes/Items/PocionDeVelocidad.png");
    _sprite.setTexture(_textur);
    _sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height);
}
bool PocionDeVelocidad::estadoPociones[3]={false};
int PocionDeVelocidad::cantPociones = 0;
int PocionDeVelocidad::decremento = 0;
void PocionDeVelocidad::update() {
    // Aquí podrías actualizar el libro si es necesario
}

sf::FloatRect PocionDeVelocidad::getBounds() const {
    return _sprite.getGlobalBounds();
}


void PocionDeVelocidad::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(_sprite, states);

}
// Método para establecer la posición del item
void PocionDeVelocidad::setPosition(const sf::Vector2f& position)
{
    _sprite.setPosition(position);
}

void PocionDeVelocidad::recolectado(int numPocion){
    estadoPociones[numPocion] = true;
}

bool PocionDeVelocidad::pocionesRecolectadas(int numPocion)const{
    return estadoPociones[numPocion];
}

int PocionDeVelocidad::cantidadDePociones()const{
    cantPociones =0;
    for(int i=0; i<3; i++){
        if (pocionesRecolectadas(i)){
            cantPociones ++;
        }
    }

    cantPociones = cantPociones-decremento;

    return cantPociones;
}

void PocionDeVelocidad::restaPociones(){
    decremento++;
}



