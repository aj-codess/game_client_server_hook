#pragma once

#include <iostream>
#include <string>

#include <boost/asio.hpp>

using namespace std;

struct domain_details{
    std::string host;
    std::string port;
};

class server_hook{
    public:
    server_hook(boost::asio::io_context& context,domain_details details)
    :ioc(context),resolver(context),domain(details) {
        cout<<"server Loaded "<<endl;
    };
    void init();
    bool isRunning(){
        bool running=false;

        // if(){
        //     running=true;
        // };

        return running;
    };

    private:
    boost::asio::io_context& ioc;
    domain_details domain;
    boost::asio::ip::tcp::resolver resolver;
    boost::asio::ip::tcp::resolver::results_types resolved_addr;
};


void server_hook::init(){

    this->resolved_addr=this->resolver.resolve(this->domain.host,this->domain.port);

};