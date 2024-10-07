#include <iostream>
#include <string>
#include <server_hook.h>

#include <boost/asio.hpp>

using namespace std;

class server_init{
    public:
    server_init(boost::asio::io_context& ioc, domain_details domain)
    :client_server(ioc,domain){

        client_server.init();

    };

    private:
    server_hook client_server;
};

int main(){
    domain_details endpoint={"localhost","8080"};

    boost::asio::io_context ioc;

    server_init operands(ioc,endpoint);

    ioc.run();

    return 0;
}