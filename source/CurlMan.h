#ifndef CURLMAN_H
#define CURLMAN_H

#include <map>
#include <string>
#include <curl/curl.h>

// Note this is a rough windows implementation

class CurlMan
{

private:

	CURL *curl;
	CURLcode res;

	std::string Url;
	std::map<std::string, std::string> Fields;
    std::string Stringify();

public:

	CurlMan();
	std::string Post();
	void Clear();
	void Add(std::string Name, std::string Value);
	void Update(std::string Name, std::string Value);
	void SetDomain(std::string NewDomain);

};

#endif // CURLMAN_H
