#pragma once
#ifndef ALIEN_H
#define ALIEN_H

#include "Base/model.h"
#include <iostream>

class Alien : public Model {
private:
	float salud;

public:
	float vida = getSalud();
	Alien(const std::string& path, Camera* camera, float salud = -60.0f)
		: Model(path, camera), salud(salud) {

	}
	void TomaDano(float cantidad) {
		salud -= cantidad;
		if (salud <= 0.0f) {
			MessageBox(NULL, L"Lo mataste!", L"YAY", MB_OK | MB_ICONEXCLAMATION);
		}
		else {
			std::cout << "Vida: " << salud << std::endl;
		}
	}
	float getSalud() const {
		return salud;
	}
};

#endif
