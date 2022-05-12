//#include<stdio.h> 
//#include<string.h>
//#include<iostream>
#include "DB_new.cpp"
#include <regex>

using namespace std;

#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <string.h>
#include <regex>
#include <stdio.h>
using namespace std;

template <typename T>
static T get_input(const std::string& strQuery);
static std::string get_username();
static std::string get_password();
static std::string get_mail();
static void login_as_client();
static void login_after_chose_login_as_client();
static void login_as_agent();
static void register_user();
static bool Check_if_user_name_exists(string user_name);
static void main_menu();
static void client_menu(string username);
static bool Email_check(string email);
static void home_page();
static void Order_management();
static void Masseges(string user_name);
static void add_package_to_db();
static string get_destination();
static float get_price();
static int get_number_of_passengers();
static void edit_package();
static void agent_menu();
///// STATMENT OF ADD NEW PACKAGE FUNCTION
static void package_management();
static void Reply_to_messages_by_an_agent();
static bool Payment(int serial_number, const char* user_name);
static bool Order_vacation(int serial_number, const char* user_name);
static Date get_start_date_of_package();
static Date get_end_date_of_package();
static void Find_vacation(string user_name);
static void Order_status(string username);
static int PendingApprovalOrder();

///// STATMENT OF ALL UPDATE FUNCTION
static void edit_by_price();
static void edit_by_arrive_date();
static void edit_by_leave_date();
static int get_serial_number();



///// STATMENT OF ALL OREDER MENGMENT FUNCTION

static void login_as_agent();




int size_after_filter = PackegesfileSize();

static void Print_vacations(Packege  vacations)
{
	printPackege(vacations);
}

static bool Print_all_vacations(Packege* vacations, int size)
{
	bool check = false;
	for (int i = 0; i < size; i++)
	{
		if (!((strcmp(vacations[i].status, "In procces")) == 0 || (strcmp(vacations[i].status, "Paid up")) == 0 || (strcmp(vacations[i].status, "Approved")) == 0))
		{
			printPackege(vacations[i]);
			cout << endl;
			cout << "_______________________________________" << endl;
			cout << endl;
			check = true;
		}

	}
	if (!check)
	{
		cout << "No packages" << endl;
	}
	return check;
}
		



//  Find customer from DB by user name
static Client Find_customer(string user_name)
{
	Client* customer = getAllClients();
	int size = ClientsfileSize();
	Client temp;
	for (int i = 0; i < size; i++)
	{
		if (customer[i].user_name == user_name)
			return customer[i];
	}
	std::cout << "The user name not found The process failed, please try again  " << endl;
	string username;
	std::cout << "enter user name:" << endl;
	std::cin >> username;
	client_menu(username);
}

//  Find customer from DB by user name and return pointer to him(בשביל הפונקציה של ההודעות)
static Client* Find_customer2(string user_name)
{
	Client* customer = getAllClients();
	int size = ClientsfileSize();
	Client temp;
	for (int i = 0; i < size; i++)
	{
		if (customer[i].user_name == user_name)
			return &customer[i];
	}
	std::cout << "The user name not found " << endl;
	return NULL;
}



static bool check_date(Date date1, Date date2)
{
	if (date1.day == date2.day && date1.month == date2.month && date1.year == date2.year)
		return true;
	return false;
}

static void PrintWishList(Client customer)
{

	bool check = false;
	int choise, serial_number;
	Packege* vacations = getAllPackeges();
	int size = PackegesfileSize();
	for (int i = 0; i < 20; i++)
	{
		if (customer.wish_list[i] != 0)
		{
			for (int j = 0; j < size; j++)
			{
				if (vacations[j].serial_number == customer.wish_list[i])
					Print_vacations(vacations[j]);
			}
		}
	}
}


// copy constructor for date
static void Copy_date(Date* sourse, Date* target)
{
	target->day = sourse->day;
	target->month = sourse->month;
	target->year = sourse->year;
}

// copy constructor for date
static void copy_message(Message* sourse, Message* target)
{
	for(int i =0; i<50;i++)
		target->title[i] = sourse->title[i];
	for (int i = 0; i < 300; i++)
		target->content[i] = sourse->content[i];
	for (int i = 0; i < 10; i++)
		target->status[i] = sourse->status[i];
	Copy_date(&(sourse->sending_date), &(target->sending_date));
	for (int i = 0; i < 300; i++)
		target->response[i] = sourse->response[i];
}


// copy constructor for vacation

static void Copy_vacations(Packege* sourse, Packege* target)
{
	target->number_of_passengers = sourse->number_of_passengers;
	Copy_date(&(sourse->start), &(target->start));
	Copy_date(&(sourse->end), &(target->end));
	for (int i = 0; i < 100; i++)
		target->destination[i] = sourse->destination[i];
	target->price = sourse->price;
	target->serial_number = sourse->serial_number;
	for (int i = 0; i < 20; i++)
		target->status[i] = sourse->status[i];
}

// sort by date
static Packege* Sort_by_date(Packege* vacations, int size)
{
	Packege* sort_by_date = new Packege[size];
	for (int i = 0; i < size; i++)
	{
		//sort_by_date[i] = new Vacation[1];
		Copy_vacations(&(vacations[i]), &(sort_by_date[i]));
	}
	int i, j;
	Packege temp;
	for (i = 1; i < size; i++)
	{
		Copy_vacations(&(sort_by_date[i]), &(temp));
		j = i - 1;
		while (j >= 0 && ((sort_by_date[j].start.year > temp.start.year) || ((sort_by_date[j].start.year == temp.start.year) && (sort_by_date[j].start.month > temp.start.month)) || ((sort_by_date[j].start.year == temp.start.year) && (sort_by_date[j].start.month == temp.start.month) && sort_by_date[j].start.day > temp.start.day)))
		{
			Copy_vacations(&(sort_by_date[j]), &(sort_by_date[j + 1]));
			j = j - 1;
		}
		Copy_vacations(&(temp), &(sort_by_date[j + 1]));
	}
	return sort_by_date;
}

