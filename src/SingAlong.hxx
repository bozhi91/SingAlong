
#ifndef _SINGALONG_
#define _SINGALONG_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>

#include "Artist.hxx"
#include "Style.hxx"
#include "User.hxx"
#include "Portal.hxx"
#include "Subject.hxx"
#include "Converter.hxx"
#include "ConvertGroup.hxx"

#include "gui/Model.hxx"

using namespace std;

class SingAlong : virtual public Model{
	public:
		ConvertGroup group;
		//Default Constructor
		SingAlong(){
			_catalogName = "Untitled Catalog";
			
			group.addConverter("mp3",bps96);
			group.addConverter("mp3",bps128);
			group.addConverter("mp3",bps192);
			group.addConverter("mp3",bps240);

			group.addConverter("ogg",bps96);
			group.addConverter("ogg",bps128);
			group.addConverter("ogg",bps192);
			group.addConverter("ogg",bps240);

			Artist artist;
		}
			
		//Destructor
		~SingAlong(){
			for(std::vector< Artist* >::iterator it=_artists.begin();it!=_artists.end(); ++it)
				delete *it;

			for(std::vector< Style* >::iterator it=_style.begin();it!=_style.end(); ++it)
				delete *it;

			for(std::vector< User* >::iterator it=_user.begin();it!=_user.end(); ++it)
				delete *it;

			for(std::vector< Portal* >::iterator it=_portal.begin();it!=_portal.end(); ++it)
				delete *it;
		}

		void userPrefersSms(string userName, string phoneNumber){
			User & user = findUser(userName);
			user.setNotificationType("sms",phoneNumber);
		}

		void userPrefersWhatsapp(string userName, string phoneNumber){
			User & user = findUser(userName);
			user.setNotificationType("whatsapp",phoneNumber);
		}

		void createNewUser(std::string userName, std::string email){
			User* user = new User(userName,email);					
			_user.push_back(user);
		}

		void createNewStyle(std::string styleName){
			Style* style = new Style(styleName);					
			_style.push_back(style);
		}

		void subscribeUserToArtist(string username, string artistname){
			User   & user   = findUser(username);
			Artist & artist = findArtist(artistname);	
			artist.addUser(&user);
		}

		void subscribeUserToStyle(std::string userName, std::string styleName){
			User  & user   = findUser(userName);
			Style & style  = findStyle(styleName);
			style.addUser(&user);
		}
		
		std::string listSubscribedToStyle(std::string styleName){
			std::stringstream stream;
			Style & style  = findStyle(styleName);
			unsigned int i;

			for(i=0;i<style.getUsers().size();i++){
				stream << style.getUsers().at(i)->getName() << "\n";
			}
			return stream.str();
		}

		std::string userList(void){
			std::stringstream stream;
			unsigned int i;

			for(i=0;i<_user.size();i++){
				stream << _user.at(i)->getName() << " <"<<_user.at(i)->getEmail()<<">\n";
			}
			return stream.str();
		}

		std::string styleList(void){
			std::string str;
			std::stringstream stream;
			unsigned int i;

			for(i=0;i<_style.size();i++){
				stream << _style.at(i)->getStyleName() << "\n";
			}
			str = stream.str();
			return str;
		}

		//Send a user notification when a style is associate with track.
		void associateStyleWithTrack(std::string styleName, std::string artistName, std::string trackName){
			Artist & artist = findArtist(artistName);
			Track  & track  = artist.findTrack(trackName);
			Style  & style  = findStyle(styleName);
			track.addStyle(&style);
			style.notify();
		}

		void includeTrackOnAlbum(std::string artistName, std::string trackName, std::string albumName){
			Artist & artist = findArtist(artistName);
			Album  & album  = artist.findAlbum(albumName);
			Track  & track  = artist.findTrack(trackName);
			album.addTrack(track);
		}

		void createArtist(std::string artistName, bool group){
			Artist* artist = new Artist(artistName, group);					
			_artists.push_back(artist);
		}

