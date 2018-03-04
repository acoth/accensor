# Autohotspot Instructions
This directory contains files and a script which should set up your Pi to automatically switch between joining a WiFi network and creating one, based on whether it sees a known network in range.  It is based on a nice script from [RaspberryConnect](http://www.raspberryconnect.com/network/item/331-raspberry-pi-auto-wifi-hotspot-switch-direct-connection)

Assuming your setup is as I gave it to you:

 1. Plug in the Accensor and wait for it to boot.  You can tell it has booted when the clock face starts showing an (incorrect) time
 2. While you wait, get this directory on your laptop.  (You'll need to download it before switching your WiFi in the next step)
 3. On your laptop, join the WiFi network it is generating.  The SSID is one of `Accensor[0-9]`, and the password is `LetThereBeLight`
 4. Copy the directory to the Pi: `scp -r path/to/autohotspot/ pi@192.168.17.1:` The password is `RhubarbAppleTarragon`.
 5. SSH into it: `ssh pi@192.168.17.1`
 6. Tell the Pi about your home WiFi: `sudo emacs /etc/wpa_supplicant/wpa_supplicant.conf` (vi and nano are also installed if you prefer).  Just replace my home network's SSID and password with yours.
 7. `cd ~/autohotspot`
 8.  Running the script should now do everything you need: `sudo ./setupHotspot.sh`.  It will overwrite some configuration files, install and enable the autohotspot tool, and setup a cron job to check for known networks once a minute, then it will reboot the Pi.
 9. Once the reboot is complete, if everything went well, the Pi will be on the network you told it about in step 6.  If your router allows DDNS, you should be able to get to it at the hostname `accensor-X` where `X` is whatever number you had in step 3.
 10. If something went wrong, or you are out of range of that WiFi, the Pi should (within a minute) start creating the `Accensor` (no number now) network, on which it will have the IP `10.0.17.1` 
