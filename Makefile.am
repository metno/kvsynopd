SUBDIRS = src 
ACLOCAL_AMFLAGS = -I m4
sqldir = $(datadir)/kvsynopd
sql_DATA = cleansynopdb.sql 
bin_SCRIPTS = kvsynopdbadmin

SED_SUBST = sed s,KVCONFIG,$(bindir)/kvconfig,g $< > $@ 

kvsynopdbadmin: kvsynopdbadmin.sh 
	$(SED_SUBST)
	
EXTRA_DIST = cleansynopdb.sql kvsynopdbadmin.sh

CLEANFILES = kvsynopdbadmin

install-data-hook:
	$(install_sh) -m 755 -d $(DESTDIR)/$(localstatedir)/lib/@PACKAGE_NAME@
	$(install_sh) -m 755 -d $(DESTDIR)/$(localstatedir)/lib/@PACKAGE_NAME@/debug
	$(install_sh) -m 755 -d $(DESTDIR)/$(localstatedir)/lib/@PACKAGE_NAME@/run
	$(install_sh) -m 755 -d $(DESTDIR)/$(localstatedir)/log/@PACKAGE_NAME@
	$(install_sh) -m 755 -d $(DESTDIR)/$(datadir)/@PACKAGE_NAME@

#pkgconfig_DATA = @PACKAGE_TARNAME@.pc
#$(pkgconfig_DATA): config.status

include mk/debian.mk