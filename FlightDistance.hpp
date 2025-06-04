#ifndef FLIGHTDISTANCE_HPP
#define FLIGHTDISTANCE_HPP

#include <string>
#include <array>

class FlightDistance {
public:
    virtual ~FlightDistance() = default;

    /// Return a formatted string representation (e.g., table row).
    virtual std::string toString(int index) const = 0;

    /**
     * Calculate distances between two coordinates.
     * Returns an array of three strings, e.g.:
     *   [0] = distance in nautical miles
     *   [1] = distance in kilometers
     *   [2] = distance in statute miles (rounded)
     */
    virtual std::array<std::string,3>
    calculateDistance(double lat1, double lon1,
                      double lat2, double lon2) const = 0;

    /**
     * Prints guidelines about how distances and times are measured.
     */
    void displayMeasurementInstructions() const;
};

#endif // FLIGHTDISTANCE_HPP
