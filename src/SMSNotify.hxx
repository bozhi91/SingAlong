
 #ifndef _SMSNotify_
 #define _SMSNotify_

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>
 
using namespace std;

class SMSNotify : public Notification{
		public:
			SMSNotify(){}
		
		virtual void notify(string userName, string account,string track, string artist){
			stringstream stream;
			stream << "[SingAlong] new track "<< track<< " by "<< artist;
			SmsStub::theInstance().sendSms(account,stream.str());
		}
};
#endif