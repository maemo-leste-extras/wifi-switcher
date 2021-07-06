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
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <gtk/gtk.h>
#include <hildon/hildon.h>
#include <gmodule.h>

#include "wifi-switcher-statusbar.h"

#define WIFI_SWITCHER_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE (obj, \
							TYPE_WIFI_SWITCHER, WifiSwitcherPrivate))

struct _WifiSwitcherPrivate
{
	GtkWidget *button;
	gpointer data;
};

HD_DEFINE_PLUGIN_MODULE (WifiSwitcher, wifi_switcher, HD_TYPE_STATUS_MENU_ITEM)

static void wifi_switcher_cb (gpointer, gpointer);

static void wifi_switcher_class_finalize (WifiSwitcherClass *klass) {}

static void wifi_switcher_class_init (WifiSwitcherClass *klass)
{
	g_type_class_add_private (klass, sizeof (WifiSwitcherPrivate));
}

/** Check if wifi module is loaded
    @return One if wifi module is loaded, zero otherwise
*/
static int check_wifi_module_loaded()
{
	int module_loaded = 0;
	char *lineptr = NULL;
	size_t res_sz;
	FILE *fp = fopen("/proc/modules", "r");

	if (fp) {
		while (getline(&lineptr, &res_sz, fp) != -1) {
			if (strncmp("wl12xx ", lineptr, 7) == 0) {
				module_loaded = 1;
				break;
			}
		}
		free(lineptr);
		fclose (fp);
	}
	return module_loaded;
}

/** Set Wifi button text according to wifi module state
	@param priv Pointer to WifiSwitcherPrivate structure
*/
static void set_wifi_button_text(WifiSwitcherPrivate *priv)
{
	const char *subtext = check_wifi_module_loaded() ? "On" : "Off";
	hildon_button_set_text (HILDON_BUTTON (priv->button),
				"Wireless LAN",
				subtext);
}

static void wifi_switcher_init (WifiSwitcher *plugin)
{
	WifiSwitcherPrivate *priv = WIFI_SWITCHER_GET_PRIVATE (plugin);
	
	GtkWidget *image = gtk_image_new_from_file ("/usr/share/icons/hicolor/scalable/hildon/kwifimanager_big.png");

	priv->button = hildon_button_new (HILDON_SIZE_FINGER_HEIGHT, HILDON_BUTTON_ARRANGEMENT_VERTICAL);

	hildon_button_set_style (HILDON_BUTTON(priv->button), HILDON_BUTTON_STYLE_PICKER);
	hildon_button_set_image (HILDON_BUTTON(priv->button), image);
	set_wifi_button_text(priv);
	hildon_button_set_alignment (HILDON_BUTTON(priv->button), 0.0, 0.0, 1.0, 1.0);

	g_signal_connect_after (G_OBJECT (priv->button), "clicked", G_CALLBACK (wifi_switcher_cb), plugin);
	gtk_container_add (GTK_CONTAINER (plugin), GTK_WIDGET(priv->button));
	gtk_widget_show_all (GTK_WIDGET(plugin));
}

static gboolean run(gpointer plugin)
{
	WifiSwitcherPrivate *priv = WIFI_SWITCHER_GET_PRIVATE (plugin);
	int status =  WEXITSTATUS(system("sudo /usr/sbin/wifi.sh"));
	GdkPixbuf *pixbuf = NULL;

	/* Update wifi button text */
	set_wifi_button_text(priv);

	if (status == 2) {
		/* Put the icon at the status bar*/	
		pixbuf = gdk_pixbuf_new_from_file_at_size ("/usr/share/icons/hicolor/scalable/hildon/wlan_off.png",
																STATUS_AREA_WIFI_SWITCHER_ICON_SIZE,
																STATUS_AREA_WIFI_SWITCHER_ICON_SIZE,
																NULL);
		if (pixbuf) {
			hd_status_plugin_item_set_status_area_icon (HD_STATUS_PLUGIN_ITEM (plugin), pixbuf);
			g_object_unref (pixbuf);
		}
	} else if (status == 0) {
		/* unset tray icon if set */
		hd_status_plugin_item_set_status_area_icon (HD_STATUS_PLUGIN_ITEM (plugin), NULL);
	}
	// else {
	// /* Helper script already displayed a error dialog, do nothing */
	//}
	return FALSE;
}

static void wifi_switcher_cb (gpointer instance, gpointer plugin)
{
	g_idle_add(run, plugin);
}