		void createNewAlbum(std::string artistName, std::string albumName){
			Artist & artist = findArtist(artistName);
			artist.newAlbum(albumName);
		}

		void createNewTrack(std::string artistName, std::string trackName, std::string master){	
			Artist & artist = findArtist(artistName);
			unsigned int duration;
			std::string masterName;
			std::stringstream stream;

			stream<<"masters/"<<master;
			masterName = stream.str();

			duration = readMaster(masterName);
			artist.newTrack(trackName,duration,master);		
		}

		Style & findStyle(std::string styleName){
			unsigned int i;
		    for(i=0;i<_style.size();i++){
				if(_style.at(i)->getStyleName() == styleName){
					return *_style.at(i); 
				}
			}
		    throw StyleNotFound();
		}

		User & findUser(std::string userName){
			unsigned int i;
		    for(i=0;i<_user.size();i++){
				if(_user.at(i)->getName() == userName){
					return *_user.at(i); 
				}
			}
		    throw UserNotFound();
		}

		Artist & findArtist(std::string artistName){
			unsigned int i;
		    for(i=0;i<_artists.size();i++){
				if(_artists.at(i)->name() == artistName){
					return *_artists.at(i);
				}
			}
		    throw ArtistNotFound();
		}

		//Reads the contain of the master file and returns the track duration
		//This function is called by the method createNewTrack()
		unsigned int readMaster(std::string masterName){
		    ifstream myfile (masterName.c_str());
  			std::string buffer;
  			unsigned int duration;

			if(!myfile)
				throw MasterNotFound();

	  		//Read the master file
	  		getline(myfile,buffer);				
	    	myfile.close();

	    	//Convert the string to unsigned int
			stringstream convert(buffer);//object from the class stringstream
			convert>>duration; 
  			return duration;
		}

		Portal & findPortal(std::string portalName){
			unsigned int i;
		    for(i=0;i<_portal.size();i++){
				if(_portal.at(i)->getName() == portalName){
					return *_portal.at(i); 
				}
			}
			 throw PortalNotFound();
		}

		void listAlbum(std::string artistName,std::string albumName){
			Artist & artist = findArtist(artistName);
			Album  & album  = artist.findAlbum(albumName);
			album.list();
		}

		void unlistAlbum(std::string artistName,std::string albumName){
			Artist & artist = findArtist(artistName);
			Album  & album  = artist.findAlbum(albumName);
			album.unlist();
		}
		//Returns a list (as String) of all artists in the array:> "A solo artist [solo]\n"
		std::string catalog(void){
			unsigned int i,j,k,l,trackSize,albumSize;
			std::string artist,solo,listed,master;
			std::stringstream stream,mas;

			Track *track;
			Album *album;

			//This method returns something like:A solo artist [solo]\n
			for(i=0; i<_artists.size(); i++){
				//===== Get the artist data
					_artists.at(i)->isSolo()==true ? solo+="[group]" : solo+="[solo]";
					stream << _artists.at(i)->name() << " " << solo << "\n";
					albumSize = _artists.at(i)->getAlbums().size();

					for(k=0; k<albumSize; k++){
					//===== Get album data =====
						album = _artists.at(i)->getAlbums().at(k);	
						album->isListed()==true ? listed+="" : listed+=" [unlisted]";
						
						if(album->getTracks().size()==0){	
							stream << "Album: " << album->title()<<listed<<"\n";
							listed = "";	
							for(l=0; l<album->getTracks().size(); l++){
								stream << album->getTracks().at(l)->title() << "++++";
							}
						}
					}

				//===== Get track data =====
					trackSize = _artists.at(i)->getTracks().size();
					for(j=0; j<trackSize; j++){
						track = _artists.at(i)->getTracks().at(j);
						stream << "\t"<<track->title() << " [";
						stream << track->duration() << "s]\n";
						stream << "\t\tmasters/" << _artists.at(i)->getTracks().at(j)->master() << "\n";

						for(unsigned int s=0; s<track->getStyles().size();s++){
							stream << "\t\t"<<track->getStyles().at(s)->getStyleName() << "\n";
						}
					}
				////////////////////////////////////////////////////////////////////////////////
				listed = "";
				for(k=0; k<albumSize; k++){
				//===== Get album data =====
					album = _artists.at(i)->getAlbums().at(k);	
					album->isListed()==true ? listed+="" : listed+=" [unlisted]";
					if(album->getTracks().size()!=0){	
						stream << "Album: " << album->title()<<listed<<"\n";
						listed = "";
						
						for(l=0; l<album->getTracks().size(); l++){
							stream << l+1<< " - " << album->getTracks().at(l)->title() <<" ["<< 
							album->getTracks().at(l)->duration()<<"s]\n";
							mas << "masters/aMasterFile.wav";
						}
					}
				}
				solo   = "";
			}
			artist = stream.str();	
			return artist;
		}
		void wrongMasterFile(void){
		    throw MasterNotFound();
		}

