#include "../core/net/contiki-net.h"
#include "../core/net/dhcpc.h"
#include "dhcp.h"

PROCESS(dhcp_process, "DHCP");
/*---------------------------------------------------------------------------*/

PROCESS_THREAD(dhcp_process, ev, data)
{
    PROCESS_BEGIN();
    dhcpc_init(uip_ethaddr.addr, sizeof(uip_ethaddr.addr));
    while(1) {
        PROCESS_WAIT_EVENT();
        if(PROCESS_EVENT_DHCP_REQ == ev) {        // send a dhcp request
            dhcpc_request();
        }else if(ev == tcpip_event || ev == PROCESS_EVENT_TIMER) {
            dhcpc_appcall(ev, data);
        } else if(ev == PROCESS_EVENT_EXIT || ev == PROCESS_EVENT_DHCP_CFG){    // already got IP, exiting..
            process_exit(&dhcp_process);
            LOADER_UNLOAD();
        }else if(ev == PROCESS_EVENT_DHCP_UNCFG){
            process_exit(&dhcp_process);
            LOADER_UNLOAD();
        }
    }
    PROCESS_END();
}
/*---------------------------------------------------------------------------*/
void
dhcpc_configured(const struct dhcpc_state *s)
{
    uip_sethostaddr(&s->ipaddr);
    uip_setnetmask(&s->netmask);
    uip_setdraddr(&s->default_router);
    resolv_conf(&s->dnsaddr);
    process_post(PROCESS_CURRENT(), PROCESS_EVENT_DHCP_CFG, NULL);
}
/*---------------------------------------------------------------------------*/
void
dhcpc_unconfigured(const struct dhcpc_state *s)
{
    process_post(PROCESS_CURRENT(), PROCESS_EVENT_DHCP_UNCFG, NULL);
}
/*---------------------------------------------------------------------------*/
