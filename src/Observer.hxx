
 
 #ifndef _observer_
 #define _observer_

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>

using namespace std;

class Subject;
class Observer{
	public:
		virtual void update(const std::string & track, const std::string & artist ) = 0;
	private:
};
#endif