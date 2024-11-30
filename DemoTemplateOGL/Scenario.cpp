#include "Scenario.h"
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include "Alien.h"
#include "Jugador.h"
#include "Bailarin.h"
#include "Base/Utilities.h"
#include "Base/Scene.h"
#include "Scenario.h"
#include <iostream>
#include "Base/model.h"
#ifdef __linux__ 
#define ZeroMemory(x,y) memset(x,0,y)
#define wcscpy_s(x,y,z) wcscpy(x,z)
#define wcscat_s(x,y,z) wcscat(x,z)
#endif

Scenario::Scenario(Camera *cam) {
    glm::vec3 translate;
	glm::vec3 scale;
    Model* model = new Model("models/Cube.obj", cam);
	translate = glm::vec3(0.0f, 0.0f, 3.0f);
	scale = glm::vec3(0.25f, 0.25f, 0.25f);	// it's a bit too big for our scene, so scale it down
	model->setScale(&scale);
	model->setTranslate(&translate);
	InitGraph(model);
}
Scenario::Scenario(Model *camIni) {
    InitGraph(camIni);
	MessageBox(NULL, L"Protege tu granja, elimina los aliens!!", L"Aviso", MB_OK | MB_ICONEXCLAMATION);
}
void Scenario::InitGraph(Model *main) {
    float matAmbient[] = { 1,1,1,1 };
	float matDiff[] = { 1,1,1,1 };
	angulo = 0;
	camara = main;
	//creamos el objeto skydome
	sky = new SkyDome(32, 32, 20, (WCHAR*)L"skydome/noche4.jpg", main->cameraDetails);
	//creamos el terreno
	terreno = new Terreno((WCHAR*)L"skydome/terreno3.jpg", (WCHAR*)L"skydome/texterr-oscuro.jpg", 400, 400, main->cameraDetails);
	water = new Water((WCHAR*)L"textures/terreno.bmp", (WCHAR*)L"textures/water.bmp", 30, 30, camara->cameraDetails);
	glm::vec3 translate;
	glm::vec3 scale;
	glm::vec3 rotation;
	std:: rand();
	bool posicionActual2;
	int posicionActual = 0;
	translate = glm::vec3(-50.0f, 18.0f, -10.0f);		//	POSICION
	water->setTranslate(&translate);
	water->setRotZ(180);
	// load models
	// -----------
	ourModel.emplace_back(main);
	Model* model;
	model = new Model("models/UFO.obj", main->cameraDetails);				//1
	translate = glm::vec3(5.0f, 26.0f, 35.0f);  // (y ,z, x) ?
	model->setTranslate(&translate);
	model->lightColor = glm::vec3(2, 2, 2);					// luz fija
	model->lightPos = glm::vec3(2, 2, 2);
	rotation = glm::vec3(0.0f, 0.0f, 0.0f); //rotation (eje)
	model->setRotY(45); // rotation (angulo)
	ourModel.emplace_back(model);
	alien = new Alien("models/aliensito.obj", main->cameraDetails);				//2
	translate = glm::vec3(1.0f, 20.0f, 25.0f);
	alien->setTranslate(&translate);
	rotation = glm::vec3(0.0f, 0.0f, 0.0f); //rotation (eje)
	alien->setRotY(200); // rotation (angulo)
	ourModel.emplace_back(alien);
	alien = new Alien("models/aliensito.obj", main->cameraDetails);				//2 repetido
	translate = glm::vec3(9.0f, 20.0f, 25.0f);
	alien->setTranslate(&translate);
	rotation = glm::vec3(0.0f, 0.0f, 0.0f); //rotation (eje)
	alien->setRotY(0); // rotation (angulo)
	ourModel.emplace_back(alien);
	alien = new Alien("models/aliensito.obj", main->cameraDetails);				//2 repetido
	translate = glm::vec3(-10.0f, 20.0f, 25.0f);
	alien->setTranslate(&translate);
	rotation = glm::vec3(0.0f, 0.0f, 0.0f); //rotation (eje)
	alien->setRotY(180); // rotation (angulo)
	ourModel.emplace_back(alien);
	alien = new Alien("models/aliensito.obj", main->cameraDetails);				//2 repetido
	translate = glm::vec3(-4.0f, 20.0f, -30.0f);
	alien->setTranslate(&translate);
	rotation = glm::vec3(0.0f, 0.0f, 0.0f); //rotation (eje)
	alien->setRotY(-50); // rotation (angulo)
	ourModel.emplace_back(alien);
	model = new Model("models/caballo.obj", main->cameraDetails);			//4
	translate = glm::vec3(-6.0f, 20.0f, -10.0f);
	model->setTranslate(&translate);
	rotation = glm::vec3(0.0f, 0.0f, 0.0f); //rotation (eje)
	model->setRotY(90); // rotation (angulo)
	scale = glm::vec3(1.7f, 1.7f, 1.7f);
	model->setScale(&scale);
	ourModel.emplace_back(model);
	model = new Model("models/barda.obj", main->cameraDetails);				//5
	translate = glm::vec3(-23.0f, 20.0f, -40.0f);
	model->setTranslate(&translate);
	model->lightColor = glm::vec3(2, 2, 2);					// luz fija
	model->lightPos = glm::vec3(2, 2, 2);
	rotation = glm::vec3(0.0f, 0.0f, 0.0f); //rotation (eje)
	model->setRotY(90); // rotation (angulo)
	ourModel.emplace_back(model);
	model = new Model("models/barda.obj", main->cameraDetails);				//5 repetido
	translate = glm::vec3(23.0f, 20.0f, -40.0f);
	model->setTranslate(&translate);
	rotation = glm::vec3(0.0f, 0.0f, 0.0f); //rotation (eje)
	model->setRotY(90); // rotation (angulo)
	ourModel.emplace_back(model);
	model = new Model("models/bardaABIERTA.obj", main->cameraDetails);				//6			esta va a la izq
	translate = glm::vec3(-26.5f, 20.0f, -29.5f);
	model->setTranslate(&translate);
	rotation = glm::vec3(0.0f, 0.0f, 0.0f); //rotation (eje)
	model->setRotY(0); // rotation (angulo)
	ourModel.emplace_back(model);
	model = new Model("models/bardaABIERTA.obj", main->cameraDetails);				//6 repetido			la derecha
	translate = glm::vec3(5.5f, 20.0f, -29.5f);
	model->setTranslate(&translate);
	rotation = glm::vec3(0.0f, 0.0f, 0.0f); //rotation (eje)
	model->setRotY(0); // rotation (angulo)
	ourModel.emplace_back(model);
	model = new Model("models/casita.obj", main->cameraDetails);		//7
	translate = glm::vec3(0.0f, 19.0f, -60.0f);
	scale = glm::vec3(20, 20, 20);
	model->setTranslate(&translate);
	//model->setScale(&scale);
	rotation = glm::vec3(1.0f, 0.0f, 0.0f); //rotation (eje)
	model->setRotY(0); // rotation (angulo)	
	//delete model->AABB;				model->AABB = NULL;
	ourModel.emplace_back(model);
															//elimina colisiones
			
	model = new Model("models/PlanoDetras.obj", main->cameraDetails);		
	translate = glm::vec3(0.0f, 19.0f, -60.0f);
	scale = glm::vec3(20, 20, 20);
	model->setTranslate(&translate);
	//model->setScale(&scale);
	rotation = glm::vec3(1.0f, 0.0f, 0.0f); //rotation (eje)
	model->setRotY(0); // rotation (angulo)	
	ourModel.emplace_back(model);
	model = new Model("models/PlanoLado.obj", main->cameraDetails);		//der
	translate = glm::vec3(0.0f, 19.0f, -60.0f);
	scale = glm::vec3(20, 20, 20);
	model->setTranslate(&translate);
	//model->setScale(&scale);
	rotation = glm::vec3(1.0f, 0.0f, 0.0f); //rotation (eje)
	model->setRotY(0); // rotation (angulo)	
	ourModel.emplace_back(model);
	model = new Model("models/PlanoLado.obj", main->cameraDetails);			//izq
	translate = glm::vec3(45.0f, 19.0f, -60.0f);
	scale = glm::vec3(20, 20, 20);
	model->setTranslate(&translate);
	//model->setScale(&scale);
	rotation = glm::vec3(1.0f, 0.0f, 0.0f); //rotation (eje)
	model->setRotY(0); // rotation (angulo)	
	ourModel.emplace_back(model);
	model = new Model("models/PlanoFrente.obj", main->cameraDetails);
	translate = glm::vec3(-7.0f, 19.0f, -55.0f);
	scale = glm::vec3(20, 20, 20);
	model->setTranslate(&translate);
	//model->setScale(&scale);
	rotation = glm::vec3(1.0f, 0.0f, 0.0f); //rotation (eje)
	model->setRotY(180); // rotation (angulo)	
	ourModel.emplace_back(model);
	model = new Model("models/PlanoPared.obj", main->cameraDetails);			//der
	translate = glm::vec3(0.0f, 19.0f, -60.0f);
	scale = glm::vec3(20, 20, 20);
	model->setTranslate(&translate);
	//model->setScale(&scale);
	rotation = glm::vec3(1.0f, 0.0f, 0.0f); //rotation (eje)
	model->setRotY(0); // rotation (angulo)	
	ourModel.emplace_back(model);
	model = new Model("models/PlanoPared.obj", main->cameraDetails);			//izq
	translate = glm::vec3(3.0f, 19.0f, -60.0f);
	scale = glm::vec3(20, 20, 20);
	model->setTranslate(&translate);
	//model->setScale(&scale);
	rotation = glm::vec3(1.0f, 0.0f, 0.0f); //rotation (eje)
	model->setRotY(0); // rotation (angulo)	
	ourModel.emplace_back(model);

	model = new Model("models/hand-truck.obj", main->cameraDetails);		//8
	translate = glm::vec3(12.0f, 20.0f, -40.0f);
	model->setTranslate(&translate);
	rotation = glm::vec3(0.0f, 0.0f, 0.0f); //rotation (eje)
	model->setRotY(45); // rotation (angulo)
	ourModel.emplace_back(model);
	model = new Model("models/pala.obj", main->cameraDetails);				//9
	translate = glm::vec3(0.0f, 20.0f, -67.0f);
	model->setTranslate(&translate);
	rotation = glm::vec3(0.0f, 0.0f, 0.0f); //rotation (eje)
	model->setRotY(45); // rotation (angulo)
	ourModel.emplace_back(model);
	model = new Model("models/well.fbx", main->cameraDetails);				//10
	translate = glm::vec3(-16.0f, 20.0f, -20.0f);
	scale = glm::vec3(30, 30, 30);
	model->setTranslate(&translate);
	rotation = glm::vec3(0.0f, 0.0f, 0.0f); //rotation (eje)
	model->setRotY(45); // rotation (angulo)
	ourModel.emplace_back(model);
	model = new Model("models/obeja.obj", main->cameraDetails);				//11
	translate = glm::vec3(-45.0f, 20.0f, -25.0f);
	model->setTranslate(&translate);
	rotation = glm::vec3(0.0f, 0.0f, 0.0f); //rotation (eje)
	ourModel.emplace_back(model);
	model = new Model("models/vaca.obj", main->cameraDetails);	//12, posición random
	translate = glm::vec3(6.0f, 25.0f, 35.0f);
	model->setTranslate(&translate);
	rotation = glm::vec3(0.0f, 0.0f, 0.0f); //rotation (eje)
	srand(time(NULL));
	int randomNumber = rand() % 3;		//genera num random
	switch ((posicionActual + randomNumber) % 4 + 1) {
	case 1:
		model->setRotZ(35); 
		break;
	case 2:
		model->setRotZ(40);
		break;
	case 3:
		model->setRotZ(120);
		break;
	case 4:
		model->setRotZ(90);
		break; 
	}
	//model->setRotZ(35); // rotation (angulo)
	ourModel.emplace_back(model);
	model = new Model("models/vaca.obj", main->cameraDetails);				//12 REPETIDO
	translate = glm::vec3(-10.0f, 20.0f, 20.0f);
	model->setTranslate(&translate);
	rotation = glm::vec3(0.0f, 0.0f, 0.0f); //rotation (eje)
	model->setRotY(-45); // rotation (angulo)
	ourModel.emplace_back(model);
	model = new Model("models/vaca.obj", main->cameraDetails, false, false);			//12 REPETIDO
	translate = glm::vec3(-5.0f, 20.0f, 18.0f);
	scale = glm::vec3(1.0f, 1.0f, 1.0f);
	rotation = glm::vec3(0.0f, 0.0f, 0.0f); //rotation (eje)
	model->setRotY(-50); // rotation (angulo)
	model->setTranslate(&translate);
	model->setScale(&scale);
	ourModel.emplace_back(model);

	model = new Model("models/cerdo.fbx", main->cameraDetails);				//13
	translate = glm::vec3(0.0f, 20.0f, 5.0f);
	model->setTranslate(&translate);
	rotation = glm::vec3(0.0f, 0.0f, 0.0f); //rotation (eje)
	model->setRotX(-90); // rotation (angulo)
	scale = glm::vec3(0.4f, 0.4f, 0.4f);
	model->setScale(&scale);
	ourModel.emplace_back(model);
	model = new Model("models/backpack.obj", main->cameraDetails, false, false);			//14
	translate = glm::vec3(2.0f, 22.0f, -55.0f);
	scale = glm::vec3(1.0f, 1.0f, 1.0f);	
	rotation = glm::vec3(0.0f, 0.0f, 0.0f); //rotation (eje)
	model->setRotY(-140); // rotation (angulo)
	model->setTranslate(&translate);
	model->setScale(&scale);
	ourModel.emplace_back(model);

	model = new Model("models/aliensitoROSA.obj", main->cameraDetails);				//15 alien rosa, posición random
	srand(time(NULL));
	int randomNumber2 = rand() % 3;		//genera num random
	switch ((posicionActual + randomNumber2) % 4 + 1) {
	case 1:
		translate = glm::vec3(14.0f, 20.0f, -40.0f);
		break;
	case 2:
		translate = glm::vec3(10.0f, 20.0f, -10.0f);
		break;
	case 3:
		translate = glm::vec3(24.0f, 20.0f, -50.0f);
		break;
	case 4:
		translate = glm::vec3(3.0f, 20.0f, 0.0f);
		break;
	}
	//translate = glm::vec3(14.0f, 20.0f, -40.0f);
	model->setTranslate(&translate);
	model->lightColor = glm::vec3(3, 3, 3);					// luz fija
	model->lightPos = glm::vec3(3, 3, 3);
	rotation = glm::vec3(0.0f, 0.0f, 0.0f); //rotation (eje)
	ourModel.emplace_back(model);


//	model = new Model("models/Dancing Twerk.dae", main->cameraDetails);				//2
//	translate = glm::vec3(5.0f, 20.0f, 25.0f);
//	model->setTranslate(&translate);
//	//model->lightColor = glm::vec3(5, 5, 5);					// luz fija
//	//model->lightPos = glm::vec3(5, 5, 5);
//	rotation = glm::vec3(0.0f, 0.0f, 0.0f); //rotation (eje)
//	model->setRotY(180); // rotation (angulo)
//	scale = glm::vec3(0.5f, 0.5f, 0.5f);
//	model->setScale(&scale);
//	ourModel.emplace_back(model);
//
//	try{
//	Animation *ani = new Animation("models/Dancing Twerk.dae", model->GetBoneInfoMap(), model->GetBoneCount());
//	model->setAnimator(new Animator(ani));
//}catch(...){
//	cout << "Could not load animation!\n";
//}

bailarin = new Bailarin("models/bailando.fbx", translate, main->cameraDetails);
translate = glm::vec3(-10.0f, terreno->Superficie(5.0f, 20.0f), -25.0f);
scale = glm::vec3(0.5f, 0.5f, 0.5f);	
bailarin->setTranslate(&translate);
bailarin->setScale(&scale);
bailarin->setRotY(0);
ourModel.emplace_back(bailarin);
try {
		Animation* ani = new Animation("models/bailando.fbx", bailarin->GetBoneInfoMap(), bailarin->GetBoneCount());
		bailarin->setAnimator(new Animator(ani));

}
	catch (...) {
		cout << "Could not load animation!\n";
	}

	bailarin = new Bailarin("models/hiphop.fbx", translate, main->cameraDetails);
	translate = glm::vec3(20.0f, terreno->Superficie(5.0f, 20.0f), -20.0f);
	scale = glm::vec3(0.5f, 0.5f, 0.5f);
	bailarin->setTranslate(&translate);
	bailarin->setScale(&scale);
	bailarin->setRotY(0);
	ourModel.emplace_back(bailarin);
	try {
		Animation* ani = new Animation("models/hiphop.fbx", bailarin->GetBoneInfoMap(), bailarin->GetBoneCount());
		bailarin->setAnimator(new Animator(ani));

	}
	catch (...) {
		cout << "Could not load animation!\n";
	}


	//model = new Model("models/bailando.fbx", translate, main->cameraDetails);
	//translate = glm::vec3(-10.0f, terreno->Superficie(5.0f, 20.0f), -25.0f);
	//scale = glm::vec3(0.5f, 0.5f, 0.5f);
	//model->setTranslate(&translate);
	//model->setScale(&scale);
	//model->setRotY(0);
	//ourModel.emplace_back(model);
	//try {
	//	Animation* ani = new Animation("models/bailando.fbx", model->GetBoneInfoMap(), model->GetBoneCount());
	//	model->setAnimator(new Animator(ani));

	//}
	//catch (...) {
	//	cout << "Could not load animation!\n";
	//}

	//// Crear instancias de Model para los aliens
	//model = ("models/aliensito.obj", translate, camara);
	//model->alien = alien;  // Asociar el alien1 con el modelo

	//model = new Model("models/aliensitoROSA.obj", translate, camara);
	//model->alien = alien;  // Asociar el alien2 con el modelo


	//	model = new Model("models/alienREAL.obj", main->cameraDetails);				//2
	//translate = glm::vec3(5.0f, 20.0f, 25.0f);
	//model->setTranslate(&translate);
	////model->lightColor = glm::vec3(5, 5, 5);					// luz fija
	////model->lightPos = glm::vec3(5, 5, 5);
	//rotation = glm::vec3(0.0f, 0.0f, 0.0f); //rotation (eje)
	//model->setRotY(180); // rotation (angulo)
	//scale = glm::vec3(0.5f, 0.5f, 0.5f);
	//model->setScale(&scale);
	//ourModel.emplace_back(model);

	//model = new Model("models/fogata.obj", main->cameraDetails);
	//translate = glm::vec3(0.0f, 10.0f, 25.0f);
	//model->setTranslate(&translate);
	//rotation = glm::vec3(1.0f, 0.0f, 0.0f); //rotation X
	//model->setRotX(45); // 45� rotation
	//ourModel.emplace_back(model);
	//model= new Model("models/pez.obj", main->cameraDetails);
	//translate = glm::vec3(0.0f, 7.0f, 50.0f);
	//model->setTranslate(&translate);
	//ourModel.emplace_back(model);
	//model = new Model("models/dancing_vampire.dae", main->cameraDetails);
	//translate = glm::vec3(0.0f, terreno->Superficie(0.0f, 60.0f) , 60.0f);
	//scale = glm::vec3(0.1f, 0.1f, 0.1f);	// it's a bit too big for our scene, so scale it down
	//model->setTranslate(&translate);
	//model->setScale(&scale);
	//model->setRotY(90);
	//ourModel.emplace_back(model);
/*	try{
		Animation *ani = new Animation("models/dancing_vampire.dae", model->GetBoneInfoMap(), model->GetBoneCount());
	    model->setAnimator(new Animator(ani));
	}catch(...){
		cout << "Could not load animation!\n";
	}*/


	glm::vec3 JugadorPosition = glm::vec3(-10.0f, terreno->Superficie(5.0f, 20.0f), -25.0f);
	float deltaTime = gameTime.deltaTime / 1000.0f; 	
	for (auto& model : ourModel) {
		Bailarin* bailarin = NULL;
		if (bailarin) {
			bailarin->conJugador(JugadorPosition, deltaTime); // Mueve el monstruo hacia la casa

			if (bailarin->HaAtacadoJugador()) { 
				jugador->tomaDano(bailarin->getataqueDano()); // Aplica daño 
			}
		}
	}


	inicializaBillboards();
	std::wstring prueba(L" ");
	ourText.emplace_back(new Texto(prueba, 20, 0, 0, SCR_HEIGHT, 0, camara));
	billBoard2D.emplace_back(new Billboard2D((WCHAR*)L"billboards/salva.png", 6, 6, 200, 450, 0, camara->cameraDetails));
	scale = glm::vec3(400.0f, 150.0f, 0.0f);	
	billBoard2D.back()->setScale(&scale);
	wchar_t componente[100] = { 0 };
	wcscpy_s(wCoordenadas, 350, L"X: ");
	swprintf(componente, 100, L"%f", getMainModel()->getTranslate()->x);
	wcscat_s(wCoordenadas, 350, componente);
	wcscat_s(wCoordenadas, 350, L" Y: ");
	swprintf(componente, 100, L"%f", getMainModel()->getTranslate()->y);
	wcscat_s(wCoordenadas, 350, componente);
	wcscat_s(wCoordenadas, 350, L" Z: ");
	swprintf(componente, 100, L"%f", getMainModel()->getTranslate()->z);
	wcscat_s(wCoordenadas, 350, componente);
	coordenadas = new Texto((WCHAR*)wCoordenadas, 15, 0, 0, 0, 0, camara);
}

