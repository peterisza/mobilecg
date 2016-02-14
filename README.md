MobilECG II
===========

MobilECG II is an open source clinical grade Holter ECG. For more information, please visit http://mobilecg.hu.

NOTE: this is only a preliminary release. It contains known bugs, but its main structure will remain the same. There is no stable branch yet. Development occours on master. When a stable software will be released, it will be split to separate stable and development branches.

Directory structure
-------------------
```
MobilECG II
├─  CAD - OpenSCAD drawings for case and other parts
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

However you can still build one yourself. If you want to build it feel free to do so and to contact us in case of any problems. There will be soon a technical blog where you will be able to find instructions on bulding one yourself.

License
-------

The hardware is released under ??? license. All software componens (that are not libraries we used) are licensed under GNU Public License v3. If you have any special license requirements, please feel free to contact us.