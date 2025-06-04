#ifndef FLIGHT_RESERVATION_HPP
#define FLIGHT_RESERVATION_HPP

#include <string>
#include <vector>
#include "DisplayClass.hpp"
#include "Flight.hpp"
#include "Customer.hpp"
using namespace std;
class FlightReservation : public DisplayClass {
private:
    // Index of a customer’s flight in their personal list
    int flightIndexInCustomerList_{-1};

    // Helpers
    void addTicketsToExistingBooking(Customer& customer, int numTickets);
    void addTicketsToNewBooking(Customer& customer, int numTickets);
    bool isFlightInCustomerList(const vector<Flight*>& flights, 
                                Flight* flight);
    int  flightPosition(const vector<Flight*>& flights, 
                        Flight* flight);
    string flightStatus(Flight* flight) const;

    // Formatting helpers
    string bookingToString(int serial, Flight* flight, 
                                const Customer& customer) const;
    string userToString(int serial, const Customer& customer, 
                             int ticketIndex) const;

public:
    // Booking and cancellation
    void bookFlight(const string& flightNo, int numTickets, 
                    const string& userID);
    void cancelFlight(const string& userID);

    // DisplayClass implementations
    void displayFlightsRegisteredByOneUser(const string& userID) override;
    void displayHeaderForUsers(const Flight& flight,
                               const vector<Customer>& users) override;
    void displayRegisteredUsersForAllFlight() override;
    void displayRegisteredUsersForASpecificFlight(
        const string& flightNo) override;
    void displayArtWork(int option) override;
};

#endif // FLIGHT_RESERVATION_HPP
