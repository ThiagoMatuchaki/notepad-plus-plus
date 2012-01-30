/*
this file is part of notepad++
Copyright (C)2003 Don HO ( donho@altern.org )

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either
version 2 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a Copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

#ifndef DOCUMENTMAP_H
#define  DOCUMENTMAP_H

#ifndef DOCKINGDLGINTERFACE_H
#include "DockingDlgInterface.h"
#endif //DOCKINGDLGINTERFACE_H

#include "documentMap_rc.h"

#define DOCUMENTMAP_SCROLL        (WM_USER + 1)
#define DOCUMENTMAP_MOUSECLICKED  (WM_USER + 2)

class ScintillaEditView;
const bool moveDown = true;
const bool moveUp = false;

enum moveMode {
	perLine,
	perPage
};

class ViewZoneDlg : public StaticDialog
{
public :
	ViewZoneDlg() : StaticDialog() {};

	void doDialog();

    virtual void destroy() {
    };

	void drawZone(long hY, long lY) {
		_higherY = hY;
		_lowerY = lY;
		::InvalidateRect(_viewZoneCanvas, NULL, TRUE);
	};

	int getViewerHeight() const {
		return (_lowerY - _higherY);
	};

	int getCurrentCenterPosY() const {
		return (_lowerY - _higherY)/2 + _higherY;
	};

protected :
	virtual BOOL CALLBACK run_dlgProc(UINT message, WPARAM wParam, LPARAM lParam);

	static BOOL CALLBACK canvasStaticProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
	BOOL CALLBACK canvas_runProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

	void drawPreviewZone(DRAWITEMSTRUCT *pdis);

private :
	HWND _viewZoneCanvas;
	WNDPROC _canvasDefaultProc;
	
	long _higherY;
	long _lowerY;
};


class DocumentMap : public DockingDlgInterface {
public:
	DocumentMap(): DockingDlgInterface(IDD_DOCUMENTMAP), _ppEditView(NULL), _pScintillaEditView(NULL)
	{};

	void init(HINSTANCE hInst, HWND hPere, ScintillaEditView **ppEditView) {
		DockingDlgInterface::init(hInst, hPere);
		_ppEditView = ppEditView;
	};

    virtual void display(bool toShow = true) const {
        DockingDlgInterface::display(toShow);
    };

    void setParent(HWND parent2set){
        _hParent = parent2set;
    };

	void reloadMap();
	void scrollMap();
	void scrollMap(bool direction, moveMode whichMode);

protected:
	virtual BOOL CALLBACK run_dlgProc(UINT message, WPARAM wParam, LPARAM lParam);

private:
	ScintillaEditView **_ppEditView;
	ScintillaEditView *_pScintillaEditView;
	//HWND _glassHandle;
	ViewZoneDlg _vzDlg;
};


#endif // DOCUMENTMAP_H