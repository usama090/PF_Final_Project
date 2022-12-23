#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;


const int INVENTORY_SIZE = 100;
const int FACULTY_SIZE = 56;

struct faculty {
	int id;
	string name;
	string department;
};

// 1, 20, Text book, Stationary, 1, 2, 3, 4, 5
// 2, 10, Pen, Stationary, 2
// 2, 10, Ink, Stationary

struct inventory {
	int id;
	int count;
	int allocCount;
	string name;
	string category;
	faculty allocations[FACULTY_SIZE];
};

string lowerCase(string str);

int searchItem(string name, inventory items[]);

int searchFaculty(int id, faculty staff[]);

bool searchAllocation(int staffId, int itemIndex, inventory items[]);

void viewItem(inventory item);

void viewItems(inventory items[]);

inventory addItem(int id, int count, string name, string category, faculty staff[]);

bool removeItem(string name, inventory items[]);

bool updateItem(inventory items[], faculty staff[], int itemIndex,
				int staffId, bool assign=false, bool retrieve=false);

faculty addFaculty(int id, string name, string department);

bool removeFaculty(int id, faculty staff[]);


int main() {
	faculty staff[FACULTY_SIZE];
	int staffCount = 0;

	staff[staffCount++].id = 1;
	staff[0].name = "Faizan Ahmad";
	staff[0].department = "Computer Science";

	staff[staffCount++].id = 2;
	staff[1].name = "Usama Akhtar";
	staff[1].department = "Computer Science";

	staff[staffCount++].id = 3;
	staff[2].name = "Ameer Hamza";
	staff[2].department = "Social Science";

	inventory items[INVENTORY_SIZE];
	int itemCount = 0;

	items[itemCount++].id = 1;
	items[0].count = 68;
	items[0].name = "Pen";
	items[0].category = "Stationary";
	items[0].allocations[0] = staff[1];
	items[0].allocations[1] = staff[0];
	items[0].allocCount = 2;

	items[itemCount++].id = 2;
	items[1].count = 55;
	items[1].name = "Text Book";
	items[1].category = "Stationary";
	items[1].allocations[0] = staff[2];
	items[1].allocCount = 1;
	
	items[itemCount++].id = 3;
	items[2].count = 10;
	items[2].name = "Printer";
	items[2].category = "Electronics";	
	items[2].allocCount = 0;


	cout << "======================================================================" << endl;
	cout << "=============== WELCOME TO INVENTORY MANAGEMENT SYSTEM ===============" << endl;
	cout << "======================================================================" << endl;

	int option = 0;
	int index = 0;
	int id = 0;

	do {
		cout << endl << "[1] ADD ITEM " << endl;
		cout << "[2] REMOVE ITEM " << endl;
		cout << "[3] EDIT ITEM " << endl;
		cout << "[4] SEARCH ITEM " << endl;
		cout << "[5] ASSIGN ITEM " << endl;
		cout << "[6] RETRIEVE ITEM " << endl;
		cout << "[7] VIEW INVENTORY " << endl;
		cout << "[0] EXIT APPLICATION" << endl;
		cout << endl << "Enter an option [0 - 7] and hit ENTER: ";
		
		cin >> option;
		if (isalnum(option) || (option < 0 || option > 7)) {
			cout << "\nOPTION IS INVALID\n" << endl;

		} else {
			switch (option)
			{
				case 1:
					cin.ignore();
					cout << "Enter item name: ";
					getline(cin, items[itemCount].name);

					if (items[itemCount].name.compare("") == 0) 
						cout << "Sorry, item's name cannot stay empty!" << endl;

					else if (searchItem(items[itemCount].name, items) == -1) {
						cout << "Enter item category: ";
						getline(cin, items[itemCount].category);

						cout << "Enter item count: ";
						cin >> items[itemCount].count;

						items[itemCount].allocCount = 0;
						items[itemCount++].id = items[itemCount - 1].id + 1;

					} else {
						cout << "Sorry, cannot add duplicate item: " << items[itemCount].name << endl;
					}

					break;

				case 2:
					cin.ignore();
					cout << "Enter item name: ";
					getline(cin, items[itemCount].name);

					if (items[itemCount].name.compare("") == 0)
						cout << "Sorry, item's name cannot stay empty!" << endl;

					else if (removeItem(items[itemCount].name, items)) {
						cout << "Item '" << items[itemCount].name << "' removed from inventory!" << endl;
						itemCount--;
					}

					else
						cout << "Sorry, unable to remove item!" << endl;
					
					break;

				case 3:
					cin.ignore();
					cout << "Enter item name: ";
					getline(cin, items[itemCount].name);

					if (items[itemCount].name.compare("") == 0) {
						cout << "Sorry, item's name cannot stay empty!" << endl;
						break;
					}

					index = searchItem(items[itemCount].name, items);

					if (index == -1)
						cout << "Sorry, item '" << items[itemCount].name << "' not found in inventory!" << endl;

					else {
						do {
							cout << "[1] EDIT NAME " << endl;
							cout << "[2] EDIT CATEGORY " << endl;
							cout << "[3] EDIT COUNT " << endl;
							cout << "[0] GO TO MAIN MENU" << endl;
							cout << endl << "Enter an option [0 - 3] and hit ENTER: ";

							cin >> option;
							if (isalnum(option) || (option < 0 || option > 3)) {
								cout << "\nOPTION IS INVALID\n" << endl;
								option = -1;
							}

							switch (option)
							{
								case 1:
									cin.ignore();
									cout << "Edit item name (" << items[index].name << "): ";
									getline(cin, items[itemCount].name);

									if (searchItem(items[itemCount].name, items) == -1)
										items[index].name = items[itemCount].name;
									else
										cout << "Sorry, cannot set duplicate item: " << items[itemCount].name << endl;

									break;
								
								case 2:
									cin.ignore();
									cout << "Edit item category (" << items[index].category << "): ";
									getline(cin, items[index].category);
									break;

								case 3:
									cin.ignore();
									cout << "Edit item count (" << items[index].count << "): ";
									cin >> items[index].count;
									break;

								default:
									break;

							}

						} while (option != 0);

						option = -1;
					}
					
					break;

				case 4:
					cin.ignore();
					cout << "Enter item name: ";
					getline(cin, items[itemCount].name);

					if (items[itemCount].name.compare("") == 0) {
						cout << "Sorry, item's name cannot stay empty!" << endl;
						break;
					}

					index = searchItem(items[itemCount].name, items);

					if (index != -1) {
						cout << endl;
						viewItem(items[index]);

					} else
						cout << "No match found with item name: " << items[itemCount].name << endl; 
					
					break;

				case 5:
					cin.ignore();
					cout << "Enter item name: ";
					getline(cin, items[itemCount].name);

					if (items[itemCount].name.compare("") == 0) {
						cout << "Sorry, item's name cannot stay empty!" << endl;
						break;
					}

					index = searchItem(items[itemCount].name, items);
					if (index != -1) {
						cout << "Enter staff id: ";
						cin >> id;

						if (searchFaculty(id, staff) == -1) {
							cout << "No match found with staf id: " << id << endl;
							break;
						}

						staff[staffCount].name = staff[searchFaculty(id, staff)].name;

						if (!searchAllocation(id, index, items)) {
							updateItem(items, staff, index, id, true, false);
							cout << "Success: Item '" << items[itemCount].name 
								 << "' assigned to faculty member '" 
								 << staff[staffCount].name << "'" << endl;

						} else {
							cout << "Failure: Item '" << items[itemCount].name 
								 << "' already assigned to faculty member '" 
								 << staff[staffCount].name << "'" << endl;
						}


					} else
						cout << "No match found with item name: " << items[itemCount].name << endl; 

					break;

				case 6:
					cin.ignore();
					cout << "Enter item name: ";
					getline(cin, items[itemCount].name);

					if (items[itemCount].name.compare("") == 0) {
						cout << "Sorry, item's name cannot stay empty!" << endl;
						break;
					}

					index = searchItem(items[itemCount].name, items);
					if (index != -1) {
						cout << "Enter staff id: ";
						cin >> id;

						if (searchFaculty(id, staff) == -1) {
							cout << "No match found with staf id: " << id << endl;
							break;
						}

						staff[staffCount].name = staff[searchFaculty(id, staff)].name;

						if (searchAllocation(id, index, items)) {
							updateItem(items, staff, index, id, false, true);
							cout << "Success: Item '" << items[itemCount].name 
								 << "' retrieved from faculty member '" 
								 << staff[staffCount].name << "'" << endl;

						} else {
							cout << "Failure: Item '" << items[itemCount].name 
								 << "' not assigned to faculty member '" 
								 << staff[staffCount].name << "'" << endl;
						}


					} else
						cout << "No match found with item name: " << items[itemCount].name << endl; 

					break;

				case 7:
					cout << endl;
					viewItems(items);
					cout << endl;
					break;

				default:
					break;
			}
		}

	} while (option != 0);

	cout << endl;
	cout << "======================================================================" << endl;
	cout << "============================== GOOD BYE ==============================" << endl;
	cout << "======================================================================" << endl;

	return 0;
}

