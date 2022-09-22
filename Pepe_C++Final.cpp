#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include "pepefunc.h"

using namespace std;

/*
Side Note( I had to change around the code for every thing so enjoy experimenting)

Added better birth day tracker

Optianal Automatic sort and save when adding

Optional Automatic load on startup

More sorting options (limited)

Additional information ( any kind )  

simple Password protect

allow user to name file

employee logins

Sub-Menus - for making passwords, looking at in debth details ext

Elaborate/robust password protect (allow changing of password, limit tries before locking out)

Individual customer screen that shows the customer peronal data such as password, Date of birth, 
		and where there gmail/phone number would go if we actually did that
		
More search options (limited) - Made it so that the user can make there own ID number, 
		so when using any of the functions you can call the user with that 
		number (This took a roundabout 6 hours for me to figure out how to do :/ )
	
Made so the users account can be tampered with unless password is verified 
		(renting/returning movies, changing password, viewing private data ext)

Could be some stuff im forgetting but Ive worked on this all night so me=tired and going to bed :/

*/

class person{
	public:
		
		//This allows members of the store class direct access to the private attributes
		friend class store;
		
		//Constructor function just sets the movie "counter" to zero
		person() { hmMovies = 0; }
		
	private:
		string first;
		string last;
		int ID;		
		int birthYear;
		int birthMonth;
		int birthDay;
		string pass;
		int hmMovies;
		string movies[10];
};

class store{
	public:
		
		//Constructor function sets the number of customers to zero
		store()	{ hmCustomer = 0; }
		
		//this function was by far the hardest, what it does is finds what index the given id is no matter where it is sorted
		int findIndex(int id){
		string filename;
		saveCust("tempdata");;
		ifstream readfile ( "tempdata" );
			
		readfile >> hmCustomer;
			
		for ( int i = 0; i < hmCustomer; i ++ ){
				readfile >> customer[i].ID
						 >> customer[i].first 
						 >> customer[i].last
						 >> customer[i].birthMonth
						 >> customer[i].birthDay  
						 >> customer[i].birthYear
						 >> customer[i].pass 
						 >> customer[i].hmMovies;
				
						 
				for( int j = 0; j < customer[i].hmMovies; j ++ ){
					readfile >> customer[i].movies[j];
					
					//Put the spaces back
					for ( int k = 0; k < customer[i].movies[j].length(); k ++){
						if ( customer[i].movies[j][k] == '_')
							customer[i].movies[j][k] = ' ';
					}
								
				}
				if (customer[i].ID == id){
						 	return i;
						 }
			}	
		}
		
		//checkes if the id is already taken by someone else
		bool isTaken(int ID){
			
			for ( int i = 0; i < hmCustomer; i ++ ){
				
				if ( ID == customer[i].ID)
				return 0;
				
			}
			return 1;
		}
		
		//Adds a new customer		
		void newCust(){
			int ID;
			int month;
			int day;
			cout << "Pick an ID number : ";
			cin >> ID;
			while(!isTaken(ID) or ID == 0){
				if (ID == 0){
					cout << "ID can't be 0, try a diffrent ID : ";
				}
				else{
					cout << "ID number " << ID << " is already taken, try a diffrent ID : ";
				}
				cin >> ID;
			}
			customer[hmCustomer].ID = ID;
			cout << "First : ";
			cin >> customer[hmCustomer].first;
			cout << "Last  : ";
			cin >> customer[hmCustomer].last;
			
			
			cout << "Month of Birth (As Number) : ";
			cin >> month;
			while(month > 12 or month < 1){
				cout << "Month must be between 1 and 12, try again : ";
				cin >> month;
			}
			customer[hmCustomer].birthMonth = month;
			
			cout << "Day of Birth : ";
			cin >> day;
			while(day > 31 or day < 1){
				cout << "Day must be between 1 and 31, try again : ";
				cin >> day;
			}
			customer[hmCustomer].birthDay = day;
			
			cout << "Year of Birth : ";
			cin >> customer[hmCustomer].birthYear;
			
			
			customer[hmCustomer].pass = makePassword();
			
			customer[hmCustomer].hmMovies = 0;
			cout << customer[hmCustomer].pass;
			
			hmCustomer++;
			system("pause");		
		}
		
