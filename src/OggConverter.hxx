  

 #ifndef _OGGCONVERT_

  #define _OGGCONVERT_

 #include <iostream>
 #include <string>
 #include "externalLibs/FraunhofferTools.hxx"
 //#include "SingAlong.hxx"
 #include "Track.hxx"
 #include "Artist.hxx"
 #include "OggVorbisEncoder.hxx"
 #include "Converter.hxx"
 #include <stdexcept>

 using namespace OGG;

 class OggConverter : public Converter {
 		public:
 			OggConverter() {
 				_bitrate    = bps96;
 				_masterFile = "masters/Master.wav";
 			    _compressedFile = "compressed/Prefix [128].mp3";
 			}

 			OggConverter(std::string format, frk_Rate bitrate){
				_bitrate = bitrate;
				_format  = format;
			}

 		    void convert(const char* masterFile, const char* compressedFile){
 				std::string  name;
 				const char *completeName;
 				name+= compressedFile;
 				name+= " [128].ogg";
 				completeName = name.c_str();

 				//Here we can call the convert method from the master class
 				compress("masters/Master.wav",completeName, 128);
 			}

 			void bitrate(const char* masterFile, const char* compressedFile,int bitrate){
				compress(masterFile,compressedFile, bitrate);

 			}

 			std::string getMaster(void){
 				return _masterFile;
 			}

 			std::string getFormat(void){
 				return _format;
 			}
 			
 		std::string getBitrate(void){
			std::string str;
			std::stringstream stream;
			const char* _bitrateFormat[] =  {"96","128","192","240"};

			stream << _bitrateFormat[_bitrate];
			str = stream.str();

			return str;
		}
	
 	private:	
 		std::string _format;
 		frk_Rate    _bitrate;
 		std::string _masterFile;
 		std::string  _compressedFile;	

 };
 #endif