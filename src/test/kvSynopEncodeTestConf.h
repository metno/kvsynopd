/*
 * kvSynopEncodeTestConf.h
 *
 *  Created on: Feb 23, 2010
 *      Author: borgem
 */

#ifndef KVSYNOPENCODETESTCONF_H_
#define KVSYNOPENCODETESTCONF_H_

const char *testconf =
"wmo_default{\n"
"  #default values\n"
"  copyto=\"/dnmi/norcom/data/incoming/kvalobs\"\n"
"  copy=\"false\"\n"
"  owner=\"AUTG\"\n"
"  list=\"99\"\n"
"  loglevel=9\n"
"}\n"
"\n"
"wmo_01389{\n"
"  #Rena\n"
"  stationid=7010\n"
"  typepriority=(312)\n"
"  owner=\"PIOG\"\n"
"  precipitation=(\"RRRtr\")\n"
"}\n"
"wmo_01001{\n"
"  #Rena\n"
"  stationid=7010\n"
"  typepriority=(330)\n"
"  owner=\"AUTG\"\n"
"  precipitation=(\"RA\")\n"
"}\n"
"\n"
"wmo_01384{\n"
"  #Gardermoen\n"
"  stationid=04780\n"
"  typepriority=(501)\n"
"  #precipitation=(\"RA\")\n"
"  owner=\"AUTG\"\n"
"}\n"
"\n";


#endif /* KVSYNOPENCODETESTCONF_H_ */
