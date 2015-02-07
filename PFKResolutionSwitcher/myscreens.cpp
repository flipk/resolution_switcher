/* -*- Mode:c++; eval:(c-set-style "BSD"); c-basic-offset:4; indent-tabs-mode:t; tab-width:4 -*- */

#include "stdafx.h"
#include "myscreens.h"

using namespace PFKResolutionSwitcher;
using namespace System;
using namespace System::Runtime::InteropServices;

namespace SysWin32
{
	// return false if failure
	[DllImport("user32.dll",CharSet = CharSet::Ansi)]
	extern bool EnumDisplayDevices(
		char* lpDevice,
		int iDevNum,
		DISPLAY_DEVICE* lpDisplayDevice,
		int dwFlags);

	[DllImport("user32.dll",CharSet = CharSet::Ansi)]
	extern bool EnumDisplaySettings(
		char *lpszDeviceName,
		int iModeNum,
		DEVMODE *lpDevMode);
};

aScreen::aScreen(int index)
{
	int ind;
	bool done, res;
	DEVMODE * pdm = 0;
	DEVMODE * dm = 0;

	modes = 0;
	dev = new DISPLAY_DEVICE;
	dev->cb = sizeof(DISPLAY_DEVICE);
	res = SysWin32::EnumDisplayDevices((char*)0, index, 
		dev, EDD_GET_DEVICE_INTERFACE_NAME);
	if (res && (dev->StateFlags & DISPLAY_DEVICE_ACTIVE))
	{
		name = gcnew System::String(dev->DeviceName);
		flags = dev->StateFlags;
		done = false;
		for (ind = 0; !done; ind++)
		{
			// if this is first, or if the previous
			// went unused, reuse it.
			if (!dm)
				dm = new DEVMODE;
			dm->dmSize = sizeof(DEVMODE);
			dm->dmDriverExtra = 0;
			res = SysWin32::EnumDisplaySettings(
				dev->DeviceName, ind, dm);
			if (res)
			{
				bool useit = true;
				// only support 32bpp and 60hz
				if (dm->dmBitsPerPel != 32)
					useit = false;
				if (dm->dmDisplayFrequency != 60)
					useit = false;
				if (pdm &&
					dm->dmPelsWidth == pdm->dmPelsWidth &&
					dm->dmPelsHeight == pdm->dmPelsHeight)
				{
					useit = false;
				}
				if (useit)
				{
					dm->next = 0;
					if (pdm)
						pdm->next = dm;
					else
						modes = dm;
					pdm = dm;
					dm = 0;
				}
				// else, reuse dm in the next entry
			}
			else
				done = true;
		}
		// free up the last unused object.
		if (dm)
			delete dm;
	}
}

aScreen::~aScreen(void)
{
	delete dev;
	DEVMODE * dm, * ndm;
	for (dm = modes; dm; dm = ndm)
	{
		ndm = dm->next;
		delete dm;
	}
}

System::String ^
aScreen::getinfo(void)
{
	DEVMODE * dm;
	int ind;
	System::String ^ ret =
		"name=" + name + "; flags=" + flags.ToString() + "; ";

	for (ind = 0, dm = modes; dm; dm = dm->next, ind++)
	{
		System::String ^ i =
			"\r\n\t" + ind.ToString()
			+ ": " + dm->dmPelsWidth.ToString()
			+ "x" + dm->dmPelsHeight.ToString();
		ret = ret + i;
	}

	return ret;
}

//static
aScreen ^
aScreen :: getScreen(int index)
{
	return gcnew aScreen(index);
}
