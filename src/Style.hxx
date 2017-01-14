
 #ifndef _STYLE_
 #define _STYLE_

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>
#include "User.hxx"
#include "Subject.hxx"
#include "Portal.hxx"

using namespace std;

class Style : public Subject {
		public:
			//A custom Constructor
			Style(std::string styleName){
				_name  = styleName;				
			}
			
			//Destructor
			~Style(){}

			std::string getStyleName(void){
				return _name;
			}

			void addUser(User* user){				
				_users.push_back(user);
				Observer* obs;
				obs = user;
				addObserver(obs);
			}
			
			std::vector<User*> getUsers(){
				return _users;
			}
			
			//Call the method notify from the class Subject
			void notify(void){
				notifyAll("A track","An artist");
			}

			
			void addPortal(Portal* portal){				
				_portals.push_back(portal);
			}
			
			std::vector<Portal*> getPortals(){
				return _portals;
			}
		
	private:
		std::string _name;
		std::vector<User*> _users;
		vector<Portal*> _portals;
};

#endif