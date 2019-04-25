#include "TickCallback.hpp"

using namespace pirkk::ticking;

TickCallback::TickCallback(std::function<void(float)> callback, float cycleDuration) :
	callback(callback),
	cycleDuration(cycleDuration)
{}

void TickCallback::setCycleDuration(float cycleDuration) {
	cycleDuration = cycleDuration;
}

void TickCallback::update(float delta) {
	this->delta += delta;
	ttnt += delta;

	// Enough time has passed for next update?
	if (this->delta >= cycleDuration) {

		// Call callback and reset delta
		callback(this->delta);
		this->delta = 0;

		tickAcc++;
	}

	if (ttnt >= 1) {
		tps = tickAcc;
		tickAcc = 0;
		ttnt = 0;
	}
}

int TickCallback::getTps() {
	return tps;
}