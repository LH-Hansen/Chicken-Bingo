#include <Arduino.h>
#include "Controllers/MovementController.h"

MovementController chicken;

void setup() { chicken.begin(); }
void loop()  { chicken.move(); }
