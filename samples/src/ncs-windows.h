/**
 * This file include all the declear of ncs windows
 *
 * Please don't modify it
 * 
 * This file is auto generated by mStudio
 *
 * ANY WORD WRITTEN BY USER WOULD BE DELETE BY MSTUDIO !
 *
 */

#ifndef NCS_MAINWNDS_H
#define NCS_MAINWNDS_H

#ifdef __cpluspus
extern "C" {
#endif

/**
 * please predefine marco NCS_WND_EXPORT 
 * if you want export these ncs main window function
 * to other libraries
 */
#ifndef NCS_WND_EXPORT
#define NCS_WND_EXPORT
#endif

/**
 * Please modify the ncs-window-types.h 
 * if you want pass a speical struct pointer by 'user_data'
 * to a main window
 *
 */
#include "ncs-window-types.h"


/** define the function for ID_MAINWND1 */
extern NCS_WND_EXPORT 
mMainWnd * ntCreateMainwnd1Ex(HPACKAGE package, HWND hParent, HICON h_icon, HMENU h_menu, DWORD user_dat);
#define ntCreateMainwnd1(package, hParent, user_data) \
	ntCreateMainwnd1Ex(package, hParent, (HICON)0, (HMENU)0, (DWORD)(user_data))


/** define the start window */
#define ntStartWindowEx  ntCreateMainwnd1Ex
#define ntStartWindow(package, hParent, user_data) \
	ntStartWindowEx(package, hParent, (HICON)0, (HMENU)0, (DWORD)(user_data))


#ifdef __cplusplus
}
#endif

#endif /* end of window list */

