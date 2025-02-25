#ifndef GRAPHICSRR_H
#define GRAPHICSRR_H

#ifdef _WIN32 
#include <windows.h>
#include <windowsx.h>
#endif
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>
#include "Base/camera.h"
#include "Base/Billboard.h"
#include <iostream>
#include "Base/Scene.h"
#include "Texto.h"
#include "Billboard2D.h"
#include "Jugador.h"
#include "Bailarin.h"
#include "Alien.h"

class Scenario : public Scene {
private:
	SkyDome* sky;
	Terreno* terreno;
	Alien* alien = nullptr;
	Bailarin* bailarin = nullptr;
	Jugador* jugador = nullptr;
	std::vector<Billboard*> billBoard;
	std::vector<Billboard*> elemento1;
	std::vector<Billboard2D*> billBoard2D;
	std::vector<Model*> ourModel;
	Model* camara;
	Water* water;
	float angulo;
	int animacion = 0;
	int animacion2 = 0;
	int frameNave = 1;
	int frameBrillos = 1;
	int framePerro = 1;
	std::vector<Texto*> ourText;
	wchar_t wCoordenadas[350];
	Texto *coordenadas = NULL;
public:
	Scenario(Camera *cam);
	Scenario(Model *camIni);
	void InitGraph(Model *main);

	void inicializaBillboards();

	//el metodo render toma el dispositivo sobre el cual va a dibujar
	//y hace su tarea ya conocida
	Scene* Render();

	std::vector<Model*> *getLoadedModels();
	std::vector<Billboard*> *getLoadedBillboards();
	Model* getMainModel();
	float getAngulo();
	void setAngulo(float angulo);
	SkyDome* getSky();
	Terreno* getTerreno();
	~Scenario();
};

#endif