#ifndef EVRSESSION_H
#define EVRSESSION_H

#include <iostream>
#include <string>


class EVRSession
{

private:
	std::string AuthToken;
	std::string Domain;

	std::string GetData();
	std::string PostData();

public:

	void SetDomain(std::string Domain);
	std::string GetTagList(std::string TagValue);
	void SetTagValue(std::string Uuid);
};




#endif // EVRSESSION_H
