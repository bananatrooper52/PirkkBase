#pragma once

#include <functional>

namespace PirkkBase {
	class TickCallback {
	private:
		// Callback function to call each tick cycle
		// The float is the delta time of the cycle, in case of irregular cycle duration
		std::function<void(float)> callback;
		
		float cycleDuration; // Length of each tick cycle
		float delta = 0; // Time since last update
	public:

		TickCallback(std::function<void(float)> _callback, float _cycleDuration);

		// Change the duration per tick cycle
		void setCycleDuration(float _cycleDuration);

		// Increment timestamps and call callback if ready
		void update(float _delta);
	};
}