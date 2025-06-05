#include "User.hpp"

// Pull in the real definitions here
#include "RolesAndPermissions.hpp"
#include "Flight.hpp"
#include "FlightReservation.hpp"
#include "Customer.hpp"

#include <iostream>
#include <limits>
#include <sstream>
using namespace std;

int User::run() {
    // -- Setup -----------------------------------------
    // Seed the admin credentials (default root/root)
    RolesAndPermissions auth({{"Standard","1234"}});

    // Generate a batch of flights
    Flight flightSchedulerInstance;
    flightSchedulerInstance.flightScheduler();

    // Booking engine
    FlightReservation bookingSystem;

    // -- Welcome & Main Menu --------------------------
    cout << "\n\t\t\t+++++++++++++ Welcome to BAV AirLines +++++++++++++\n\n"
              << "To Further Proceed, Please enter a value.\n\n"
              << "***** Default Username & Password is root/root *****\n"
              << "  Using default credentials grants view-only access.\n\n";
    displayMainMenu();

    int choice;
    cin >> choice;
    while (choice < 0 || choice > 5) {
        cout << "ERROR! Enter a value between 0 and 5: ";
        cin >> choice;
    }

    // -- Main Loop ------------------------------------
    do {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 0) {
            welcomeScreen(-1);
            break;
        }
        else if (choice == 1) {
            // --- Admin Login ---
            printArtWork(1);
            string user, pass;
            cout << "Username: "; getline(cin, user);
            cout << "Password: "; getline(cin, pass);

            int idx = auth.isPrivilegedUserOrNot(user, pass);
            if (idx < 0) {
                cout << "ERROR: Invalid admin credentials.\n";
            }
            else if (idx == 0) {
                cout << "Logged in as standard admin (view only).\n";
                Customer::displayCustomersData(true);
            }
            else {
                cout << "Logged in as \"" << user << "\".\n";
                int sub;
                do {
                    cout << "\n\t+++++ Admin Menu (" << user << ") +++++\n"
                                 " 1) Add Passenger\n"
                                 " 2) Search Passenger\n"
                                 " 3) Update Passenger\n"
                                 " 4) Delete Passenger\n"
                                 " 5) List All Passengers\n"
                                 " 6) Passenger's Flights\n"
                                 " 7) Passengers by Flight\n"
                                 " 8) Delete Flight\n"
                                 " 0) Logout\n"
                                 "Choice: ";
                    cin >> sub;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    switch (sub) {
                        case 1:
                            Customer::displayArtWork(1);
                            Customer::addNewCustomer();
                            break;
                        case 2: {
                            Customer::displayArtWork(2);
                            Customer::displayCustomersData(false);
                            cout<<"Enter CustomerID: ";
                            string id; getline(cin,id);
                            Customer::searchUser(id);
                            break;
                        }
                        case 3: {
                            bookingSystem.displayArtWork(2);
                            Customer::displayCustomersData(false);
                            cout<<"Enter CustomerID: ";
                            string id; getline(cin,id);
                            Customer::editUserInfo(id);
                            break;
                        }
                        case 4: {
                            bookingSystem.displayArtWork(3);
                            Customer::displayCustomersData(false);
                            cout<<"Enter CustomerID: ";
                            string id; getline(cin,id);
                            Customer::deleteUser(id);
                            break;
                        }
                        case 5:
                            Customer::displayArtWork(3);
                            Customer::displayCustomersData(false);
                            break;
                        case 6: {
                            bookingSystem.displayArtWork(6);
                            Customer::displayCustomersData(false);
                            cout<<"Enter CustomerID: ";
                            string id; getline(cin,id);
                            bookingSystem.displayFlightsRegisteredByOneUser(id);
                            break;
                        }
                        case 7: {
                            Customer::displayArtWork(4);
                            cout<<"Show all flights? (Y/N): ";
                            char c; cin>>c; cin.ignore();
                            if (c=='Y'||c=='y'){
                                //Flight flightInstance;
                                bookingSystem.displayRegisteredUsersForAllFlight();
                                //bookingSystem.displayArtWork(4);
                                // flightInstance.displayFlightSchedule();
                                // flightInstance.displayMeasurementInstructions();
                                //bookingSystem.displayArtWork(1);
                                //flightInstance.displayFlightSchedule();
                            }
                            else {
                                Flight flightInstance;
                                flightInstance.displayFlightSchedule();
                                cout<<"Flight#: ";
                                string f; getline(cin,f);
                                bookingSystem.displayRegisteredUsersForASpecificFlight(f);
                            }
                            break;
                        }
                        case 8: {
                            Customer::displayArtWork(5);
                            Flight flightInstance;
                            flightInstance.displayFlightSchedule();
                            cout<<"Flight#: ";
                            string f; getline(cin,f);
                            flightInstance.deleteFlight(f);
                            break;
                        }
                    }
                } while (sub != 0);
            }
        }
        else if (choice == 2) {
            // --- Admin Registration ---
            printArtWork(2);
            string u,p;
            cout<<"New admin username: "; getline(cin,u);
            cout<<"Password: ";               getline(cin,p);
             auth.registerAdmin(u,p); 
        }
        else if (choice == 3) {
            // --- Passenger Login ---
            printArtWork(3);
            string e,p;
            cout<<"Email: ";    getline(cin,e);
            cout<<"Password: "; getline(cin,p);
            string res = auth.isPassengerRegistered(e,p);
            if (res[0]=='1') {
                string uid = res.substr(2);
                int sub;
                cout<<"Logged in as user "<<e<<"\n";
                Flight flightInstance;
                do {
                    cout<<"\n\t+++++ Passenger Menu ("<<e<<") +++++\n"
                             " 1) Book Flight\n"
                             " 2) Update Info\n"
                             " 3) Delete Account\n"
                             " 4) View Schedule\n"
                             " 5) Cancel Flight\n"
                             " 6) My Bookings\n"
                             " 0) Logout\n"
                             "Choice: ";
                    cin>>sub;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    switch (sub) {
                        case 1: {
                            bookingSystem.displayArtWork(1);
                            flightInstance.displayFlightSchedule();
                            string fn; int n;
                            cout<<"Flight#: "; getline(cin,fn);
                            cout<<"Tickets: "; cin>>n; cin.ignore();
                            bookingSystem.bookFlight(fn,n,uid);
                            break;
                        }
                        case 2:
                            bookingSystem.displayArtWork(2);
                            Customer::editUserInfo(uid);
                            break;
                        case 3: {
                            bookingSystem.displayArtWork(3);
                            cout<<"Confirm delete (Y/N): ";
                            char c; cin>>c; cin.ignore();
                            if (c=='Y'||c=='y') {
                                Customer::deleteUser(uid);
                                sub = 0;
                            }
                            break;
                        }
                        case 4:
                            bookingSystem.displayArtWork(4);
                            flightInstance.displayFlightSchedule();
                            flightInstance.displayMeasurementInstructions();
                            break;
                        case 5:
                            bookingSystem.displayArtWork(5);
                            bookingSystem.cancelFlight(uid);
                            break;
                        case 6:
                            bookingSystem.displayArtWork(6);
                            bookingSystem.displayFlightsRegisteredByOneUser(uid);
                            break;
                    }
                } while (sub != 0);
            }
            else {
                cout<<"ERROR: Invalid passenger credentials.\n";
            }
        }
        else if (choice == 4) {
            // --- Passenger Registration ---
            printArtWork(4);
            Customer::addNewCustomer();
        }
        else if (choice == 5) {
            // --- User Manual ---
            manualInstructions();
        }

        displayMainMenu();
        cin >> choice;
    } while (choice != 0);

    return 0;
}

void User::displayMainMenu() {
    cout << "\n(a) 0=Exit   (b) 1=Admin Login   (c) 2=Admin Register\n"
                 "(d) 3=Passenger Login   (e) 4=Passenger Register   (f) 5=User Manual\n"
                 "Choice: ";
}

void User::manualInstructions() {
    printArtWork(5);
    cout << "(1) Admin have full CRUD on customers.\n"
                 "(2) Register admin via option 2 in main menu.\n"
                 "(3) Passenger can book/cancel flights up to 10 tickets.\n"
                 "(4) Use ±1h buffer on arrival times.\n"
                 "...(see on-screen prompts for details)\n";
}

void User::welcomeScreen(int option) {
    if (option == 1)
        cout << "Welcome to Bay Airlines\n";
    else
        cout << "Flying With Trust For Five Decades\n";
}

void User::printArtWork(int option) {
    static const vector<string> arts = {
        "", "ADMIN LOGIN", "ADMIN REGISTER", "PASSENGER LOGIN",
        "PASSENGER REGISTER", "USER MANUAL"
    };
    if (option >= 1 && option < static_cast<int>(arts.size())) {
        cout << "\n=== " << arts[option] << " ===\n";
    }
}

// Define the global main
int main() {
    return User::run();
}
