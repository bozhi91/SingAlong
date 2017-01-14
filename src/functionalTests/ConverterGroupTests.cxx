#include "MiniCppUnit.hxx"
#include "LibFileSystem.hxx"

//#include "SingAlong.hxx"
#include "Mp3Converter.hxx"
#include "OggConverter.hxx"
#include "externalLibs/FraunhofferTools.hxx"
#include "Converter.hxx"
#include "ConvertGroup.hxx"

#include <fstream>

class ConverterGroupTests: public TestFixture<ConverterGroupTests>
{
public:
	TEST_FIXTURE( ConverterGroupTests ){

		TEST_CASE( testConvert_withMp3Converter );
		TEST_CASE(testConvert_withoutConverter);
		TEST_CASE(testConvert_withMp3AndOggConverters);
		TEST_CASE(testConvert_withUnknownConverter);
	}

	/**
	 * setUp is automatically called before each test case
	 */
	void setUp()
	{
		LibFileSystem::createNetDirectory( "masters" );
		LibFileSystem::createNetDirectory( "compressed" );
		LibFileSystem::createNetDirectory( "config" );
	}

	/**
	 * tearDown is automatically called after each test case
	 */
	void tearDown()
	{
		LibFileSystem::cleanupDirectory( "masters" );
		LibFileSystem::cleanupDirectory( "compressed" );
		LibFileSystem::cleanupDirectory( "config" );
	}

	void createMasterFile( const std::string & name, int duration )
	{
		std::string completeName( "masters/" );
		completeName += name;
		std::ofstream os( completeName.c_str() );
		os << duration << std::endl;
	}

	///////////////// TEST GOES HERE /////////////////////
	void testConvert_withMp3Converter(){
		ConvertGroup group;
		group.addConverter("mp3",bps96);

		ASSERT_EQUALS(
			"Converter's format: mp3. Converter's bitrate: 96 bps",
			 group.getMp3Converter()
		);
	}

	void testConvert_withoutConverter(){
		ConvertGroup group;
		ASSERT_EQUALS(
			"",
			 group.getMp3Converter()
		);
	}

	void testConvert_withMp3AndOggConverters(){

		ConvertGroup group;
		group.addConverter("mp3",bps96);
		group.addConverter("mp3",bps128);
		group.addConverter("ogg",bps192);
		group.addConverter("ogg",bps240);

		group.getConverters();

		ASSERT_EQUALS(
			"FILE: mp3. Bitrate: 96 bps\n"
			"FILE: mp3. Bitrate: 128 bps\n"
			"FILE: ogg. Bitrate: 192 bps\n"
			"FILE: ogg. Bitrate: 240 bps\n",
			group.getConverters()
		);
	}

	void testConvert_withUnknownConverter(){

		ConvertGroup group;
		
		try{
			group.addConverter("mp4",bps96);
			FAIL( "An exception should be caught!" );
		}
		catch( std::exception & e )
		{
			ASSERT_EQUALS( "Unsupported format", e.what() );
		}
	}

///////////////// TEST GOES HERE /////////////////////
};
REGISTER_FIXTURE( ConverterGroupTests )


