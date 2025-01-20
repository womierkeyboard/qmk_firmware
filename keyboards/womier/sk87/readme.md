# SK87
[![SK87](https://s21.ax1x.com/2025/01/20/pEkH8wd.png)](https://imgse.com/i/pEkH8wd)
A customizable 80% multimodal keyboard.

* Keyboard Maintainer: [jonylee@hfd](https://github.com/jonylee1986)
* Hardware Supported: [SK87](https://womierkeyboard.com/products/womier-sk87)
* Hardware Availability: [womier](http://www.womierkeyboard.com)

Make example for this keyboard (after setting up your build environment):

    make womier/sk87:default

Flashing example for this keyboard:

    make womier/sk87:default:flash
    
See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Bootmagic reset**: Hold down the Hold down the top left key (commonly programmed as *Esc*) and plug in the keyboard
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
