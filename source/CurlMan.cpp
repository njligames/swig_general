
#include "CurlMan.h"

CurlMan::CurlMan()
{
	curl = curl_easy_init();
}

std::string CurlMan::Stringify()
{
	std::string mapString = { "\"" };

	for (auto it = Fields.cbegin(); it != Fields.cend(); it++) 
	{
		mapString.append(it->first + "=" + it->second + "&");
	}

	if (mapString.back() == '&')  mapString.pop_back();
	mapString.append("\"");

	return mapString;
}

std::string CurlMan::Post()
{
	std::string DataString = this->Stringify();

	curl_easy_setopt(curl, CURLOPT_POST, 1);
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, DataString.c_str());

	res = curl_easy_perform(curl);
	std::string resString = curl_easy_strerror(res);

	curl_easy_cleanup(curl);

	return resString;  // set status from Curl res
}

void CurlMan::Clear()
{
	Fields.clear();
}

void CurlMan::Add(std::string Name, std::string Value)
{
	Fields.insert(std::make_pair(Name, Value));
}

void CurlMan::Update(std::string Name, std::string Value)
{
	auto it = Fields.find(Name);
	if (it != Fields.end())
		it->second = Value;
	else
		this->Add(Name, Value);
}

void CurlMan::SetDomain(std::string NewDomain)
{
	curl_easy_setopt(curl, CURLOPT_URL, NewDomain.c_str());
}
