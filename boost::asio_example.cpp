#include <iostream>
#include <boost/beast.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <string>

using namespace std;
namespace http = boost::beast::http;

const static string MAIN_API = "ip-api.com";
const static string API_ARGUMENTS = "/json/";

class Client 
{
public:
	static string GetResponse(string ip) 
	{
		// IO_CONTEXT, RESOLVER, SOCKET
		boost::asio::io_context io;
		boost::asio::ip::tcp::resolver resolver(io);
		boost::asio::ip::tcp::socket socket(io);

		// CONNECT
		boost::asio::connect(socket, resolver.resolve(MAIN_API, "80"));

		// REQUEST
		string argument = API_ARGUMENTS + ip;
		http::request<http::string_body> req(http::verb::get, argument, 11);
		req.set(http::field::host, MAIN_API);
		req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

		// WRITE
		http::write(socket, req);

		// RESPONCE
		string responce;
		{
			boost::beast::flat_buffer buffer;
			http::response<http::dynamic_body> res;
			http::read(socket, buffer, res);
			responce = boost::beast::buffers_to_string(res.body().data());
		}

		// SOCKET_SHUTDOWN
		socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);

		return responce;
	};
};

int main()
{
	cout << Client::GetResponse("google.com") << endl;;
}
