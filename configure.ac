#
# Wifi switcher for N900  Copyright (C) 2010 -2011 by Tito Ragusa <farmatito@tiscali.it>
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


AC_INIT(Makefile.am)
AM_INIT_AUTOMAKE(wifi-switcher, 0.0.10)
AM_CONFIG_HEADER(config.h)
AM_GNU_GETTEXT([external])
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LIBTOOL
AC_LIB_RPATH

# Some CFLAGS comes from debian/rules
CFLAGS="$CFLAGS -Wall -pedantic -Wmissing-prototypes -Wmissing-declarations -std=gnu99"

# Check for pkgconfig
AC_CHECK_PROG(HAVE_PKGCONFIG, pkg-config, yes, no)
# Give error and exit if we don't have pkgconfig
if test "x$HAVE_PKGCONFIG" = "xno"; then
        AC_MSG_ERROR(you need to have pkgconfig installed !)
fi

#PKG_CHECK_MODULES(prefix, list-of-modules, action-if-found, action-if-not-found)
PKG_CHECK_MODULES([GLIB], [glib-2.0 >= 2.8])
AC_SUBST(GLIB_LIBS)
AC_SUBST(GLIB_CFLAGS)

PKG_CHECK_MODULES(GTK, gtk+-2.0)
AC_SUBST(GTK_LIBS)
AC_SUBST(GTK_CFLAGS)

PKG_CHECK_MODULES([HILDON], [hildon-1 libhildondesktop-1])
AC_SUBST(HILDON_LIBS)
AC_SUBST(HILDON_CFLAGS)

PKG_CHECK_MODULES(DBUS, dbus-glib-1 >= 0.60)
AC_SUBST(DBUS_LIBS)
AC_SUBST(DBUS_CFLAGS)

AC_OUTPUT( po/Makefile.in
        Makefile \
        data/Makefile \
        src/Makefile
)
