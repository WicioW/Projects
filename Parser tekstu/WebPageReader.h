#pragma once
#include "AbstractReader.h"
#include <vector>
#include <string>

using namespace std;

class WebPageReader:public AbstractReader
{
public:
	virtual void read() override;
	virtual void show_number_of_links() override;
	virtual void show_all_links() override;

	int number_of_links;

	vector <string> vector_with_links;

	WebPageReader();
	~WebPageReader();
};