void viewItem(inventory item) {
	cout << "=================================== ITEM ===================================" << endl;
	cout << "|ID \t|Name \t\t\t|Category \t\t|Count \t|Allocations" << endl;

	cout << '|' << item.id << setw(7);
	cout << '|' << item.name << setw(24 - item.name.length());
	cout << '|' << item.category << setw(24 - item.category.length());
	cout << '|' << item.count << setw(6);
	cout << '|' << item.allocCount;
	cout << endl;
	cout << "============================================================================" << endl;
}

void viewItems(inventory items[]) {
	cout << "================================== ITEMS ===================================" << endl;
	cout << "|ID \t|Name \t\t\t|Category \t\t|Count \t|Allocations" << endl;

	for (int i = 0; i < INVENTORY_SIZE; i++) {
		if (!items[i].id) break;

		cout << '|' << items[i].id << setw(7);
		cout << '|' << items[i].name << setw(24 - items[i].name.length());
		cout << '|' << items[i].category << setw(24 - items[i].category.length());
		cout << '|' << items[i].count << setw(6);
		cout << '|' << items[i].allocCount;
		cout << endl;
	}
	cout << "============================================================================" << endl;

}

inventory addItem(int id, int count, string name, string category, faculty staff[])
{
	inventory item;
	item.id = id;
	item.count = count;
	item.name = name;
	item.category = category;

	for (int i = 0; i < FACULTY_SIZE; i++)
		item.allocations[i] = staff[i];

    return item;
}