//Sort by price
static Packege* Sort_by_price(Packege* vacations, int size)
{
	Packege* sort_by_price = new Packege[size];
	for (int i = 0; i < size; i++)
	{
		//sort_by_price[i] = new Vacation[1];
		Copy_vacations(&(vacations[i]), &(sort_by_price[i]));
	}
	int i, j;
	Packege temp;
	for (i = 1; i < size; i++)
	{
		Copy_vacations(&(sort_by_price[i]), &(temp));
		j = i - 1;
		while (j >= 0 && sort_by_price[j].price > temp.price)
		{
			Copy_vacations(&(sort_by_price[j]), &(sort_by_price[j + 1]));
			j = j - 1;
		}
		Copy_vacations(&(temp), &(sort_by_price[j + 1]));
	}
	return sort_by_price;
}

static bool Payment(int serial_number, const char* user_name)
{
	if (searchClientByUserName(user_name) == -1 || searchPackegeBySerialNumber(serial_number) == -1)
		return false;
	Date date;
	string first_name , last_name;
	int id,cvc,temp,x=0;
	unsigned long long credit_card;
	
	cout << "****PAYMENT****" << endl;
	cout << endl;
	cout << "Enter the name of the cardholder: " << endl;
	cout << "first name: " << endl;
	cin >> first_name;
	cout << "last name: " << endl;
	cin >> last_name;
	cout << "Please enter ID: " << endl;
	cin >> id;
	cout << "Please enter credit card number: " << endl;
	cin >> credit_card;
	while (credit_card< 1000000000000000 || credit_card>9999999999999999)
	{
		cout << "The credit card mest to be wits 16 digits exacly, enter again: " << endl;
		cin >> credit_card;
	}
	cout << "Please enter expiration date: " << endl;
	cout << "Month: " << endl;
	cin >> date.month;
	cout << "Year: " << endl;
	cin >> date.year;
	cout << "Please enter CVC: " << endl;
	cin >> cvc;
	while (cvc < 100 || cvc>999)
	{
		cout << "The cvc mest to be wits 3 digits exacly, enter again: " << endl;
		cin >> cvc;
	}

	if (!UpdateClientPaymentDetails(user_name, id, credit_card, serial_number))
		return false;
	if (!UpdatePackegeStatus(2, serial_number))
		return false;
	if (!UpdatePackegeBuyerName(user_name, serial_number))
		return false;

	return true;

}

//show all orders status for client and let him canceled it
static void Order_status(string username)
{
	bool check = false;
	const char* user_name = username.c_str();
	Client client = getClientByIndex(searchClientByUserName(user_name) - 1); // get Client 

	for (int i = 0; i < client.vacations_list_size; i++) // move in client vaction list 
	{
		Packege p = getPackegeByIndex((searchPackegeBySerialNumber(client.vacations_list[i]) - 1));
		
		
		printPackege(p);
		check = true;
		cout << "Status:" << p.status << endl;
		cout << "______________________" << endl;
		cout << endl;
		if (strcmp(p.status, "Paid up") == 0) // paid uo but no approved
		{
			cout << "Pending approval" << endl;
			cout << endl;
			cout << "For cancelation press 1, else press 0 and Continue to the following orders" << endl;
			bool chiose;
			cin >> chiose;
			if (chiose)
			{
				if (UpdatePackegeStatus(3, p.serial_number))
				{
					cout << "The update sucsses" << endl;
				}
				else
					cout << "The update failed" << endl;
			}
		}
	}
	if (!check)
		cout << "No active orders" << endl;
	client_menu(user_name);

}


//if return true - continue to payment else exit to main menu
static bool Order_vacation(int serial_number, const char* user_name)
{
	if (searchClientByUserName(user_name) == -1 || searchPackegeBySerialNumber(serial_number) == -1)
		return false;

	UpdatePackegeStatus(1, serial_number);

	cout << "****ORDER VACATION****" << endl;
	cout << endl;
	printPackege(getPackegeByIndex(searchPackegeBySerialNumber(serial_number) - 1));
	cout << "Order now!" << endl;
	cout << endl;
	bool choise;
	cout << "To order -  press 1" << endl;
	cout << "(or 0 to Main Menu)" << endl;
	cin >> choise;

	if (choise)
	{
		char name[20];
		char last_name[20];
		int phone_number ,temp, x=0;
		cout << "Enter your details:" << endl;
		cout << "Name - " << endl;
		cin >> name;
		cout << "Last name - " << endl;
		cin >> last_name;
		cout << "Phone number - " << endl;
		cin >> phone_number;
		while (x != 10)
		{
			x = 1;
			temp = phone_number;
			while (temp != 0)
			{
				temp = temp / 10;
				x++;
			}
			if (x != 10)
			{
				std::cout << "Incorrect phone number try again " << endl;
				std::cin >> phone_number;
			}
		}

		if (!UpdateClientsOrderDetails(user_name, name, last_name, phone_number))
			return false;
		cout << "Press to continue" << endl;

		return true;
	}
	else
		UpdatePackegeStatus(0, serial_number);

	return false;
}