		//allows customer to change their password
		void changePassword(){
			int id, index;
			printCust();
			cout << "What user ID wants to change their password : ";
			cin >> id;
			index = findIndex(id);
			
			if (inputPassword(id)){
			customer[index].pass = makePassword();
			}
		}
		
		//process for making a valid password
		string makePassword(){
				string password;
				int length;
				bool acceptable = false;
				bool upper = false;
				bool lower = false;
				bool digit = false;
				bool symbol = false;
				do{
					system("cls");
					cout << "The requirements for a valid password are as follows:" << endl
						 << "1. Must be at least 6 characters" << endl 
						 << "2. Must have at least one uppercase letter" << endl 
						 << "3. Must have at least one lowercase letter" << endl
						 << "4. Must have at least one digit" << endl
						 << "5. Must have at least one symbol" << endl << endl;
					
					upper = false;
					lower = false;
					digit = false;
					symbol = false;
					
					cout << "Enter a password.\n";
					getline(cin, password);
					length = password.length();
					if(length<6){
					cout<<"Error! Your password must be at least 6 characters\n";
					}
					
					for(int i = 0; i < length; i++){
						if(isupper(password[i])){
						upper=true;
						}
						
						if(islower(password[i])){
						lower=true;
						}
						
						if(isdigit(password[i])){
						digit=true;
						}
						
						if(ispunct(password[i])){
						symbol=true;
						}
					}
					if(upper and lower and digit and symbol){
					acceptable=true;
					}
					else{
						if (!upper)
							cout << "Your password is missing a uppercase letter" << endl;
						if (!lower)
							cout << "Your password is missing a lowercase letter" << endl;
						if (!digit)
							cout << "Your password is missing a digit " << endl;
						if (!symbol)
							cout << "Your password is missing a symbol " << endl;	
						system("pause");
					}
				}while(acceptable==false);
				cout<<"Your password is acceptable.\n";

				return password;
		}
		
		//Used whenevr password verification is needed
		bool inputPassword(int id){
			int index = findIndex(id);
			int tries = 3;
			string pass;
			do{
				cout << "To perform this action you need " << customer[index].first << "'s password : ";
				cin >> pass;
				if (pass == customer[index].pass){
					return 1;
				}
				else{
					tries -= 1;
					if (tries > 0)
					cout << tries << " tries remaining until forced shutdown" << endl << endl;
					}
			}while (pass != customer[index].pass and tries != 0 );
			if (tries == 0){
				cout << "Now terminating connection";
				rest(4);
				cout << endl << endl << "Goodbye...";
				return 0;}
				
		}
		
		//Removes customers
		void removeCust(string file){
			int id, index;
			printCust();
			cout << endl << endl << "Which customer ID would you like to remove? : ";
			cin >> id;
			index = findIndex(id);
			
			if (inputPassword(id)){
				
				
				ofstream myfile ("tempdata");
	  			if (myfile.is_open()){
	  				
	  				rest(1);
	    			myfile << hmCustomer - 1 << " ";
				
						for ( int i = 0; i < hmCustomer; i ++ ){
							if ( customer[i].ID != id){
								myfile << customer[i].ID  << " "
								<< customer[i].first << " "
								<< customer[i].last  << " "
								<< customer[i].birthMonth << " "
								<< customer[i].birthDay << " "
								<< customer[i].birthYear << " "
								<< customer[i].hmMovies << " ";
								
								for ( int j = 0; j < customer[i].hmMovies; j ++ ){
									//Replace spaces in the movie name with underscores
									for ( int k = 0; k < customer[i].movies[j].length(); k ++){
										if ( customer[i].movies[j][k] == ' ')
											customer[i].movies[j][k] = '_';
									}
														
									myfile << customer[i].movies[j] << " ";
								}					  	}
						}
	  				}
	  	
	  			else cout << "Unable to open file";
	  				return;
	  				
	  			hmCustomer -= 1;
	  			rest(2);
	  			saveCust(file);
			}
		}
		
