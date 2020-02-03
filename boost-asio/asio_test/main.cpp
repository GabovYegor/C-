#include <iostream>
#include <fstream>
#include <istream>
#include <ostream>
#include <string>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

int main()
{
    std::locale::global(std::locale(""));
    try
    {
        std::cout << "Enter URL(example: [url]www.cyberforum.ru):[/url] ";
        std::string URL;// = "www.cyberforum.ru";
        std::getline(std::cin, URL, '\n');

        boost::asio::io_service io_service;

        tcp::resolver resolver(io_service);
        tcp::resolver::query query(URL, "8080");
        tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
        tcp::resolver::iterator end;

        tcp::socket socket(io_service);
        boost::system::error_code error = boost::asio::error::host_not_found;
        while (error && endpoint_iterator != end)
        {
            socket.close();
            socket.connect(*endpoint_iterator++, error);
        }
        if (error)
            throw boost::system::system_error(error);

        boost::asio::streambuf request;
        std::ostream request_stream(&request);
        request_stream << "GET / HTTP/1.0\r\n"
                       << "Host: " + URL + "\r\n"
                       << "Accept: text/html\r\n"
                       << "Connection: close\r\n\r\n";

        boost::asio::write(socket, request);
        boost::asio::streambuf response;
        boost::asio::read_until(socket, response, "\r\n");

        std::istream response_stream(&response);
        std::string header;
        while (std::getline(response_stream, header) && header != "\r");

        std::ofstream file("web_source.txt");
        if(!file)
            throw std::runtime_error("Cannot create file");

        while (boost::asio::read(socket, response, boost::asio::transfer_at_least(1), error))
        {
            file << &response;
        }
        if (error != boost::asio::error::eof)
            throw boost::system::system_error(error);

        std::cout << "Done!\n";
        std::getchar();
    }
    catch (std::exception& e)
    {
        std::cout << "Exception: " << e.what();
        std::getchar();
    }
    return 0;
}
