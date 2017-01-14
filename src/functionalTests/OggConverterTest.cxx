#include "MiniCppUnit.hxx"
#include "LibFileSystem.hxx"

//#include "SingAlong.hxx"
#include "Mp3Converter.hxx"
#include "OggConverter.hxx"
#include "externalLibs/FraunhofferTools.hxx"
#include "Converter.hxx"


#include <fstream>

class OggConverterTests : public TestFixture<OggConverterTests>
{
public:
	TEST_FIXTURE( OggConverterTests ){

		TEST_CASE( testConvert_generateFile );
		TEST_CASE( testConvert_generateContent);
		TEST_CASE( testConvert_withDifferentBitrate );
		TEST_CASE( testConvert_withInexistentMaster );
		TEST_CASE( testConvert_polymorphicCall );
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

	void testConvert_generateFile(){

		OggConverter converter;
		createMasterFile("Master.wav",50);
		converter.convert("masters/Master.wav","compressed/Prefix");
		
			ASSERT_EQUALS(
				"compressed/Prefix [128].ogg\n",
			LibFileSystem::listDirectoryInOrder( "compressed" )
		);
	}
	
	
	void testConvert_generateContent(){
		OggConverter converter;
		createMasterFile("Master.wav",50);
		converter.convert("masters/Master.wav","compressed/Prefix");
		
			ASSERT_EQUALS(
				"OGG extracted from 'masters/Master.wav' at 128 bps and length 50s.\n",
			LibFileSystem::fileContent( "compressed/Prefix [128].ogg" )
		);
	}



	void testConvert_withDifferentBitrate(){
		OggConverter converter;
		createMasterFile("Master.wav",50);
		converter.convert("masters/Master.wav","compressed/Prefix");
		converter.bitrate("masters/Master.wav","compressed/Prefix [128].mp3",256);

		ASSERT_EQUALS(
			"OGG extracted from 'masters/Master.wav' at 256 bps and length 50s.\n",
				LibFileSystem::fileContent( "compressed/Prefix [128].mp3" )
		);
	}



	void testConvert_withInexistentMaster(){

		try{
			OggConverter converter;
			createMasterFile("Master.wav",50);
			converter.convert("Invalid master file","compressed/Prefix");
			converter.bitrate("Invalid master file","compressed/Prefix",96);

			FAIL( "An exception should be caught!" );
		}
		catch( std::exception & e )
		{
			ASSERT_EQUALS( "The master file does not exist", e.what() );
		}
	}

	void testConvert_polymorphicCall(){
		
		Converter *conv;
		OggConverter oggConv;
		conv = & oggConv;

		createMasterFile("Master.wav",50);
		conv->convert("masters/Master.wav","compressed/Prefix");
		
	}

///////////////// TEST GOES HERE /////////////////////
};

REGISTER_FIXTURE( OggConverterTests )


