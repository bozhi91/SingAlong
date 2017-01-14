
 #ifndef _ARTIST_
 #define _ARTIST_

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>
#include "Track.hxx"
#include "Album.hxx"
#include "Subject.hxx"
#include "Portal.hxx"

using namespace std;

class Artist : public Subject{
		public:
			std::string& name(){
				return _name;		
			}
			
			void name(std::string name){
				_name = name; 
			}
			
			//Sets some description for the artist
			std::string& description(){
			    _solo==true ?_name+=" [solo]\n" : _name+=" [group]\n";
				return _name;
			}
			
			//Defines if the artist is from a group or not
			void addToGroup(){
				_solo = false;
			}
			
			//Returns FALSE if the artist is from a group. TRUE otherwise
			bool isSolo(){
				return _solo;
			}

			//Returns a pointer to the vector of the tracks
			std::vector<Track*> getTracks(){
				return _tracks;
			}

			//Returns a pointer to the vector of the tracks
			std::vector<Album*> getAlbums(){
				return _albums;
			}

			/*Search for a given track(we search the track by name) in the track list and 
			  returns pointer to this track if the track exist. Otherwise we call an exception.
			*/
			Track & findTrack(std::string trackName){
				unsigned int i;
			    for(i=0;i<_tracks.size();i++){
					if(_tracks.at(i)->title() == trackName){
						return *_tracks.at(i); 
					}
				}
			    throw TrackNotFound();
			}
			
			Album & findAlbum(std::string albumName){
				unsigned int i;
				
			    for(i=0;i<_albums.size();i++){
					if(_albums.at(i)->title() == albumName){
						return *_albums.at(i); 
					}
				}
			    throw AlbumNotFound();
			}

			//Returns a list (as String) of all tracks in the array in the following format:  "\t Trackname [trackDuration s]\n \t\t trackMaster\n"
			std::string catalogTracks(void){
				std::string tracks;
				std::stringstream stream;
				unsigned int i;
				
				for(i=0; i<_tracks.size(); i++){
					stream << "\t" << _tracks.at(i)->title() << " [" << 
					_tracks.at(i)->duration() << "s]\n\t\t" << _tracks.at(i)->master() << "\n";
				}
				tracks = stream.str();
				return tracks;
			}
			
			std::string descriptionCatalog(void){
				std::string catalog,solo,listed;
				std::stringstream stream;
				unsigned int i;
		
				_solo==true ?solo+=" [solo]" : solo+=" [group]";
				stream << name()+solo+"\n"; //An artist [solo / group]
				
				//If the tracklist is not empty
				if(_tracks.size()!=0){
					for(i=0; i<_tracks.size(); i++){
					  	stream<<"\t"<<_tracks.at(i)->title()<<" ["<< 
					  	_tracks.at(i)->duration()<<"s]\n"<<"\t\t"<<_tracks.at(i)->master()<<"\n";
					}
				}
				
				//If the album list is not empty
				if(_albums.size()!=0){
					for(i=0; i<_albums.size(); i++){
						_albums.at(i)->isListed()==true?listed+="":listed+=" [unlisted]";
						stream << "Album: "<< _albums.at(i)->title() << listed<<"\n"; // Album: Album Name\n
					}
				}
				catalog = stream.str();
				return catalog;
			}
			
			void assignTrackToAlbum(std::string trackName, std::string albumName){
				Album & album = findAlbum(albumName);
				Track & track = findTrack(trackName);
				album.addTrack(track);
			}
			
			//Creates a new Track
			void newTrack(std::string trackname, unsigned  int duration, std::string filename){
			    Track* tr = new Track(trackname, duration, filename);					
				_tracks.push_back(tr);
				notifyAll(trackname,_name);
			}
			
			void newAlbum(std::string album){
			    Album* al = new Album(album);					
				_albums.push_back(al);
			}

			//Default Constructor
			Artist(){
				_name = "Tiësto";
				_solo = true;				
			}

			//A custom Constructor
			Artist(std::string name, bool solo){
				_name = name;
				_solo = solo;				
			}

			//Destructor
			virtual ~Artist(){
				for(std::vector< Track* >::iterator it=_tracks.begin();it!=_tracks.end(); ++it)
					delete *it;
					
				for(std::vector< Album* >::iterator it=_albums.begin(); it!=_albums.end();++it)
					delete *it;
			}
		
		//Returns a pointer to the array of users subscribed to this artist.	
		std::vector<User*> getUsers(void){
			return _users;
		}

		//Assign user to artist
		void addUser(User* user){				
			_users.push_back(user);

			Observer* obs;
			obs = user;
			addObserver(obs);
		}

		void addPortal(Portal* portal){
			_portal.push_back(portal);
		}

		//Returns a pointer to the vector of the tracks
		std::vector<Portal*> getPortals(){
			return _portal;
		}

		private:
			std::string _name;
			std::string _description;
	
			bool _solo;
			std::vector<Track*>_tracks;
			std::vector<Album*>_albums;
			std::vector<User*>_users;
			std::vector<Portal*>_portal;
			
			//Exception Class	
			class TrackNotFound : public std::exception{
				const char * what() const throw (){
					return "The track does not exist";
				}
			};		
			class AlbumNotFound : public std::exception{
				const char * what() const throw (){
					return "The album does not exist";
				}
			};		
};

#endif