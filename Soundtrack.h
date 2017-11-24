#ifndef _SOUND_TRACK
#define _SOUND_TRACK

#include <string>
#include <iostream>
#include <sstream>
using namespace std;

class Soundtrack
{
	// Overloaded stream insertion and extraction operators
	friend std::ostream &operator<<(std::ostream &, const Soundtrack &);
	friend std::istream &operator>>(std::istream&, Soundtrack&);

private:
	string composer;
	string title;
	string label;
	string catalogNumber;
	string dateRecorded;
	int dateReleased;

public:
	Soundtrack();
	Soundtrack(const string& theComposer, const string& theTitle, const string& theLabel,
		const string& theCatalogNumber, const string& theDateRecorded, const int& theDateReleased);

	void clear();

	void setComposer(const string& theComposer);
	void setTitle(const string& theTitle);
	void setLabel(const string& theLabel);
	void setCatalogNumber(const string& theCatalogNumber);
	void setDateRecorded(const string& theDateRecorded);
	void setDateReleased(const int& theDateReleased);

	string getComposer() const;
	string getTitle() const;
	string getLabel() const;
	string getCatalogNumber() const;
	string getDateRecorded() const;
	int getDateReleased() const;

	Soundtrack& operator=(const Soundtrack& right);

	bool operator==(const Soundtrack&) const;
	bool operator>(const Soundtrack&) const;
	bool operator<(const Soundtrack&) const;
}; // end Soundtrack

#endif