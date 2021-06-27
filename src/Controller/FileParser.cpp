#include "FileParser.h"
#include "../Model/Port.h"
#include "../Model/Model.h"
/*********************************/
FileParser::FileParser(const char * filename)	{

		std::fstream ports_file(filename);

		if( !ports_file )	{ throw FileOpenException(); }

		// port generating tools
		double x, y;
		int line = 0;
		string extract;
		string port_name;
		Location port_loc;
		int fuel_start_cap;
		int fuel_generate_per_hr;

		// parsing tools
		string line_buffer;
		stringstream parser;
		stringstream sub_parser;

		// initially add port Nagoya by default (default c'tor generates this port).
		Model::getInstance().get()->getAllPorts().push_back(make_shared<Port>(new Port()));

		while( getline(ports_file,line_buffer) )	{

			parser.clear();
			sub_parser.clear();
			parser << line_buffer;
			if( parser.fail() )	{ throw InvalidContentException(line); }

			// extract port's name
			parser >> port_name;
			if( port_name.length() > 12 )	{ throw InvalidContentException(line); }

			// extract port's location
			getline(parser,extract,'(');
			getline(parser,extract,',');
			sub_parser << extract;
			sub_parser >> x;
			getline(parser,extract,')');
			sub_parser << extract;
			sub_parser >> y;
			port_loc = Location(x,y);

			// extract port's starting fuel capacity ( cannot be negative )
			parser >> fuel_start_cap;
			if( fuel_start_cap < 0 )	{ throw InvalidContentException(line); }

			// extract port's fuel generating capacity per hr ( cannot be negative )
			parser >> fuel_generate_per_hr;
			if( fuel_generate_per_hr < 0 )	{ throw InvalidContentException(line); }

			// initialize a new port by given arguments and add it to model's database.
			Model::getInstance().get()->getAllPorts().push_back(make_shared<Port>(new Port(fuel_start_cap, fuel_generate_per_hr, port_name, port_loc)));

			++line;
	}
}
