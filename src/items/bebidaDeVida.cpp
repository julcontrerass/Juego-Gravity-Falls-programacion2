#include "../../bebidaDeVida.h"

BebidaDeVida::BebidaDeVida(){
    _textur.loadFromFile("./Imagenes/Items/BebidaDeVida.png");
    _sprite.setTexture(_textur);
    _sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height);
}

bool BebidaDeVida::estadoBebidas[3]={false};
int BebidaDeVida::cantBebidas = 0;
int BebidaDeVida::decremento = 0;
void BebidaDeVida::update() {
    // Aquí podrías actualizar el libro si es necesario
}

sf::FloatRect BebidaDeVida::getBounds() const {
    return _sprite.getGlobalBounds();
}


void BebidaDeVida::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(_sprite, states);

}
// Método para establecer la posición del item
void BebidaDeVida::setPosition(const sf::Vector2f& position)
{
    _sprite.setPosition(position);
}

void BebidaDeVida::recolectado(int numBebida){
    estadoBebidas[numBebida] = true;
}

bool BebidaDeVida::bebidasRecolectadas(int numBebida)const{
    return estadoBebidas[numBebida];
}

int BebidaDeVida::cantidadDeBebidas()const{
    cantBebidas =0;
    for(int i=0; i<3; i++){
        if (bebidasRecolectadas(i)){
            cantBebidas ++;
        }
    }
    cantBebidas = cantBebidas-decremento;
    return cantBebidas;
}

void BebidaDeVida::restaBebidas(){
    decremento++;
}

