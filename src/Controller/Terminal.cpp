#include "Terminal.h"
#include "Controller.h"
#include "Boat.h"
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
            	/*
            	 *
            	 * TODO: raise exception for invalid argument here !
            	 *
            	 */
            }
            if( second_word == "course" )	{
                s >> deg >> speed;
                b.lock()->setCourse(deg);      ///add order to queue
            }
            else if( second_word == "position" )	{

                s >> x >> y >> speed;
                ///add order to queue
                b.lock()->setDestLocation(Location(x,y));
                b.lock()->setSpeed(speed); //TODO: Boat interface does not exist !!
            }
            else if( second_word == "destination" )	{
                string dest_port_name;
                double speed;
                s >> dest_port_name;
                if( s.fail() )	{
                	/*
                	 *
                	 * TODO: handle exceptions here !
                	 *
                	 */
                }
                s >> speed;
                if( s.fail() )	{
					/*
					 *
					 * TODO: handle exceptions here !
					 *
					 */
                }
                if(!Model::getInstance()->isPortExist(dest_port_name))	{
                	/*
                	 *
                	 * TODO: handle exceptions here !
                	 *
                	 */
                    cerr << "Destination does not exist. try again. "<<endl;
                    break;
                }

                ///add order to queue, check if destination is load/un_load
                b.lock()->setDestLocation(Model::getInstance()->getPort(dest_port_name).lock().get()->get_Location());
            }
            else if(second_word == "load_at")	{
                string port_name;
                s >> port_name;
                if(!Model::getInstance()->isPortExist(port_name))	{
                	/*
                	 *
                	 * TODO: handle exceptions here !
                	 *
                	 */
                    cerr << "Port does not exist. try again. "<<endl;
                    break;
                }

                ///add port to vector
                b.lock()->setDestLocation(Model::getInstance()->getPort(dest_port_name).lock()->get_Location());

            }
            else if(second_word == "unload_at"){
                string port_name;
                int containers;
                s >> port_name;
                if( s.fail() )	{
                	/*
                	 *
                	 * TODO: handle exceptions here !
                	 *
                	 *
                	 */
                }
                s >> containers;
                if( s.fail() )	{
					/*
					 *
					 * TODO: handle exceptions here !
					 *
					 *
					 */
                }
                if(!Model::getInstance()->isPortExist(port_name))	{
                	/*
                	 *
                	 * TODO: handle exceptions here !
                	 *
                	 *
                	 */
                    cerr << "Port does not exist. try again. "<<endl;
                    break;
                }

                ///add port to vector
                b.lock()->setDestLocation(Model::getInstance()->getPort(dest_port_name).lock()->get_Location());

            }
            else if( second_word == "dock_at" )	{
                string dock_port;
                s >> dock_port;
                if( s.fail() )	{
                	/*
                	 *
                	 *
                	 * TODO: handle exceptions here !
                	 *
                	 *
                	 */

                }
                if(!Model::getInstance()->isPortExist(dock_port))	{
                	/*
                	 *
                	 *
                	 * TODO: handle exceptions here !
                	 *
                	 *
                	 */
                    cerr << "Port does not exist. try again. "<<endl;
                    break;
                }
                ///add order to queue
                b.lock()->setDock(Model::getInstance()->getPort(dest_port_name)); // TODO: Boat interface does not exist !!
            }
            else if(second_word == "attack"){
                string attack_port;
                s >> attack_port;
                if(!Model::getInstance()->isBoatExist(attack_port))	{
                	/*
                	 *
                	 * TODO: handle exceptions here !
                	 *
                	 *
                	 */
                    cerr << "Boat does not exist. try again. "<<endl;
                    break;
                }
                ///add order to queue
            }
            else if( second_word == "refuel" )	{
                ///add order to queue
            }
            else if(second_word == "stop")	{
                ///add order to queue
            }

            else	{
            	/*
            	 *
            	 *
            	 * TODO: handle exceptions here !
            	 *
            	 *
            	 */
            }
            continue;
        }

        else if( first_word == "default" )	{ view._default(); continue; }
        else if(first_word == "size")	{
            int arg1;
            s >> arg1;
            if( s.fail() )	{
            	/*
            	 *
            	 * TODO: handle exceptions here !
            	 *
            	 */
            }
            view.size(arg1);
            continue;
        }
        else if( first_word == "zoom" )	{
            double arg1;
            s >> arg1;
            if( s.fail() )	{
				/*
				 *
				 * TODO: handle exceptions here !
				 *
				 */
            }
            view.zoom(arg1);
            continue;
        }
        else if(first_word == "pan")	{
            double x,y;
            s >> x >> y;
            if( s.fail() )	{
				/*
				 *
				 * TODO: handle exceptions here !
				 *
				 */
            }
            view.pan(x,y);
            continue;
        }
        else if( first_word == "show" )	{ view.show(); continue; }
        else	{
        	/*
        	 *
        	 * TODO: handle exceptions here !
        	 *
        	 */
        }
    }
}
/*********************************************/
