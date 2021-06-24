#ifndef CONTROLLER_FILEPARSER_H_
#define CONTROLLER_FILEPARSER_H_

#include <exception>
#include <sstream>
#include <string>

using namespace std;
/*********************************/
class Port;
/*********************************/
class FileParser	{ // This class object is responsible for generating all simulation's ports according to
					  // given file's data. it will throw an exception if the file didn't open successfully / an invalid
					  // content was detected.
public:
	/* excpetions*/
	class InvalidContentException : public exception	{
		int line;
	public:
		InvalidContentException(int line):line(line)	{}
		const char * what() const noexcept	{
			stringstream s;
			s << line;
			string line_str = s.str();
			return string("ERROR: invalid content given at line "  + line_str).c_str();
		}
	};

	class FileOpenException : public exception	{
		public : const char * what() const noexcept	{
			return "ERROR: given file won't open.";
		}
	};

	/*c'tors & d'tors*/
	FileParser(const char * filename);
	~FileParser()	 {}
};
/*********************************/
#endif
