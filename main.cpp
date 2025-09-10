#include <iostream>
#include <string>
#include <array>
#include <memory>
#include <stdexcept>
#include <sstream>
#include <nlohmann/json.hpp> 

using json = nlohmann::json;

std::string exec(const std::string& cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd.c_str(), "r"), pclose);

    if (!pipe) throw std::runtime_error("popen() failed!");

    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

int main() {
    std::string url;
    std::cout << "Enter website URL: ";
    std::getline(std::cin, url);

    std::string cmd = "node extract.js " + url;
    std::string output = exec(cmd);

    try {
        auto data = json::parse(output);
        std::cout << "\n📄 Title: " << data["title"] << "\n";
        std::cout << "🔗 Found " << data["links"].size() << " links:\n";
        for (auto& link : data["links"]) {
            std::cout << " - " << link << "\n";
        }
    } catch (std::exception& e) {
        std::cerr << "Error parsing JSON: " << e.what() << "\n";
    }

    return 0;
}
