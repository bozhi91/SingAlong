

 #ifndef _USER_
 #define _USER_

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>

#include "externalLibs/MailStub.hxx"
#include "Observer.hxx"

#include "Notification.hxx"
#include "MailNotify.hxx"
#include "SMSNotify.hxx"
#include "WhatsappNotify.hxx"

#include "Observer.hxx"

using namespace std;

class User : public Observer{

		public:
			//A custom Constructor  
			User(std::string name,std::string email){
				_name  = name;
				_email = email;	
				notification = &mailNotify;	
				_userAccount = 	email;		
			}

			///Default constructor
			User(){
				_name  = "nameless User";
				_email = "user@server.com";	
				notification = &mailNotify;		
				_userAccount = 	"user@server.com";		
			}

			//Destructor
			virtual ~User(){}

			void setName(std::string name){
				_name = name; 
			}

			void setEmail(std::string email){
				_email = email; 
			}

			std::string getName(void){
				return _name;
			}
		
			std::string getEmail(void){
				return _email;
			}

			//This method is called from SingAlong from the method: userPrefersSms() or userPrefersEmail(), etc.
			//The userAccount could be the phone number in case of SMS or whatsapp notification, 
			//or an e-mail address in case of email notification.
			void setNotificationType(string type,string userAccount){
				if(type == "mail"){
					notification = &mailNotify;	
				}
				else if(type == "sms"){
					notification = &smsNotify;	
				}	
				else if(type == "whatsapp"){
					notification = &whatsappNotify;
				}
				else{
					cout << "\n\n\t Unknown notification type: [ "<<type<<" ]\n\n";
				}
				_userAccount = userAccount;
			}
			//By default, we send a mail notification. The notification type is set in the constructor
			void update(const std::string & track, const std::string & artist ){
				notification->notify(_name, _userAccount,track,artist);
			}

		private:
			std::string _name;
			std::string _email;
			std::string _userAccount;

			Notification *notification;
			MailNotify mailNotify;
			SMSNotify smsNotify;
			WhatsappNotify whatsappNotify;
};

#endif