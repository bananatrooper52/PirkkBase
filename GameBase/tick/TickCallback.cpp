#include "TickCallback.h"

using namespace PirkkBase::Ticking;

TickCallback::TickCallback(std::function<void(float)> _callback, float _cycleDuration) :
	callback(_callback),
	cycleDuration(_cycleDuration)
{}

void TickCallback::setCycleDuration(float _cycleDuration) {
	cycleDuration = _cycleDuration;
}

void TickCallback::update(float _delta) {
	delta += _delta;

	// Enough time has passed for next update?
	if (delta >= cycleDuration) {

		// Call callback and reset delta
		callback(delta);
		delta = 0;
	}
}
