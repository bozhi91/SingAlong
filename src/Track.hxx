
 #ifndef _TRACK_
 #define _TRACK_

#include <iostream>
#include <string>
#include "Style.hxx"
#include "Subject.hxx"

using namespace std;

class Track : public Subject{
		public:
			std::string& title(){
				return _title;
			}
			//The track title
			void title(std::string title){
				_title = title;
			}
			
			unsigned int duration(){
				return _trackDuration;
			}
			//Track duration in secconds
			void duration(unsigned  int duradion){
				_trackDuration = duradion;
			}
		
			std::string& master(){
				return _master;
			}
			//The track master. Something like track/file name(ex: track_1.mp3) This is NOT the track title
			void master(std::string master){
				_master = master;
			}
			
			//Track default constructor
			Track(){
				_title          = "-- Untitled --";
				_trackDuration  = 0u;
				_master         = "";
			}
			
			Track(std::string trackname, unsigned  int duration, std::string filename){
				_title          = trackname;
				_trackDuration  = duration;
				_master         = filename;
			}

			~Track(){
				//for(std::vector< Style* >::iterator it=_styles.begin();it!=_styles.end(); ++it)
				//	delete *it;
			}

			void addStyle(Style* style){				
				_styles.push_back(style);
			}
			
			std::vector<Style*> getStyles(){
				return _styles;
			}

		private:
			std::string _title;
			std::string _master;
			std::vector<Style*> _styles;
			unsigned int _trackDuration;	
};

#endif
