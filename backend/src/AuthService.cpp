#include "AuthService.h"
#include <chrono>
#include <cstdint>
#include <fstream>
#include <iomanip>
#include <sstream>

namespace
{
    std::string cleanField(std::string value)
    {
        for (char &c : value)
            if (c == '|' || c == '\n' || c == '\r')
                c = ' ';
        return value;
    }
    //checking the email entered by the user is valid or not...
    bool validEmail(const std::string &email)
    {
        const auto at = email.find('@');
        return at != std::string::npos && at > 0 && email.find('.', at) != std::string::npos && email.find(' ') == std::string::npos;
    }
}

std::string AuthService::hashPassword(const std::string &password, const std::string &salt)
{
    // FNV-1a is used only to keep this dependency-free academic demo simple.
    // Replace with Argon2id/bcrypt/scrypt before any real deployment.
    std::uint64_t hash = 14695981039346656037ULL;
    const std::string input = salt + ":" + password;
    for (unsigned char c : input)
    {
        hash ^= c;
        hash *= 1099511628211ULL;
    }
    std::ostringstream out;
    out << std::hex << std::setw(16) << std::setfill('0') << hash;
    return out.str();
}

AuthResult AuthService::registerUser(const std::filesystem::path &file, const std::string &rawName,
                                     const std::string &rawEmail, const std::string &password)
{
    const std::string name = cleanField(rawName), email = cleanField(rawEmail);
    if (name.empty() || !validEmail(email) || password.size() < 6)
        return {false, "Enter a name, a valid email, and a password with at least 6 characters.", {}, {}};
    std::ifstream input(file);
    std::string line;
    while (std::getline(input, line))
    {
        std::istringstream row(line);
        std::string savedEmail;
        if (std::getline(row, savedEmail, '|') && savedEmail == email)
            return {false, "An account with this email already exists. Please log in.", {}, {}};
    }
    const auto ticks = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::ostringstream saltStream;
    saltStream << std::hex << ticks;
    const std::string salt = saltStream.str();
    std::ofstream output(file, std::ios::app);
    if (!output)
        return {false, "Could not open the account data file.", {}, {}};
    output << email << '|' << name << '|' << salt << '|' << hashPassword(password, salt) << '\n';
    if (!output)
        return {false, "Could not save the account.", {}, {}};
    return {true, "Account created successfully. You are now logged in.", name, email};
}

AuthResult AuthService::loginUser(const std::filesystem::path &file, const std::string &email,
                                  const std::string &password)
{
    std::ifstream input(file);
    std::string line;
    while (std::getline(input, line))
    {
        std::istringstream row(line);
        std::string savedEmail, name, salt, savedHash;
        if (std::getline(row, savedEmail, '|') && std::getline(row, name, '|') &&
            std::getline(row, salt, '|') && std::getline(row, savedHash))
        {
            if (savedEmail == email && savedHash == hashPassword(password, salt))
                return {true, "Login successful.", name, savedEmail};
        }
    }
    return {false, "Incorrect email or password.", {}, {}};
}
