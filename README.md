#TCP-IP Example

This is a simple practise project which was used to learn about building a basic TCP/IP stack for linux in C. This project is a work through of the blog series taken from here:

[www.saminiir.com](http://www.saminiir.com/)

This code is largely based on the source code which accompanies this blog series:

[github.com/saminiir/level-ip](http://github.com/saminiir/level-ip)

##Versions

There are a bunch of tags which corresponds to different posts in the series.

### ARP

This corresponds to the first post in the series. The program does the following:

* Reads incoming from the tun/tap interface
* Processes and responds to ARP requests
* Builds an ARP table from the requests it receives
