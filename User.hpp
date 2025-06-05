#ifndef USER_HPP
#define USER_HPP

#include <string>

// Forward declarations to break cycles
class RolesAndPermissions;
class Flight;
class FlightReservation;
class Customer;

class User {
public:
    /// Entrypoint: runs the entire console application.
    static int run();

    /// Prints the top‐level menu.
    static void displayMainMenu();

    /// Prints the user manual/instructions.
    static void manualInstructions();

    /// A small welcome banner.
    static void welcomeScreen(int option);

    /// Prints contextual ASCII banners (e.g. “ADMIN LOGIN”).
    static void printArtWork(int option);

protected:
    User() = default;  // allow derived classes to construct
};

#endif // USER_HPP
