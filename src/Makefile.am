#
# Wifi switcher for N900  Copyright (C) 2010 by Tito Ragusa <farmatito@tiscali.it>
#
# Wifi switicher is a tool to tenable/disable wifi on the Nokia N900
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License as
# published by the Free Software Foundation; either version 2 of
# the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
#
# Please read the COPYING and README file!!!
#
# Report bugs to <farmatito@tiscali.it>
#


# The status menu plugin
dist_sbin_SCRIPTS = wifi.sh

pluginlibdir = `pkg-config libhildondesktop-1 --variable=hildondesktoplibdir`
pluginlib_LTLIBRARIES = libwifi_switcher.la

libwifi_switcher_la_CFLAGS = $(GLIB_CFLAGS) $(GTK_CFLAGS) \
				   $(HILDON_CFLAGS)
libwifi_switcher_la_LIBADD = $(GLIB_LIBS) $(GTK_LIBS) \
				   $(HILDON_LIBS)
libwifi_switcher_la_LDFLAGS = -module -avoid-version
libwifi_switcher_la_SOURCES = wifi-switcher-statusbar.c


CLEAN_FILES = $(BUILT_SOURCES)
