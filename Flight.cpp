// Flight.cpp
#include "Flight.hpp"
#include <iomanip>
#include <sstream>
#include <random>
#include <iostream>
using namespace std;
using namespace chrono;

// Helper functions for angle conversions
static double deg2rad(double deg) {
    return deg * (3.14159265358979323846 / 180.0);
}

static double rad2deg(double rad) {
    return rad * (180.0 / 3.14159265358979323846);
}

// Static member definitions
vector<unique_ptr<Flight>> Flight::flightList_;
int Flight::nextFlightDay_ = 0;

const vector<unique_ptr<Flight>>&
Flight::getFlightList() {
    return flightList_;
}
// Helper to format chrono::time_point
string Flight::formatDateTime(const system_clock::time_point& tp,
                                   const char* fmt) const {
    auto timeT = system_clock::to_time_t(tp);
    ostringstream ss;
    ss << put_time(localtime(&timeT), fmt);
    return ss.str();
}

// Default ctor
Flight::Flight()
  : flightSchedule_(), flightNumber_(), fromCity_(),
    toCity_(), gate_() {}

// Parameterized ctor
Flight::Flight(const string& schedule,
               const string& number,
               int seats,
               const array<array<string,3>,2>& chosenDestinations,
               const array<string,3>& distances,
               const string& gate)
  : flightSchedule_(schedule),
    flightNumber_(number),
    fromCity_(chosenDestinations[0][0]),
    toCity_(chosenDestinations[1][0]),
    gate_(gate),
    numOfSeats_(seats),
    distMiles_(stod(distances[0])),
    distKm_(stod(distances[1]))
{
    flightTime_ = calculateFlightTime(distMiles_);
}

#include <chrono>

// Generate a batch of random flights
void Flight::flightScheduler() {
    const int numOfFlights = 15;
    RandomGenerator rnd;
    for (int i = 0; i < numOfFlights; ++i) {
        auto dests = rnd.randomDestinations();               // array<array<string,3>,2>
        auto dists = calculateDistance(
            stod(dests[0][1]), stod(dests[0][2]),
            stod(dests[1][1]), stod(dests[1][2])
        );
        string schedule = computeNextSchedule();
        string number   = rnd.randomFlightNumbGen(2,1);
        int seats            = rnd.randomNumOfSeats();
        string g        = rnd.randomFlightNumbGen(1,30);
        flightList_.push_back(make_unique<Flight>(
            schedule, number, seats, dests, dists, g
        ));
    }
}

string Flight::computeNextSchedule() {
    using namespace chrono;
    system_clock::time_point now = system_clock::now();
    // Add nextFlightDay_ days to now
    system_clock::time_point flightTime = now + hours(24 * nextFlightDay_);
    // Increment for next call
    ++nextFlightDay_;
    // Format date/time string
    return formatDateTime(flightTime, "%Y-%m-%d %H:%M");
}

// Register or update tickets
void Flight::addNewCustomerToFlight(Customer* cust) {
    registeredCustomers_.push_back(cust);
}

void Flight::addTicketsToExistingCustomer(Customer* cust, int numTickets) {
    cust->addExistingFlightToCustomerList(customerIndex_, numTickets);
}

bool Flight::isCustomerAlreadyAdded(const vector<Customer*>& list,
                                    Customer* cust)
{
    for (size_t i = 0; i < list.size(); ++i) {
        if (list[i]->getUserID() == cust->getUserID()) {
            customerIndex_ = i;
            return true;
        }
    }
    return false;
}

// Time and distance calculations
string Flight::calculateFlightTime(double miles) {
    const double speed = 450.0; // knots
    double hours = miles / speed;
    int h = static_cast<int>(hours);
    int m = static_cast<int>((hours - h) * 60 + 0.5);
    m = (m + 2) / 5 * 5;        // round to nearest 5 minutes
    if (m >= 60) { m -= 60; ++h; }
    ostringstream ss;
    ss << setw(2) << setfill('0') << h
       << ':' << setw(2) << setfill('0') << m;
    return ss.str();
}

array<string,3> Flight::calculateDistance(double lat1,double lon1,
                                                   double lat2,double lon2) const
{
    double theta = lon1 - lon2;
    double dist = sin(deg2rad(lat1)) * sin(deg2rad(lat2))
                + cos(deg2rad(lat1)) * cos(deg2rad(lat2))
                  * cos(deg2rad(theta));
    dist = acos(dist);
    dist = rad2deg(dist) * 60 * 1.1515;
    array<string,3> out;
    out[0] = to_string(dist * 0.8684);
    out[1] = to_string(dist * 1.609344);
    out[2] = to_string(round(dist * 100.0) / 100.0);
    return out;
}

string Flight::fetchArrivalTime() const {
    // parse flightSchedule_ with strptime or use custom parser...
    // then add h/m from flightTime_ to produce arrival tp
    // finally format with formatDateTime(...)
    // For now, return flightSchedule_ as placeholder
    return flightSchedule_;
}

// Remove by flight number
void Flight::deleteFlight(const string& flightNum) {
    auto it = remove_if(
        flightList_.begin(), flightList_.end(),
        [&](const unique_ptr<Flight>& f){
            return f->getFlightNumber() == flightNum;
        }
    );
    if (it != flightList_.end()) {
        flightList_.erase(it, flightList_.end());
    }
    displayFlightSchedule();
}

// Console display
void Flight::displayFlightSchedule() {
    cout << "+------+-------------------------------------------+-----------+------------------+-----------------------+------------------------+---------------------------+-------------+--------+------------------------+\n";
    cout << "| Num  | FLIGHT SCHEDULE                          | FLIGHT NO |    Total Seats    | FROM                  | TO                     | ARRIVAL TIME              | FLIGHT TIME | GATE   | DISTANCE (M/K)         |\n";
    cout << "+------+-------------------------------------------+-----------+------------------+-----------------------+------------------------+---------------------------+-------------+--------+------------------------+\n";
    for (size_t i = 0; i < flightList_.size(); ++i) {
        cout << flightList_[i]->toString(static_cast<int>(i+1)) << "\n";
    }
    cout << "+------+-------------------------------------------+-----------+------------------+-----------------------+------------------------+---------------------------+-------------+--------+------------------------+\n";
}

string Flight::toString(int idx) const {
    ostringstream ss;
    ss << "| " << setw(4) << idx
       << " | " << setw(41) << flightSchedule_
       << " | " << setw(9)  << flightNumber_
       << " | " << setw(16) << numOfSeats_
       << " | " << setw(21) << fromCity_
       << " | " << setw(22) << toCity_
       << " | " << setw(11) << fetchArrivalTime()
       << " | " << setw(9)  << flightTime_ << "Hrs"
       << " | " << setw(6)  << gate_
       << " | " << setw(5)  << distMiles_
       << "/"  << setw(5)  << distKm_
       << " |";
    return ss.str();
}

// Simple getters
int Flight::getNoOfSeats() const { return numOfSeats_; }
const string& Flight::getFlightNumber() const { return flightNumber_; }
const vector<Customer*>& Flight::getRegisteredCustomers() const { return registeredCustomers_; }
const string& Flight::getFlightSchedule() const { return flightSchedule_; }
const string& Flight::getFromCity() const { return fromCity_; }
const string& Flight::getToCity() const { return toCity_; }
const string& Flight::getGate() const { return gate_; }
const string& Flight::getFlightTimeStr() const { return flightTime_; }