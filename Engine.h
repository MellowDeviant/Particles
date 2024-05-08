#pragma once
#pragma once
#include <SFML/Graphics.hpp>
#include "Particle.h"
using namespace sf;
using namespace std;

class Engine
{
private:
	// A regular RenderWindow
	RenderWindow m_Window;

	//vector for Particles
	vector<Particle> m_particles;

	// Private functions for internal use only
	void input();
	void update(float dtAsSeconds);
	void draw();

	Vector2i e_clickPos; //keep track of where the initial click is
	//no local version of this variable was working
	Vector2i e_releasePos;

public:
	// The Engine constructor
	Engine();

	// Run will call all the private functions
	void run();

};