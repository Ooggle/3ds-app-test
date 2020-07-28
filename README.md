# 3ds-app-test
simple 3DS Homebrew made with libctru and citro2d.

## Build

This project works with the default 3ds devkitpro installation.
At this state, this is still fullfilled with bugs and disgraceful tricks.

To test the app, you can do the following on Linux:
```sh
// build
git clone https://github.com/Ooggle/3ds-app-test && cd 3ds-app-test
make

// upload the app using 3dslink
$DEVKITPRO/tools/bin/3dslink -a {IP} 3ds-app-test.3dsx
```
