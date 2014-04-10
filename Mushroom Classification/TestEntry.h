
#ifndef TEST_ENTRY_H
#define TEST_ENTRY_H

class TestEntry: public ID3DataEntry
{
public:
	TestEntry(bool state) {
		mState = state;
	};

	void setAttribute(int index, int value) {
		mAttributes[index] = value;
	};

	virtual bool getState() {return mState;};

	virtual int getAttribute(int index) {return mAttributes[index];};

private:
	bool mState;
	int mAttributes[3];
};

#endif