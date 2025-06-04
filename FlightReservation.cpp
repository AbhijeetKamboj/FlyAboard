#include "FlightReservation.hpp"
#include <iostream>
#include <iomanip>
#include <iterator>
#include <algorithm>
#include <sstream>
#include <limits>

// --- Private helpers ---

void FlightReservation::addTicketsToExistingBooking(Customer& customer, 
                                                    int numTickets)
{
    auto& counts = customer.getTicketCounts();
    counts[flightIndexInCustomerList_] += numTickets;
}

void FlightReservation::addTicketsToNewBooking(Customer& customer, 
                                               int numTickets)
{
    customer.getTicketCounts().push_back(numTickets);
}

bool FlightReservation::isFlightInCustomerList(const vector<Flight*>& flights, 
                                               Flight* flight)
{
    for (size_t i = 0; i < flights.size(); ++i) {
        if (flights[i]->getFlightNumber() == flight->getFlightNumber()) {
            flightIndexInCustomerList_ = static_cast<int>(i);
            return true;
        }
    }
    return false;
}

// const vector<unique_ptr<Flight>>& Flight::getFlightList() {
//     return flightList_;
// }

int FlightReservation::flightPosition(const vector<Flight*>& flights, 
                                      Flight* flight)
{
    auto it = find_if(flights.begin(), flights.end(),
        [&](Flight* f){ return f->getFlightNumber() == flight->getFlightNumber(); });
    return (it != flights.end()) 
         ? static_cast<int>(distance(flights.begin(), it)) 
         : -1;
}

string FlightReservation::flightStatus(Flight* flight) const
{
    // Check presence in master schedule
    for (const auto& fptr : Flight::getFlightList()) {
        if (fptr->getFlightNumber() == flight->getFlightNumber())
            return "As Per Schedule";
    }
    return "   Cancelled   ";
}

string FlightReservation::bookingToString(int serial, Flight* flt, 
                                              const Customer& cust) const
{
    ostringstream ss;
    ss << "| " << setw(4) << serial
       << " | " << setw(41) << flt->getFlightSchedule()
       << " | " << setw(9)  << flt->getFlightNumber()
       << " | " << setw(16) << cust.getTicketCount(serial)
       << " | " << setw(21) << flt->getFromCity()
       << " | " << setw(22) << flt->getToCity()
       << " | " << setw(11) << flt->fetchArrivalTime()
       << " | " << setw(9)  << flt->getFlightTimeStr() << "Hrs"
       << " | " << setw(6)  << flt->getGate()
       << " | " << setw(10) << flightStatus(flt)
       << " |";
    return ss.str();
}

string FlightReservation::userToString(int serial, 
                                           const Customer& cust, 
                                           int idx) const
{
    ostringstream ss;
    ss << setw(10) << ""
       << "| " << setw(5) << (serial+1)
       << " | " << setw(8) << cust.getFormattedUserID()
       << " | " << left << setw(32) << cust.getName()
       << " | " << setw(3) << cust.getAge()
       << " | " << setw(29) << cust.getEmail()
       << " | " << setw(35) << cust.getAddress()
       << " | " << setw(23) << cust.getPhone()
       << " | " << setw(5) << cust.getTicketCount(idx)
       << " |";
    return ss.str();
}

// --- Public methods ---

void FlightReservation::bookFlight(const string& flightNo, 
                                   int numTickets, 
                                   const string& userID)
{
    bool booked = false;
    const auto& flights = Flight::getFlightList();
    for (const auto& fptr : flights) {
        if (flightNo == fptr->getFlightNumber()) {
            for (auto& cust : Customer::customerCollection) {
                if (userID == cust.getUserID()) {
                    booked = true;

                    auto& regList = fptr->getRegisteredCustomers();
                    if (!fptr->isCustomerAlreadyAdded(regList, &cust)){
                        fptr->addNewCustomerToFlight(&cust);
                        addTicketsToNewBooking(cust,numTickets);
                    }
                    const auto& userFlights = cust.getFlights();
                    if (isFlightInCustomerList(userFlights, fptr.get())) {
                        addTicketsToExistingBooking(cust, numTickets);
                    } else {
                        cust.addNewFlightToCustomerList(fptr.get());
                        addTicketsToNewBooking(cust, numTickets);
                    }
                    break;
                }
            }
            break;
        }
    }
    if (!booked) {
        cout << "Invalid Flight Number \"" << flightNo << "\".\n";
    } else {
        cout << setw(50) 
                  << "You've booked " << numTickets 
                  << " tickets for Flight \"" << flightNo << "\".\n";
                
    }
}