//return size of vacations by location
static int Get_size_vacations_by_location(Packege* vacations, string location)
{

	int counter = 0;
	for (int i = 0; i < size_after_filter; i++)
	{
		if (vacations[i].destination == location)
			counter++;
	}
	size_after_filter = counter;
	return size_after_filter;
}

//filter by destenation
static Packege* Get_vactions_by_location(Packege* vacation, string location)
{
	int size1 = size_after_filter;
	Packege temp;
	Packege* vacations = vacation;
	int counter = Get_size_vacations_by_location(vacations, location);
	int size = counter;
	Packege* new_vacations = new Packege[counter];
	counter = 0;
	for (int i = 0; i < size1; i++)
	{
		if (vacations[i].destination == location)
		{
			//new_vacations[i] = new Vacation[1];
			Copy_vacations(&(vacations[i]), &(new_vacations[counter]));
			counter++;
		}
	}

	return new_vacations;
}


//return size of vacations by passenger amount
static int Get_size_vacations_by_amount(Packege* vacations, int amount)
{
	int counter = 0;
	for (int i = 0; i < size_after_filter; i++)
	{
		if (vacations[i].number_of_passengers == amount)
			counter++;
	}
	size_after_filter = counter;
	return size_after_filter;
}

//filter by  passenger amount
static Packege* Get_vactions_by_passenger_amount(Packege* vacation, int amount)
{
	int size1 = size_after_filter;
	Packege temp;
	Packege* vacations = vacation;
	int counter = Get_size_vacations_by_amount(vacations, amount);
	int size = counter;
	Packege* new_vacations = new Packege[counter];
	counter = 0;
	for (int i = 0; i < size1; i++)
	{
		if (vacations[i].number_of_passengers == amount)
		{
			//new_vacations = new Vacation[1];
			Copy_vacations(&(vacations[i]), &(new_vacations[counter]));
			counter++;
		}
	}

	return new_vacations;
}


//return size of vacations by date
static int Get_size_vacations_by_date(Packege* vacations, Date check_in, Date check_out)
{
	int counter = 0;
	for (int i = 0; i < size_after_filter; i++)
	{
		if (vacations[i].start.day == check_in.day && vacations[i].start.month == check_in.month && vacations[i].start.year == check_in.year)
		{
			if (vacations[i].end.day == check_out.day && vacations[i].end.month == check_out.month && vacations[i].end.year == check_out.year)
				counter++;
		}
	}
	size_after_filter = counter;
	return size_after_filter;
}

//filter by date
static Packege* Get_vactions_by_date(Packege* vacation, Date check_in, Date check_out)
{
	int size1 = size_after_filter;
	Packege temp;
	Packege* vacations = vacation;
	int counter = Get_size_vacations_by_date(vacations, check_in, check_out);
	int size = counter;
	Packege* new_vacations = new Packege[counter];
	counter = 0;
	for (int i = 0; i < size1; i++)
	{
		if (check_date(vacation[i].start, check_in) && check_date(vacation[i].end, check_out))
		{
			//new_vacations = new Vacation[1];
			Copy_vacations(&(vacation[i]), &(new_vacations[counter]));
			counter++;
		}
	}
	return new_vacations;
}

static void Package_filtering(string user_name)
{
	const char* user_name_new = user_name.c_str();
	bool check4 = false, check5 = false;
	Client customer;
	int Serial_number_selected;
	int choise;
	Date check_in, check_out;
	string destination;
	int  passenger_amount, check, back, check2;
	int size = PackegesfileSize();
	Packege* vacations = getAllPackeges();
	std::cout << "If you want to back to menu  select 1 or select 0 to continue" << endl;
	std::cin >> check;
	if (check == 1)
		client_menu(user_name);
	std::cout << "Please enter a destination or select 0 to continue" << endl;
	std::cin >> destination;
	std::cout << "Please enter a passenger amount or select 0 to continue" << endl;
	std::cin >> passenger_amount;
	std::cout << "If you want to enter check-in and check-out select 1 or select 0 to continue" << endl;
	std::cin >> check2;
	if (destination != "0")
		vacations = Get_vactions_by_location(vacations, destination);
	if (passenger_amount != 0)
		vacations = Get_vactions_by_passenger_amount(vacations, passenger_amount);
	if (check2 == 1)
	{
		std::cout << "enter check in:" << endl;
		std::cout << "day: " << endl; 
		std::cin >> check_in.day;
		std::cout << "month: " << endl;
		std::cin >> check_in.month;
		std::cout << "year: " << endl;
		std::cin >> check_in.year;
		std::cout << "enter check out :"<<endl; 
		std::cout << "day: " << endl;
		std::cin >> check_out.day;
		std::cout << "month: " << endl;
		std::cin >> check_out.month;
		std::cout << "year: " << endl;
		std::cin >> check_out.year;
	}
	std::cout << "If you want to sort by date, select 1" << endl;
	std::cout << "If you want to sort by price, select 2" << endl;
	std::cout << "If you want to sort by price and by date, select 3" << endl;
	std::cout << "If you  dont want to sort , select 0" << endl;
	std::cout << "If you want to just add to wish list, select 4" << endl;
	std::cin >> check;
	while (check > 4 || check < 0)
	{
		std::cout << "Wrong choice Please try again" << endl;
		std::cin >> check;
	}
	if (vacations == NULL)
	{
		std::cout << "No suitable package was found" << endl;
		Package_filtering(user_name);
	}
	if (check == 1)
		Print_all_vacations(Sort_by_date(vacations, size_after_filter), size_after_filter);
	if (check == 2)
		Print_all_vacations(Sort_by_price(vacations, size_after_filter), size_after_filter);
	if (check == 3)
		Print_all_vacations(Sort_by_date(Sort_by_price(vacations, size_after_filter), size_after_filter), size_after_filter);
	if (check == 0)
		Print_all_vacations(vacations, size_after_filter);
	std::cout << "Enter the package number you selected" << endl;
	std::cin >> Serial_number_selected;
	check2 = searchPackegeBySerialNumber(Serial_number_selected);
	while (check2 == -1)
	{
		std::cout << "Wrong choice Please try again" << endl;
		std::cin >> Serial_number_selected;
		check2 = searchPackegeBySerialNumber(Serial_number_selected);
	}
	if (check == 4)
	{
		customer = Find_customer(user_name);// לבדוק מה קורה אם חוזר 0 זה בעיה
		check4 = UpdateClientWishlist(user_name_new, Serial_number_selected);
		if (check4)
			std::cout << "The package has been added to the wish list" << endl;
		else
			std::cout << "The package was not added to the wish list" << endl;
		client_menu(user_name);
	}
	else
	{
		check5 = Order_vacation(Serial_number_selected, user_name_new);
		if(Payment(Serial_number_selected, user_name_new))
			cout << "Payment completed successfully" << endl;
		else
		{
			cout << "Payment not successfully" << endl;
			UpdatePackegeStatus(0, Serial_number_selected);
		}
		client_menu(user_name);
	}
}

