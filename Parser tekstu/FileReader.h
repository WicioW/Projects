#pragma once
#include "AbstractReader.h"
#include <vector>
#include <string>

using namespace std;

class FileReader : public AbstractReader
{
public:
	virtual void read() override;
	virtual void show_number_of_links() override;
	virtual void show_all_links() override;

	vector <string> vector_with_links;

	int number_of_links;

	FileReader();
	~FileReader();
};

