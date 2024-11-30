#pragma once
#ifndef BAILARIN_H
#define BAILARIN_H

#include "Base/model.h"
#include "Jugador.h"
#include <iostream>

#include <glm/glm.hpp>

class Bailarin : public Model {
private:
    float ataqueDano;
    bool YAconJugador;

public:
    
    Bailarin(const std::string& path, glm::vec3 position, Camera* camera, float ataqueDano = 50.0f)
        : Model(path, camera), ataqueDano(ataqueDano), YAconJugador(false) {
        setTranslate(&position); // Establece la posici�n inicial 
    }
    
    void conJugador(const glm::vec3& JugadorPosition, float deltaTime) {
        if (YAconJugador) return;

        glm::vec3 currentPosition = *getTranslate();

        // Actualiza la posici�n
        setTranslate(&currentPosition);
        setNextTranslate(&currentPosition);

        float distance = glm::distance(currentPosition, JugadorPosition);
        if (distance < 1.0f) {
            YAconJugador = true;
            std::cout << "Est� atacando!" << std::endl;
        }
    }

    // Inflige da�o al jugador
    void ataqueJugador(Jugador jugador) {
        if (YAconJugador) {
            std::cout << "El alien inflige " << ataqueDano << " de ataque." << std::endl;
            jugador.tomaDano(getataqueDano());
        }
    }
    bool HaAtacadoJugador() const {
        return YAconJugador;
    }
    float getataqueDano() {
        return ataqueDano;
    }

};

#endif