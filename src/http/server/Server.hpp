#pragma once
#include "../../HTTP/Security/Security.hpp"
#include "../../HTTP/ServerConfig/ServerConfig.hpp"
#include "../../Config/Config.hpp"
#include "../../Logger/Logger.hpp"
#include <cpprest/http_listener.h>
#include <cpprest/http_listener.h> 
#include <cpprest/json.h>  
#include <cpprest/uri.h>         
#include <cpprest/containerstream.h>    
#include <cpprest/interopstream.h>             
#include <cpprest/rawptrstream.h>     
#include <cpprest/producerconsumerstream.h>   

using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;
using namespace web::http::experimental::listener;  
using namespace web::json;   

class HTTPServer
{
	public:
		HTTPServer(Config & config);
		~HTTPServer();
	private:

		static const string_t HEADER_NAME;

		void InitServer();
		void HandleGet(http_request request);
		void HandlePost(http_request request);
		void SendJSONResponse(int code, const http_request& request,const json::value& jsonObject);
		void LoadServerConfig();

		static std::string GetHeaderValue(const http_headers & headers, const string_t & key);

		http_listener m_listener;
		Config& m_config;
		ServerConfig * m_serverConfig;
};