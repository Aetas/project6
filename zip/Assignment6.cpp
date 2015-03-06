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
#include<json/json.h>

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
		string title, buffer, key;
		while (!in_file.eof())
		{
		    json_object* tALog = json_object_new_array();

			getline(in_file, buffer, ',');
			rating = stoi(buffer);
			getline(in_file, buffer, ',');
			title = buffer;
			getline(in_file, buffer, ',');
			year = stoi(buffer);
			getline(in_file, buffer);
			quantity = stoi(buffer);

			database->addRawNode(rating, title, year, quantity, tALog);

			json_object* jAWrapper = json_object_new_object();
			json_object* jAOperation = json_object_new_string("add");
			json_object* jATitle = json_object_new_string(title.c_str());

		    json_object_object_add(jAWrapper, "operation", jAOperation);
		    json_object_object_add(jAWrapper, "parameter", jATitle);
		    json_object_object_add(jAWrapper, "output", tALog);

		    key = std::to_string(database->operations);

		    json_object_object_add(database->getJsonObject(), key.c_str(), jAWrapper);

		    database->operations++;
		}

	}
	else
	{
		cout << argv[1] << "----File was not found. Check local directory for" << argv[1] << "----" << endl;
		return 0;
		//could also -> while(!in_file.is_open()) {...requent new input... open()}
	}
	in_file.close();
	int select = -1;
	MovieNode * temp = nullptr;
	while (select != 5)
	{
		cout << "======Main Menu=====" << endl
			<< "1. Rent a movie" << endl
			<< "2. Print the inventory" << endl
			<< "3. Delete a movie" << endl
			<< "4. Count movies in tree" << endl
			<< "5. Quit" << endl;
		cin >> select;
		if (select == 1)	//rent a movie
        {
            string title = "";
			cout << "Enter title:";
			cin.ignore(10000, '\n');
			std::getline(cin, title);
			temp = database->iterative_search(title);
			if (temp == NULL)
				cout << "Movie not found." << endl;
			else if (temp->quantity == 0)
                cout << "Movie out of stock." << endl;

	//		if (temp != NULL || temp != nullptr)
	//		{
            if (temp != NULL || temp != nullptr)
			    temp->quantity--;

			    json_object* jROperation = json_object_new_string("rent");           //makes a value string with rent
			    json_object* jRTitle = json_object_new_string(title.c_str());  //makes a value string with title
			    //json_object* jRQuantity = json_object_new_int(temp->quantity);       //makes a value int with quantity
			    json_object* jRWrapper = json_object_new_object();

			    json_object_object_add(jRWrapper, "operation", jROperation);
			    json_object_object_add(jRWrapper, "parameter", jRTitle);
                if (temp != NULL || temp != nullptr)
                {
                    json_object* jRQuantity = json_object_new_string(std::to_string(temp->quantity).c_str());
                    json_object_object_add(jRWrapper, "output", jRQuantity);
                }
			    else
			    {
			        json_object* jRQuantity = json_object_new_string("0");
			        json_object_object_add(jRWrapper, "output", jRQuantity);
			    }

                string key = std::to_string(database->operations);          //***THIS MAY CAUSE YOU ISSUES LATER*** requires c++11 standards. appears to compile on g++4.7 -std=c++0x
                json_object_object_add(database->getJsonObject(), key.c_str(), jRWrapper);
                database->operations++;

            if (temp != NULL || temp != nullptr)
            {
                    cout << "Movie has been rented." << endl
                    << "Movie Info:" << endl
                    << "===========" << endl
                    << "Ranking:" << temp->ranking << endl
                    << "Title:" << temp->title << endl
                    << "Year:" << temp->year << endl
                    << "Quantity:" << temp->quantity << endl;
                if (temp->quantity == 0)
                {
                    json_object* tDLog = json_object_new_array();
                    temp = database->search(title, tDLog);
                    json_object* jDWrapper = json_object_new_object();
                    json_object* jDOperation = json_object_new_string("delete");
                    json_object* jDTitle = json_object_new_string(temp->title.c_str());
                    json_object_object_add(jDWrapper, "operation", jDOperation);
                    json_object_object_add(jDWrapper, "parameter", jDTitle);
                    json_object_object_add(jDWrapper, "output", tDLog);

                    string key = std::to_string(database->operations);

                    json_object_object_add(database->getJsonObject(), key.c_str(), jDWrapper);

                    database->delete_node(temp);

                    database->operations++;
                }
            }
        }
		if (select == 2)	//print inventory
		{

		    json_object* jWWrapper = json_object_new_object();
		    json_object* jWOperation = json_object_new_string("traverse");

		    json_object* tWLog = json_object_new_array();

		    database->inorder_walk(tWLog);

            json_object_object_add(jWWrapper, "operation", jWOperation);
		    json_object_object_add(jWWrapper, "output", tWLog);
		    string key = std::to_string(database->operations);
		    json_object_object_add(database->getJsonObject(), key.c_str(), jWWrapper);

		    database->operations++;

		}

        if (select == 3) //delete a movie
        {
            cout << "Enter title:";
            string title = "";
            cin.ignore(1000, '\n');
			std::getline(cin, title);

			json_object* tDLog = json_object_new_array();

			temp = database->search(title, tDLog);
			if (temp == NULL || temp == nullptr)
			{
				cout << "Movie not found." << endl;
			}
			else
			{
			    json_object* jDWrapper = json_object_new_object();
                json_object* jDOperation = json_object_new_string("delete");
                json_object* jDTitle = json_object_new_string(temp->title.c_str());
                json_object_object_add(jDWrapper, "operation", jDOperation);
                json_object_object_add(jDWrapper, "parameter", jDTitle);
                json_object_object_add(jDWrapper, "output", tDLog);

                string key = std::to_string(database->operations);

                json_object_object_add(database->getJsonObject(), key.c_str(), jDWrapper);

                database->delete_node(temp);

                database->operations++;
			}
        }

        if (select == 4) //count movies in tree
        {
            int size = database->getTreeSize();
            json_object* jCWrapper = json_object_new_object();
            json_object* jOOperation = json_object_new_string("count");
            json_object* jsize = json_object_new_int(size);

            json_object_object_add(jCWrapper, "operation", jOOperation);
            json_object_object_add(jCWrapper, "output", jsize);

            string key = std::to_string(database->operations);

            json_object_object_add(database->getJsonObject(), key.c_str(), jCWrapper);

            database->operations++;

        }

		if (select == 5)
			cout << "Goodbye!" << endl;

	}

	std::ofstream out_file;
	out_file.open("Assignment6Output.txt");
	out_file << json_object_to_json_string_ext(database->getJsonObject(), JSON_C_TO_STRING_PRETTY);
	if (temp != nullptr)
		delete temp;
	delete database;
	return 0;
}