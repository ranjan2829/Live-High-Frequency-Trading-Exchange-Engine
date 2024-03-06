#pragma once
#include <iostream>
#include <string>
#include <unordered_set>
#include <sstream>
#include <sys/epoll.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <ifaddrs.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <fcntl.h>


#include "macros.h"
#include "logging.h"
namespace Common{
    struct SocketCfg{
        std::string ip_;
        std::string iface_;
        int port_=-1;
        bool is_udp_=false;
        bool is_listening_=false;
        bool needs_so_timestamp_=false;
        auto toString() const {
            std::stringstream ss;
            ss<<"SocketCfg[ip :"<<ip_
            << "iface :"<<iface_
            <<"port : "<<port_
            <<"is udp :"<<is_udp_
            <<"is listening  "<< is_listening_
            <<"need s0 timestamp :"<<needs_so_timestamp_
            <<"]";
            return ss.str();
        }


    };
    constexpr int MaxTcpServerBacklog =1024;
    inline auto getIfaceIP(const std::string &iface)->std::string{
        char buf[NI_MAXHOST]={'\0'};
        ifaddrs *ifaddr =nullptr;
        if(getifaddrs(&ifaddr)!=-1){
            for(ifaddrs *ifa =ifaddr;ifa;ifa=ifa->ifa_next){
                if(ifa->ifa_addr && ifa->ifa_addr->sa_family==AF_INET && iface==ifa->ifa_name){
                    getnameinfo(ifa->ifa_addr,sizeof(sockaddr_in),buf,sizeof(buf),NULL,0,NI_NUMERICHOST);
                    break;

                }



            }
            freeifaddrs(ifaddr);
        }
        return buf;


    }
    inline auto setNonBlocking(int fd)->bool{
        const auto flags=fcntl(fd,F_GETFL,0);
        if(flags & 0_NONBLOCK){
            return true;
        }
        return (fcntl(fd,F_SETFL,flags | 0_NONBLOCK) !=-1);
    }
    
}