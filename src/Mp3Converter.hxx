
 #ifndef __MP3CONVERTER__
 #define __MP3CONVERTER__
 
#include <iostream>
#include <string>
#include "externalLibs/FraunhofferTools.hxx"

#include "Converter.hxx"
#include <stdexcept>

using namespace std;

class Mp3Converter : public Converter {

		public:
			Mp3Converter() {
				_bitrate    = bps96;
				_masterFile = "masters/Master.wav";
			    _compressedFile = "compressed/Prefix [128].mp3";
			}

			Mp3Converter(std::string format, frk_Rate bitrate){
				_bitrate = bitrate;
				_format  = format;
			}

		    void convert(const char* masterFile, const char* compressedFile){
				int convertResult;
				std::string  name;
				const char *completeName;

				name+= compressedFile;
				name+= " [128].mp3";
				completeName = name.c_str();

				//Here we can call the convert method from the master class
				convertResult = frk_MP3_compression(masterFile,completeName, bps128);

				if(convertResult==-1)
					throw InvalidMasterFile();
			}

			void bitrate(int bitrate){
				frk_Rate rate;
				switch(bitrate){
					case 96:
						rate = bps96;
					break;
					
					case 128:
						rate = bps128;
					break;
					
					case 192:
						rate = bps192;
					break;

					case 240:
						rate = bps240;
					break;

					default:
						throw WrongFileFormat();
				}
				frk_MP3_compression("masters/Master.wav","compressed/Prefix [128].mp3", rate);
			}

		std::string getBitrate(void){
			std::string str="";
			std::stringstream stream;
			const char* _bitrateFormat[] =  {"96","128","192","240"};

			stream << _bitrateFormat[_bitrate];
			str = stream.str();

			return str;
		}	

		std::string getFormat(void){
			return _format;
		}

		std::string getMp3Format(void){
			return _format;
		}


	private:	
		std::string  _format;
		frk_Rate     _bitrate;
		std::string  _masterFile;
		std::string  _compressedFile;	
		
		class WrongFileFormat : public std::exception{	
			const char * what() const throw (){
				return "Unsupported Format";
			}
		};

		class InvalidMasterFile : public std::exception{	
			const char * what() const throw (){
				return "The master does not exist";
			}
		};	
};

#endif
