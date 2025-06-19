# ✈️ FlyBoard (C++ | OOP Project)

## 📌 Overview

FlyBoard is a **Airline Reservation System** a C++ project built using Object-Oriented Programming principles. It simulates a simple airline management platform where customers can book and manage flights, while admins can control the system using CRUD operations. This project was developed to apply and strengthen core concepts of Object-Oriented Programming (OOP) in a practical scenario.

---

## 🛠 Requirements

- **C++17** or higher
- **g++ / clang++ compiler**
- Any preferred C++ IDE (e.g., IntelliJ with C++ plugin, CLion, VS Code, Code::Blocks)

---

## 📁 Project Structure


### 🔍 Module Descriptions

| File | Purpose |
|------|---------|
| `User.hpp/cpp` | Base class with shared attributes and virtual methods |
| `Customer.hpp/cpp` | Derived class for user-side functionality |
| `RolesAndPermissions.hpp/cpp` | Admin-side functionalities including flight and customer control |
| `Flight.hpp/cpp` | Flight data representation including metadata and seats |
| `FlightReservation.hpp/cpp` | Booking and cancellation logic |
| `FlightDistance.hpp/cpp` | Calculates flight distance (can be extended for pricing logic) |
| `RandomGenerator.hpp/cpp` | Generates random flight schedules |
| `DisplayClass.hpp` | Handles UI-style display formatting |

---

## 🚀 Features

### 🧑‍💼 Admin

- Add, update, or delete flights
- View all registered customers
- View bookings of a specific customer
- View passenger list of any flight

### 👤 Customer

- Register and login
- Book a flight by flight number and ticket count
- Cancel flight tickets
- Update personal profile
- Delete account (removes user, not bookings)
- View booked flights and their current status

---

## 🔍 OOP Concepts Demonstrated

| Concept | Where It’s Used |
|--------|------------------|
| **Encapsulation** | Data fields are private/protected with public methods |
| **Inheritance** | `Customer` and `Admin` inherit from `User` |
| **Virtual Inheritance** | Avoids diamond problem when using multiple inheritance |
| **Multiple Inheritance** | `RolesAndPermissions` may inherit from multiple utility classes |
| **Polymorphism** | Virtual methods overridden by derived classes for dynamic behavior |
| **Function Overriding** | `displayDetails()` behaves differently in child classes |
| **Abstraction** | Interface-style class definitions (e.g., `DisplayClass`) |
| **Composition** | `Customer` class has `FlightReservation` objects inside |

---

## 📅 Flight Scheduler

- Flights are scheduled randomly at runtime using the `RandomGenerator` module.
- You can modify the total number of flights by changing constants in `RandomGenerator.cpp`.

---

## 🔒 Authentication Flow

1. User/Admin registers
2. Secure login required to access features
3. Each session offers different functionalities based on user role

---

## 👨‍💻 Contributors

- **Abhijeet Singh** 
- **Parashdeep Singh**

---

## 💡 Future Enhancements

- Add file-based or database persistence
- Add pricing and payment simulation logic
- Create a GUI to show the options
- Add logging and role-based permissions more granularly

