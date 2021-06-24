#include "../View/View.h"
/*****************************/
class Controller;
/*****************************/
class Terminal	 {
    static int Time;
    View view;
public:
    /*exceptions*/
    class InvalidInputException : public exception	{
        public:
        	virtual const char *what() const noexcept	{return "ERROR: invalid input inserted.";}
    };

    /*c'tors & d'tors*/
    Terminal() {Time = 0;}
    ~Terminal()	{}

    /*class functions*/
    void run();
};
/*****************************/
