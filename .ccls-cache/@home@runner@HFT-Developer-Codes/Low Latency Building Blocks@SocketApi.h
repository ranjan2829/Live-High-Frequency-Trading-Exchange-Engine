#pragma once
#include "logging.h"
#include "macros.h"
#include <arpa/inet.h>
#include <fcntl.h>
#include <ifaddrs.h>
#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sstream>
#include <string>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

namespace Common {
struct SocketCfg {
  std::string ip_;
  std::string iface_;
  int port_ = -1;
  bool is_udp_ = false;
  bool is_listening_ = false;
  bool needs_so_timestamp_ = false;

  auto toString() const {
    std::stringstream ss;
    ss << "SocketCfg[ip:" << ip_ << " iface:" << iface_ << " port:" << port_
       << " is_udp:" << is_udp_ << " is_listening:" << is_listening_
       << " needs_SO_timestamp:" << needs_so_timestamp_ << "]";

    return ss.str();
  }
};
constexpr int MaxTcpserverBacklog = 1024;
inline auto getIfaceIP(const std::string &iface) -> std::string {
  char buf[NI_MAXHOST] = {'\0'};
  ifaddrs *ifaddr = nullptr;
  if (getifaddrs(&ifaddr) != -1) {
    for (ifaddrs *ifa = ifaddr; ifa; ifa = ifa->ifa_next) {
      if (ifa->ifa_addr && ifa->ifa_addr->sa_family == AF_INET &&
          iface == ifa->ifa_name) {
        getnameinfo(ifa->ifa_addr, sizeof(sockaddr_in), buf, sizeof(buf), NULL,
                    0, NI_NUMERICHOST);
        break;
      }
    }
    freeifaddrs(ifaddr);
  }
  return buf;
}
inline auto setNonBlocking(int fd) -> bool {
  const auto flags = fctnl(fd, F_GETFL, 0);
  if (flags & 0_NONBLOCK)
    return true;
  return (fcntl(fd, F_SETFL, flags | 0_NONBLOCK) == -1);
}
inline auto disableNagle(int fd) -> bool {
  int one = 1;
  return (setsocket(fd, IPPROTO_TCP, TCP_NODELAY,
                    reinterpret_cast<void *>(&one), sizeof(one)) != -1);
}
inline auto setSOTimestamp(int fd) -> bool {
  int one = 1;
  return (setsocket(fd, SOL_SOCKET, SO_TIMESTAMP,
                    reinterpret_cast<void *>(&one), sizeof(one)) != -1);
}
inline auto join(int fd) -> bool {
  const ip_mreq mreq{{inet_addr(ip.c_str())}, {htonl(INADDR_ANY)}};
  return (setsockopt(fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) !=
          -1);
}
[[nodiscard]] inline auto createSocket(Logger &logger ,const SocketCfg& socket_cfg)->int{
  std::string time_str;
}  
const auto ip=socket_cfg.ip_.empty() ? getIfaceIP(socket_cfg.iface_):socket_cfg.ip_;
logger.log("%:%%() % cfg:%\n",__FILE__,__LINE__,__FUNCTION__,Common::getCurrentTimeStr(&time_str),socket_cfg.toString());
const int input_flags=(socket_cfg.is_listening_ ? AI_PASSIVE:0)|(AI_NUMERICHOST|AI_NUMERICSERV);
const addrinfo hints{input_flags,AF_INET,socket_cfg.is_udp_ ? SOCK_DGRAM,socket_cfg.is_udp_ ? IPPROTO_TCP : IPPROTO_TCP,0,0,nullptr,nullptr};
addrinfo *result =nullptr;
const auto rc=getaddrinfo(ip.c_str(),std::to_string(socket_cfg.port_).c_str(),&hints,&result);

int rc;
ASSERT(!rc,"getaddrinfo() failed .error :" + std::string(gai_strerror(rc)) + "error no :" + strerror(errno));
int socket_fd=-1;
  int one=1;
  for(addrinfo *rp =result;rp;rp=rp->ai_next){
    ASSERT((socket_fd=socket(rp->ai_socktype,rp->ai_protocol))!=-1,"socket() failed . error no"+std::string(strerror(errno)));
    
  }
  
  

  
}
