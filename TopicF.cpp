#pragma warning (disable: 4290)

#include "Soundtrack.h"
#include "AVL.h"
#include <fstream>
#include <vector>
using namespace std;

// Opens file for reading, calls readInput
bool openFile(const string& fileName, vector<Soundtrack>& cdVector, AvlTree<Soundtrack>& avlTree);

/** Creates Soundtrack objects from valid file data
@param inputFile  The file to be processed
@param cd	The Soundtrack object to be initialized
@pre  File is valid and opened
@post Soundtrack object created
@return  true if file data is valid
		 false if data is invalid	*/
bool readInput(ifstream& inputFile, Soundtrack& cd);

/** Displays this message:
**************** Press Enter to Continue -->	*/
void continueProgram();

// Displays items in a tree
template<class ItemType>
void display(ItemType& entries);

/** Gets Soundtrack IDs for Soundtracks recorded in the 1950s
@param cdVector	 Soundtrack objects created from file data
@param matchedYear	Holds Soundtrack IDs from matches  */
void getYear(const vector<Soundtrack>& cdVector, vector<Soundtrack>& matchedYear);


int main()
{
	AvlTree<Soundtrack> avlTree;
	vector<Soundtrack> cdVector;  // Holds soundtrack objects created from file input
	string fileName = "Topic F Soundtrack.txt";  // File to open
	bool ableToOpen;  // Test success of opening file

	cout << "Create and populate AVL tree\n\n";
	
	do {
		ableToOpen = openFile(fileName, cdVector, avlTree);
		if (!ableToOpen)
		{
			cout << fileName << " cannot be opened.  Enter another file name -->  ";
			getline(cin, fileName);
		}
	} while (!ableToOpen);

	continueProgram();

	cout << "Get item with key \"FSMBox 03 Disc 8\":\n\n";
	Soundtrack FSM;
	FSM.setLabel("FSM");
	FSM.setCatalogNumber("Box 03 Disc 8");
	if ( !avlTree.get(FSM) )
		cout << "No items found with key \"FSMBox 03 Disc 8\"\n\n";
	cout << "\n\nGet item with key \"FSMBox 07 Disc 8\":\n\n";
	Soundtrack FSM2;
	FSM2.setLabel("FSM");
	FSM2.setCatalogNumber("Box 07 Disc 8");
	if (!avlTree.get(FSM2))
		cout << "No items found with key \"FSMBox 07 Disc 8\"\n";

	continueProgram();

	cout << "Listing of all items in the tree: (There are " << avlTree.getNumberOfNodes() << " items in the tree)\n\n";
	avlTree.inorderTraverse(display);

	continueProgram();

	cout << "\n\nList all soundtracks recorded in the 1950s:\n\n";
	vector<Soundtrack> matchedYear;
	getYear(cdVector, matchedYear);
	for (unsigned int i = 0; i < matchedYear.size(); i++)
	{
		if (avlTree.get(matchedYear[i]))
			cout << matchedYear[i];
	}

	continueProgram();

	cout << "\n\nDelete all items with key \"FSM V8N11\":";
	Soundtrack dltFSM;
	dltFSM.setLabel("FSM");
	dltFSM.setCatalogNumber("V8N11");
	if (avlTree.get(dltFSM))
	{
		avlTree.remove(dltFSM);
		cout << dltFSM << "\nhas been deleted\n\n";
	}
	cout << "Again delete all items with key \"FSM V8N11\":\n";
	if (avlTree.get(dltFSM))
	{
		avlTree.remove(dltFSM);
		cout << dltFSM << "\nhas been deleted\n\n";
	}
	else
		cout << "NO items for \"FSM V8N11\"";

	continueProgram();

	cout << "\nListing of all items in the tree: (There are " << avlTree.getNumberOfNodes() << " items in the tree)\n";
	avlTree.inorderTraverse(display);

	cin.ignore( cin.rdbuf()->in_avail() );
	cout << "\n\nProgram Ending\n\n";
	cout << "Press Enter to end -->  ";
	cin.ignore();
}  // end main


bool openFile(const string& fileName, vector<Soundtrack>& cdVector, AvlTree<Soundtrack>& avlTree)
{
	ifstream inputFile(fileName);
	bool validData, ableToAdd;

	if (inputFile.fail())
		return false;
	else
	{
		while (!inputFile.eof())
		{
			Soundtrack* cd = new Soundtrack();
			validData = readInput(inputFile, *cd);
			if (validData)
			{
				cdVector.push_back(*cd);
				ableToAdd = avlTree.add(*cd);
				if (!ableToAdd)
					cout << *cd << " is a duplicate";
			}
			delete cd;
			cd = nullptr;
		}
		inputFile.close();
	}
	return true;
}  // end openFile


bool readInput(ifstream& inputFile, Soundtrack& cd)
{
	int iBuf;
	string buffer, temp;
	string delimiter = " \t";  // Remove trailing whitespace

	getline(inputFile, buffer, '\n');

	// 0 - 24
	temp = buffer.substr(0, 24);
	string composer = temp.substr(0, temp.find_last_not_of(delimiter) + 1);
	cd.setComposer(composer);

	// 24 - 64
	temp = buffer.substr(24, 40);
	string title = temp.substr(0, temp.find_last_not_of(delimiter) + 1);
	cd.setTitle(title);

	// 64 - 80
	temp = buffer.substr(64, 16);
	string label = temp.substr(0, temp.find_last_not_of(delimiter) + 1);
	cd.setLabel(label);

	// 80 - 104
	temp = buffer.substr(80, 24);
	string catalogNumber = temp.substr(0, temp.find_last_not_of(delimiter) + 1);
	cd.setCatalogNumber(catalogNumber);

	// 104 - 112
	temp = buffer.substr(104, 8);
	string dateRecorded = temp.substr(0, temp.find_last_not_of(delimiter) + 1);
	cd.setDateRecorded(dateRecorded);

	// 112 - 116
	try 
	{
		iBuf = stoi(buffer.substr(112, 4));
		cd.setDateReleased(iBuf);
	}
	catch (std::exception) 
	{
		cout << endl << endl << buffer.substr(112, 4) << " is not a numeric value.  This input ignored:";
		cout << cd << "   " << buffer.substr(112, 4);
		return false;
	}
	return true;
}  // end readInput


void continueProgram()
{
	cin.ignore( cin.rdbuf()->in_avail() );
	cout << "\n\n************************************* Press Enter to continue  -->  ";
	cin.ignore();
}  // end continueProgram


template<class ItemType>
void display(ItemType& entries)
{
	cout << entries;
}  // end display


void getYear(const vector<Soundtrack>& cdVector, vector<Soundtrack>& matchedYear)
{
	vector<string> years = { "50", "51", "52", "53", "54", "55", "56", "57", "58", "59" };
	Soundtrack inTheFifties;

	for (unsigned int i = 0; i < cdVector.size(); i++)
	{
		for (unsigned int j = 0; j < years.size(); j++)
		{
			if (cdVector[i].getDateRecorded().substr(2, 2) == years[j])
			{
				inTheFifties.setLabel(cdVector[i].getLabel());
				inTheFifties.setCatalogNumber(cdVector[i].getCatalogNumber());
				matchedYear.push_back(inTheFifties);
				inTheFifties.clear();
			}
		}
	}
}  // end getYear