//Header indicating it's me (cppdvl) the author of this software
// Author: cppdvl (Julian Andres Guarin Reyes)
// Date: 2023-12-03

#include <map>
#include <array>
#include <string>
#include <iostream>
#include <ifaddrs.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>


using namespace std;



namespace Utilities::Network
{
    std::map<std::string, std::map<std::string, std::string>> getIfaceAddressMap();
    std::map<std::string, std::map<std::string, std::string>> getIfaceAddressMap()
    {

        struct ifaddrs* interfacesPtr  {nullptr};
        struct ifaddrs* tempPtr        {nullptr};
        auto success        = getifaddrs(&interfacesPtr) == 0;
    
        std::array<char, INET_ADDRSTRLEN> bufferIPV4{};
        std::array<char, INET6_ADDRSTRLEN> bufferIPV6{};
        
        std::map<std::string, std::string> ifaceAddrMapIPV4{};
        std::map<std::string, std::string> ifaceAddrMapIPV6{};
        if (success)
        {
            tempPtr = interfacesPtr;
            while (tempPtr)
            {
                if (tempPtr->ifa_addr && tempPtr->ifa_addr->sa_family == AF_INET)
                {
                    inet_ntop(AF_INET, &(reinterpret_cast<struct sockaddr_in*>(tempPtr->ifa_addr)->sin_addr), bufferIPV4.data(), INET_ADDRSTRLEN);
                    ifaceAddrMapIPV4[tempPtr->ifa_name] = bufferIPV4.data();
                }
                tempPtr = tempPtr->ifa_next;
            }
        }

        return {{"IPV4", ifaceAddrMapIPV4}, {"IPV6", ifaceAddrMapIPV6}};
    }
}

int main()
{
    auto famIfacesAddress = Utilities::Network::getIfaceAddressMap();
    for (auto& [family, ifaceAddrMap] : famIfacesAddress)
    {
        std::cout << family << ":\n";
        for (auto& [iface, addr] : ifaceAddrMap)
        {
            std::cout << "\t" << iface << ": " << addr << "\n";
        }
    }
    return 0;
}
