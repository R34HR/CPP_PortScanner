#include <iostream>
#include <iomanip>
#include <vector>
#include <regex>
#include <SFML/Network/TcpSocket.hpp>
#include <SFML/Network/IpAddress.hpp>
#include <string>
static::std::vector<std::string> split(const std::string& str, char delimiter = ' ', bool allow_empty = false){
    
    std::vector<std::string> tokens;
    std::stringstream sstream(str);
    std::string token;
    //treats the string as a string-stream and appends substring everytime it encounters the specified delimeter
    while(std::getline(sstream, token, delimiter)){
        if(allow_empty || token.size() > 0) {
            tokens.push_back(token);
        }
    }
    return tokens;
}
static bool port_is_open (const std::string& address, int port){
    return(sf::TcpSocket().connect(address, port) == sf::Socket::Done);
}
static bool validate_address (std::string addr){
    std::regex IPaddr_regex(R"(/[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\b/)");
    std::regex url_regex(R"(https?:\/\/(www\.)?[-a-zA-Z0-9@:%._\+~#=]{1,256}\.[-a-zA-Z0-9()]{1,6}\b)");
    std::vector <std::string> split_str;
    
    if(regex_match(addr, IPaddr_regex) && isdigit(addr[0])){

        split_str = split(addr, '.'); 
        
        for(auto str: split_str){ 
            if( 255 >= stoi(str) && stoi(str) >= 0 )
            {
                continue;
            } else {
                return false;
            }
            
        }

        return true;

    }
        
    return(regex_match(addr, url_regex));
    
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

    std::cout << "Port 20: ";
    if (port_is_open("127.0.0.1", 20)){
        std::cout << "OPEN" << std::endl;
    } else {
        std::cout << "CLOSED" << std::endl;
    }
    
    return 0;
}