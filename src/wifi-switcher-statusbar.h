/*
*
* Wifi switcher for N900  Copyright (C) 2010 by Tito Ragusa <farmatito@tiscali.it>
*
* Wifi switicher is a tool to tenable/disable wifi on the Nokia N900
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License as
* published by the Free Software Foundation; either version 2 of
* the License, or (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*
* Please read the COPYING and README file!!!
*
* Report bugs to <farmatito@tiscali.it>
*
*/

#ifndef __WIFI_SWITCHER_H__
#define __WIFI_SWITCHER_H__

#include <libhildondesktop/libhildondesktop.h>

G_BEGIN_DECLS

#define TYPE_WIFI_SWITCHER            (wifi_switcher_get_type ())

#define WIFI_SWITCHER(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), \
                                    TYPE_WIFI_SWITCHER, WifiSwitcher))

#define WIFI_SWITCHER_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), \
                                TYPE_WIFI_SWITCHER, WifiSwitcherClass))

#define IS_WIFI_SWITCHER(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), \
                                                    TYPE_WIFI_SWITCHER))

#define IS_WIFI_SWITCHER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), \
                                                    TYPE_WIFI_SWITCHER))

#define WIFI_SWITCHER_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), \
                            TYPE_WIFI_SWITCHER, WifiSwitcherClass))

#define STATUS_AREA_WIFI_SWITCHER_ICON_SIZE 22

typedef struct _WifiSwitcher        WifiSwitcher;
typedef struct _WifiSwitcherClass   WifiSwitcherClass;
typedef struct _WifiSwitcherPrivate WifiSwitcherPrivate;

struct _WifiSwitcher
{
    HDStatusMenuItem parent;

    WifiSwitcherPrivate *priv;
};

struct _WifiSwitcherClass
{
    HDStatusMenuItemClass parent;
};

GType wifi_switcher_get_type (void);

G_END_DECLS

#endif

