===========
TIFS and DM
===========


Device Manager and TI Foundational Security Introduction
========================================================

This is the firmware source for the Device Management & Security
Controller (DMSC), an embedded microcontroller on Texas Instruments SoCs
offering Power, Device, Security, and Resource management services to the
reset of the system.

Overview
========

Traditional Texas Instruments SoCs have implemented system control
functions such as power management within operating systems on each of
the processing units (ARM/DSP). However, such a traditional approach
has had tremendous challenges to ensure system stability. Few of the
challenges faced include:

* Complex interactions between Operating Systems on heterogeneous SoCs for
  generic features.
* Lack of centralized knowledge of system state.
* Consistency in SoC feature entitlement in all OSes for the SoC
  for complex SoC features and system quirks.

Device Management and Security control (DMSC) attempts to resolve
these issues by being a consistent component of Keystone 3 SoC
architecture performing the role of a centralized SoC power, security
and device management controller. In effect, this is a microcontroller
and runs a safety and security certified firmware that provides
services to the rest of the OSes/Software running on various other
processors on the SoC

What to read Next
=================

The following files may be useful in getting started:

* System Firmware build setup :docs/BUILD.rst
* Host build support Libraries: scripts/LIBRARIES.rst
* Coding Style for System Firmware: docs/CODINGSTYLE.rst
* TIFS library integration: docs/TIFS_LIB_INTEGRATION.rst
* TISCI Core Design Document: docs/design/index.rst

Although all documentation can be viewed directly under the `docs` path as
raw reStructuredText, the best way to view the documentation is to run the
following at the top level:

$ make alldocs

and then view docs/sphinx/build/html/index.html in a web browser.
