// Example usage for RadioHead library by William Espinoza.

#include "RadioHead.h"

// Initialize objects from the lib
RadioHead radioHead;

void setup() {
    // Call functions on initialized library objects that require hardware
    radioHead.begin();
}

void loop() {
    // Use the library's initialized objects and functions
    radioHead.process();
}
