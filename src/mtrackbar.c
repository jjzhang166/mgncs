/*
**
** mtrackbar.c
**
** wangjian<wangjian@minigui.prg>
**
** 2009-3-16.
**
*/

#include <string.h>

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/fixedmath.h>

#include "mgncsconfig.h"
#include "mcommon.h"
#include "mobject.h"
#include "mcomponent.h"
#include "mwidget.h"
#include "mslider.h"
#include "mtrackbar.h"
#include "mrdr.h"

#include "piece.h"

#define NCSTRB_DEF_MIN          0
#define NCSTRB_DEF_MAX          10
#define NCSTRB_DEF_CUR          0
#define NCSTRB_DEF_LINESTEP     1
#define NCSTRB_DEF_PAGESTEP     5
#define NCSTRB_DEF_TICKFREQ     1

static BOOL mTrackBar_onPiece(mTrackBar *self, mHotPiece * sender, int event_id, DWORD param)
{
	int notif_id = 0;

	switch(event_id)
	{
	case NCSN_SLIDERPIECE_POSCHANGED:
		notif_id = NCSN_TRKBAR_CHANGED;
		break;
	case NCSN_SLIDERPIECE_REACHMAX:
		notif_id = NCSN_TRKBAR_REACHMAX;
		break;
	case NCSN_SLIDERPIECE_REACHMIN:
		notif_id = NCSN_TRKBAR_REACHMIN;
		break;
	default:
		return TRUE;
	}

	if(notif_id > 0)
		ncsNotifyParent((mWidget*)self, notif_id);

	return FALSE;
}

static mObject * mTrackBar_createBody(mTrackBar *self)
{
	RECT rc_thumb={0, 0};
	int event_ids[] = {
		NCSN_SLIDERPIECE_POSCHANGED, 
		NCSN_SLIDERPIECE_REACHMAX,
		NCSN_SLIDERPIECE_REACHMIN,
		0
	};
	DWORD dwStyle = GetWindowStyle(self->hwnd);

	mSliderPiece * sliderPiece = NEWPIECE(mSliderPiece);
	mSliderPiece_setCenterThumb(sliderPiece);
	
	sliderPiece->body = (mHotPiece*)NEWPIECE(mTrackBarPiece);
	sliderPiece->thumb = (mHotPiece*)NEWPIECE(mThumbBoxPiece);

	
	if(dwStyle & NCSS_TRKBAR_VERTICAL)
	{
		rc_thumb.right = VERT_SLIDER_W;
		rc_thumb.bottom = VERT_SLIDER_H;
		_c(sliderPiece)->setProperty(sliderPiece, NCSP_SLIDERPIECE_DIRECTION,1);
	}
	else
	{
		rc_thumb.right = HORZ_SLIDER_W;
		rc_thumb.bottom = HORZ_SLIDER_H;
	}

	if(dwStyle & NCSS_TRKBAR_NOTICK)
		_c(sliderPiece)->setProperty(sliderPiece, NCSP_SLIDERPIECE_TICK, 0);

	if(sliderPiece->thumb)
		_c(sliderPiece->thumb)->setRect(sliderPiece->thumb, &rc_thumb);

	ncsAddEventListeners( (mObject*)sliderPiece, (mObject*)self,(NCS_CB_ONPIECEEVENT)mTrackBar_onPiece, event_ids);
	return (mObject*)sliderPiece;
}

static inline mHotPiece * get_thumb_piece(mTrackBar* self)
{
	mSliderPiece * sliderPiece = (mSliderPiece*)(self->body);
	if(sliderPiece)
		return sliderPiece->thumb;
	return NULL;
}

static void set_thumb_size(mTrackBar *self, int size, BOOL bWidth)
{
	mHotPiece * piece;
	RECT rc;
	piece = get_thumb_piece(self);
	if(!piece || !(_c(piece)->getRect(piece, &rc)))
		return;

	if(bWidth)
	{
		rc.left = (rc.left + rc.right - size) / 2;
		rc.right = rc.left + size;
	}
	else
	{
		rc.top = (rc.top + rc.bottom - size) / 2;
		rc.bottom = rc.top + size;
	}
	_c(piece)->setRect(piece, &rc);
}

static int get_thumb_size(mTrackBar *self, BOOL bwidth)
{
	mHotPiece * piece;
	RECT rc;
	piece = get_thumb_piece(self);
	if(!piece || !(_c(piece)->getRect(piece, &rc)))
		return 0;

	if(bwidth)
		return RECTW(rc);
	else
		return RECTH(rc);
	
}


static BOOL mTrackBar_setProperty (mTrackBar* self, int id, DWORD value)
{
    if (id >= NCSP_TRKBAR_MAX)
        return FALSE;

	switch(id)
	{
	case NCSP_TRKBAR_THUMB_WIDTH:
		set_thumb_size(self, (int)value, TRUE);
		InvalidateRect(self->hwnd, NULL, TRUE);
		return TRUE;
	case NCSP_TRKBAR_THUMB_HEIGHT:
		set_thumb_size(self, (int)value, FALSE);
		InvalidateRect(self->hwnd, NULL, TRUE);
		return TRUE;
	}

	return Class(mSlider).setProperty ((mSlider*)self, id, value);
}

static DWORD mTrackBar_getProperty (mTrackBar* self, int id)
{
	if (id >= NCSP_TRKBAR_MAX)
		return 0;
	
	switch(id)
	{
	case NCSP_TRKBAR_THUMB_WIDTH:
		return get_thumb_size(self, TRUE);
	case NCSP_TRKBAR_THUMB_HEIGHT:
		return get_thumb_size(self, FALSE);
	}

	return Class(mSlider).getProperty ((mSlider*)self, id);
}

BEGIN_CMPT_CLASS (mTrackBar, mSlider)	
    CLASS_METHOD_MAP (mTrackBar, createBody )
	CLASS_METHOD_MAP (mTrackBar, setProperty)
	CLASS_METHOD_MAP (mTrackBar, getProperty)
END_CMPT_CLASS

