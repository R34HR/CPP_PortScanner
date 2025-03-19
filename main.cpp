#include <iostream>
#include <iomanip>
#include <limits>
#include <vector>
#include <regex>
#include <SFML/Network/TcpSocket.hpp>
#include <SFML/Network/IpAddress.hpp>
#include <string>
void swap(int &a, int &b){
    int temp;
    if (a > b){
        temp = a;
        a = b;
        b = temp;
    }
}
static::std::vector<std::string> split(const std::string& str, char delimiter = ' ', bool allow_empty = false){
    
    std::vector<std::string> tokens;
    std::stringstream sstream(str);
    std::string token;
    //treats the string as a string-stream and appends substring to string vector everytime it encounters the specified delimeter
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
    std::regex IPaddr_regex(R"(^[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}$\b)");
    std::regex url_regex(R"((https:\/\/)?(www\.)?[-a-zA-Z0-9@:%._\+~#=]{1,128}\.[a-zA-Z0-9()]{1,6}\b)");
    std::vector <std::string> split_str;
    std::cout << addr << "\n";
    if(regex_match(addr, IPaddr_regex)){
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

    } else {
      return ((regex_match(addr, url_regex)));
    }
    
}
static bool validate_ports (const std::string& addr) {
     std::regex ports_regex (R"(^[\d]{2,5}\-[\d]{2,5}([\,][\s]?)?([\d]{2,5}(([\s])?[\,]([\s])?)?)*$\b)");
     if (regex_match(addr, ports_regex)){
        std::vector<std::string> port_list = split(addr,',');
        std::string range = port_list[0];
        int range_pos = range.find('-');
        int min = stoi(range.substr(0,range_pos));
        int max = stoi(range.substr(range_pos + 1, range.size()-1));
        swap(min,max);
        if (min < 20){
           std::cout << "Port #: " << min << " has to be greater than 20." << std::endl;
           return false;
        } else if (max > 65535){
           std::cout << "Port #: " << max << " has to be lesser than 65,535." << std::endl;
           return false;
        }
     }
    return(regex_match(addr, ports_regex));
}
static std::vector<int> parse_ports(std::string& usr_ports) {
    std::vector<int> ports;
    std::vector<std::string> port_list = split(usr_ports,',');
    int range_pos;

    for(auto i : port_list){
        std::cout << i << std::endl;
        range_pos = i.find('-');
        if(range_pos != std::string::npos){
            int min = stoi(i.substr(0,range_pos));
            int max = stoi(i.substr(range_pos + 1, i.size()-1));
            swap(min,max);
            std::cout << "min: " << min << " max: " << max << std::endl; 
            // // for(int j = min; j < max; j++){
            // //     ports.push_back(j);
            // // }
        }
        else {
            ports.push_back(stoi(i));

        }
    }
    return ports;

}
void greeting (std::string& addr, std::vector<int>& ports ) {
    std::string usr_ports;
    bool valid_addr;
    bool valid_ports;
    std::cout << "-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~\n";
    std::cout << std::setw(45) << "Welcome to PrtScanner\n";
    std::cout << std::setw(25) << "Please enter the URL or IPv4 address that you'd like to scan: ";
    std::cin >> addr;
    valid_addr = validate_address(addr);
    while (!valid_addr) {
        std::cout << addr <<" is not valid, Please enter a valid URL or IP address you'd like to scan: ";
        std::cin >> addr;
        valid_addr = validate_address(addr);
    }
    std::cout << std::setw(5) << "Please enter a range-of ports + any other specific ports you'd like to scan seperated by a comma (ex: 20-80, 443): ";
    std::cin.ignore();
    getline(std::cin, usr_ports, '\n');
    valid_ports = validate_ports(usr_ports);
    while(!valid_ports){
        std::cout << usr_ports <<" is not valid, Please enter a port entry you'd like to scan: ";
        getline(std::cin, usr_ports, '\n');
        valid_ports = validate_ports(usr_ports);

    }
    std::cout << "Everything is valid\n";
    ports = parse_ports(usr_ports);
    std::cout << "-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~\n";
}

int main () {
    bool program_runs = true;
    std::string user_addr = {};
    std::vector<int> user_ports = {};

    do{
        greeting(user_addr, user_ports);

        std::cout << "user address: " << user_addr << std::endl;
        std::cout << "user ports: " << user_ports[0] << std::endl;
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