
#ifndef ID3_DATA_ENTRY_H
#define ID3_DATA_ENTRY_H

class ID3DataEntry
{
public:
	virtual bool getState() = 0;
	virtual int getAttribute(int index) = 0;
};

#endif