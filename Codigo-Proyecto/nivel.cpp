#include "nivel.h"

nivel::nivel()
    : terminado(false),
    victoria(false) {}

nivel::~nivel(){}

bool nivel::estaTerminado() const{
    return terminado;
}
bool nivel::hayVictoria() const{
    return victoria;
}

jugador& nivel::getJugador()
{
    return bob;
}

void nivel::setTerminado(bool estado)
{
    terminado = estado;
}

void nivel::setVictoria(bool estado)
{
    victoria = estado;
}