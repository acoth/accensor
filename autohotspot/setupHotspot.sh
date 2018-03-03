#!/bin/sh

# This file sets up the pi to use the
# autohotspot script from RaspberryConnect.com
# Every minute, the pi will check whether it sees a known
# wifi network (described in /etc/wpa_supplicant/wpa_supplicant.conf
# and join it if possible.  Otherwise it will create it's own network

apt-get -y install hostapd
apt-get -y install dnsmasq
systemctl disable hostapd
systemctl disable dnsmasq
cp hostapd.conf /etc/hostapd/hostapd.conf
cp hostapd /etc/default/hostapd
cp dnsmasq.conf /etc/
cp autohotspot.service /etc/systemd/system/
systemctl enable autohotspot.service
cp autohotspot /usr/bin/
crontab crontab.txt
reboot
