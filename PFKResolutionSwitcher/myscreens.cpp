/* -*- Mode:c++; eval:(c-set-style "BSD"); c-basic-offset:4; indent-tabs-mode:t; tab-width:4 -*- */

#include "stdafx.h"
#include "myscreens.h"

using namespace PFKResolutionSwitcher;
using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Collections;

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

allScreens::allScreens(void)
{
	screens = gcnew System::Collections::Generic::List<aScreen^>;
	int ind;
	bool done = false;
	for (ind = 0; !done; ind++)
	{
		aScreen ^ scr = gcnew aScreen(ind);
		if (scr->good)
			screens->Add(scr);
		done = scr->done;
	}
}

allScreens::~allScreens(void)
{
	// nothing to do
}

System::String ^
allScreens::getInfo(void)
{
	System::String ^ ret = "";
	for each (aScreen ^ scr in screens)
		ret += scr->getInfo();
	return ret;
}

aScreen::aScreen(int index)
{
	bool res, modes_done;
	int mode_index;
	aScreenMode ^ mode;
	aScreenMode ^ prevMode;

	dev = new DISPLAY_DEVICE;
	modes = gcnew System::Collections::Generic::List<aScreenMode^>;

	dev->cb = sizeof(DISPLAY_DEVICE);
	res = SysWin32::EnumDisplayDevices(
		(char*)0, index, dev, EDD_GET_DEVICE_INTERFACE_NAME);
	if (res)
	{
		if (dev->StateFlags & DISPLAY_DEVICE_ACTIVE)
		{
			good = true;
			name = gcnew System::String(dev->DeviceName);
			for (modes_done = false, mode_index = 0;
				!modes_done;
				mode_index++)
			{
				mode = gcnew aScreenMode(this, prevMode, mode_index);
				if (mode->good)
				{
					modes->Add(mode);
					mode->screen = this;
					prevMode = mode;
				}
				modes_done = mode->done;
			}
		}
		else
		{
			good = false;
		}
		done = false;
	}
	else
	{
		good = false;
		done = true;
	}
}

aScreen::~aScreen(void)
{
	delete dev;
}

System::String ^
aScreen::getInfo(void)
{
	System::String ^ ret;
	ret = "Screen:" + name + "; modes: ";
	for each (aScreenMode ^ mode in modes)
		ret += mode->getInfo() + " ";
	ret += "\r\n";
	return ret;
}

aScreenMode::aScreenMode(aScreen ^ scr, aScreenMode ^ prev, int index)
{
	bool res;

	mode = new DEVMODE;
	mode->dmSize = sizeof(DEVMODE);
	mode->dmDriverExtra = 0;
	res = SysWin32::EnumDisplaySettings(
		scr->dev->DeviceName, index, mode);
	if (res)
	{
		if (mode->dmBitsPerPel != 32)
			good = false;
		else if (mode->dmDisplayFrequency != 60)
			good = false;
		else if (prev &&
			prev->mode->dmPelsWidth == mode->dmPelsWidth &&
			prev->mode->dmPelsHeight == mode->dmPelsHeight)
			good = false;
		else
			good = true;
		done = false;
	}
	else
	{
		good = false;
		done = true;
	}
	if (good)
	{
		name = mode->dmPelsWidth.ToString()
			+ "x"
			+ mode->dmPelsHeight.ToString();
	}
}

aScreenMode::~aScreenMode(void)
{
	delete mode;
}

System::String ^
aScreenMode::getInfo(void)
{
	return name;
}