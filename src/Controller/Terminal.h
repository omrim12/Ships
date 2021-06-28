#include <exception>
#include <string>
#include "../View/View.h"
/*****************************/
class Terminal	 {
    static int Time;
    View view;
public:
    /*exceptions*/
    class InvalidInputException : public exception	{
        string msg;
    	public:
        	InvalidInputException(string msg):msg(msg)	{}
        	virtual const char *what() const noexcept	{return string("ERROR: invalid input : " + msg).c_str();}
    };

    /*c'tors & d'tors*/
    Terminal() {Time = 0;}
    ~Terminal()	{}

    /*class functions*/
    void run();
};
/*****************************/