static void Find_vacation(string user_name)
{
	if (PackegesfileSize() == -1)
	{
		cout << "NO packeges exsit yet, Sorry" << endl;
		client_menu(user_name);

	}
	const char* user = user_name.c_str();
	bool check4 = false, check5 = false;
	Client customer;
	int choise, Serial_number_selected, check, check2 = -1;
	std::cout << "Please select an option:" << endl;
	std::cout << "To view existing packages, select - 1" << endl;
	std::cout << "To filter packages, select - 2" << endl;
	std::cout << "for back select - 3" << endl;
	std::cin >> choise;
	while (choise > 3 || choise < 1)
	{
		std::cout << "Wrong choice Please try again" << endl;
		std::cin >> choise;
	}
	if (choise == 1)
	{

		std::cout << "If you dont want to sort , select 0" << endl;
		std::cout << "If you want to sort by date, select 1" << endl;
		std::cout << "If you want to sort by price, select 2" << endl;
		std::cout << "If you want to sort by price and by date, select 3" << endl;
		std::cout << "If you want to just add to wish list, select 4" << endl;
		std::cin >> check;
		while (check > 4 || check < 0)
		{
			std::cout << "Wrong choice Please try again" << endl;
			std::cin >> check;
		}
		if (check == 0)
			Print_all_vacations(getAllPackeges(), PackegesfileSize());
		if (check == 1)
			Print_all_vacations(Sort_by_date(getAllPackeges(), PackegesfileSize()), PackegesfileSize());
		if (check == 2)
			Print_all_vacations(Sort_by_price(getAllPackeges(), PackegesfileSize()), PackegesfileSize());
		if (check == 3)
			Print_all_vacations(Sort_by_date(Sort_by_price(getAllPackeges(), PackegesfileSize()), PackegesfileSize()), PackegesfileSize());
		if (check == 4)
		{
			Print_all_vacations(getAllPackeges(), PackegesfileSize());
			std::cout << "Enter the package number you selected to put in wish list" << endl;
			std::cin >> Serial_number_selected;
			check2 = searchPackegeBySerialNumber(Serial_number_selected);
			while (check2 == -1)
			{
				std::cout << "Wrong choice Please try again" << endl;
				std::cin >> Serial_number_selected;
				check2 = searchPackegeBySerialNumber(Serial_number_selected);
			}
			customer = Find_customer(user_name);// לבדוק מה קורה אם חוזר 0 זה בעיה
			check4 = UpdateClientWishlist(user, Serial_number_selected);
			if(check4)
				std::cout << "The package has been added to the wish list" << endl;
			else
				std::cout << "The package was not added to the wish list" << endl;
			client_menu(user_name);
		}
		std::cout << "Enter the package number you selected" << endl;
		std::cin >> Serial_number_selected;//בדיקה שנבחר מס סידורי קיים
		check2 = searchPackegeBySerialNumber(Serial_number_selected);
		while (check2 == -1)
		{
			std::cout << "Wrong choice Please try again" << endl;
			std::cin >> Serial_number_selected;
			check2 = searchPackegeBySerialNumber(Serial_number_selected);
		}
		check5 = Order_vacation(Serial_number_selected, user);
		if (check5)
		{
			if(Payment(Serial_number_selected, user))
				cout<< "Payment completed successfully" << endl;
			else
			{
				cout << "Payment not successfully" << endl;
				UpdatePackegeStatus(0, Serial_number_selected);
			}
				
			client_menu(user_name);
		}
			
		else
			client_menu(user_name);
	}
	if (choise == 2)
		Package_filtering(user_name);
	if (choise == 3)
		return client_menu(user_name);
}


