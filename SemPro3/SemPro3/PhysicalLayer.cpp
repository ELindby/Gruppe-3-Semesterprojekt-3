#include "PhysicalLayer.h"

PhysicalLayer::PhysicalLayer() {}
PhysicalLayer::~PhysicalLayer() {}

PhysicalLayer::PhysicalLayer(char input) {
	DTMFConverter(input);
	ToneGenerator();
}

