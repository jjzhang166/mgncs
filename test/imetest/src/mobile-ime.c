/*
 * mobile-ime.c
 *
 *  Created on: 2009-12-19
 *      Author: dongjunjie
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>

#include "mgncs.h"

#include "resource.h"
#include "ncs-windows.h"
#include "mobile-ime.h"


////////////////////////////////////////


static BOOL mMobileIMManager_procIMMsg(mMobileIMManager* self, int message, WPARAM wParam, LPARAM lParam, int *pret)
{
	switch(message)
	{
	case MSG_KEYDOWN:
		if(wParam == SCANCODE_CURSORBLOCKLEFT
				|| wParam == SCANCODE_CURSORBLOCKRIGHT
				|| wParam == SCANCODE_CURSORBLOCKUP
				|| wParam == SCANCODE_CURSORBLOCKDOWN)
			return IME_CONTINUE_MSG; //break the message
		else if(wParam == SCANCODE_3 && (lParam & KS_SHIFT)) // #
		{
			_c(self)->nextIME(self);
			return IME_STOP_MSG;
		}
		break;
	case MSG_CHAR:
		switch(wParam)
		{
		case '2' ... '9':
			break;
		case '0':
			return 0; //let the ime view process it
		}
		break;
	}
	return _SUPER(mIMManager, self, procIMMsg, message, wParam, lParam, pret);
}

static mIME* create_ime(HWND host, mIMEngine* ime_engine)
{
	mDigitIME* ime = NEW(mDigitIME);
	mMainWnd * ime_view;
	_c(ime)->setIMEngine(ime,  ime_engine);
	ime_view = ntCreateIdmImeview(hPackage, host, (DWORD)ime);
	mIME_attach((mIME*)ime, ime_view->hwnd);

	return (mIME*)ime;
}


static  void mMobileIMManager_construct(mMobileIMManager* self, DWORD param)
{
	//create immanger tray window
	//self->hwnd = _c(self)->createTray(self, HWND_DESKTOP);

	//add the imes
	_c(self)->addIME(self, create_ime(HWND_DESKTOP,Class(mDigitPtiEngine).create(NULL, 0)));
	_c(self)->addIME(self, create_ime(HWND_DESKTOP,Class(mDigitPyEngine).create(NULL, 0)));

	_c(self)->setEncoding(self, "UTF-8");
	//_c(self)->setIME(self,"abc*");
	//_c(self)->setIME(self,"pinyin");
}

BEGIN_MINI_CLASS(mMobileIMManager, mIMManager)
	CLASS_METHOD_MAP(mMobileIMManager, construct)
	CLASS_METHOD_MAP(mMobileIMManager, procIMMsg)
END_MINI_CLASS
