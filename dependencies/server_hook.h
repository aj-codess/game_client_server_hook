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
    :ioc(context),resolver(context), socket(ioc),domain(details) {
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
    void connector();

    private:
    boost::asio::io_context& ioc;
    domain_details domain;
    boost::asio::ip::tcp::resolver resolver;
    boost::asio::ip::tcp::resolver::results_type resolved_addr;
    boost::asio::ip::tcp::socket socket;
};


void server_hook::init(){
    boost::system::error_code ec;

    this->resolved_addr=this->resolver.resolve(this->domain.host,this->domain.port,ec);

   if(this->resolved_addr.empty() || ec){

        cout<<"Error Resolving Endpoints - "<<ec.message()<<endl;

    } else{

        this->connector();

    };

};



void server_hook::connector(){

    boost::asio::async_connect(this->socket,this->resolved_addr,[&](boost::system::error_code ec,boost::asio::ip::tcp::endpoint endP){

        if(ec){

            cout<<"error connecting the endpoint - "<<ec.message()<<endl;

        } else{

            

        };

    });

};