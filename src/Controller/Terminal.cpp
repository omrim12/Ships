#include "Terminal.h"
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include "../Model/Boat.h"
#include "../Model/Model.h"
#include "../Model/Port.h"
/*********************************************/
void Terminal::run()	{

	string command;
	string first_word, second_word;
	string dest_port_name;
	stringstream s;
	double deg, speed, x ,y;
	int res_pow,cap_range;
	bool exit_stat = false;
	string boat_name, boat_type, str_x, str_y;

	while( !exit_stat )	{

		try	{

			cout<< "Time " << Time << ": Enter Command: ";

			// get command line
			cin.clear();
			s.clear();
			getline(cin,command);
			s.str(command);

			s >> first_word;

			if(first_word=="exit")	{ exit_stat = true; continue; }
			else if(first_word=="status")	{ Model::getInstance()->status(); continue; }
			else if(first_word=="go")	{ Model::getInstance()->go(); continue; }
			else if(first_word=="create")	{

				s >> boat_name >> boat_type >> str_x >> str_y;
				s >> res_pow;

				//one more argument:
				//*in case of freighter boat -> capacity of possible containers
				//*in case of cruiser boat -> attack range
				if(s.tellg() != -1) s >> cap_range;
				else cap_range = 0;

				str_x = str_x.substr(1,5);
				str_y = str_y.substr(0,5);
				x = stod(str_x);
				y = stod(str_y);
				Model::getInstance()->create(boat_name, boat_type, x, y, res_pow, cap_range);
				continue;
			}

			// case of first word is a name of an existing boat
			else if(Model::getInstance()->isBoatExist(first_word))	{
				boat_name = first_word;
				weak_ptr<Boat> b = Model::getInstance()->getBoat(boat_name);
				s >> second_word;
				if( s.fail() )	{
					throw( InvalidInputException("illegal command.") );
				}
				if( second_word == "course" )	{
					s >> deg >> speed;
					b.lock()->addOrder(second_word,deg);      //add order to queue
					continue;
				}
				else if( second_word == "position" )	{
					s >> x >> y >> speed;
					//add order to queue
					b.lock()->addOrder(second_word,speed,x,y);
					continue;
				}
				else if( second_word == "destination" )	{
					string dest_port_name;
					double speed;
					s >> dest_port_name;
					if( s.fail() )	{ throw( InvalidInputException("boat's destination port is missing.") ); }
					s >> speed;
					if( s.fail() )	{
						throw( InvalidInputException("boat's speed is missing.") );
					}
					if(!Model::getInstance()->isPortExist(dest_port_name))	{
						throw( InvalidInputException("given destination port does not exist.") );
					}

					b.lock()->addOrder(second_word,0,0,0,0,Model::getInstance()->getPort(dest_port_name));
					continue;
				}
				else if(second_word == "load_at")	{
					string port_name;
					s >> port_name;
					if(!Model::getInstance()->isPortExist(port_name))	{
						throw( InvalidInputException("given port does not exist.") );
					}

					//add port to load destination list
					b.lock()->add_load_dest(Model::getInstance()->getPort(port_name));
					continue;
				}
				else if(second_word == "unload_at"){
					string port_name;
					int containers;
					s >> port_name;
					if( s.fail() )	{
						throw( InvalidInputException("port name is missing."));
					}
					s >> containers;
					if( s.fail() )	{
						throw( InvalidInputException("number of containers to unload is missing.") );
					}
					if(!Model::getInstance()->isPortExist(port_name))	{
						throw( InvalidInputException("Port does not exist.") );
					}

					//add port to unload destination list
					b.lock()->add_unload_dest(Model::getInstance()->getPort(port_name),containers);
					continue;
				}
				else if( second_word == "dock_at" )	{
					string dock_port;
					s >> dock_port;
					if( s.fail() )	{
						throw( InvalidInputException("port name is missing.") );
					}
					if(!Model::getInstance()->isPortExist(dock_port))	{
						throw( InvalidInputException("given port does not exist.") );
					}
					//add order to queue
					b.lock()->addOrder(second_word,0,0,0,0,Model::getInstance()->getPort(dock_port));
					continue;
				}
				else if(second_word == "attack")	{
					string attack_port;
					s >> attack_port;
					if(!Model::getInstance()->isBoatExist(attack_port))	{
						throw( InvalidInputException("given port does not exist.") );
					}
					//add order to queue
					b.lock()->addOrder(second_word,0,0,0,0,Model::getInstance()->getPort(attack_port));
					continue;
				}
				else if( second_word == "refuel" )	{
					b.lock()->setAskForFuel(true);
					continue;
				}
				else if(second_word == "stop")	{
					//add order to queue
					b.lock()->addOrder(second_word);
					continue;
				}

				else	{
					throw( InvalidInputException("command is illegal.") );
				}

			}

			else if( first_word == "default" )	{ view._default(); continue; }
			else if(first_word == "size")	{
				int arg1;
				s >> arg1;
				if( s.fail() )	{
					throw( InvalidInputException("size argument is missing.") );
				}

				view.size(arg1);
				continue;
			}
			else if( first_word == "zoom" )	{
				double arg1;
				s >> arg1;
				if( s.fail() )	{
					throw( InvalidInputException("zoom argument is missing.") );
				}
				view.zoom(arg1);
				continue;
			}
			else if(first_word == "pan")	{
				double x,y;
				s >> x >> y;
				if( s.fail() )	{
					throw( InvalidInputException("pan argument is missing") );
				}
				view.pan(x,y);
				continue;
			}
			else if( first_word == "show" )	{ view.show(); continue; }
			else	{
				throw( InvalidInputException("illegal command.") );
			}
		}
		catch( exception& e )	{ cerr << e.what() << endl; }
	}
}
/*********************************************/
