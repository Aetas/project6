/*
 * Derek Prince
 * Assignment 5
 * CU - Boulder
 * CSCI 2270 - Algorithms and Datastructures - Rhonda Hoenigman
 * Binary Search Tree
*/

#include<iostream>
#include<fstream>
#include<string>
#include"MovieTree.h"
#include<json-c/json.h>

using std::cin;
using std::cout;
using std::endl;
using std::string;



int main(int argc, char* argv[])
{
	MovieTree* database = new MovieTree();
	std::ifstream in_file;
	if(argc >= 1)
		in_file.open(argv[1]);

	if (in_file.is_open())
	{
		int rating, year, quantity;
		string title, buffer;
		while (!in_file.eof())
		{
			getline(in_file, buffer, ',');
			rating = stoi(buffer);
			getline(in_file, buffer, ',');
			title = buffer;
			getline(in_file, buffer, ',');
			year = stoi(buffer);
			getline(in_file, buffer);
			quantity = stoi(buffer);
			database->addRawNode(rating, title, year, quantity);
		}
	}
	else
	{
		cout << argv[1] << "----File was not found. Check local directory for" << argv[1] << "----" << endl;
		return 0;
		//could also -> while(!in_file.is_open()) {...requent new input... open()}
	}
	in_file.close();
    int size;
	int select = -1;
	MovieNode* temp = nullptr;
	json_object* jstring;
	json_object* jwrapper;
	int key = 1;
	while (select != 5)
	{
		string title = "";
		cout << "======Main Menu=====" << endl
			<< "1. Rent a movie" << endl
			<< "2. Print the inventory" << endl
			<< "3. Delete a movie" << endl
			<< "4. Count movies in tree" << endl
			<< "5. Quit" << endl;
		cin >> select;
		switch (select)
		{
		case 1:	//rent a movie
			cout << "Enter title:";
			cin >> title;
			temp = database->search(title);
			if (temp == NULL)
			{
				cout << "Movie not found." << endl;
				break;
			}
			if (temp->quantity == 0)
			{
				cout << "Movie out of stock." << endl;
				break;
			}
			//database->rentMovie(title);
			temp->quantity--;
			cout << "Movie has been rented." << endl
				<< "Movie Info:" << endl
				<< "===========" << endl
				<< "Ranking:" << temp->ranking << endl
				<< "Title:" << temp->title << endl
				<< "Year:" << temp->year << endl
				<< "Quantity:" << temp->quantity << endl;
            if (temp->quantity == 0)
                database->delete_node(temp);
			break;
		case 2:	//print inventory
			database->inorder_walk();
			break;
        case 3: //delete a movie
            cout << "Enter title:";
			cin >> title;
			temp = database->search(title);
			if (temp == NULL || temp = nullptr)
			{
				cout << "Movie not found." << endl;
				break;
			}
			database->delete_node(temp);
			break;
        case 4: //count movies in tree
            size = database->getTreeSize();
		case 5:
			cout << "Goodbye!" << endl;
			break;
		default://not an option
			cout << "That was not an option" << endl;
			break;
		}
	}
	ostream out_file("Assignment6Output.txt");
	out_file << database->getJsonObject();
	if (temp != nullptr)
		delete temp;
	delete database;
	return 0;
}

/* Old find movie menu option;

			cout << "Enter title:";
			cin >> title;
			temp = database->search(title);
			if (temp == NULL)
			{
				cout << "Movie not found." << endl;
				break;
			}
			cout << "Movie Info:" << endl
				<< "===========" << endl
				<< "Ranking:" << temp->ranking << endl
				<< "Title:" << temp->title << endl
				<< "Year:" << temp->year << endl
				<< "Quantity:" << temp->quantity << endl;
			break;

*/
