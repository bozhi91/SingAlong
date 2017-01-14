
#ifndef _SUBJECT_
#define _SUBJECT_

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>

#include "Observer.hxx"

using namespace std;

class Subject{

protected:
    std::vector< Observer* > _observers;

public:
    void addObserver( Observer * observer ){
        _observers.push_back( observer );
    }

    //I can't get the iterator working. Will fix it later!!!
    void notifyAll( const std::string & track, const std::string & artist ) {
       /*for ( Observer::const_iterator it = _observers.begin(); it != _observers.end(); ++it ){
            (*it)->update( track, artist );
        }*/
        unsigned int i;
        for(i = 0; i<_observers.size();i++){
        	_observers.at(i)->update(track,artist);
        }
    }
};

#endif