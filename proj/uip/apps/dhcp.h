
#ifndef _APPS_DHCP_H_
#define _APPS_DHCP_H_

#define PROCESS_EVENT_DHCP_REQ        0x01        // send request
#define PROCESS_EVENT_DHCP_CFG        0x02        // dhcp configured
#define PROCESS_EVENT_DHCP_UNCFG      0x03        // dhcp configured

PROCESS_NAME(dhcp_process);

#endif

