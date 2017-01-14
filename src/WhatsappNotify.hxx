
 
 #ifndef _WhatsappNotify_
 #define _WhatsappNotify_

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>
 
using namespace std;

class WhatsappNotify : public Notification{
		public:
			WhatsappNotify(){}
		
		virtual void notify(string userName, string account,string track, string artist){
			stringstream stream;
			stream << "[SingAlong] new track "<< track<< " by "<< artist;
			WhatsappStub::theInstance().sendWhatsapp(account,stream.str());
		}
};
#endif