void Scenario::inicializaBillboards() {
	float ye = terreno->Superficie(0, 20);
	billBoard.emplace_back(new Billboard((WCHAR*)L"billboards/Arbol.png", 6, 6, 0, ye - 1, 0, camara->cameraDetails));

	ye = terreno->Superficie(5, -15);
	billBoard.emplace_back(new Billboard((WCHAR*)L"billboards/Arbol2.png", 6, 6, 5, ye - 1, -5, camara->cameraDetails));

	ye = terreno->Superficie(-9, -15);
	billBoard.emplace_back(new Billboard((WCHAR*)L"billboards/Arbol3.png", 8, 8, -9, ye - 1, -15, camara->cameraDetails));
}

	//el metodo render toma el dispositivo sobre el cual va a dibujar
	//y hace su tarea ya conocida
Scene* Scenario::Render() {
	//borramos el biffer de color y el z para el control de profundidad a la 
	//hora del render a nivel pixel.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
//	glClearColor(255.0f, 255.0f, 255.0f, 255.0f);

	// Actualizamos la camara
	camara->cameraDetails->CamaraUpdate(camara->getRotY(), camara->getTranslate());

	if (this->animacion > 10) { // Timer se ejecuta cada 1000/30 = 33.333 ms
		float ye = terreno->Superficie(5, -5);
		Billboard* temporal = billBoard[1];
		wchar_t textura[50] = {L"billboards/nave"};
		if (this->frameNave != 1)
			wcscat_s(textura, 50, to_wstring(this->frameNave).c_str());
		wcscat_s(textura, 50, L".png");
		billBoard[1] = new Billboard((WCHAR*)textura, 20, 20, 5, ye - 1, 35, camara->cameraDetails);
		if (this->frameNave == 7) {
			this->frameNave = 1;
		}
		else {
			this->frameNave++;
		}
		this->animacion = 0;
		delete temporal;
	}
	else {
		animacion++;
	}

	//Billboard *elemento1 = nullptr;
	//if (this->animacion2 > 10) { // Timer se ejecuta cada 1000/30 = 33.333 ms
	//	float ye = terreno->Superficie(5, -5);
	//	Billboard* temporal = elemento1[1];
	//	wchar_t textura2[50] = {L"billboards/spark"};
	//	if (this->frameBrillos != 1)
	//		wcscat_s(textura2, 50, to_wstring(this->frameBrillos).c_str());
	//	wcscat_s(textura2, 50, L".png");
	//	elemento1[1] = new Billboard((WCHAR*)textura2, 10, 10, 5, ye - 1, 28, camara->cameraDetails);
	//	if (this->frameBrillos == 24) {
	//		this->frameBrillos = 1;
	//	}
	//	else {
	//		this->frameBrillos++;
	//	}
	//	this->animacion2 = 0;
	//	delete temporal;
	//}
	//else {
	//	animacion2++;
	//}


	//if (this->animacion > 10) { // Timer se ejecuta cada 1000/30 = 33.333 ms
	//	float ye = terreno->Superficie(5, -5);
	//	Billboard* temporal = billBoard[1];
	//	wstring textura = L"billboards/spark" +
	//		(this->frameBrillos == 1 ? L"" : to_wstring(this->frameBrillos)) + L".png";
	//	billBoard[1] = new Billboard((WCHAR*)textura.c_str(), 20, 20, 5, ye - 1, 30, camara->cameraDetails);		//primeros dos son de escala
	//	if (this->frameBrillos == 24) {
	//		this->frameBrillos = 1;
	//	}
	//	else {
	//		this->frameBrillos++;
	//	}
	//	this->animacion = 0;
	//	delete temporal;
	//}
	//else {
	//	animacion++;
	//}


	//if (this->animacion > 25) { // Timer se ejecuta cada 1000/30 = 33.333 ms
	//	float ye = terreno->Superficie(5, -5);
	//	Billboard* temporal = billBoard[1];
	//	wstring textura = L"billboards/perro" +
	//		(this->framePerro == 1 ? L"" : to_wstring(this->framePerro)) + L".png";
	//	billBoard[1] = new Billboard((WCHAR*)textura.c_str(), 20, 20, 5, ye - 1, -5, camara->cameraDetails);		//primeros dos son de escala
	//	if (this->framePerro == 4) {
	//		this->framePerro = 1;
	//	}
	//	else {
	//		this->framePerro++;
	//	}
	//	this->animacion = 0;
	//	delete temporal;
	//}
	//else {
	//	animacion++;
	//}

	Model* vaca = NULL;
	bool vacaMovida = 0;
	for (Model* model : ourModel)
		if (model->name.compare("vaca") == 0) {
			vaca = model;
			break;
		}
	if (vaca != NULL) {
		glm::vec3 &posicion = *vaca->getTranslate();
		posicion.y = posicion.y + 1 * (gameTime.deltaTime / 1000);
	}

	Model* UFO = NULL;
	bool naveRotación = 0;
	for (Model* model : ourModel)
		if (model->name.compare("UFO") == 0) {
			UFO = model;
			break;
		}
	if (UFO != NULL) {
		glm::vec3 &posicion = *UFO->getTranslate();
		posicion.y = posicion.y + .2 * (gameTime.deltaTime / 1000);	//checar angulos z y x
	}

	// Decimos que dibuje la media esfera
	sky->Draw();
	// Ahora el terreno
	terreno->Draw();
	water->Draw();
	// Dibujamos cada billboard que este cargado en el arreglo de billboards.
	for (int i = 0; i < billBoard.size(); i++)
		billBoard[i]->Draw();
	for (int i = 0; i < billBoard2D.size(); i++)
		billBoard2D[i]->Draw();
	// Dibujamos cada modelo que este cargado en nuestro arreglo de modelos
	for (int i = 0; i < ourModel.size(); i++) {
		ourModel[i]->Draw();
	}
	for (int i = 0; i < ourText.size(); i++) {
		ourText[i]->Draw();
	}
	
	// No es optimo ya que crea el texto cada renderizado....
	wchar_t componente[100] = { 0 };
	wcscpy_s(wCoordenadas, 350, L"X: ");
	swprintf(componente, 100, L"%f", getMainModel()->getTranslate()->x);
	wcscat_s(wCoordenadas, 350, componente);
	wcscat_s(wCoordenadas, 350, L" Y: ");
	swprintf(componente, 100, L"%f", getMainModel()->getTranslate()->y);
	wcscat_s(wCoordenadas, 350, componente);
	wcscat_s(wCoordenadas, 350, L" Z: ");
	swprintf(componente, 100, L"%f", getMainModel()->getTranslate()->z);
	wcscat_s(wCoordenadas, 350, componente);
	coordenadas->initTexto((WCHAR*)wCoordenadas);
	coordenadas->Draw();
	// Le decimos a winapi que haga el update en la ventana
	return this;
}
	