void FlightReservation::cancelFlight(const string& userID)
{
    string flightNo;
    int index = 0;
    bool found = false;

    for (auto& cust : Customer::customerCollection) {
        if (userID == cust.getUserID()) {
            const auto& userFlights = cust.getFlights();
            if (userFlights.empty()) {
                cout << "No flights registered under ID \"" 
                          << userID << "\".\n";
                return;
            }

            displayFlightsRegisteredByOneUser(userID);
            cout << "Enter Flight Number to cancel: ";
            getline(cin, flightNo);
            cout << "Enter number of tickets to cancel: ";
            int numTickets; 
            cin >> numTickets;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            for (auto it = userFlights.begin(); 
                 it != userFlights.end(); 
                 ++it, ++index)
            {
                if (flightNo == (*it)->getFlightNumber()) {
                    found = true;
                    int booked   = cust.getTicketCount(index);
                    int toReturn = min(numTickets, booked);

                    // adjust or remove booking
                    if (toReturn == booked) {
                        cust.removeFlightAt(index);
                    } else {
                        cust.setTicketCount(index, booked - toReturn);
                    }

                    // No setAvailableSeats method, so skip or implement seat tracking
                    break;
                }
            }

            if (!found) {
                cout << "No booking found for flight \"" 
                          << flightNo << "\".\n";
            }
            return;
        }
    }
}

// --- DisplayClass overrides ---

void FlightReservation::displayFlightsRegisteredByOneUser(
    const string& userID)
{
    displayArtWork(6);
    cout << "+------+-------------------------------------------+-----------+------------------+-----------------------+------------------------+---------------------------+-------------+--------+-----------------+\n"
              << "| Num  | FLIGHT SCHEDULE                          | FLIGHT NO | Booked Tickets   | FROM                  | TO                     | ARRIVAL TIME              | FLIGHT TIME | GATE   | FLIGHT STATUS  |\n"
              << "+------+-------------------------------------------+-----------+------------------+-----------------------+------------------------+---------------------------+-------------+--------+-----------------+\n";
    for (const auto& cust : Customer::customerCollection) {
        if (cust.getUserID() == userID) {
            const auto& flights = cust.getFlights();
            for (size_t i = 0; i < flights.size(); ++i) {
                cout << bookingToString(i,flights[i], cust) << "\n"
                          << "+------+-------------------------------------------+-----------+------------------+-----------------------+------------------------+---------------------------+-------------+--------+-----------------+\n";
            }
            break;
        }
    }
}

void FlightReservation::displayHeaderForUsers(
    const Flight& flight, 
    const vector<Customer>& users)
{
    cout << "\n"
              << setw(65) 
              << "Displaying Registered Customers for Flight No. \"" 
              << flight.getFlightNumber() << "\"\n\n"
              << setw(10) << "" 
              << "+------------+------------+----------------------------------+---------+-----------------------------+-------------------------------------+-------------------------+----------------+\n"
              << setw(10) << "" 
              << "| SerialNum  |   UserID   | Passenger Names                  | Age     | EmailID                      | Home Address                        | Phone Number            | Tickets         |\n"
              << setw(10) << "" 
              << "+------------+------------+----------------------------------+---------+-----------------------------+-------------------------------------+-------------------------+----------------+\n";

    for (size_t i = 0; i < users.size(); ++i) {
        cout << userToString(static_cast<int>(i), users[i], flightPosition(
                             users[i].getFlights(), const_cast<Flight*>(&flight))) << "\n"
                  << setw(10) << "" 
                  << "+------------+------------+----------------------------------+---------+-----------------------------+-------------------------------------+-------------------------+----------------+\n";
    }
}

void FlightReservation::displayRegisteredUsersForASpecificFlight(
    const string& flightNo)
{
    displayArtWork(4);
    const auto& flights = Flight::getFlightList();
    for (const auto& fptr : flights) {
        if (fptr->getFlightNumber() == flightNo) {
            // Convert vector<Customer*> to vector<Customer>
            vector<Customer> customers;
            for (auto custPtr : fptr->getRegisteredCustomers()) {
                customers.push_back(*custPtr);
            }
            displayHeaderForUsers(*fptr, customers);
            break;
        }
    }
}

void FlightReservation::displayRegisteredUsersForAllFlight()
{
    displayArtWork(4);
    const auto& flights = Flight::getFlightList();
    for (const auto& fptr : flights) {
        auto users = fptr->getRegisteredCustomers();
        if (!users.empty()) {
            // Convert vector<Customer*> to vector<Customer>
            vector<Customer> customers;
            for (auto custPtr : users) {
                customers.push_back(*custPtr);
            }
            displayHeaderForUsers(*fptr, customers);
        }
    }
}

// void FlightReservation::displayRegisteredUsersForASpecificFlight(
//     const string& flightNo)
// {
//     displayArtWork(4);
//     const auto& flights = Flight::getFlightList();
//     for (const auto& fptr : flights) {
//         if (fptr->getFlightNumber() == flightNo) {
//             // Convert vector<Customer*> to vector<Customer>
//             vector<Customer> customers;
//             for (auto custPtr : fptr->getRegisteredCustomers()) {
//                 customers.push_back(*custPtr);
//             }
//             displayHeaderForUsers(*fptr, customers);
//             break;
//         }
//     }
// }

void FlightReservation::displayArtWork(int option)
{
    static const char* titles[] = {
        "","Book Flight","Edit Info","Delete Account",
        "Random Flight Schedule","Cancel Flight",
        "Registered Flights by Passenger","Logged Out"
    };
    if (option >= 1 && option <= 7)
        cout << "=== " << titles[option] << " ===\n";
}
