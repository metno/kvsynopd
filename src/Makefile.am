AM_CPPFLAGS = -D_REENTRANT \
              $(putools_CFLAGS) \
              $(kvcpp_CFLAGS) \
              $(BOOST_CPPFLAGS) \
              $(omniORB4_CFLAGS)  

nodist_idl_sources=kvsynopd.idl 


CLEANFILES = $(nodist_idl_sources:.idl=SK.cc) $(nodist_idl_sources:.idl=.hh) 


%SK.cc %.hh: %.idl
#	$(IDL) -bcxx -Wbinline -I$(KVIDLDIR) $<
	$(IDL) -bcxx -I$(KVIDLDIR) $<

#noinst_PROGRAMS = kvSynopEncodeTest

bin_PROGRAMS = kvsynopd kvsynopclt kvsynopdbclt kvsynopdparse

kvsynopd_SOURCES = kvsynopd.hh kvsynopdSK.cc \
				   kvsynopd.cc \
                   App.cc App.h \
                   DataReceiver.cc DataReceiver.h \
                   Data.cc Data.h \
                   SynopWorker.cc SynopWorker.h \
                   SynopData.cc SynopData.h \
                   DataList.cc DataList.h \
                   StationInfo.cc StationInfo.h \
                   StationInfoParse.cc StationInfoParse.h \
                   tblSynop.cc tblSynop.h \
                   kvsynopdImpl.cc kvsynopdImpl.h \
                   Replay.cc Replay.h \
                   synop.cc synop.h \
                   Validate.cc Validate.h \
                   tblWaiting.cc tblWaiting.h \
                   Waiting.cc Waiting.h \
                   delaycontrol.cc delaycontrol.h \
                   tblKeyVal.cc tblKeyVal.h \
                   InitLogger.cc InitLogger.h \
                   getDataReceiver.cc getDataReceiver.h \
                   GetDataThread.cc GetDataThread.h \
                   kvsynopdImpl.h obsevent.h \
                   LoadSynopData.h LoadSynopData.cc \
                   SemiUniqueName.cc SemiUniqueName.h \
                   defines.h

kvsynopd_CPPFLAGS = $(AM_CPPFLAGS) 
kvsynopd_CXXFLAGS=$(GCC_NO_DEPRECATED)
kvsynopd_LDFLAGS = -pthread -export-dynamic $(BOOST_LDFLAGS)

kvsynopd_LDADD = \
				 $(putools_LIBS) \
                 $(kvcpp_LIBS) \
                 $(BOOST_THREAD_LIB) \
				 $(BOOST_FILESYSTEM_LIB) \
				 $(BOOST_SYSTEM_LIB) \
                 -lm         
                 
EXTRA_DIST = kvsynopd_schema.sql
 
kvsynopclt_SOURCES = kvsynopclt.cc \
                     kvsynopCltSynopcbImp.cc kvsynopCltSynopcbImp.h \
                     kvsynopCltApp.cc  kvsynopCltApp.h \
                     kvsynopCorbaThread.cc kvsynopCorbaThread.h \
                     kvsynopd.hh kvsynopdSK.cc
                     
kvsynopclt_CPPFLAGS = $(AM_CPPFLAGS)
kvsynopclt_CXXFLAGS=$(GCC_NO_DEPRECATED)
kvsynopclt_LDFLAGS = -pthread $(BOOST_LDFLAGS)
kvsynopclt_LDADD = \
	$(kvcpp_LIBS)  $(putools_LIBS)  $(BOOST_THREAD_LIB) \
   $(BOOST_SYSTEM_LIB) \
   -lm  
                   
kvsynopdbclt_SOURCES = kvsynopdbclt.cc \
                       tblSynop.cc tblSynop.h
kvsynopdbclt_LDFLAGS = -pthread $(BOOST_LDFLAGS) 
kvsynopdbclt_LDADD = \
	$(kvcpp_LIBS) $(putools_LIBS)  $(BOOST_THREAD_LIB) \
	$(BOOST_SYSTEM_LIB) \
   -lm 
kvsynopdparse_SOURCES = kvsynopdparse.cc \
                        StationInfo.cc StationInfo.h \
                        StationInfoParse.cc StationInfoParse.h
kvsynopdparse_LDFLAGS = -pthread $(BOOST_LDFLAGS)
kvsynopdparce_CXXFLAGS=$(GCC_NO_DEPRECATED)
kvsynopdparse_LDADD = \
	$(kvcpp_LIBS)  $(putools_LIBS)  $(BOOST_THREAD_LIB) \
	$(BOOST_SYSTEM_LIB) \
   -lm
                        
sqldir=$(datadir)/kvsynopd
sql_DATA=kvsynopd_schema.sql
bin_SCRIPTS = kvsynopd_initdb

if HAVE_GTEST


noinst_PROGRAMS=kvSynopEncodeTest

check_PROGRAMS=kvSynopEncodeTest
TESTS=$(check_PROGRAMS)

kvSynopEncodeTest_SOURCES = test/kvSynopEncodeTest.cc \
							test/kvSynopEncodeTestConf.h \
							test/ReadDataFile.h test/ReadDataFile.cc \
							Data.cc Data.h\
							DataList.cc DataList.h \
		                    SynopData.cc SynopData.h \
		                    StationInfo.cc StationInfo.h \
						    StationInfoParse.cc StationInfoParse.h \
		                    synop.cc synop.h \
		                    Validate.cc Validate.h \
		                    InitLogger.cc InitLogger.h \
		                    LoadSynopData.h LoadSynopData.cc 
		                    
 
kvSynopEncodeTest_CPPFLAGS = $(AM_CPPFLAGS) \
                           -DTESTDATADIR="\""$(top_srcdir)/src/test"\"" \
                           $(gtest_CFLAGS) 
kvSynopEncodeTest_CXXFLAGS=$(GCC_NO_DEPRECATED)
kvSynopEncodeTest_LDADD = $(gtest_LIBS) \
						  $(kvcpp_LIBS) \
						  $(putools_LIBS) 
endif