std::vector<Model*> *Scenario::getLoadedModels() {
	return &ourModel;
}
std::vector<Billboard*> *Scenario::getLoadedBillboards() {
	return &billBoard;
}
Model* Scenario::getMainModel() {
	return this->camara;
}
float Scenario::getAngulo() {
	return this->angulo;
}
void Scenario::setAngulo(float angulo) {
	this->angulo = angulo;
}
SkyDome* Scenario::getSky() {
	return sky;
}
Terreno* Scenario::getTerreno() {
	return terreno;
}

	Scenario::~Scenario() {
	if (this->sky != NULL) {
		delete this->sky;
		this->sky = NULL;
	}
	if (this->terreno != NULL) {
		delete this->terreno;
		this->terreno = NULL;
	}
	if (billBoard.size() > 0)
		for (int i = 0; i < billBoard.size(); i++)
			delete billBoard[i];
	if (billBoard2D.size() > 0)
		for (int i = 0; i < billBoard2D.size(); i++)
			delete billBoard2D[i];
	this->billBoard.clear();
	if (ourText.size() > 0)
		for (int i = 0; i < ourText.size(); i++)
			delete ourText[i];
	this->ourText.clear();
	if (ourModel.size() > 0)
		for (int i = 0; i < ourModel.size(); i++)
			if (ourModel[i] != camara)
			delete ourModel[i];
	this->ourModel.clear();

}