// Wish list
static void Wishsh_list(string user_name)
{
	if (PackegesfileSize() == -1)
	{
		cout << "NO packeges exsit yet, Sorry" << endl;
		client_menu(user_name);

	}
	const char* user = user_name.c_str();
	bool check = false;
	int choise, serial_number;
	Client temp = Find_customer(user_name);// לבדוק מה קורה אם חוזר 0 זה בעיה
	cout << "The packages that you liked: " << endl;
	PrintWishList(temp);
	cout << "If you want to place an order Select 1, To return to the main menu, press 0" << endl;
	cin >> choise;
	while (choise < 0 || choise > 1)
	{
		cout << "Wrong choice Please try again" << endl;
		cin >> choise;
	}
	if (choise == 1)
	{
		cout << "enter serial number" << endl;
		cin >> serial_number;
		while (!check)
		{
			for (int i = 0; i < 20; i++)
			{
				if (temp.wish_list[i] == serial_number)
					check = true;
			}
			if (check)
			{
				if (Order_vacation(serial_number, user))
				{
					if (Payment(serial_number, user))
						cout << "Payment completed successfully" << endl;
					else
					{
						cout << "Payment not successfully" << endl;
						UpdatePackegeStatus(0, serial_number);
					}	
					client_menu(user_name);
				}		
				else
				{
					cout << "The system was unable to update the details" << endl;
					client_menu(user_name);
				}
			}
			else
			{
				cout << "the serial number not found in wish list" << endl;
				client_menu(user_name);
			}
		}
	}
	if (choise == 0)
		client_menu(user_name);
}



static void Masseges(string user_name)
{
	
	int choise;
	cout << "To contact us, press 1, to read your Masseges press 0 " << endl;
	cin >> choise;
	while (choise < 0 || choise > 1)
	{
		cout << "Wrong choice Please try again" << endl;
		cin >> choise;
	}
	if (choise == 1)
	{
		char title[20];
		char content[20];
		cout << "enter title: " << endl;
		cin >> title;
		cout << "enter content: " << endl;
		cin >> content;
		Message message = creatNewMessage(title, content);
	   const char* user_name_new = user_name.c_str();
		UpdateClientMessage(user_name_new, message);
		
	}
	cout << "My Masseges" << endl;
	int i = 0;
	bool check = false;
	Client* customer = Find_customer2(user_name);
	while (!check)
	{
		if (customer->message_list[i].content[0] != '0')
		{
			printMassege(customer->message_list[i]);
			i++;
		}
		else
			check = true;
	}
}



static void package_management()
{
	int choice, serial_number;
	do
	{
		cout <<
			"[1] add new package" "\n"
			"[2] edit package" "\n"
			"[3] remove package" "\n"
			"[4] back to agent menu" "\n";
		cout << "Enter ur choise:";
		cin >> choice;
		switch (choice)
		{
		case 1:
			add_package_to_db();
			break;
		case 2:
			edit_package();
			break;
		case 3:
		{
			
			if (Print_all_vacations(getAllPackeges(), PackegesfileSize()))
			{
				cout << "enter serial number that you want remove" << endl;
				cin >> serial_number;
				int x = deletePackegeFromDb(serial_number);
				if (x == -1)
					cout << "Unexpected malfunction" << endl;
				if (x == 0)
					cout << "The serial number does not exist" << endl;
				if (x == 1)
					cout << "The deletion succeeded" << endl;

			}
			break;
		}
			
		case 4:
			agent_menu();
			break;
		}
	} while (true);
}

static void add_package_to_db()
{
	Packege New;
	Date start_of_package, end_of_package;

	string destination;
	float price;
	int day, month, year, number_of_passengers;
	start_of_package = get_start_date_of_package();
	end_of_package = get_end_date_of_package();
	destination = get_destination();
	const char* p_destination = destination.c_str();
	price = get_price();
	number_of_passengers = get_number_of_passengers();
	New = creatNewPackege(p_destination, price, start_of_package, end_of_package, number_of_passengers);
	if (setPackegeToDB(New))
	{
		cout << "package added successfully" "\n";
		cout << endl;
	}
	else
		cout << "Failed to add package, contact your administrator " "\n";
	Print_all_vacations(getAllPackeges(),PackegesfileSize());
}

static Date get_start_date_of_package()
{
	Date start;
	int day, month, year;
	cout << "Enter start date of package:" << endl;
	cout << "day:" << endl;
	cin >> day;
	cout << "month:" << endl;
	cin >> month;
	cout << "year:" << endl;
	cin >> year;
	start = getNewDate(day, month, year);
	return start;

}

static Date get_end_date_of_package()
{
	Date end;
	int day, month, year;
	cout << "Enter end date of package:"<<endl;
	cout << "day:" << endl;
	cin >> day;
	cout << "month:" << endl;
	cin >> month;
	cout << "year:" << endl;
	cin >> year;
	end = getNewDate(day, month, year);
	return end;
}

//
static string get_destination()
{
	bool check_if_re_enter;
	string destination;
	cout << "Enter destination :"<<endl;
	cin >> destination;
	while (destination.size() >= 100)
	{
		cout << "destination name must be up to 100 characters, press 0 to exit and move to agent menu or 1 to re-enter destination name: ";
		cin >> check_if_re_enter;
		if (check_if_re_enter)
		{
			cout << "enter destination name: ";
			cin >> destination;

		}
		else
			agent_menu();

	}
	return destination;
}

static float get_price()
{
	int check_if_price_below_equal_0;
	float price ;
	cout << "Enter price :" << endl;
	cin >> price;
	while (price <= 0)
	{
		cout << "price can't be below\equal to 0, press 0 to exit and move to agent menu or 1 to re-enter price : ";
		cin >> check_if_price_below_equal_0;
		if (check_if_price_below_equal_0)
		{
			cout << "enter new price: ";
			cin >> price;

		}
		else
			agent_menu();

	}
	return price;
}

