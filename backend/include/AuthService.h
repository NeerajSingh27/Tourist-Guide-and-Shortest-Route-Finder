#pragma once
#include <filesystem>
#include <string>

struct AuthResult {
    bool ok{false};
    std::string message;
    std::string name;
    std::string email;
};

// Academic-demo authentication backed by a local file.
// The included hash is not suitable for production password storage.
class AuthService {
public:
    static AuthResult registerUser(const std::filesystem::path& file,
                                   const std::string& name,
                                   const std::string& email,
                                   const std::string& password);
    static AuthResult loginUser(const std::filesystem::path& file,
                                const std::string& email,
                                const std::string& password);
private:
    static std::string hashPassword(const std::string& password, const std::string& salt);
};