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
"wmo_01327{\n"
"  #Kvamskogen\n"
"  stationid=50310\n"
"  typepriority=(308,\"*330\")\n"
"  delay=(\"SS:02\")\n"
"  owner=\"HYBR\"\n"
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
"\n"
"wmo_01492{\n"
"  name=\"OSLO-BLINDERN\"\n"
"  height=94\n"
"  height_wind=28\n"
"  height_precip=1\n"
"  height_temperature=2\n"
"  height_pressure=94\n"
"  stationid=18700\n"
"  typepriority=(\"*330\",308)\n"
"  delay=(\"SS:05\")\n"
"  precipitation=(\"RRRtr\")\n"
"  owner=\"HYBR\"\n"
"  latitude=59.9423\n"
"  longitude=10.72\n"
"}\n"
"\n"
"wmo_89504{\n"
"  #Troll i antarktis\n"
"  stationid=99990\n"
"  typepriority=(\"*1\", \"*308\" )\n"
"  #    delay=(\"SS:02\")\n"
"  owner=\"AUTG\"\n"
"  precipitation=(\"RRRtr\")\n"
"}\n"
"\n";


#endif /* KVSYNOPENCODETESTCONF_H_ */