static int get_number_of_passengers()
{
	bool check_if_passengers_below_equal_0;
	int get_number_of_passengers;
	cout << "number_of_passengers:"<<endl;
	cin >> get_number_of_passengers;
	while (get_number_of_passengers <= 0)
	{
		cout << "number of passengers can't be below\equal to 0, press 0 to exit and move to agent menu or 1 to re-enter price : ";
		cin >> check_if_passengers_below_equal_0;
		;
		if (check_if_passengers_below_equal_0)
		{
			cout << "number of passengers:"<<endl;
			cin >> get_number_of_passengers;

		}
		else
			agent_menu();

	}
	return get_number_of_passengers;
}



static void Reply_to_messages_by_an_agent()
{
	bool check = false;
	string respone;
	string user_name;
	int choise, index;
	if (PrintAllUnReadMasseges() == -1)
		cout << "Unexpected malfunction" << endl;
	else if(PrintAllUnReadMasseges() == 0)
		cout << "No messages" << endl;
	else 
	{
		std::cout << "To respond select 1, return to the menu Select 0" << endl;
		std::cin >> choise;
		while (choise > 1 || choise < 0)
		{
			std::cout << "Wrong choice Please try again" << endl;
			std::cin >> choise;
		}
		while(choise == 1)
		{
			std::cout << "enter user name of Client that you respone him:" << endl;
			std::cin >> user_name;
			std::cout << "enter index of Client that you respone him:" << endl;
			std::cin >> index;
			std::cout << "enter your respone:" << endl;
			std::cin >> respone;
			const char* user_name_new = user_name.c_str();
			const char* respone_new = respone.c_str();
			while (strlen(respone_new) > 299)
			{
				std::cout << "the respone should be up tp 300 characters, enter again: " << endl;
				std::cin >> respone;
			}
			check = UpdateClientMessageResponse(user_name_new, respone_new, index);
			if(check)
				std::cout << "The response was received " << endl;
			else
				std::cout << "No response was received. Please try again " << endl;
			std::cout << "To respond select 1, return to the menu Select 0" << endl;
			std::cin >> choise;
		}
		
	}
	agent_menu();
}



//############################################################package_management :  EDIT PACKAGE TO DB ##########################################

static void edit_package()
{
	bool check = Print_all_vacations(getAllPackeges(), PackegesfileSize());
	int choice;
	do
	{
		cout <<
			"[1] edit by price" "\n"
			"[2] edit by arrive date" "\n"
			"[3] edit by leave date" "\n"
			"[4] edit amount for packege" "\n"
			"[5] back to agent menu" "\n";
		cout << "Enter ur choise:";
		cin >> choice;
		switch (choice)
		{
		case 1:
			edit_by_price();
			break;
		case 2:
			edit_by_arrive_date();
			break;
		case 3:
			edit_by_leave_date();
			break;
		case 4:
			if (check)
			{
				int serial_number;
				serial_number = get_serial_number();
				int count;
				cout << "Enter amount: " << endl;
				cin >> count;
				while (count <= 0)
				{
					cout << "wrong amount, Enter amount that bigger then 0: " << endl;
					cin >> count;
				}
				if (!(AddingQuantityToPackege(serial_number, count)))
					cout << "the packege not exist " << endl;
			}
			else
				cout << "No packeges" << endl;
			break;
		case 5:
			agent_menu();
			break;
		}
	} while (true);
}

static void edit_by_price()
{
	int serial_number;
	float new_price;
	serial_number = get_serial_number();
	new_price = get_price();
	if (UpdatePackegePrice(new_price, serial_number))
		cout << "price has updated succesfiyl""\n";
	else
		cout << "price has updated failed""\n";
	edit_package();

}

static int get_serial_number()
{

	int serial_number;
	cout << "Enter serial number of package that you want to edit:";
	cin >> serial_number;
	if (searchPackegeBySerialNumber(serial_number) != -1)
	{
		return serial_number;
	}
	return -1;
}

static void edit_by_arrive_date()
{
	Date arrival_date;
	int serial_number;
	serial_number = get_serial_number();
	arrival_date = get_start_date_of_package();
	if (UpdatePackegeArrivalDate(arrival_date, serial_number))
		cout << "arrive date has updated succesfiyl""\n";
	else
		cout << "arrive date has updated failed""\n";

	edit_package();

}

static void edit_by_leave_date()
{
	Date leave_date;
	int serial_number;
	serial_number = get_serial_number();
	leave_date = get_end_date_of_package();
	if (UpdatePackegeLeavingDate(leave_date, serial_number))
		cout << "leave date has updated succesfiyl""\n";
	else
		cout << "leave date has updated failed""\n";

	edit_package();
}

//############################################################Order_management  ##########################################


static void Order_management()
{

	int choice;
	do
	{
		cout <<
			"[1] Orders awaiting confirmation" "\n"
			"[2] Canceled orders" "\n"
			"[3] back to agent menu""\n";
		cout << endl;

			

		cout << "Enter ur choise:";
		cin >> choice;
		switch (choice)
		{
		case 1:
			if(PendingApprovalOrder()==-2)
				cout << "No packages are awaiting approval" << endl;
			break;
		case 2:
			if (PrintAllPackagesCanceled() == -2)
				cout << "Unexpected malfunction" << endl;
			if (PrintAllPackagesCanceled() == -1)
				cout << "There are no canceled packages" << endl;
			break;
		case 3:
			agent_menu();
			break;
		}
	} while (true);
}