		void createNewPortal(string name, string description){
			Portal* portal = new Portal(name, description);					
			_portal.push_back(portal);
		}

		string rssByPortal(string portalName){
			stringstream stream;
			Portal & portal = findPortal(portalName);
			unsigned int i,j;

			stream << "<?xml version='1.0' encoding='ISO-8859-15'?>\n";
				stream << "<!DOCTYPE rss PUBLIC '-//Netscape Communications//DTD RSS 0.91//EN'\n";
				stream << "'http://my.netscape.com/publish/formats/rss-0.91.dtd'>\n";
				stream << "<rss version='0.91'>\n";
				stream << "<channel>\n";
				stream << "<title>SingAlong: "<<portal.getName()<<"</title>\n";
				stream << "<link>http://www.singalong.com/"<<_portal.at(0)->getName()<<"</link>\n";
				stream << "<description>"<<portal.getDescription()<<"</description>\n";

				for(i=0;i<_artists.size();i++){
					for(j=0;j<_artists.at(i)->getTracks().size();j++){

						stream << "<item>\n";
						stream << "<title>New track: '"<< _artists.at(i)->getTracks().at(j)->title() <<"' by '"
						<< _artists.at(i)->name() <<"'</title>\n";

						stream <<"<link>http://www.singalong.com/infoTrack?artist='"<< _artists.at(i)->name() <<"'&title='"
						<< _artists.at(i)->getTracks().at(j)->title() <<"'</link>\n";
						stream << "</item>\n";
					}
				}

				stream << "</channel>\n";
				stream << "</rss>\n";		
			return stream.str();
		}	


		string listPortals(void){
			stringstream stream;
			unsigned int i;
			for(i=0;i<_portal.size();i++){
				stream << _portal.at(i)->getName()<<"\n"<<"\t"<<_portal.at(i)->getDescription()<<"\n";
			}
			return stream.str();
		}

	void subscribePortalToArtist(string portalName, string artistName){
		Portal & portal = findPortal(portalName);
		Artist & artist = findArtist(artistName);
		artist.addPortal(&portal);
	}

	void subscribePortalToStyle(string portalName, string styleName){
		Portal & portal = findPortal(portalName);
		Style & style = findStyle(styleName);
		style.addPortal(&portal);
	}

	private:
		//The catalog has an array of artists
		std::vector<Artist*>_artists;
		std::vector<Style*>_style;
		std::vector<User*>_user;
		std::vector<Portal*>_portal;
		std::string _catalogName;

	//Our exception class
	class PortalNotFound : public std::exception{
		const char * what() const throw (){
			return "The portal does not exist";
		}
	};	

	class ArtistNotFound : public std::exception{
		const char * what() const throw (){
			return "The artist does not exist";
		}
	};	

	class UserNotFound : public std::exception{
		const char * what() const throw (){
			return "The user does not exist";
		}
	};	


	class StyleNotFound : public std::exception{
		const char * what() const throw (){
			return "The style does not exist";
		}
	};	

	class MasterNotFound : public std::exception{
		const char * what() const throw (){
			return "The master file does not exist";
		}
	};	
};

#endif