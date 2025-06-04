#ifndef FLIGHT_HPP
#define FLIGHT_HPP

#include <string>
#include <vector>
#include <array>
#include <memory>
#include <chrono>
#include "FlightDistance.hpp"
#include "Customer.hpp"
#include "RandomGenerator.hpp"
using namespace std;
class Flight : public FlightDistance {
private:
    // Flight data
    string flightSchedule_;
    string flightNumber_;
    string fromCity_;
    string toCity_;
    string gate_;
    int numOfSeats_{0};
    double distMiles_{0.0};
    double distKm_{0.0};
    string flightTime_;
    vector<Customer*> registeredCustomers_;
    size_t customerIndex_{0};

    // Static collection of all flights
    static vector<unique_ptr<Flight>> flightList_;
    static int nextFlightDay_;

    // Helpers
    string formatDateTime(const chrono::system_clock::time_point& tp,
                               const char* fmt) const;
    string calculateFlightTime(double miles);

    // New helper to compute next schedule string
    string computeNextSchedule();

public:
    // Constructors
    Flight();
    Flight(const string& schedule,
           const string& number,
           int seats,
           const array<array<string,3>,2>& chosenDestinations,
           const array<string,3>& distances,
           const string& gate);

    // Scheduler and CRUD
    void flightScheduler(); 
    void addNewCustomerToFlight(Customer* cust);
    void addTicketsToExistingCustomer(Customer* cust, int numTickets);
    bool isCustomerAlreadyAdded(const vector<Customer*>& list,
                                Customer* cust);
    void deleteFlight(const string& flightNum);

    // Time & distance
    string fetchArrivalTime() const;
    array<string,3> calculateDistance(double lat1,double lon1,
                                                double lat2,double lon2) const override;

    // Display
    static void displayFlightSchedule();
    string toString(int index) const override;

    // Getters
    int getNoOfSeats() const;
    const string& getFlightNumber() const;
    static const vector<unique_ptr<Flight>>& getFlightList();
    const vector<Customer*>& getRegisteredCustomers() const;
    const string& getFlightSchedule() const;
    const string& getFromCity() const;
    const string& getToCity() const;
    const string& getGate() const;
    const string& getFlightTimeStr() const;
};

#endif // FLIGHT_HPP
