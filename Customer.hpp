#ifndef CUSTOMER_HPP
#define CUSTOMER_HPP

#include <string>
#include <vector>
using namespace std;
// Forward declarations
class Flight;
class RandomGenerator;

class Customer {
private:
    string userID_;
    string email_;
    string name_;
    string phone_;
    string password_;
    string address_;
    int age_{0};

public:
    const string& getPassword() const;

    vector<Flight*> flightsRegisteredByUser_;
    vector<int>    numOfTicketsBookedByUser_;

    // Helpers
    string randomIDDisplay(const string& id) const;
    string toString(int index) const;

public:
    static void displayArtWork(int option);
    static void displayHeader();

public:
    // Shared collection of all customers
    static vector<Customer> customerCollection;

    // Constructors
    Customer();
    Customer(const string& name,
             const string& email,
             const string& password,
             const string& phone,
             const string& address,
             int age);

    // Customer management
    static void addNewCustomer();
    static bool isUniqueData(const string& email);
    static void displayCustomersData(bool showHeader = true);
    static void searchUser(const string& userID);
    static void editUserInfo(const string& userID);
    static void deleteUser(const string& userID);

    // Flight‐related
    void addNewFlightToCustomerList(Flight* f);
    void addExistingFlightToCustomerList(size_t idx, int numTickets);

    // New methods to support FlightReservation usage
    vector<int>& getTicketCounts();
    int getTicketCount(size_t idx) const;
    string getFormattedUserID() const;
    const vector<Flight*>& getFlights() const;
    void removeFlightAt(size_t idx);
    void setTicketCount(size_t idx, int count);

    // Getters
    const string& getUserID()  const;
    const string& getEmail()   const;
    const string& getName()    const;
    const string& getPhone()   const;
    const string& getAddress() const;
    int                getAge()     const;

    // Setters
    void setName(const string& v);
    void setEmail(const string& v);
    void setPhone(const string& v);
    void setAddress(const string& v);
    void setAge(int v);
};

#endif // CUSTOMER_HPP
