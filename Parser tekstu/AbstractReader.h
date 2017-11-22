#pragma once
class AbstractReader
{
public:
	virtual void read() = 0;
	virtual void show_number_of_links() = 0;
	virtual void show_all_links() = 0;

	AbstractReader();
	~AbstractReader();

};