		//Sorts customers by name
		void sortCust(string sortType){
			person temp;
			bool done;
			if (sortType == "first"){ //Sorts by first name
				system("cls");
				cout << "The array has been sorted by First Name A->Z" << endl;
				do{
					//Assume the array is sorted
					done = true;
					
					for( int i = 0; i < hmCustomer - 1; i ++ ){
						if ( customer[i].first > customer[i+1].first ){
							//If we find two customers out of order... we ain't sorted yet
							done = false;
							
							temp = customer[i];
							customer[i] = customer[i+1];
							customer[i+1] = temp;
						}
					}
				}while( !done );//So keep going
			}
			
			if (sortType == "last"){ //Sorts by last name
				system("cls");
				cout << "The array has been sorted by Last Name A->Z" << endl;
				do{
					//Assume the array is sorted
					done = true;
					
					for( int i = 0; i < hmCustomer - 1; i ++ ){
						if ( customer[i].last > customer[i+1].last ){
							//If we find two customers out of order... we ain't sorted yet
							done = false;
							
							temp = customer[i];
							customer[i] = customer[i+1];
							customer[i+1] = temp;
						}
					}
				}while( !done );
			}
							
			if (sortType == "id"){ //Sorts by id
				system("cls");
				cout << "The array has been sorted by ID Low->Hi" << endl;
					do{
						//Assume the array is sorted
						done = true;
						
						for( int i = 0; i < hmCustomer - 1; i ++ ){
							if ( customer[i].ID > customer[i+1].ID ){
								//If we find two customers out of order... we ain't sorted yet
								done = false;
								
								temp = customer[i];
								customer[i] = customer[i+1];
								customer[i+1] = temp;
							}
						}
					}while( !done );//So keep going
				}
				
			if (sortType == "age"){ //Sorts by age
				system("cls");
				cout << "The array has been sorted by Age Oldest->Youngest" << endl;
				do{
					//Assume the array is sorted
					done = true;
					
					for( int i = 0; i < hmCustomer - 1; i ++ ){
						if( customer[i].birthYear > customer[i+1].birthYear ){
								done = false;
								temp = customer[i];
								customer[i] = customer[i+1];
								customer[i+1] = temp;
								}
								
						if( customer[i].birthYear == customer[i+1].birthYear and customer[i].birthMonth > customer[i+1].birthMonth  ){
								done = false;
								temp = customer[i];
								customer[i] = customer[i+1];
								customer[i+1] = temp;
								}
						if( customer[i].birthMonth == customer[i+1].birthMonth and customer[i].birthDay > customer[i+1].birthDay ){
								done = false;
								temp = customer[i];
								customer[i] = customer[i+1];
								customer[i+1] = temp;
								}
						}
				}while( !done );//So keep going
			}
				
			if (sortType == "movies"){ //Sorts by ammount of movies
				system("cls");
				cout << "The array has been sorted by the Ammount of Movies in Posession Hi->Low" << endl;
					do{
						//Assume the array is sorted
						done = true;
						
						for( int i = 0; i < hmCustomer - 1; i ++ ){
							if ( customer[i].hmMovies < customer[i+1].hmMovies){
								//If we find two customers out of order... we ain't sorted yet
								done = false;
								
								temp = customer[i];
								customer[i] = customer[i+1];
								customer[i+1] = temp;
							}
						}
					}while( !done );//So keep going
				}	
		}
		
