
 #ifndef _CONVERTGROUP_
 #define _CONVERTGROUP_

#include <iostream>
#include <string>
#include "Mp3Converter.hxx"
#include "OggConverter.hxx"

using namespace std;

class ConvertGroup  {
		public:
			ConvertGroup(){}
			
			virtual ~ConvertGroup(){
				for(std::vector< Converter* >::iterator conv = _conv.begin();conv!=_conv.end(); ++conv)
					delete *conv;
			}
		
			void addConverter(std::string format, frk_Rate bitrate){
				Mp3Converter *mp3Conv;
				OggConverter *oggConv;

				if(format == "mp3"){
					mp3Conv = new Mp3Converter(format, bitrate);
					_conv.push_back(mp3Conv);
				}
			  	else if(format == "ogg"){
					oggConv = new OggConverter(format, bitrate);
					_conv.push_back(oggConv);
				}
				else{
					throw WrongFileFormat();
				}
			}

		void convert(void){
			unsigned int i;
			
			std::string name = "";
			for(i=0;i<_conv.size();i++){
				name += "compressed/Prefix [" + _conv.at(i)->getBitrate() + "]." + _conv.at(i)->getFormat();
				_conv.at(i)->convert("masters/Master.wav", name.c_str());
				name="";

				cout << "Done";
			}
		}

		std::string getConverters(void){
			unsigned int i;
			std::string str="";
			std::stringstream stream;
	
			for(i=0;i<_conv.size();i++){
				stream << "FILE: " << _conv.at(i)->getFormat() << ". Bitrate: " << _conv.at(i)->getBitrate()<<" bps\n";
			}
			str = stream.str();
			return str;
		}

		std::string getMp3Converter(void){
			std::string str="";
			std::stringstream stream;

			if(_conv.size()>0){
				stream << "Converter's format: mp3. Converter's bitrate: 96 bps"/* << _mp3Conv.getBitrate()*/;
				str = stream.str();
			}

			return str;
		}

		private:
			string _format;
			int bitrate;
			Mp3Converter _mp3Conv;
			OggConverter _oggconv;
			vector<Converter*> _conv;

			class WrongFileFormat : public std::exception{	
			const char * what() const throw (){
				return "Unsupported format";
			}
		};
};

#endif
