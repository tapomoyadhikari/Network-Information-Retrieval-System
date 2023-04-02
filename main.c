#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<net/if.h>
#include<net/if_arp.h>
#include<sys/ioctl.h>
#include<netinet/in.h>

#define MAX_INTERFACES 16
int main()
{
    int sockfd;
    struct ifreq ifr[MAX_INTERFACES];
    struct ifconf ifc;
    char buffer[1024];
    struct sockaddr_in *s_in;
    int i;

    // Create a socket that we'll use to get the info
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
    {
        perror("socket");
        exit(1);
    }

    // Get the list of interfaces
    ifc.ifc_len = sizeof(ifr);
    ifc.ifc_buf = (caddr_t)ifr;
    if (ioctl(sockfd, SIOCGIFCONF, &ifc) < 0)
    {
        perror("ioctl");
        exit(1);
    }

    // Get the MAC address of each interface
    int num_interfaces = ifc.ifc_len / sizeof(struct ifreq);
    printf("Number of network interfaces configured: %d\n", num_interfaces);
    printf("\n");
    for (i = 0; i < num_interfaces; i++)
    {
        printf("Interface %d:\n", i);
        printf("  Name: %s\n", ifr[i].ifr_name);

        // Get the MAC address
        if (ioctl(sockfd, SIOCGIFHWADDR, &ifr[i]) < 0)
        {
            perror("ioctl");
            exit(1);
        }
        printf("  MAC Address: %.2X:%.2X:%.2X:%.2X:%.2X:%.2X\n",
            (unsigned char)ifr[i].ifr_hwaddr.sa_data[0],
            (unsigned char)ifr[i].ifr_hwaddr.sa_data[1],
            (unsigned char)ifr[i].ifr_hwaddr.sa_data[2],
            (unsigned char)ifr[i].ifr_hwaddr.sa_data[3],
            (unsigned char)ifr[i].ifr_hwaddr.sa_data[4],
            (unsigned char)ifr[i].ifr_hwaddr.sa_data[5]);

        // Get the IP address
        if (ioctl(sockfd, SIOCGIFADDR, &ifr[i]) < 0)
        {
            perror("ioctl");
            exit(1);
        }
        s_in = (struct sockaddr_in *)&ifr[i].ifr_addr;
        strcpy(buffer, inet_ntoa(s_in->sin_addr));
        printf("  IP Address: %s\n", buffer);

        // Get the IPv6 address
        if (ioctl(sockfd, SIOCGIFADDR, &ifr[i]) < 0)
        {
            perror("ioctl");
            exit(1);
        }
        s_in = (struct sockaddr_in *)&ifr[i].ifr_addr;
        strcpy(buffer, inet_ntop(AF_INET6, &s_in->sin_addr, buffer, sizeof(buffer)));
        printf("  IPv6 Address: %s\n", buffer);

        // Get the username
        char username[1024];
        getlogin_r(username, sizeof(username));
        printf("  Username: %s\n", username);

        // Get the location
        char location[1024];
        getcwd(location, sizeof(location));
        printf("  Location: %s\n", location);

        printf("\n");
    }

    return 0;
}
