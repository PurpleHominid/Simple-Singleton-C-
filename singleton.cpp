#include <iostream>


using namespace std;

//the singleton class typically defines the `GetInstance` method that serves as an
//'constructor' thereby letting 'clients' access the same instance of the class
//by doing this no matter which instance is accessed it always points back to the 'one' instance

//potentially considered perhaps an antipattern due to initial possible overused and its potential 
//to introduce unnecessary issues in situations where an entire instance of a class may not be required
//in addition it introduces a possible 'global state' into solution.

class singleton {
	private: //essentially, private means that only members of the same class are allowed to access
		//the singleton's constructor should always be private or protected to limit direct construction calls with the `new` operator.
		singleton(const std::string reference, const int value): 
			reference_(reference), //initialise the variable 'singleton::reference_' with the value passed as 'reference' 
			value_ (value) //initialise the variable 'singleton::value_' with the value passes as 'value'
			//the above code lines use an initialisation list, because 'const' must be initialised (once)
			//and is not owned by a specific instance we can use the method above to initialise the values
			//search 'initialisation list c++' for more info
			{
				//possible constructor code
				cout << "\nsingleton contructor code started";
			}

		static singleton* inst_; //a pointer to the 'one' cached (single) instance

	protected: //essentially, protected means that members of subclasses are also allowed
		std::string reference_;
		//mutable std::string reference_;
		int value_;
		int boardwidth_;
		int boardheight_;

	public: //essentially, public means everyone is allowed to access
		singleton(singleton &other) = delete; //execute a delete - singletons should not be cloneable.
    void operator=(const singleton &) = delete; //execute a delete - singletons should not be assignable.
   	~singleton() {} //destructor

		//define the static method to control access to the singleton instance 
		//initially, it will create a new singleton object and places it into the static field. 
		//on later calls, it simply returns the original object instance stored in the static field.
		static singleton *getInstance(const std::string &reference, const int &value);

		std::string businessLogic(std::string data) {
			//...
			return "doing something really useful: " + data;
		}

    std::string reference() const { //the const type after the function name is a "defensive" technique to help guard against programming errors; in this instance, you are stating that the function should not modify that parameter the 'const' causes the compiler to prevent you from doing so (unless they are marked mutable)
			//reference_ = "hello";
			return reference_;
    }
		int value() const{
			return value_;
		}

};


singleton* singleton::inst_= nullptr; //initialise the default state of the singleton

//static methods should generally be defined outside the class - this is because they are are not part of the individual class objects, 
//they are treated similarly to global variables and get initialized when the program starts meaning they should be explicitly defined 
//outside of the class (in the global scope)
singleton *singleton::getInstance(const std::string &reference, const int &value) {
	//this is a safer way to create an instance rather than instance = new singleton to help avoid 
	//issue related to potential multithreaded calls wanting access at the same time
	if(inst_== nullptr){
		inst_ = new singleton(reference, value); //no previous instance stored, create and store the original
	}
	return inst_; //return the stored instance
}


int main() {

	//create an multiple instances of the singleton; essentially each is an access point to the same class
	//this initial parameters being past are only utilised if the singleton has not been instantiated, else
	//they are ignored
	singleton* instanceFoo = singleton::getInstance("foo", 101);
	singleton* instanceBar = singleton::getInstance("bar", 1001);


	std::cout << "\ninstanceFoo reference: " << instanceFoo->reference(); //use the arrow operator (->) to access members using pointers
	std::cout << "\ninstanceFoo value: " << instanceFoo->value(); //use the arrow operator (->) to access members using pointers

	std::cout << "\ninstanceBar reference: " << instanceBar->reference(); //use the arrow operator (->) to access members using pointers
	std::cout << "\ninstanceBar value: " << instanceBar->value(); //use the arrow operator (->) to access members using pointers

	std::cout << "\nbusiness logic: " << instanceBar->businessLogic("hello");


	std::cout << "\n";
	return 0;
}
