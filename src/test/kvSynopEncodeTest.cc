/*
  Kvalobs - Free Quality Control Software for Meteorological Observations

  $Id: synop.h,v 1.12.2.5 2007/09/27 09:02:18 paule Exp $

  Copyright (C) 2007 met.no

  Contact information:
  Norwegian Meteorological Institute
  Box 43 Blindern
  0313 OSLO
  NORWAY
  email: kvalobs-dev@met.no

  This file is part of KVALOBS

  KVALOBS is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License as
  published by the Free Software Foundation; either version 2
  of the License, or (at your option) any later version.

  KVALOBS is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with KVALOBS; if not, write to the Free Software Foundation Inc.,
  51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include <float.h>
#include <limits.h>
#include <string>
#include <puTools/miTime.h>
#include <miutil/cmprspace.h>
#include <kvalobs/kvData.h>
#include <list>
#include <kvalobs/kvStation.h>
#include <milog/milog.h>
#include "synop.h"
#include "kvSynopEncodeTestConf.h"
#include "StationInfoParse.h"
#include <sstream>
#include "ReadDataFile.h"
#include <gtest/gtest.h>

using namespace std;

namespace {
}

class MySynop : public Synop
{
public:
   MySynop():Synop(){}
   MySynop( Synop::EPrecipitation precipitation ) :
      Synop( precipitation)
   {
   }
   bool Sjekk_kode( std::string &kode ) { return Synop::Sjekk_kode( kode ); }
};

class SynopEncodeTest : public testing::Test
{

protected:
	Synop synopEncoder;
	std::list<StationInfoPtr> stationList;

	StationInfoPtr findWmoNo( int wmono ) {
		for( std::list<StationInfoPtr>::iterator it=stationList.begin(); it!=stationList.end(); ++it ) {
			if( (*it)->wmono() == wmono )
				return *it;
		}

		return StationInfoPtr();
	}

	///Called before each test case.
	virtual void SetUp() {
		using namespace miutil::conf;
		ConfParser confParser;
		istringstream iconf(testconf);

		//Turn off almost all logging.
		milog::Logger::logger().logLevel( milog::ERROR );

		synopEncoder.setTest( true );
		//cerr << "[" << endl << testconf << endl << "]" << endl;

		ConfSection *conf = confParser.parse( iconf );

		ASSERT_TRUE( conf ) << "Cant parse the configuration settings.";

		StationInfoParse stationParser;

		ASSERT_TRUE( stationParser.parse( conf, stationList ) ) << "Cant parse the station information.";
	}

	///Called after each test case.
	virtual void TearDown() {

	}


};



TEST_F( SynopEncodeTest, RR24_for_RRRtr )
{
	SynopDataList data;
	StationInfoPtr stInfo;
	string synop;
	kvdatacheck::Validate validData( kvdatacheck::Validate::NoCheck );
	stInfo = findWmoNo( 1389 );

	ASSERT_TRUE( stInfo ) << "No station information for wmono " << 1389;

	loadSynopDataFromFile( "data_7010-1.dat", stInfo, data, validData );
	EXPECT_TRUE( synopEncoder.doSynop( stInfo, data, synop, false ) ) << "FAILED: Cant generate synop for "<< 1389;
	miutil::cmprspace( synop, true );
    EXPECT_EQ( synop, "AAXX 23061 01389 16/// ///// 1//// 2//// 69912 333 70003 555 41///=") << "Generated synop 1: " << synop;

    loadSynopDataFromFile( "data_7010-2.dat", stInfo, data, validData );
    EXPECT_TRUE( synopEncoder.doSynop( stInfo, data, synop, false ) ) << "FAILED: Cant generate synop for "<< 1389;
    miutil::cmprspace( synop, true );
    EXPECT_EQ( synop, "AAXX 23061 01389 16/// ///// 1//// 2//// 60002 333 70000 555 40///=")<< "Generated synop 2: " << synop;

    loadSynopDataFromFile( "data_7010-3.dat", stInfo, data, validData );
    EXPECT_TRUE( synopEncoder.doSynop( stInfo, data, synop, false ) ) << "FAILED: Cant generate synop for "<< 1389;
    miutil::cmprspace( synop, true );
    EXPECT_EQ( synop, "AAXX 23061 01389 16/// ///// 1//// 2//// 60002 333 79999 555 40///=")<< "Generated synop 3: " << synop;

    loadSynopDataFromFile( "data_7010-4.dat", stInfo, data, validData );
    EXPECT_TRUE( synopEncoder.doSynop( stInfo, data, synop, false ) ) << "FAILED: Cant generate synop for "<< 1389;
    miutil::cmprspace( synop, true );
    EXPECT_EQ( synop, "AAXX 23061 01389 16/// ///// 1//// 2//// 69902 333 79999 555 40///=")<< "Generated synop 4: " << synop;

    loadSynopDataFromFile( "data_7010-5.dat", stInfo, data, validData );
    EXPECT_TRUE( synopEncoder.doSynop( stInfo, data, synop, false ) ) << "FAILED: Cant generate synop for "<< 1389;
    miutil::cmprspace( synop, true );
    EXPECT_EQ( synop, "AAXX 23061 01389 16/// ///// 1//// 2//// 69912 333 70001 555 41///=")<< "Generated synop 5: " << synop;
}


TEST_F( SynopEncodeTest, encode_TzFxFx )
{
	SynopDataList data;
	StationInfoPtr stInfo;
	string synop;
	kvdatacheck::Validate validData( kvdatacheck::Validate::NoCheck );
	int wmono=1001;
	stInfo = findWmoNo( wmono );


	ASSERT_TRUE( stInfo ) << "No station information for wmono " << wmono;

	loadSynopDataFromFile( "data_TzFxFx-1.dat", stInfo, data, validData );
	EXPECT_TRUE( synopEncoder.doSynop( stInfo, data, synop, false ) ) << "FAILED: Cant generate synop for "<< 1389;
	miutil::cmprspace( synop, true );
    EXPECT_EQ( synop, "AAXX 22151 01001 46/// ///// 1//// 2//// 555 0/003=") << "Generated synop 1: " << synop;

    loadSynopDataFromFile( "data_TzFxFx-2.dat", stInfo, data, validData );
    EXPECT_TRUE( synopEncoder.doSynop( stInfo, data, synop, false ) ) << "FAILED: Cant generate synop for "<< 1389;
    miutil::cmprspace( synop, true );
    EXPECT_EQ( synop, "AAXX 22151 01001 46/// ///// 1//// 2//// 555 0/003=") << "Generated synop 2: " << synop;

    loadSynopDataFromFile( "data_TzFxFx-3.dat", stInfo, data, validData );
    EXPECT_TRUE( synopEncoder.doSynop( stInfo, data, synop, false ) ) << "FAILED: Cant generate synop for "<< 1389;
    miutil::cmprspace( synop, true );
    EXPECT_EQ( synop, "AAXX 22151 01001 46/// ///// 1//// 2//// 555 0/103=") << "Generated synop 3: " << synop;

    loadSynopDataFromFile( "data_TzFxFx-4.dat", stInfo, data, validData );
    EXPECT_TRUE( synopEncoder.doSynop( stInfo, data, synop, false ) ) << "FAILED: Cant generate synop for "<< 1389;
    miutil::cmprspace( synop, true );
    EXPECT_EQ( synop, "AAXX 22151 01001 46/// ///// 1//// 2//// 555 0/304=") << "Generated synop 4: " << synop;

    loadSynopDataFromFile( "data_TzFxFx-5.dat", stInfo, data, validData );
    EXPECT_TRUE( synopEncoder.doSynop( stInfo, data, synop, false ) ) << "FAILED: Cant generate synop for "<< 1389;
    miutil::cmprspace( synop, true );
    EXPECT_EQ( synop, "AAXX 22121 01001 16/// ///// 1//// 2//// 6//// 555 0/405=") << "Generated synop 5: " << synop;

    loadSynopDataFromFile( "data_TzFxFx-6.dat", stInfo, data, validData );
    EXPECT_TRUE( synopEncoder.doSynop( stInfo, data, synop, false ) ) << "FAILED: Cant generate synop for "<< 1389;
    miutil::cmprspace( synop, true );
    EXPECT_EQ( synop, "AAXX 22121 01001 16/// ///// 1//// 2//// 6//// 555 0/404=") << "Generated synop 6: " << synop;

    loadSynopDataFromFile( "data_TzFxFx-7.dat", stInfo, data, validData );
    EXPECT_TRUE( synopEncoder.doSynop( stInfo, data, synop, false ) ) << "FAILED: Cant generate synop for "<< 1389;
    miutil::cmprspace( synop, true );
    EXPECT_EQ( synop, "AAXX 22121 01001 16/// ///// 1//// 2//// 6//// 555 0/405=") << "Generated synop 7: " << synop;

    loadSynopDataFromFile( "data_TzFxFx-8.dat", stInfo, data, validData );
    EXPECT_TRUE( synopEncoder.doSynop( stInfo, data, synop, false ) ) << "FAILED: Cant generate synop for "<< 1389;
    miutil::cmprspace( synop, true );
    EXPECT_EQ( synop, "AAXX 22121 01001 16/// ///// 1//// 2//// 6//// 555 0/008=") << "Generated synop 8: " << synop;

    loadSynopDataFromFile( "data_TzFxFx-9.dat", stInfo, data, validData );
    EXPECT_TRUE( synopEncoder.doSynop( stInfo, data, synop, false ) ) << "FAILED: Cant generate synop for "<< 1389;
    miutil::cmprspace( synop, true );
    EXPECT_EQ( synop, "AAXX 22121 01001 16/// ///// 1//// 2//// 6//// 555 0/005=") << "Generated synop 9: " << synop;
}

TEST_F( SynopEncodeTest, encode_nddff )
{
   using namespace miutil;
   SynopDataList allData;
   SynopDataList data;
   StationInfoPtr stInfo;
   string synop;
   miTime dt;
   kvdatacheck::Validate validData( kvdatacheck::Validate::NoCheck );
   int wmono=1001;
   stInfo = findWmoNo( wmono );


   ASSERT_TRUE( stInfo ) << "No station information for wmono " << wmono;

   loadSynopDataFromFile( "data_nddff.dat", stInfo, allData, validData );

   dt=miTime("2010-02-21 06:00:00");
   data = allData.subData( dt );
   EXPECT_TRUE( data.firstTime() == dt );
   EXPECT_TRUE( synopEncoder.doSynop( stInfo, data, synop, false ) ) << "FAILED: Cant generate synop for "<< 1389;
   miutil::cmprspace( synop, true );
   EXPECT_EQ( synop, "AAXX 21061 01001 16/// ///21 1//// 2//// 6////=") << "Generated synop 1: " << synop;

   dt=miTime("2010-02-22 06:00:00");
   data = allData.subData( dt );
   EXPECT_TRUE( data.firstTime() == dt );
   EXPECT_TRUE( synopEncoder.doSynop( stInfo, data, synop, false ) ) << "FAILED: Cant generate synop for "<< 1389;
   miutil::cmprspace( synop, true );
   EXPECT_EQ( synop, "AAXX 22061 01001 16/// /3601 1//// 2//// 6////=") << "Generated synop 1: " << synop;

   dt=miTime("2010-02-23 06:00:00");
   data = allData.subData( dt );
   EXPECT_TRUE( data.firstTime() == dt );
   EXPECT_TRUE( synopEncoder.doSynop( stInfo, data, synop, false ) ) << "FAILED: Cant generate synop for "<< 1389;
   miutil::cmprspace( synop, true );
   EXPECT_EQ( synop, "AAXX 23061 01001 16/// /3601 1//// 2//// 6////=") << "Generated synop 1: " << synop;

   dt=miTime("2010-02-24 06:00:00");
   data = allData.subData( dt );
   EXPECT_TRUE( data.firstTime() == dt );
   EXPECT_TRUE( synopEncoder.doSynop( stInfo, data, synop, false ) ) << "FAILED: Cant generate synop for "<< 1389;
   miutil::cmprspace( synop, true );
   EXPECT_EQ( synop, "AAXX 24061 01001 16/// /0401 1//// 2//// 6////=") << "Generated synop 1: " << synop;

   dt=miTime("2010-02-25 06:00:00");
   data = allData.subData( dt );
   EXPECT_TRUE( data.firstTime() == dt );
   EXPECT_TRUE( synopEncoder.doSynop( stInfo, data, synop, false ) ) << "FAILED: Cant generate synop for "<< 1389;
   miutil::cmprspace( synop, true );
   EXPECT_EQ( synop, "AAXX 25061 01001 16/// ///01 1//// 2//// 6////=") << "Generated synop 1: " << synop;

   dt=miTime("2010-02-26 06:00:00");
   data = allData.subData( dt );
   EXPECT_TRUE( data.firstTime() == dt );
   EXPECT_TRUE( synopEncoder.doSynop( stInfo, data, synop, false ) ) << "FAILED: Cant generate synop for "<< 1389;
   miutil::cmprspace( synop, true );
   EXPECT_EQ( synop, "AAXX 26061 01001 16/// /0000 1//// 2//// 6////=") << "Generated synop 1: " << synop;

   dt=miTime("2010-02-27 06:00:00");
   data = allData.subData( dt );
   EXPECT_TRUE( data.firstTime() == dt );
   EXPECT_TRUE( synopEncoder.doSynop( stInfo, data, synop, false ) ) << "FAILED: Cant generate synop for "<< 1389;
   miutil::cmprspace( synop, true );
   EXPECT_EQ( synop, "AAXX 27061 01001 16/// /3501 1//// 2//// 6////=") << "Generated synop 1: " << synop;

   dt=miTime("2010-02-28 06:00:00");
   data = allData.subData( dt );
   EXPECT_TRUE( data.firstTime() == dt );
   EXPECT_TRUE( synopEncoder.doSynop( stInfo, data, synop, false ) ) << "FAILED: Cant generate synop for "<< 1389;
   miutil::cmprspace( synop, true );
   EXPECT_EQ( synop, "AAXX 28061 01001 16/// /35// 1//// 2//// 6////=") << "Generated synop 1: " << synop;
}

TEST_F( SynopEncodeTest, Sjekk_kode )
{
   MySynop synopGen;
   string totest("41234");
   string totestSaved(totest);


   EXPECT_TRUE( synopGen.Sjekk_kode( totest) );
   EXPECT_EQ( totestSaved, totest );

   totest = totestSaved = " 04123";
   EXPECT_TRUE( synopGen.Sjekk_kode( totest) );
   EXPECT_EQ( totestSaved, totest );

   totest = totestSaved = " 4////";
   EXPECT_FALSE( synopGen.Sjekk_kode( totest) );
   EXPECT_TRUE( totest.empty() ) << "Kode: '" << totest << "'";

   totest = totestSaved = " 4//99 59999";
   EXPECT_TRUE( synopGen.Sjekk_kode( totest) );
   EXPECT_EQ( totestSaved, totest ) << "Kode: '" << totest << "'";

}

TEST_F( SynopEncodeTest, encode_noData )
{
   SynopDataList data;
   StationInfoPtr stInfo;
   string synop;
   kvdatacheck::Validate validData( kvdatacheck::Validate::UseOnlyUseInfo );
   int wmono=1384;
   stInfo = findWmoNo( wmono );


   ASSERT_TRUE( stInfo ) << "No station information for wmono " << wmono;

   loadSynopDataFromFile( "data_4780-1.dat", stInfo, data, validData );

   EXPECT_TRUE( data.size() == 0 ) << "It is expected that the datalist is empty, but the size is: " << data.size();
}

TEST_F(SynopEncodeTest, synop_to_synop )
{
   using namespace miutil;
   SynopDataList data;
   SynopDataList allData;
   StationInfoPtr stInfo;
   string synop;
   miTime dt;
   kvdatacheck::Validate validData( kvdatacheck::Validate::UseOnlyUseInfo );
   int wmono=89504;
   stInfo = findWmoNo( wmono );


   loadSynopDataFromFile( "data_99990.dat", stInfo, allData, validData );

   dt=miTime("2010-06-22 06:00:00");
   data = allData.subData( dt );
   EXPECT_TRUE( data.firstTime() == dt );
   EXPECT_TRUE( synopEncoder.doSynop( stInfo, data, synop, false ) ) << "FAILED: Cant generate synop for "<< 1389;
   miutil::cmprspace( synop, true );
   EXPECT_EQ( synop, "AAXX 22061 89504 43/// /0203 11211 21400 38316 49857 55004 333 21340=");

   loadSynopDataFromFile( "data_99990-1.dat", stInfo, allData, validData );
   dt=miTime("2010-06-25 06:00:00");
   data = allData.subData( dt );
   EXPECT_TRUE( data.firstTime() == dt );
   EXPECT_TRUE( synopEncoder.doSynop( stInfo, data, synop, false ) ) << "FAILED: Cant generate synop for "<< 1389;
   miutil::cmprspace( synop, true );
   EXPECT_EQ( synop, "AAXX 25061 89504 43/// /1301 11227 21257 38358 49920 53002 333 21282=");
}

TEST_F( SynopEncodeTest, RR_FROM_RA )
{
   SynopDataList data;
   StationInfoPtr stInfo;
   string synop;
   kvdatacheck::Validate validData( kvdatacheck::Validate::NoCheck );
   stInfo = findWmoNo( 1327 );

   ASSERT_TRUE( stInfo );

   loadSynopDataFromFile( "data-50310.dat", stInfo, data, validData );
   EXPECT_TRUE( synopEncoder.doSynop( stInfo, data, synop, false ) ) << "FAILED: Cant generate synop for "<< 1389;
   miutil::cmprspace( synop, true );

   //cerr << "SYNOP: [" << synop << "]" << endl;
   EXPECT_EQ( synop, "AAXX 03061 01327 11358 82804 10042 20017 60152 78188 889// 333 20042 70553 91115 555 0/109 10073 455//=");

}

TEST_F( SynopEncodeTest, EmAndE )
{
   using namespace miutil;
   SynopDataList allData;
   SynopDataList data;
   StationInfoPtr stInfo;
   string synop;
   miTime dt;
   kvdatacheck::Validate validData( kvdatacheck::Validate::NoCheck );
   stInfo = findWmoNo( 1492 );

   ASSERT_TRUE( stInfo );

   loadSynopDataFromFile( "data_18700-1.dat", stInfo, allData, validData );
   dt=miTime("2012-03-12 06:00:00");
   data = allData.subData( dt );

   EXPECT_TRUE( data.firstTime() == dt ) << "time: " << data.firstTime();
   EXPECT_TRUE( synopEncoder.doSynop( stInfo, data, synop, false ) ) << "FAILED: Cant generate synop for "<< 1492;
   miutil::cmprspace( synop, true );

   //E'sss from Em (paramid 7).
   //cerr << "SYNOP: [" << synop << "]" << endl;
   EXPECT_EQ( synop, "AAXX 12061 01492 16/// ///// 1//// 2//// 6//// 333 41///=");

   dt=miTime("2012-03-13 06:00:00");
   data = allData.subData( dt );
   EXPECT_TRUE( data.firstTime() == dt );

   //E'sss from E (paramid 129)
   EXPECT_TRUE( synopEncoder.doSynop( stInfo, data, synop, false ) ) << "FAILED: Cant generate synop for "<< 1492;
   miutil::cmprspace( synop, true );
   EXPECT_EQ( synop, "AAXX 13061 01492 16/// ///// 1//// 2//// 6//// 333 41///=");

   //Test when both E and Em is given. It should use Em.
   dt=miTime("2012-03-14 06:00:00");
   data = allData.subData( dt );
   EXPECT_TRUE( data.firstTime() == dt );
   EXPECT_TRUE( synopEncoder.doSynop( stInfo, data, synop, false ) ) << "FAILED: Cant generate synop for "<< 1492;
   miutil::cmprspace( synop, true );
   EXPECT_EQ( synop, "AAXX 14061 01492 16/// ///// 1//// 2//// 6//// 333 42///=");

   dt=miTime("2012-03-15 06:00:00");
   data = allData.subData( dt );
   EXPECT_TRUE( data.firstTime() == dt );
   EXPECT_TRUE( synopEncoder.doSynop( stInfo, data, synop, false ) ) << "FAILED: Cant generate synop for "<< 1492;
   miutil::cmprspace( synop, true );
   EXPECT_EQ( synop, "AAXX 15061 01492 16/// ///// 1//// 2//// 6//// 333 31///=");
}




int
main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
