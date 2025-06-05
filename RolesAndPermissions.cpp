#include "RolesAndPermissions.hpp"
#include <algorithm>
using namespace std;
// Constructor
RolesAndPermissions::RolesAndPermissions(
    const vector<pair<string, string>>& admins)
  : adminCredentials_(admins)
{}

// Returns index of matching admin, or -1 if none found
int RolesAndPermissions::isPrivilegedUserOrNot(
    const string& username,
    const string& password) const
{
    for (size_t i = 0; i < adminCredentials_.size(); ++i) {
        if (adminCredentials_[i].first == username &&
            adminCredentials_[i].second == password)
        {
            return static_cast<int>(i);
        }
    }
    return -1;
}

// Returns "1-<userID>" if a Customer with matching email/password exists, else "0"
string RolesAndPermissions::isPassengerRegistered(
    const string& email,
    const string& password) const
{
    for (const auto& c : Customer::customerCollection) {
        if (c.getEmail() == email && c.getPassword() == password) {
            return "1-" + c.getUserID();
        }
    }
    return "0";
}
// Adds a new admin with the given username and password
void RolesAndPermissions::registerAdmin(const string& username, const string& password)
{
    adminCredentials_.emplace_back(username, password);
}