		//This will save our entire customer object to the file
		void saveCust(string filename){
			ofstream myfile (filename.c_str());
  			if (myfile.is_open()){
    			myfile << hmCustomer << " ";
			
					for ( int i = 0; i < hmCustomer; i ++ ){
						myfile << customer[i].ID  << " "
						<< customer[i].first << " "
						<< customer[i].last  << " "
						<< customer[i].birthMonth << " "
						<< customer[i].birthDay << " "
						<< customer[i].birthYear << " "
						<< customer[i].pass << " "
						<< customer[i].hmMovies << " ";
						
						
						for ( int j = 0; j < customer[i].hmMovies; j ++ ){
							//Replace spaces in the movie name with underscores
							for ( int k = 0; k < customer[i].movies[j].length(); k ++){
								if ( customer[i].movies[j][k] == ' ')
									customer[i].movies[j][k] = '_';
							}
												
							myfile << customer[i].movies[j] << " ";
						}
					}
    			myfile.close();
  				}
  			else cout << "Unable to open file";
  				return;
	}
		
		void loadCust(string filename){
			ifstream myfile ( filename.c_str() );
			if (myfile.is_open()){
				myfile >> hmCustomer;
			      for ( int i = 0; i < hmCustomer; i ++ ){
						myfile >> customer[i].ID
								 >> customer[i].first 
								 >> customer[i].last
								 >> customer[i].birthMonth
								 >> customer[i].birthDay  
								 >> customer[i].birthYear
								 >> customer[i].pass 
								 >> customer[i].hmMovies;
						 
						for( int j = 0; j < customer[i].hmMovies; j ++ ){
							myfile >> customer[i].movies[j];
					
							//Put the spaces back
							for ( int k = 0; k < customer[i].movies[j].length(); k ++){
								if ( customer[i].movies[j][k] == '_')
									customer[i].movies[j][k] = ' ';
							}		
						}		
					}
			    }
			else cout << "Unable to open file"; 
				return;
				
			printCust();
			cout << endl << endl << filename << " has been opened" << endl;
			system("pause");
		}
		
		//Prints out the customers with their information
		void printCust(){
			int choice;
			cout << endl
				 << " ID     First      Last   Age  Movies" << endl
				 << "-----------------------------------------"<< endl;
			
			//Cycle through the customers	 
			for ( int i = 0; i < hmCustomer; i ++ ){
				//Output their name and information
				cout << setw(3) << right << customer[i].ID
					 << setw(10) << customer[i].first
					 << setw(10) << customer[i].last
					 << setw(6) << 2020 - customer[i].birthYear
					 << setw(5) <<customer[i].hmMovies;
				
				//And their rented movies
				for ( int j = 0; j < customer[i].hmMovies; j ++ ){
					cout << "     " << left << "'" << customer[i].movies[j]<< "'";
				}
				cout << endl << endl;
			}
			
					
		}
		
		void moreInfo(){
			int choice;
			cout << "For more in depth data type the user id, to go back type 0 : ";
			cin >> choice;
			if ( choice != 0){
				if (inputPassword(choice)){
					choice = findIndex(choice);
					system("cls");
					cout << endl
					 << " ID     First      Last   Age    Birthday        Password      Movies" << endl
					 << "-----------------------------------------------------------------------"<< endl
					 << setw(3) << right << customer[choice].ID
					 << setw(10) << customer[choice].first
					 << setw(10) << customer[choice].last
					 << setw(6) << 2020 - customer[choice].birthYear
	 				 << setw(4) << customer[choice].birthMonth << "/" << customer[choice].birthDay << "/" << customer[choice].birthYear
	 				 << setw(16) << customer[choice].pass
					 << setw(7) << customer[choice].hmMovies;
					 
					 for ( int j = 0; j < customer[choice].hmMovies; j ++ ){
						cout << "     " << left << "'" << customer[choice].movies[j]<< "'";
					}
					cout << endl << endl;
				}
			}
	}
		
