#!/bin/sh
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

print_msg()
{
	run-standalone.sh dbus-send --print-reply  \
		--type=method_call --dest=org.freedesktop.Notifications  \
		/org/freedesktop/Notifications org.freedesktop.Notifications.SystemNoteDialog \
		string:"$1" uint32:0 string:'$2';
}

if_failed_print_and_die()
{
	if [ $? -ne "0" ] ; then
		print_msg "CANNOT $action WLAN: $step FAILED" "KO";
		exit 1;
	fi;
}

out=`ifconfig wlan0`
if [ "x$?" = "x0" ] ; then
	# wlan is up
	action="DISABLE";
	if [ `echo "$out" | grep -c "RUNNING"` -gt "0" ] ; then
		# Disconnect it
		run-standalone.sh dbus-send --system \
			--dest=com.nokia.icd /com/nokia/icd_ui com.nokia.icd_ui.disconnect boolean:true;
	fi;
	# sleep 3
	# Setting ip to 0.0.0.0 is needed to reset ip-monitoring widgets.
	# Put Down the interface  to run hooks in /etc/network/if-*down.d, ignore errors if any.
	ifconfig wlan0 0.0.0.0 down;
	# Remove the module
	step="RMMOD";
	rmmod wl12xx;
	if_failed_print_and_die;
	# No need to stop/start/restart wlancond here.
	print_msg "WIRELESS LAN DISABLED" "OK";
	exit 2
else
	# wlan is not configured, reload modules 
	action="ENABLE";
	step="MODPROBE";
	modprobe wl12xx;
	if_failed_print_and_die;
	# Calibrate: do not remove this. It is needed even if 'start wlancond'
	# triggers one more calibration later
	step="CALIBRATION";
	wl1251-cal;
	if_failed_print_and_die;
	# Restart wlancond properly
	stop wlancond;
	start wlancond;
	# Up the interface, to run hooks in /etc/network/if*/
	step="'IFCONFIG WLAN0 UP'";
	ifconfig wlan0 up;
	if_failed_print_and_die;
	run-standalone.sh dbus-send --print-reply --system \
		--dest=com.nokia.icd_ui /com/nokia/icd_ui com.nokia.icd_ui.show_conn_dlg boolean:false;
	exit 0;
fi;

