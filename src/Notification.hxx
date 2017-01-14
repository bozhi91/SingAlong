
 #ifndef _NOTIFICATION_
 #define _NOTIFICATION_

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>
 
using namespace std;

class Notification {
		public:
			Notification(){}
		
		virtual void notify(string userName, string account,string track, string artist){
			cout << "If you see this, something went wrong!!! You can't call this method!!\n";
		}
};
#endif