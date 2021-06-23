
#include "Terminal.h"



void Terminal::run(){
    while(true){
        string command, first_word;
        cout<< "Time "<<Time<<": Enter Command: ";
        getline(cin,command);
        stringstream s(command);
        s >> first_word;
        if(first_word=="exit"){exit(0);}
        else if(first_word=="status") Model::getInstance().status();
        else if(first_word=="go") Model::getInstance().go();
        else if(first_word=="create"){
            ///****5 args required
            Model::getInstance().create();
        }
        else if(Model::getInstance().isBoatExist(first_word)){
            //case of first word is an exist boat command
            string boat_name = first_word;
            weak_ptr<Boat> b = Model::getInstance().getBoat(boat_name);
            string second_word;
            s >> second_word;
            if(second_word=="course"){
                double deg, speed;
                s >> deg >> speed;
                b.lock()->setCourse(deg);      ///add order to queue
            }
            else if(second_word=="position"){
                double x,y, speed;
                s >> x >> y >> speed;
                ///add order to queue
                b.lock()->setDestLocation(Location(x,y));
                b.lock()->setSpeed(speed);
            }
            else if(second_word=="destination"){
                string dest_port_name;
                double speed;
                s >> dest_port_name;
                s >> speed;
                if(!Model::getInstance().isPortExist(dest_port_name)){
                    cerr << "Destination does not exist. try again. "<<endl;
                    break;
                }
                ///add order to queue, check if destination is load/un_load
                b.lock()->setDestLocation(Model::getInstance().getPort(dest_port_name).get_Location());
            }
            else if(second_word=="load_at"){
                string port_name;
                s >> port_name;
                if(!Model::getInstance().isPortExist(port_name)){
                    cerr << "Port does not exist. try again. "<<endl;
                    break;
                }
                ///add port to vector
                b.lock()->setDestLocation(Model::getInstance().getPort(dest_port_name).get_Location());


            }
            else if(second_word=="unload_at"){
                string port_name;
                int containers;
                s >> port_name;
                s >> containers;
                if(!Model::getInstance().isPortExist(port_name)){
                    cerr << "Port does not exist. try again. "<<endl;
                    break;
                }
                ///add struct port to vector
                b.lock()->setDestLocation(Model::getInstance().getPort(dest_port_name).get_Location());

            }
            else if(second_word=="dock_at"){
                string dock_port;
                s >> dock_port;
                if(!Model::getInstance().isPortExist(dock_port)){
                    cerr << "Port does not exist. try again. "<<endl;
                    break;
                }
                ///add order to queue
                b.lock()->setDock(Model::getInstance().getPort(dest_port_name));
            }
            else if(second_word=="attack"){
                string attack_port;
                s >> attack_port;
                if(!Model::getInstance().isBoatExist(attack_port)){
                    cerr << "Boat does not exist. try again. "<<endl;
                    break;
                }
                ///add order to queue
            }
            else if(second_word=="refuel"){
                ///add order to queue
            }
            else if(second_word=="stop"){
                ///add order to queue
            }
        }
        else if(first_word=="default")view.Default();
        else if(first_word=="size"){
            int arg1;
            s >> arg1;
            view.size(arg1);
        }
        else if(first_word=="zoom"){
            double arg1;
            s >> arg1;
            view.zoom(arg1);
        }
        else if(first_word=="pan"){
            double x,y;
            s >> x >> y;
            view.pan(x,y);
        }
        else if(first_word=="show")view.show();
        else{cerr << "Illegal Command . try again .";}
    }
}