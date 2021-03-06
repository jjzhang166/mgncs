/**
 * \file miconview.h
 * \author XiaoweiYan
 * \date 2009/06/13
 *
 * This file includes the definition of IconView.
 *
 \verbatim

    Copyright (C) 2009 Feynman Software.

    All rights reserved by Feynman Software.

    This file is part of mgncs, which is new control 
    set of MiniGUI.

  	\endverbatim
 */

/**
 * $Id: miconview.h 726 2009-12-21 01:57:37Z xwyan $
 *
 *      Copyright (C) 2009 Feynman Software.
 */

#ifndef _MGUI_CTRL_ICONV_H
#define _MGUI_CTRL_ICONV_H
 

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

/**
 * \defgroup Widget_IconView mIconView
 * @{
 */

/** 
 * Structure of the iconview item info, contains information about an item.
 * This structure is used for creating or retrieving an item. 
 */
typedef struct _NCS_ICONV_ITEMINFO
{
    /**
     * The index of the item
     */
    int index;

    /**
     * The bitmap icon of the item
     */
    PBITMAP bmp;

    /**
     * The text label of the item
     */
    const char *label;

    /** Attached additional data of this item */
    DWORD addData;
}NCS_ICONV_ITEMINFO;

typedef struct _mIconView mIconView;
typedef struct _mIconViewClass mIconViewClass;
typedef struct _mIconViewRenderer mIconViewRenderer;

/**
 * \def NCSCTRL_ICONVIEW
 * \brief The control class name of mIconView.
 */
#define NCSCTRL_ICONVIEW NCSCLASSNAME("iconview")

/**
 * \def NCSS_ICONV_SHIFT
 * \brief The bits used by mIconView in style.
 */
#define NCSS_ICONV_SHIFT     (NCSS_SCRLV_SHIFT)

/**
 * \def NCSS_ICONV_SORT
 * \sa NCSS_ITEMV_AUTOSORT
 */
#define NCSS_ICONV_SORT      NCSS_ITEMV_AUTOSORT

/**
 * \def NCSS_ICONV_LOOP
 * \sa NCSS_ITEMV_LOOP
 */
#define NCSS_ICONV_LOOP      NCSS_ITEMV_LOOP

#define mIconViewHeader(className)  \
    mItemViewHeader(className)      \
    int defItemWidth;               \
    int nrCol;                      \
    DWORD flags;

/**
 * \struct mIconView
 * \brief The structure of mItemView control, which derived from
 *        mScrollWidget. It is the abstract superclass of all classes
 *        which represent controls that have items.
 *
 *  - defItemWidth\n
 *    The default icon width.
 *
 *  - nrCol\n
 *    The number of column.
 *
 *  - flags\n
 *    The iconview flags.
 */
struct _mIconView
{
	mIconViewHeader(mIconView)
};

#define mIconViewClassHeader(clsName, parentClass)          \
    mItemViewClassHeader(clsName, parentClass)              \
    void (*setIconSize)(clsName*, int width, int height);   \
    HITEM (*addItem)(clsName*, NCS_ICONV_ITEMINFO *info, int *pos);


struct _mIconViewClass
{
	mIconViewClassHeader(mIconView, mItemView)
};

/**
 * \struct mIconViewClass
 * \brief The virtual function table of mIconView, which derived from
 *        mItemViewClass.
 *
 * - void (*\b setIconSize)(mIconView *self, int width, int height);\n
 *   Sets the icon size.
 *
 * - HITEM (*\b addItem)(mIconView *self, \ref NCS_ICONV_ITEMINFO *info, int *pos);\n
 *   Add a new item according to \a info to iconview.
 *      \param info     The item information.
 *      \param pos      The position in which item has been inserted. It can be NULL.
 *      \return         The handle to new item.
 */
#define mIconViewRendererHeader(clsName, parentClass) \
	mItemViewRendererHeader(clsName, parentClass)

/**
 * \struct mIconViewRenderer
 * \brief The structure of mIconView renderer, which derived
 *        from mItemViewRenderer.
 */
struct  _mIconViewRenderer {
	mIconViewRendererHeader(mIconView, mItemView)
};

/**
 * \enum mIconViewProp
 * \brief The properties id of mIconView.
 */
enum mIconViewProp
{
    /**
     * The default icon height.
     */
	NCSP_ICONV_DEFICONHEIGHT = NCSP_ITEMV_DEFITEMHEIGHT,

    /**
     * The default icon width.
     */
	NCSP_ICONV_DEFICONWIDTH = NCSP_ITEMV_MAX + 1,
    /**
     * The maximum value of mIconView properties id.
     */
    NCSP_ICONV_MAX,
};

/**
 * \enum mIconViewNotify
 * \brief The notification code id of mIconView.
 */
enum mIconViewNotify
{
    NCSN_ICONV_CLICKED = NCSN_ITEMV_CLICKED,
    NCSN_ICONV_SELCHANGED = NCSN_ITEMV_SELCHANGED,
    /**
     * The maximum value of mIconView notification code id.
     */
    NCSN_ICONV_MAX = NCSN_ITEMV_MAX + 1,
};

/**
 * \var g_stmIconViewCls
 * \brief The instance of mIconViewClass.
 *
 * \sa mIconViewClass
 */
MGNCS_EXPORT extern mIconViewClass g_stmIconViewCls;
    /** @} end of Widget_IconView */

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif /* _MGUI_CTRL_ICONV_H */
