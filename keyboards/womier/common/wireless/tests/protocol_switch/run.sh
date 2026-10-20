#!/bin/sh
# Host-side check of USB <-> wireless protocol-state handling in transport.c.
# Builds the real transport.c and tmk_core usb_device_state.c against stubbed
# drivers, in both the default and KEEP_USB_CONNECTION_IN_WIRELESS_MODE configs.
set -e
here=$(cd "$(dirname "$0")" && pwd)
root=$(cd "$here/../../../../../.." && pwd)
wls="$root/keyboards/womier/common/wireless"
out=$(mktemp -d)
for def in "" "-DKEEP_USB_CONNECTION_IN_WIRELESS_MODE"; do
    gcc -w $def -I"$here/stubs" -I"$wls" -I"$root/tmk_core/protocol" \
        -o "$out/t" "$here/protocol_switch_test.c" "$root/tmk_core/protocol/usb_device_state.c"
    "$out/t"
done
rm -rf "$out"
