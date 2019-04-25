#pragma once

#include <functional>

namespace pirkk::ticking {
	class TickCallback {
	private:
		// Callback function to call each tick cycle
		// The float is the delta time of the cycle, in case of irregular cycle duration
		std::function<void(float)> callback;

		float cycleDuration; // Length of each tick cycle
		float delta = 0; // Time since last update
		int tickAcc = 0; // Accumulated ticks
		float tps = 0; // Current ticks per second
		float ttnt = 0; // Time to next tick
	public:

		TickCallback(std::function<void(float)> callback, float cycleDuration);

		// Change the duration per tick cycle
		void setCycleDuration(float cycleDuration);

		// Increment timestamps and call callback if ready
		void update(float delta);

		int getTps();
	};
}