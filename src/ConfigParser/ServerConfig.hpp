#ifndef ServerConfig_hpp
# define ServerConfig_hpp

# include <iostream>
# include <map>
# include <vector>
# include <list>
# include "LocationRules.hpp"
# include <fstream>
# include <string>
# include <cstdlib>

class ServerConfig
{
private:
    int                                     _host;
    int                                     _port;
    bool                                    _empty_server;                         
    std::list<std::string>                  _serverNames;

public:
    std::map<std::string, LocationRules>  locations; //Mapa donde almacenamos la info de las locations
    ServerConfig();
    ServerConfig(int host, int port, std::list<std::string> serverNames,
            std::map<std::string, LocationRules> locations);
    ~ServerConfig();
    void setHost(unsigned int host);
    void setPort(unsigned int port);
    void setServerName(std::string serverName);
    int getHost()const;//No tengo claro que host nos sirva para algo, es necesario?
    int getPort()const;
    std::list<std::string> getServerNames();
    std::map<std::string, LocationRules>  getLocations()const;

    bool setHostAndPort(std::string & hostAndPort);
    void printServerConfig() const;
    bool isEmptyServer() const;
};

#endif
