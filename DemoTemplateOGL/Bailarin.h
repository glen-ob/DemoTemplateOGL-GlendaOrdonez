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
        setTranslate(&position); // Establece la posición inicial 
    }
    
    void conJugador(const glm::vec3& JugadorPosition, float deltaTime) {
        if (YAconJugador) return;

        glm::vec3 currentPosition = *getTranslate();

        // Actualiza la posición
        setTranslate(&currentPosition);
        setNextTranslate(&currentPosition);

        float distance = glm::distance(currentPosition, JugadorPosition);
        if (distance < 1.0f) {
            YAconJugador = true;
            std::cout << "Está atacando!" << std::endl;
        }
    }

    // Inflige daño al jugador
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