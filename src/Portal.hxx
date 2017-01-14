
 #ifndef _PORTAL_
 #define _PORTAL_

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>

 //#include "Object.hxx"
 
using namespace std;

class Portal {
		public:
			Portal(string name, string description){
				_name = name;
				_description = description;
			}

			~Portal(){}
		
			string getName(void){
				return _name;
			}

			string getDescription(void){
				return _description;
			}	

			void setRSS(void){
				stringstream stream;

				stream << "<?xml version='1.0' encoding='ISO-8859-15'?>\n";
				stream << "<!DOCTYPE rss PUBLIC '-//Netscape Communications//DTD RSS 0.91//EN'\n";
				stream << "'http://my.netscape.com/publish/formats/rss-0.91.dtd'>\n";
				stream << "<rss version='0.91'>\n";
				stream << "<channel>\n";
				stream << "<title>SingAlong: Headbangers</title>\n";
				stream << "<link>http://www.singalong.com/Headbangers</link>\n";
				stream << "<description>A portal for heavy metal fans</description>\n";
				stream << "</channel>\n";
				stream << "</rss>\n";

				_rss = stream.str();
			}

			string getRSS(void){
				return _rss;
			}

	private:
		string _name;
		string _description;
		string _rss;
};

#endif