#include "PhysicalLayer.h"

PhysicalLayer::PhysicalLayer() {}
PhysicalLayer::~PhysicalLayer() {}

PhysicalLayer::PhysicalLayer(char input) {
	DTMFConverter converter(input, *lowDTMFL, *lowDTMFU, *highDTMFL, *highDTMFU);
	ToneGenerator();
}

