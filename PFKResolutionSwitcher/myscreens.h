/* -*- Mode:c++; eval:(c-set-style "BSD"); c-basic-offset:4; indent-tabs-mode:t; tab-width:4 -*- */

#include "stdafx.h"

namespace PFKResolutionSwitcher {
	//forward decl
	ref class Form1;
};

namespace PFKResolutionSwitcher {

struct DISPLAY_DEVICE
{
	int cb;
	char DeviceName[32];
	char DeviceString[128];
	int StateFlags;
	char DeviceID[128];
	char DeviceKey[128];
};

// stateflags:
#define DISPLAY_DEVICE_ACTIVE 1
// DISPLAY_DEVICE_MIRRORING_DRIVER
// DISPLAY_DEVICE_MODESPRUNED
#define DISPLAY_DEVICE_PRIMARY_DEVICE 4
// DISPLAY_DEVICE_REMOVABLE
// DISPLAY_DEVICE_VGA_COMPATIBLE

#define EDD_GET_DEVICE_INTERFACE_NAME 0x00000001

#define WORD unsigned short
#define DWORD unsigned int
#define LONG long

struct POINTL {
  LONG x;
  LONG y;
};

struct DEVMODE {
  char dmDeviceName[32/*CCHDEVICENAME*/];
  WORD  dmSpecVersion;
  WORD  dmDriverVersion;
  WORD  dmSize;
  WORD  dmDriverExtra;
  DWORD dmFields;
  union {
    struct {
      short dmOrientation;
      short dmPaperSize;
      short dmPaperLength;
      short dmPaperWidth;
      short dmScale;
      short dmCopies;
      short dmDefaultSource;
      short dmPrintQuality;
    };
    struct {
      POINTL dmPosition;
      DWORD  dmDisplayOrientation;
      DWORD  dmDisplayFixedOutput;
    };
  };
  short dmColor;
  short dmDuplex;
  short dmYResolution;
  short dmTTOption;
  short dmCollate;
  char dmFormName[32/*CCHFORMNAME*/];
  WORD  dmLogPixels;
  DWORD dmBitsPerPel;
  DWORD dmPelsWidth;
  DWORD dmPelsHeight;
  union {
    DWORD dmDisplayFlags;
    DWORD dmNup;
  };
  DWORD dmDisplayFrequency;
  DWORD dmICMMethod;
  DWORD dmICMIntent;
  DWORD dmMediaType;
  DWORD dmDitherType;
  DWORD dmReserved1;
  DWORD dmReserved2;
  DWORD dmPanningWidth;
  DWORD dmPanningHeight;
};
#define ENUM_CURRENT_SETTINGS -1

	ref class aScreen;
	public ref class aScreenMode
	{
	public:
		aScreenMode(aScreen ^ scr, aScreenMode ^ prev, int index);
		~aScreenMode(void);
		bool good;
		bool done;
		bool current;
		DEVMODE * mode;
		aScreen ^ screen;
		System::String ^ name;
		System::String ^ getInfo(void);
		bool sameMode(aScreenMode ^ other);
		PFKResolutionSwitcher::Form1 ^ form1;
		System::Void btnClicked(System::Object^  sender, System::EventArgs^  e);
	};

	public ref class aScreen
	{
	public:
		aScreen(int index);
		~aScreen(void);
		bool good;
		bool done;
		DISPLAY_DEVICE * dev;
		System::String ^ getInfo(void);
		System::String ^ name;
		System::Collections::Generic::List<aScreenMode^> ^ modes;
	};

	public ref class allScreens
	{
	public:
		allScreens(void);
		~allScreens(void);
		System::Collections::Generic::List<aScreen^> ^ screens;
		System::String ^ getInfo(void);
	};
};
