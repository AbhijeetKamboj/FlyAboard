#ifndef ROLES_AND_PERMISSIONS_HPP
#define ROLES_AND_PERMISSIONS_HPP

#include <string>
#include <vector>
#include <utility>
#include "User.hpp"
#include "Customer.hpp"
using namespace std;
class RolesAndPermissions : public User {
private:
    // Each pair holds {username, password}
    vector<pair<string, string>> adminCredentials_;

public:
    // Initialize with a list of {username, password} pairs
    explicit RolesAndPermissions(
        const vector<pair<string, string>>& admins);

    // Returns index of matching admin, or -1 if none found
    int isPrivilegedUserOrNot(const string& username,
                              const string& password) const;

    // Returns "1-<userID>" if passenger found, else "0"
    string isPassengerRegistered(const string& email,
                                      const string& password) const;
    //adds a new user as admin with name and password
    void registerAdmin(const string& username, const string& password);
};

#endif // ROLES_AND_PERMISSIONS_HPP
