#include "Engine.h"

//Engine constructor
Engine::Engine() {
	m_Window.create(VideoMode::getDesktopMode(), "WINDOW");
}

void Engine::run() {
	Clock clock;
	Time time_per_frame;
	//unit testing
	cout << "Starting Particle unit tests..." << endl;
	Particle p(m_Window, 4, { (int)m_Window.getSize().x / 2, (int)m_Window.getSize().y / 2 }, { (int)m_Window.getSize().x / 2, (int)m_Window.getSize().y / 2 });
	p.unitTests();
	cout << "Unit tests complete.  Starting engine..." << endl;

	//game loop
	while (m_Window.isOpen()) {
		time_per_frame = clock.restart();

		input();
		update(static_cast<float>(time_per_frame.asSeconds()));
		draw();

	}

}

void Engine::input() {
	Event aevent;
	if (m_Window.pollEvent(aevent)) {
		//handle window closing
		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			m_Window.close();
		}
		if (aevent.type == Event::Closed) {
			m_Window.close();
		}

		//handle click
		if (aevent.type == Event::MouseButtonPressed) {
			e_clickPos = Mouse::getPosition();
		}
		if (aevent.type == Event::MouseButtonReleased) {
			//create 5 particles
			e_releasePos = Mouse::getPosition();
			//cout << "click: " << e_clickPos.x << " " << e_clickPos.y << endl;
			//cout << "release: " << e_releasePos.x << " " << e_releasePos.y << endl << endl;
			for (int i = 0; i < 5; i++) {
				Particle p(m_Window, rand() % (50 - 25 + 1) + 25, e_clickPos, e_releasePos);//randomizing number of points
				m_particles.push_back(p);
			}
		}
	}
}

void Engine::update(float dtAsSeconds) {//auto type for iterator type (research needed)
	for (auto it = m_particles.begin(); it != m_particles.end();) {
		if (it->getTTL() > 0.0) {
			it->update(dtAsSeconds);
			it++;
		}
		else {
			it = m_particles.erase(it);
		}
	}
}

void Engine::draw() {
	m_Window.clear();
	for (int i = 0; i < m_particles.size(); i++) {
		m_Window.draw(m_particles.at(i));	//polymorphism!
	}
	m_Window.display();
}