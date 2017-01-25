# 433mhz
Library for controlling simple 433mhz transmitter/receiver modules with the Raspberry Pi

Build Dependencies:
* [wiringPi](http://wiringpi.com/) - available on Raspbian as wiringpi
* [tclap](http://tclap.sourceforge.net/) - available on Raspbian as [libtclap-dev](https://packages.debian.org/stable/devel/libtclap-dev)

Run Dependencies:
* wiringPi

Tested Environments:
* Raspbian on Raspberry Pi model B rev 2

To Install:
* Copy www directory contents into /var/www/
* Copy codesend executable into /var/www/bin/
* Configure apache to serve that folder. (Good luck)
* Note: If installing somewhere other than /var/www/ be sure to change the path at the top of www/toggle.php to reflect the actual location.
