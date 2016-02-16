MobilECG II
===========

MobilECG II is an open source clinical grade Holter ECG. For more information, please visit http://mobilecg.hu.

NOTE: this is only a preliminary release. It contains known bugs, but its main structure will remain the same. There is no stable branch yet. Development occours on master. When a stable software is released, it will be split to separate stable and development branches.

Directory structure
-------------------
```
MobilECG II
├─  CAD - OpenSCAD drawings for the case and other parts
├─  Hardware - the hardware design of MobilECG II
│
├───Software
│    ├─  AndroidApp - Android demo application for resting ECG
│    ├─  Common - Source code used both in firmware and host app
│    └─  Firmware - Firmware running on the microcontroller
|
└───CardECG - Toy, credit card ECG project.

```

How to get one?
---------------

MobilECG is not publicly available yet. In order to sell a medical device, certification is needed. We are working hard to bring MobilECG to the users as soon as possible.

However you can still build one yourself. If you want to build it, feel free to do so. Contact us in case of any problems. There will be soon a technical blog where you will be able to find instructions on bulding one yourself.

Compatibility
-------------

The whole project is built using free or open source tools. The hardware is designed in KiCAD (http://kicad-pcb.org), the firmware compiles with ARM GCC (you can find binaries here: https://launchpad.net/gcc-arm-embedded), CAD files are designed with OpenSCAD (http://www.openscad.org) and 3D printed using MatterControl on a Prusa i3. The development occours on Mac OS X and Linux, building was never tested on Microsoft Windows (and we are not interested in making this software build on Windows except the Windows client app that will be written).

How to support us?
------------------

If you know a doctor or someone with a heart condition, please let them know about our project. Their subscription will help us find investment.

If you are a business angel or an investor, please contact us.

License
-------

The hardware is released under the Creative Commons Attribution-ShareAlike 4.0 International License. All software componens (except Bluetopia, STM32 peripherial libraries,
FreeRTOS, and scmRTOS, which are freely available) are licensed under the GNU Public License v3. If you have any special license requirements, please feel free to contact us.