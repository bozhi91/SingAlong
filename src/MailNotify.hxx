
 #ifndef _MailNotify_
 #define _MailNotify_

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>
#include "Notification.hxx"
 
using namespace std;

class MailNotify : public Notification{
		public:
			MailNotify(){}
		
		virtual void notify(string userName, string account,string track, string artist){
			stringstream stream;
			stream << "new track "<< track<< " by "<< artist;
			MailStub::theInstance().sendMail(userName+" <"+account+">",stream.str());
		}
};
#endif