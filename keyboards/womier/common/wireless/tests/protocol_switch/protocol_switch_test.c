#include "quantum.h"
#include "module.h"
#include "transport.h"
#include <assert.h>
USBDriver usbd = {USB_ACTIVE, 0};
static host_driver_t chibios_driver_s, wireless_driver_s, *cur;
host_driver_t chibios_driver, wireless_driver;
bool last_suspend_state;
static uint8_t md_state = 0; uint8_t *md_getp_state(void){return &md_state;}
host_driver_t *host_get_driver(void){return cur;}
void host_set_driver(host_driver_t *d){cur=d;}
void host_keyboard_send(report_keyboard_t*r){} void host_nkro_send(report_nkro_t*r){}
static int restarts; void restart_usb_driver(USBDriver*d){restarts++;}
void usbStop(USBDriver*d){} void usbDisconnectBus(USBDriver*d){} void usbWakeupHost(USBDriver*d){}
void suspend_power_down(void){} void suspend_wakeup_init(void){} bool suspend_wakeup_condition(void){return 0;}
uint32_t sync_timer_read32(void){return 0;} uint32_t sync_timer_elapsed32(uint32_t t){return 0;} void wait_ms(int x){}
void notify_usb_device_state_change_user(struct usb_device_state s){}
#include "transport.c"
static bool nkro_active(bool nkro_cfg){ /* predicate used by tmk_core/protocol/report.c */
    return usb_device_state_get_protocol()==USB_PROTOCOL_REPORT && nkro_cfg; }
#define CHECK(c) do{ printf("  %-62s %s\n", #c, (c)?"ok":"FAIL"); if(!(c)) fails++; }while(0)
int main(void){
    int fails=0; cur=&chibios_driver;
#ifdef KEEP_USB_CONNECTION_IN_WIRELESS_MODE
    puts("== KEEP_USB_CONNECTION_IN_WIRELESS_MODE ==");
#else
    puts("== default (USB restarted on switch) ==");
#endif
    puts("Host negotiated Boot protocol:");
    usb_device_state_set_protocol(USB_PROTOCOL_BOOT);
    CHECK(!nkro_active(true));
    set_transport(TRANSPORT_WLS);
    CHECK(host_get_driver()==&wireless_driver);
    CHECK(usb_device_state_get_protocol()==USB_PROTOCOL_REPORT);
    CHECK(nkro_active(true));
    set_transport(TRANSPORT_USB);
    CHECK(host_get_driver()==&chibios_driver);
#ifdef KEEP_USB_CONNECTION_IN_WIRELESS_MODE
    CHECK(usb_device_state_get_protocol()==USB_PROTOCOL_BOOT);   /* no reset: host's choice honored */
    CHECK(!nkro_active(true));
    CHECK(restarts==0);
#else
    CHECK(usb_device_state_get_protocol()==USB_PROTOCOL_REPORT); /* re-enumerated */
    CHECK(restarts==1);
#endif
    puts("Host negotiated Report protocol:");
    usb_device_state_set_protocol(USB_PROTOCOL_REPORT);
    set_transport(TRANSPORT_WLS); set_transport(TRANSPORT_USB);
    CHECK(usb_device_state_get_protocol()==USB_PROTOCOL_REPORT);
    CHECK(nkro_active(true)); CHECK(!nkro_active(false));
    puts("Repeated WLS->WLS does not clobber saved protocol:");
    usb_device_state_set_protocol(USB_PROTOCOL_BOOT);
    set_transport(TRANSPORT_WLS); set_transport(TRANSPORT_WLS); set_transport(TRANSPORT_USB);
#ifdef KEEP_USB_CONNECTION_IN_WIRELESS_MODE
    CHECK(usb_device_state_get_protocol()==USB_PROTOCOL_BOOT);
#else
    CHECK(usb_device_state_get_protocol()==USB_PROTOCOL_REPORT);
#endif
    printf("%s (%d failures)\n", fails?"FAILED":"PASSED", fails); return fails;
}
