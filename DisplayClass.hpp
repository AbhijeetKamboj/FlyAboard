// DisplayClass.hpp
#ifndef DISPLAY_CLASS_HPP
#define DISPLAY_CLASS_HPP

#include <string>
#include <vector>

// Forward declarations
class Flight;
class Customer;

class DisplayClass {
public:
    // Virtual destructor to ensure proper cleanup of derived classes
    virtual ~DisplayClass() = default;

    // Shows all passengers registered on every flight
    virtual void displayRegisteredUsersForAllFlight() = 0;

    // Shows passengers registered on the flight identified by flightNum
    virtual void displayRegisteredUsersForASpecificFlight(const std::string& flightNum) = 0;

    // Prints a header (or table) for a given flight and list of customers
    virtual void displayHeaderForUsers(const Flight& flight,
                                       const std::vector<Customer>& customers) = 0;

    // Lists all flights a single user (by userID) has registered for
    virtual void displayFlightsRegisteredByOneUser(const std::string& userID) = 0;

    // Shows ASCII art or banners based on the option code
    virtual void displayArtWork(int option) = 0;
};

#endif // DISPLAY_CLASS_HPP
