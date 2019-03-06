#include "TickManager.h"

#include <iostream>
#include <chrono>

using namespace PirkkBase;

std::vector<TickCallback> TickManager::callbacks;
std::atomic_bool TickManager::running = false;

void TickManager::start() {
	if (running) {
		std::cerr << "TickManager is already started" << std::endl;
		return;
	}

	running = true;
	loop();
}

void TickManager::stop() {
	if (!running) {
		std::cerr << "TickManager is already stopped" << std::endl;
		return;
	}

	running = false;
}

void TickManager::loop() {

	// Store last iteration timestamp
	std::chrono::steady_clock::time_point lt = std::chrono::high_resolution_clock::now();

	while (running) {

		// Compute delta
		std::chrono::steady_clock::time_point now = std::chrono::high_resolution_clock::now();
		float delta = (float)std::chrono::duration_cast<std::chrono::nanoseconds>(now - lt).count() / 1000000000.f;
		lt = now;

		// Update each callback
		for (size_t i = 0; i < callbacks.size(); i++) {
			callbacks[i].update(delta);
		}
	}
}

void TickManager::registerCallback(TickCallback callback) {
	callbacks.push_back(callback);
}