//View all packages waiting for approval, if not, the function returns -2, if the process fails the function returns 0
//if the agent chooses to leave the process the function returns -1
static int PendingApprovalOrder()
{
	cout << "****ORDER MANAGEMENT****" << endl;
	cout << endl;
	if (PrintAllPackagesAwaitingApproval() == -1)/// print all the order thats pending approval
		return -2;
	cout << endl;

	cout << "To confirm or cancel an order press 1" << endl;
	cout << "To return to the main menu press 0" << endl;
	int choise;
	cin >> choise;
	cout << endl;
	if (choise)
	{
		cout << "Enter a package serial number" << endl;
		int serial_number;
		cin >> serial_number;
		while (searchPackegeBySerialNumber(serial_number) == -1)
		{
			cout << "The package does not exist" << endl;
			cout << "Enter a package serial number" << endl;
			cin >> serial_number;
		}
		cout << endl;
		cout << "To confirm press 1, to cancel press 0" << endl;
		cin >> choise;
		if (choise)
		{
			if (!UpdatePackegeStatus(4, serial_number))
			{
				cout << "Unexpected malfunction" << endl;
				return 0;
			}
			cout << "Package status updated" << endl;
			cout << endl;
			return 1;
		}
		else
		{
			if (UpdatePackegeStatus(3, serial_number));
			{
				cout << "Unexpected malfunction" << endl;
				return 0;
			}
			cout << "Package status updated" << endl;
			cout << endl;
			return 1;
		}
	}
	else
		return -1;

}

































/////////// HOME PAGE OF PROGRAM /////////////
static void home_page() {

	std::cout << "#############################################################" << endl;
	std::cout << "#                 Welcome to Harel Tours                    #" << endl;
	std::cout << "#                    _                                      #" << endl;
	std::cout << "#                  -=\\`\\                                    #" << endl;
	std::cout << "#              |\\ ____\\_\\___                                #" << endl;
	std::cout << "#            -=\\c`_________ _`)                             #" << endl;
	std::cout << "#               `~~~~~/ /~~`\                                #" << endl;
	std::cout << "#                 -==/ /                                    #" << endl;
	std::cout << "#                   '-'                                     #" << endl;
	std::cout << "#                  _  _                                     #" << endl;
	std::cout << "#                 ( `   )_                                  #" << endl;
	std::cout << "#                (    )    `)                               #" << endl;
	std::cout << "#              (_   (_ .  _) _)                             #" << endl;
	std::cout << "#                                             _             #" << endl;
	std::cout << "#                                            (  )           #" << endl;
	std::cout << "#                                          ( `  ) . )       #" << endl;
	std::cout << "#           Hotel                         (_, _(  ,_)_)     #" << endl;
	std::cout << "#         |_______|                                         #" << endl;
	std::cout << "#         |_______|                                         #" << endl;
	std::cout << "#         |_______|                                         #" << endl;
	std::cout << "#         |_______|                                         #" << endl;
	std::cout << "#         |_______|                                         #" << endl;
	std::cout << "#         |_______|                                         #" << endl;
	std::cout << "#         |_______|                                         #" << endl;
	std::cout << "#         |_______|                                         #" << endl;
	std::cout << "#############################################################" << endl;
	main_menu();
}
/////////// MAIN_MENU OF PROGRAM /////////////
static void main_menu()
{
	int choice;
	do
	{
		std::cout << "Hello, Would you like to login(register inside login) in or register?" "\n"
			"[1] Login as client" "\n"
			"[2] Login as agent" "\n"
			"[3] Exit""\n";
		std::cout << "Enter your choise:";
		std::cin >> choice;
		while (choice > 3 || choice < 1)
		{
			std::cout << "wrong choise try again:"<<endl;
			std::cin >> choice;
		}
		switch (choice)
		{
		case 1:
			login_as_client();
			break;
		case 2:
			login_as_agent();
			break;
		case 3:
			exit(1);
			break;
		}
	} while (true);
}
/////////// CHOOSE LOGIN AS CLIENT ( 4 OPTIONS :1-LOGIN 2-REGISTER 3-GO BACK TO MAIN MENU /////////////
static void login_as_client()
{
	int choise;
	do
	{
		std::cout << "For login press 1 ""\n"
			"For register press 2""\n"
			"return to home page 3""\n"
			"Enter ur choise:";
		std::cin >> choise;
		switch (choise)
		{
		case 1:
			login_after_chose_login_as_client();
			break;
		case 2:
			register_user();
			break;
		case 3:
			main_menu();
			break;
		}
	} while (true);
}
/////////// LOGIN AS CLIENT /////////////
static void login_after_chose_login_as_client()
{
	Client* Customer_Information = getAllClients();
	string username = get_username();
	string password = get_password();
	const char* username1 = username.c_str();
	const char* password1 = password.c_str();
	int size_of_users = ClientsfileSize();
	bool keep_trying = true;

	for (int i = 0; i < size_of_users; ++i)
	{

		if (strcmp(Customer_Information[i].user_name, username1) == 0)
		{
			while (keep_trying)
			{
				if (strcmp(Customer_Information[i].password, password1) == 0)
				{
					client_menu(username);
				}
				else
				{
					std::cout << "Incorrect password do you want to re-enter the password? 0-No , 1-Yes " << endl;
					std::cin >> keep_trying;
					if (keep_trying)
					{
						password = get_password();
						password1 = password.c_str();
					}
				}
			}
		}
	}
	std::cout << "User hasn't found""\n";
	main_menu();
}
/////////// SHOW CLIENT MENU : 1-FIND_VACTION 2-ORDER STATUS 3-WISH_LIST 4-MESSAGES 5 HOME PAGE 6 EXIT/////////////
static void client_menu(string username) {
	int choice;
	do
	{
		std::cout <<
			"[1] Find a vaction" "\n"
			"[2] Order status" "\n"
			"[3] Wish list" "\n"
			"[4] Messages""\n"
			"[5] Home page(Log out)"<<endl;
			

		std::cout << "Enter ur choise:";
		std::cin >> choice;
		switch (choice)
		{
		case 1:
			Find_vacation(username);
			break;
		case 2:
			Order_status(username);
			break;
		case 3:
			Wishsh_list(username);
			break;
		case 4:
			Masseges(username);
			break;
		case 5:
			home_page();
			break;
		}
	} while (true);
};
/////////// REGISTER NEW CLIENT IF SUCCSESS SEND TO LOGIN ELSE PRINT FAILED AND RETURN TO HOME PAGE /////////////
static void register_user()
{
	std::string username;
	bool keep_trying = true;
	while (keep_trying)
	{
		username = get_username();
		if (Check_if_user_name_exists(username)) //// if user name existed, return false
		{
			keep_trying = false;
		}
		else
		{
			std::cout << "name is already used , want to try another name?0-No ,1-Yes:";
			std::cin >> keep_trying;
			if (keep_trying == 0)
			{
				home_page();
			}
		}
	}

	std::string password = get_password();
	std::string mail = get_mail();

	const char* username1 = username.c_str();
	const char* password1 = password.c_str();
	const char* mail1 = mail.c_str();

	Client new_acc = creatNewClient(username1, password1, mail1);   ///////////// createNewClient return clint
	if (setClientToDB(new_acc))
	{
		std::cout << "create has succeed""\n";
		login_after_chose_login_as_client();
	}
	else
	{
		std::cout << "create hasn't succeed , try again later""\n";
		home_page();
	}
}
/////////// IF USER EXIST RETURN FALSE ELSE RETURN TRUE /////////////
static bool Check_if_user_name_exists(string user_name)
{
	Client* db_all_clients = getAllClients();
	int size_of_all_clients = ClientsfileSize();
	const char* username1 = user_name.c_str();
	bool keep_trying = true;
	for (int i = 0; i < size_of_all_clients; ++i)
	{
		if (strcmp(db_all_clients[i].user_name, username1) == 0)
		{
			return false;
		}
	}
	return true;
}


