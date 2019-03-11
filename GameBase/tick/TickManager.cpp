#include "TickManager.h"

#include <iostream>
#include <chrono>

using namespace PirkkBase;

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
		for (auto &it : callbacks) {
			it.second->update(delta);
		}
	}
}

void TickManager::registerCallback(const char *name, TickCallback *callback) {
	callbacks[name] = callback;
}

void TickManager::unregisterCallback(const char *name) {
	callbacks.erase(name);
}

TickCallback *TickManager::getCallback(const char *name) {
	auto it = callbacks.find(name);
	if (it == callbacks.end()) throw std::runtime_error(std::string("Couldn't find callback: ") + std::string(name));
	return it->second;
}