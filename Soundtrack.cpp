#include "Soundtrack.h"

Soundtrack::Soundtrack() :
	composer(""), title(""), label(""), catalogNumber(""), dateRecorded(""), dateReleased(1900)
{
} // end default constructor

Soundtrack::Soundtrack(const string& theComposer, const string& theTitle, const string& theLabel, const string& theCatalogNumber,
	const string& theDateRecorded, const int& theDateReleased) :
	composer(theComposer), title(theTitle), label(theLabel), catalogNumber(theCatalogNumber),
	dateRecorded(theDateRecorded), dateReleased(theDateReleased)
{
} // end constructor

void Soundtrack::clear()
{
	composer = "";
	title = "";
	label = "";
	catalogNumber = "";
	dateRecorded = "";
	dateReleased = 1990;
}  // end clear

void Soundtrack::setComposer(const string & theComposer)
{
	composer = theComposer;
} // end setComposer

void Soundtrack::setTitle(const string & theTitle)
{
	title = theTitle;
} // end setTitle

void Soundtrack::setLabel(const string & theLabel)
{
	label = theLabel;
} // end setLabel

void Soundtrack::setCatalogNumber(const string & theCatalogNumber)
{
	catalogNumber = theCatalogNumber;
} // end setCatalogNumber

void Soundtrack::setDateRecorded(const string & theDateRecorded)
{
	dateRecorded = theDateRecorded;
} // end setDateRecorded

void Soundtrack::setDateReleased(const int & theDateReleased)
{
	dateReleased = theDateReleased;
} // end setDateReleased

string Soundtrack::getComposer() const
{
	return composer;
} // end getComposer

string Soundtrack::getTitle() const
{
	return title;
} // end getTitle

string Soundtrack::getLabel() const
{
	return label;
} // end getLabel

string Soundtrack::getCatalogNumber() const
{
	return catalogNumber;
} // end getCatalogNumber

string Soundtrack::getDateRecorded() const
{
	return dateRecorded;
} // end getDateRecorded

int Soundtrack::getDateReleased() const
{
	return dateReleased;
} // end getDateReleased

Soundtrack& Soundtrack::operator=(const Soundtrack& right)
{
	setComposer( right.getComposer() );
	setTitle( right.getTitle() );
	setLabel( right.getLabel() );
	setCatalogNumber( right.getCatalogNumber() );
	setDateRecorded( right.getDateRecorded() );
	setDateReleased( right.getDateReleased() );

	return *this;
}  // end overloaded = operator

bool Soundtrack::operator==(const Soundtrack& right) const
{
	if ( (label == right.label) && (catalogNumber == right.catalogNumber) )
		return true;
	else
		return false;
} // end overloaded == operator

bool Soundtrack::operator>(const Soundtrack& right) const
{
	if (     (label >  right.label)  
		|| ( (label == right.label) && (catalogNumber >  right.catalogNumber) ) )
		return true;
	else
		return false;
}

bool Soundtrack::operator<(const Soundtrack& right) const
{
	if (     (label <  right.label)  
		|| ( (label == right.label) && (catalogNumber <  right.catalogNumber) ) )
		return true;
	else
		return false;
}

ostream &operator<<(ostream& out, const Soundtrack& cd)
{
	out << endl << cd.getComposer() << "   ";
	out << cd.getTitle() << "   ";
	out << cd.getLabel() << "   ";
	out << cd.getCatalogNumber() << "   ";
	out << cd.getDateRecorded() << "   ";
	out << cd.getDateReleased();

	return out;
} // end overloaded << operator

istream &operator>>(istream &in, Soundtrack &val)
{
	string buf;
	int iBuf;

	getline(in, buf);
	val.setComposer(buf);

	getline(in, buf);
	val.setTitle(buf);

	getline(in, buf);
	val.setLabel(buf);

	getline(in, buf);
	val.setCatalogNumber(buf);

	getline(in, buf);
	val.setDateRecorded(buf);

	in >> iBuf;
	val.setDateReleased(iBuf);

	in.get();

	return in;
} // end overloaded >> operator