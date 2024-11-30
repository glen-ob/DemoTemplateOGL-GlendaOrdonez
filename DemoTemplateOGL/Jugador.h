#pragma once
#ifndef JUGADOR_H
#define JUGADOR_H

#include "Base/model.h"
#include "Alien.h"
#include <iostream>

class Jugador : public Model {
private:
    float Salud; 
    float ataqueDano; 

public:
    // Constructor del jugador
    Jugador(const std::string& path, glm::vec3 position, Camera* camera, float ataqueDano = 40.0f)
        : Model(path, camera), Salud(100.0f), ataqueDano(ataqueDano) {
        setTranslate(&position);
    }


    // Verifica si el jugador está colisionando con otro objeto
    bool checkCollision(Alien& alien) {
        if (this->colisionaCon(alien)) {
            MessageBox(NULL, L"Atacando!", L" ", MB_OK | MB_ICONEXCLAMATION);
            return true;
        }
        return false;
    }

    // Aplica daño al jugador
    void tomaDano(float cantidad) {
        Salud -= cantidad;
        if (Salud <= 0.0f) {
            MessageBox(NULL, L"Te mataron!", L"Perdiste!", MB_OK | MB_ICONEXCLAMATION);
            // Lógica de derrota del jugador
        }
    }

    // Aplica daño a otro modelo 
    void ataque(Alien alien) {
        // Aquí podrías implementar cómo el ataque afecta al objetivo
        std::cout << "Has inflingido " << ataqueDano << " de ataque!" << std::endl;
    }

    // Obtiene la vida actual del jugador
    float getSalud() const {
        return Salud;
    }
};

#endif
