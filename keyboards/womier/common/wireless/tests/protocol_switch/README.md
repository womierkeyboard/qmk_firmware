# protocol_switch

Host-side test (gcc only, no hardware) for `set_transport()` in `../../transport.c`.
Run `./run.sh`. It checks, with and without `KEEP_USB_CONNECTION_IN_WIRELESS_MODE`,
that USB -> wireless -> USB leaves the shared HID protocol state correct for a host in
Boot or Report protocol. The NKRO check mirrors the predicate in `tmk_core/protocol/report.c`.
