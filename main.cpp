#include <iostream>
#include <iomanip>
#include <vector>
#include <regex>
#include <SFML/Network/TcpSocket.hpp>
#include <SFML/Network/IpAddress.hpp>
#include <string>
static bool port_is_open (const std::string& address, int port){
    return(sf::TcpSocket().connect(address, port) == sf::Socket::Done);
}
static bool validate_address (std::string addr){
    std::regex IPaddr_regex(R"([0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\b)");
    std::regex url_regex(R"(https?:\/\/(www\.)?[-a-zA-Z0-9@:%._\+~#=]{1,256}\.[-a-zA-Z0-9()]{1,6}\b)");

    if(isdigit(addr[0])){
        return (regex_match(addr, IPaddr_regex));

    } else {
        return(regex_match(addr, url_regex));
    }
}
void greeting (std::string& addr, std::string& ports ) {
    bool valid_addr;
    std::cout << "-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~\n";
    std::cout << std::setw(15) << "Welcome to PrtScanner\n";
    std::cout << std::setw(5) << "Please enter the URL or IPv4 address that you'd like to scan: ";
    std::cin >> addr;
    valid_addr = validate_address(addr);
    if (!valid_addr){
        std::cout << std::setw(5) << addr <<" is not valid, Please enter a valid entry you'd like to scan: ";
        std::cin >> addr;
    }
    std::cout << std::setw(5) << "Please enter the ports OR range-of ports you'd like to scan seperated by a comma (ex: 20-80, 443): ";
    std::cin >> ports;
    std::cout << "-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~\n";
}

static::std::vector<std::string> split (const std::string& str, char delimiter = ' ', bool allow_empty = false){

}

static std::vector<int> parse_ports ( std::string ports) {

}

int main () {
    bool program_runs = true;
    std::string user_addr = {};
    std::string user_ports = {};

    do{
        greeting(user_addr, user_ports);

        std::cout << "user address: " << user_addr << std::endl;
        std::cout << "user ports: " << user_ports << std::endl;
        program_runs = false; 

    } while(program_runs);

    std::cout << "Port: 443 : ";
    if (port_is_open("127.0.0.1", 443)){
        std::cout << "OPEN" << std::endl;
    } else {
        std::cout << "CLOSED" << std::endl;
    }
    
    return 0;
}