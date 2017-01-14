
 #ifndef _CONVERTER_
 #define _CONVERTER_
 
#include <iostream>
#include <string>
#include "externalLibs/FraunhofferTools.hxx"

#include <stdexcept>

using namespace std;

class Converter {

		public:
			Converter(){}

			virtual ~Converter(){}

			virtual void convert(const char* masterFile, const char* compressedFile){
				cout << "This method doesn't have defined any convert algorithm";
			}

			virtual std::string getFormat(void){
				return "you can't use this method";
			}
		
			virtual std::string getBitrate(void){
				return "you can't use this method";
			}
		
	private:
		std::string _format;
		frk_Rate    _bitrate;
		std::string _masterFile;
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
