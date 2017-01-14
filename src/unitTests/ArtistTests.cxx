
  #include "MiniCppUnit.hxx"
  #include "Artist.hxx"
  
class ArtistTests : public TestFixture<ArtistTests>
{
public:

	TEST_FIXTURE( ArtistTests )
	{
		TEST_CASE( testName_byDefault );
		TEST_CASE( testName_afterModifying );
		TEST_CASE( testDescription_byDefault );
		TEST_CASE( testDescription_afterModifying );
	}
	
	void testName_byDefault()
	{
		Artist artist;
		ASSERT_EQUALS( "Tiësto", artist.name());
	}
	
	void testName_afterModifying()
	{
		Artist artist;
		artist.name( "Tiesto" );
		ASSERT_EQUALS( "Tiesto", artist.name() );
	}
	
	void testDescription_byDefault()
	{
		Artist artist;
		ASSERT_EQUALS( "Tiësto [solo]\n", artist.description() );
	}

	void testDescription_afterModifying()
	{
		Artist artist;
		artist.addToGroup();
		ASSERT_EQUALS( "Tiësto [group]\n", artist.description() );
	}
};

REGISTER_FIXTURE( ArtistTests )


