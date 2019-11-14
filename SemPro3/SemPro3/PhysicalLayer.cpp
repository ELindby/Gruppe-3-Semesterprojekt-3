#include "PhysicalLayer.h"

PhysicalLayer::PhysicalLayer() {}
PhysicalLayer::~PhysicalLayer() {}

PhysicalLayer::PhysicalLayer(char input) {
	DTMFConverter(input, *lowDTMFL, *lowDTMFU, *highDTMFL, *highDTMFU);
	ToneGenerator(*lowDTMFL, *lowDTMFU, *highDTMFL, *highDTMFU);
}
