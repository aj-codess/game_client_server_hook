#pragma once

#include <iostream>
#include <string>

#include <boost/asio.hpp>
#include <boost/asio/spawn.hpp>

using namespace std;

struct payload_struct{

};


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

        if(){
            running=true;
        };

        return running;
    };
    std::vector<payload_struct> payload_stack;

    private:
    boost::asio::io_context& ioc;
    domain_details domain;
    boost::asio::ip::udp::resolver resolver;
    boost::asio::ip::udp::resolver::results_type resolved_addr;
    boost::asio::ip::udp::socket socket;
    void connector();
    void session(boost::asio::yield_context yield);
    void read(std::function<void()> callback);
    void write(std::function<void()> callback);
    std::vector<payload_struct> write_queue;
    std::vector<payload_struct> read_queue;
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

            boost::asio::spawn(this->socket.get_executor(),[&](boost::asio::yield_context yield){

                this->session(yield);

            });

        };

    });

};




void server_hook::session(boost::asio::yield_context yield){

            try{

                //ping network to keep alive
                if(this->payload_stack.size=0){

                    this->keep_alive();

                } else{

                    this->write()

                };

            } catch(const std::exception& e){
                
                cout<<"Error with session -"<<e.what()<<endl;

                breaker=true;

            };

};



void server_hook::read(std::function<void()> callback){

    this->socket.async_read_some(boost::asio::buffer(data,size),[&](boost::system::error_code ec,std::size_t byte){



    });

};




void server_hook::write(std::function<void()> callback){

    this->socket.async_write_some(boost::asio::buffer(data,size),[&](boost::system::error_code ec,std::size_t byte){



    });

};