
 
#ifndef _ALBUM_
 #define _ALBUM_

#include <iostream>
#include <string>

class Album {
	
		public:
			std::string& title(){
				return _title;
			}
			
			void title(std::string title){
				_title = title;
			}
			
			bool isListed(){
				return _listed;
			}

			//Returns a pointer to the vector of the tracks
			std::vector<Track*> getTracks(){
				return _tracks;
			}

			std::string trackList(){
				unsigned int i;
				std::string trackList;
				std::stringstream stream;

				for(i=0; i<_tracks.size(); i++){
					stream<< i+1<< " - "<<_tracks.at(i)->title()<<" ["<<_tracks.at(i)->duration()<<"s]\n";
				}
				trackList = stream.str();
				return trackList;
			}
			
			void list(void){
				_listed = true;
			}
			
			void unlist(void){
				_listed = false;
			}

			void addTrack(Track track){
				Track* tr = new Track(track.title(), track.duration(), track.master());					
				_tracks.push_back(tr);
			}

			Album(std::string albumName){
				_title  = albumName;
				_listed = false;
			}
			
			
			Album(){
				_title  = "-- Untitled --";
				_listed = false;
			}

			~Album(){
				for(std::vector< Track* >::iterator it=_tracks.begin();it!=_tracks.end(); ++it)
					delete *it;
			}
			
		private:
			std::string _title;
			bool   _listed;
			std::vector<Track*>_tracks;
};

#endif