template <typename T>
static T get_input(const std::string& strQuery)
{
	std::cout << strQuery << "\n> ";
	T out = T();

	while (!(std::cin >> out)) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits <std::streamsize>::max(), '\n');
		std::cout << "Error!" "\n";
		std::cout << strQuery << "\n> ";
	}

	return out;
}

/////////// RETURN PASSWORD ,CONDITION UP TO 8 CHARACTERS /////////////
static std::string get_password()
{

	std::string password1 = get_input <std::string>("Please enter your password.");
	while (password1.size() >= 8)
	{
		std::cout << "Error! Password up to 8 characters." "\n";
		password1 = get_input <std::string>("Please enter your password.");
	}
	

	return password1;
}
/////////// RETURN NAME UP TO 100 CHARACTERS /////////////
static std::string get_username()
{
	std::string username = get_input <std::string>("Please enter a username.");
	while (username.size() >= 100)
	{
		std::cout << "Error! username should be up to 100 characters." "\n";
		username = get_input <std::string>("Please enter a username.");
	}
	return username;
}
/////////// RETURN MAIL ONLY IF HE VALID  /////////////
static std::string get_mail()
{
	string mail;
	std::cout << "Enter your Email-Id:";
	std::cin >> mail;
	bool flag = true;
	while (flag)
	{
		while (mail.size() >= 20 && (!(Email_check(mail))))
		{
			std::cout << "Error! mail should be up to 20 characters." "\n";
			mail = get_input <std::string>("Please enter a username.");
		}

		while (!(Email_check(mail)))
		{
			std::cout << "bad email , try again:";
			std::cin >> mail;
		}
		if (mail.size() <= 20 && Email_check(mail))
			return mail;
	}
	return "";
}
/////////// CHECK IF MAIL IS VALID , IF ITS OK RETURN TRUE ELSE FALSE   /////////////
static bool Email_check(string email)
{
	const regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
	return regex_match(email, pattern);
}







///////////login_as_agent /////////////
static void login_as_agent()
{
	int check_what_returns_from_CheckingValidityAgentDetials;
	string username = get_username();
	string password = get_password();
	const char* username1 = username.c_str();
	const char* password1 = password.c_str();

	check_what_returns_from_CheckingValidityAgentDetials = CheckingValidityAgentDetials(username1, password1);
	if (check_what_returns_from_CheckingValidityAgentDetials == -2)
		cout << "You are not registered in the system, contact with ur work manager ""\n";
	if (check_what_returns_from_CheckingValidityAgentDetials == -1)
		cout << " password is incorrect ""\n";
	if (check_what_returns_from_CheckingValidityAgentDetials == 0)
		agent_menu();
	if (check_what_returns_from_CheckingValidityAgentDetials == -3)
		cout << "file opening failed ""\n";

	home_page();

}



///////////NOT FINISH /////////////



static void agent_menu() {
	int choice;

	do
	{
		std::cout <<
			"[1] package management" "\n"
			"[2] Order management" "\n"
			"[3] Messages" "\n"
			"[4] Home page(Log out)" << endl;
			
		std::cout << "Enter ur choise:";
		std::cin >> choice;
		switch (choice)
		{
		case 1:
			package_management();
			break;
		case 2:
			Order_management();
			break;
		case 3:
			Reply_to_messages_by_an_agent();
			break;
		case 4:
			home_page();
			break;
		}
	} while (true);
};



int main()
{
	
	home_page();
	return 0;
}