		//Rents movies to the customer
		void rentMovie(){
			int which;
			string movie;
			
			//Print out the customers so the user can choose one	
			printCust();
			
			//Let the user choose one
			cout << "Which customer ID would like to rent? : ";
			cin >> which;
			
			if (inputPassword(which)){
				which = findIndex(which);
				
				//Enter movies until done
				cin.ignore();//so the endline from the last cin doesn't get read as the first movie
				cout << "Enter some movies, enter stop when done" << endl;
				do{
					getline(cin,movie);
					customer[which].movies[customer[which].hmMovies] = movie;
					customer[which].hmMovies ++;
				}while(movie != "stop");
			 	
			 	customer[which].hmMovies --;
			}
		}
		
		
		void returnMovie(){
			int which;
			
			printCust();
			
			cout << "Which customer ID is returning their movies? : ";
			cin >> which;
			if (inputPassword(which)){
				which = findIndex(which);
				
				customer[which].hmMovies = 0;	
			}
		}
		
	private:
		//Maybe add a name
		person customer[100];
		int hmCustomer;	
};

int main(){
	string AdminPass = "LetMeIn"; // This is the password required at the begining (Feel free to change it)
	bool Auto = false; // Set this to true for any changes you make to automatticaly save and or sort the array
	bool StartLoad = true; //
	string AutoLocation = "Pepe_StoreData"; //change this if you want a diffrent filename to be autosaved/loaded
	store BBuster;
	int choice;
	string file;
	string type;
	int tries = 3;
	system("color E1");
	
	
	
	string pass1;
	
	do{
	cout << "Please enter the Admin Password... : "; 
	cin >> pass1;
	if (pass1 == AdminPass){
		tries = 3;
		pass1 = " ";
		if (StartLoad){
		BBuster.loadCust(AutoLocation);
		}
		do{
			system("cls");
			cout << "Movie Menu" << endl
				 << "1 - Add a customer" << endl
				 << "2 - Remove a customer" << endl
				 << "3 - Sort customers" << endl
				 << "4 - Print customers" << endl
				 << "5 - Rent movies" << endl
				 << "6 - Return movies" << endl
				 << "7 - Change Password" << endl
				 << "8 - Save" << endl
				 << "9 - Load" << endl
				 << "0 - Quit" << endl << endl
				 << "Your choice : ";
				 
			cin >> choice;
			
			switch ( choice ){
				case 1:
					BBuster.newCust();
					
					if (Auto){
						BBuster.sortCust("id");
						BBuster.saveCust(AutoLocation);
					}	
					break;
					
				case 2:
					file = "tempdata";
					BBuster.removeCust(file);
					BBuster.loadCust(file);			  			
	
					
					if (Auto){
						BBuster.sortCust("id");
						BBuster.saveCust(AutoLocation);
					}	
					break;
					
				case 3:
					cout << "How do you want to sort (First, Last, ID, age, Movies) : ";
					cin >> type;
					cap(type, 2, true);
					BBuster.sortCust(type);
					BBuster.printCust();
					system("pause");
	
					break;
					
				case 4:
					BBuster.printCust();
					BBuster.moreInfo();
					system("pause");
					break;
					
				case 5:
					BBuster.rentMovie();
					
					if (Auto){
						BBuster.saveCust(AutoLocation);
					}
					break;
					
				case 6:
					BBuster.returnMovie();
					
					if (Auto){
						BBuster.saveCust(AutoLocation);
					}
					
					break;
					
				case 7:
					BBuster.changePassword();
					if (Auto){
						BBuster.saveCust(AutoLocation);
					}
					break;
				case 8:
					cout << "What file name would you like to save this as? : ";
					cin >> file;
					BBuster.saveCust(file);
					break;
					
				case 9:
					cout << "What file would you like to open? : ";
					cin >> file;
					BBuster.loadCust(file);
					break;
			}
			
		}while( choice != 0 );
		cout << "Now logging out" ;
		rest(6);
		system("cls");
	}
else{
	tries -= 1;
	if (tries > 0)
	cout << tries << " tries remaining until forced shutdown" << endl << endl;
	
	else{
		cout << "Now terminating connection";
		rest(4);
		cout << endl << endl << "Goodbye...";}
}
}while(pass1 != AdminPass and tries != 0);
	
	cout << endl << endl;
	system("pause");
	return 1;
}
