#!/bin/sh
set -x
libtoolize --copy --automake
aclocal-1.8 || aclocal
autoconf
autoheader
automake-1.8 --add-missing --foreign || automake --add-missing --foreign
./configure --enable-maintainer-mode --prefix=/usr
