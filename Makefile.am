SUBDIRS = src/gtest src 
ACLOCAL_AMFLAGS = -I m4
sqldir = $(datadir)/kvsynopd
sql_DATA = cleansynopdb.sql 
bin_SCRIPTS = kvsynopdbadmin check_kvsynopd.sh

SED_SUBST = sed s,__KVCONFIG__,$(bindir)/kvconfig,g $< > $@ 

kvsynopdbadmin: kvsynopdbadmin.sh 
	$(SED_SUBST)
	
EXTRA_DIST = cleansynopdb.sql kvsynopdbadmin.sh changelog

CLEANFILES = kvsynopdbadmin

install-data-hook:
	$(install_sh) -m 755 -d $(DESTDIR)/$(localstatedir)/lib/@PACKAGE_NAME@
	$(install_sh) -m 755 -d $(DESTDIR)/$(localstatedir)/lib/@PACKAGE_NAME@/debug
	$(install_sh) -m 755 -d $(DESTDIR)/$(localstatedir)/run/kvalobs
	$(install_sh) -m 755 -d $(DESTDIR)/$(localstatedir)/log/kvalobs
	$(install_sh) -m 755 -d $(DESTDIR)/$(localstatedir)/log/kvalobs/kvsynop
	$(install_sh) -m 755 -d $(DESTDIR)/$(datadir)/@PACKAGE_NAME@

#pkgconfig_DATA = @PACKAGE_TARNAME@.pc
#$(pkgconfig_DATA): config.status

include mk/debian.mk