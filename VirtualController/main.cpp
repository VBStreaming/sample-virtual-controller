

#include <iostream>
#include "VirtualController.h"

int main() {
    VirtualController controller;
    if (controller.Initialize()) {
        controller.RunLoop();
    }
    
    controller.Release();

    return -1;
}