bool removeItem(string name, inventory items[]) {
	int itemIndex = searchItem(name, items);

	if (itemIndex == -1)
		return false;

	for (int i = itemIndex; i < INVENTORY_SIZE - 1; i++) {
		items[i] = items[i + 1];

		if (!items[i].id) 
			break;
	}

	return true;
}

bool updateItem(inventory items[], faculty staff[], int itemIndex,
				int staffId, bool assign, bool retrieve) {
		
	if (assign) {
		// decrease item count
		items[itemIndex].count--;

		int allocCount = items[itemIndex].allocCount;

		// add staff to item allocations array
		items[itemIndex].allocations[allocCount] = staff[searchFaculty(staffId, staff)];

		// increase allocation count
		items[itemIndex].allocCount++;
	}

	if (retrieve) {
		// increase item count
		items[itemIndex].count++;

		// decrease allocation count
		items[itemIndex].allocCount--;

		// remove staff from allocations array
		removeFaculty(staffId, items[itemIndex].allocations);
	}

	return true;
}

// int countAllocations(faculty allocations[]) {
// 	int count = -1;

// 	while (allocations[++count].id);

// 	return count;
// }

faculty addFaculty(int id, string name, string department)
{
	faculty staff;
	staff.id = id;
	staff.name = name;
	staff.department = department;

    return staff;
}

bool removeFaculty(int id, faculty staff[]) {
	int staffIndex = searchFaculty(id, staff);

	if (staffIndex == -1)
		return false;

	for (int i = staffIndex; i < FACULTY_SIZE - 1; i++) {
		staff[i] = staff[i + 1];

		if (!staff[i].id) 
			break;
	}

	return true;
}

string lowerCase(string str)
{
	string lowerStr = str;
    for (int i = 0; i < str.length(); i++)
		lowerStr[i] = tolower(str[i]);

	return lowerStr;
}

int searchItem(string name, inventory items[])
{
    for (int i = 0; i < INVENTORY_SIZE; i++) {
		if (!items[i].id)
			return -1;
		
		if (lowerCase(items[i].name).compare(lowerCase(name)) == 0)
			return i;
	}
	
	return -1;
}

int searchFaculty(int id, faculty staff[]) {
	for (int i = 0; i < FACULTY_SIZE; i++) {
		if (!staff[i].id)
			return -1;
			
		if (staff[i].id == id)
			return i;
	}
	
	cout << "not found!!!" << endl;
	return -1;
}

bool searchAllocation(int staffId, int itemIndex, inventory items[]) {
	int staffIndex = searchFaculty(staffId, items[itemIndex].allocations);

	if (staffIndex == -1)
		return false;
	
	return true;
}

