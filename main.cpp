#include "Navigator.h"
#include <iostream>

int main() {
    CubicleNavigator nav;
    
    // 1. Load the data
    nav.loadEmployees("employees.csv");
    
    // 2. Execute search
    nav.findPath("Andy", "Pala");
    
    return 0;
}