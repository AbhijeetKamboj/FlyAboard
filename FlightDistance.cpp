#include "FlightDistance.hpp"
#include <iostream>
#include <iomanip>
#include <string>

void FlightDistance::displayMeasurementInstructions() const {
    const std::string symbols = "+---------------------------+";
    const std::string title   = "|   SOME IMPORTANT GUIDELINES   |";
    const int totalWidth = 100;

    // Helper to center a line within totalWidth
    auto printCentered = [&](const std::string& line){
        int padding = std::max(0, (totalWidth - static_cast<int>(line.size())) / 2);
        std::cout << std::string(padding, ' ') << line << "\n";
    };

    std::cout << "\n\n";
    printCentered(symbols);
    printCentered(title);
    printCentered(symbols);
    std::cout << "\n"
              << "\t1. Distance calculations are based on airport coordinates (latitudes & longitudes).\n\n"
              << "\t2. Actual flight distances may vary per airline routing policies and airspace restrictions.\n\n"
              << "\t3. Flight time depends on factors such as ground speed (assumed 450 knots), aircraft type,\n"
                 "\t   altitude, and weather conditions.\n\n"
              << "\t4. Arrival time is approximate; plan a buffer of ±1 hour.\n\n"
              << "\t5. Departure time is when the aircraft pushes back from the gate. Arrival time is when\n"
              << "\t   it pulls into the gate (not runway touchdown).\n\n";
}
