# Network Information Retrieval System

The Network Information Retrieval System is a software program developed in the C programming language. This system retrieves information about the network interfaces of a machine, including the MAC address, public IPv4 and IPv6 address, username, and location.

## Purpose

The purpose of this system is to provide network administrators and users with an easy way to access important information about their network interfaces. This information can be useful in diagnosing network problems, configuring network settings, and monitoring network activity.

## Methodology

The system uses the Sockets API to create a socket that retrieves information about the network interfaces of a machine. The system then uses the ioctl function to retrieve the MAC address, public IPv4 and IPv6 address, username, and location of each interface. The retrieved information is then printed to the console.

## Implementation

The system uses the following C libraries:

- stdio.h: for input and output operations
- stdlib.h: for memory allocation and deallocation
- string.h: for string manipulation
- net/if.h: for network interface operations
- net/if_arp.h: for ARP protocol operations
- sys/ioctl.h: for I/O control operations
- netinet/in.h: for internet protocol operations

The system creates a socket using the socket function and retrieves information about the network interfaces of a machine using the ioctl function. The system then uses the inet_ntoa and inet_ntop functions to retrieve the IPv4 and IPv6 addresses of each interface. The system also uses the getlogin_r function to retrieve the username and the getcwd function to retrieve the location of each interface.

## Usage

To run the program, compile the source code and run the resulting executable file. The retrieved information will be printed to the console.

