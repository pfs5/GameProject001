// SFML_project.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Application.h"
#include "DefaultState.h"
#include "Util.h"

#include <iostream>
#include <SFML/Graphics.hpp>

int main() {	
	srand(time(NULL));

	Application app{};
	app.addGameState(new DefaultState(app));

	app.runMainLoop();

    return 0;
}

