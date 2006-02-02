#include "stdafx.h"
#include "resource.h"

#include "DlgSettingsConsole.h"

//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////

DlgSettingsConsole::DlgSettingsConsole(CComPtr<IXMLDOMElement>& pOptionsRoot)
: DlgSettingsBase(pOptionsRoot)
, m_strShell(L"")
, m_strInitialDir(L"")
{
	IDD = IDD_SETTINGS_CONSOLE;
}

//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////

LRESULT DlgSettingsConsole::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/) {

	m_consoleSettings.Load(m_pOptionsRoot);
	m_strShell		= m_consoleSettings.strShell.c_str();
	m_strInitialDir	= m_consoleSettings.strInitialDir.c_str();

	DoDataExchange(DDX_LOAD);
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////

LRESULT DlgSettingsConsole::OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/) {

	EndDialog(wID);
	return 0;
}

//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////

LRESULT DlgSettingsConsole::OnCtlColorStatic(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {


	CWindow		staticCtl(reinterpret_cast<HWND>(lParam));
	CDCHandle	dc(reinterpret_cast<HDC>(wParam));
	DWORD		i;

	for (i = IDC_DEF_00; i <= IDC_DEF_15; ++i) {

		if (staticCtl.m_hWnd == GetDlgItem(i)) {

			CBrush	brush(::CreateSolidBrush(m_consoleSettings.defaultConsoleColors[i-IDC_DEF_00]));
			RECT	rect;

			staticCtl.GetClientRect(&rect);
			dc.FillRect(&rect, brush);
			return 0;
		}
	}

	for (i = IDC_CLR_00; i <= IDC_CLR_15; ++i) {

		if (staticCtl.m_hWnd == GetDlgItem(i)) {

			CBrush	brush(::CreateSolidBrush(m_consoleSettings.consoleColors[i-IDC_CLR_00]));
			RECT	rect;

			staticCtl.GetClientRect(&rect);
			dc.FillRect(&rect, brush);
			return 0;
		}
	}

	bHandled = FALSE;
	return 0;
}

//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////

LRESULT DlgSettingsConsole::OnClickedBtnBrowseShell(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/) {

	CFileDialog fileDialog(
					TRUE, 
					NULL, 
					NULL, 
					OFN_FILEMUSTEXIST|OFN_HIDEREADONLY|OFN_NOCHANGEDIR|OFN_PATHMUSTEXIST, 
					L"Executable Files (*.exe)\0*.exe\0All Files (*.*)\0*.*\0\0");

	if (fileDialog.DoModal() == IDOK) {
		m_strShell = fileDialog.m_szFileName;
		DoDataExchange(DDX_LOAD);
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////

LRESULT DlgSettingsConsole::OnClickedBtnBrowseDir(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/) {

	CFolderDialog folderDialog(m_hWnd, L"Choose initial directory");

	if (folderDialog.DoModal() == IDOK) {
		m_strInitialDir = folderDialog.m_szFolderPath;
		DoDataExchange(DDX_LOAD);
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////

LRESULT DlgSettingsConsole::OnClickedClrBtn(WORD /*wNotifyCode*/, WORD wID, HWND hWndCtl, BOOL& /*bHandled*/) {

	CColorDialog	dlg(m_consoleSettings.consoleColors[wID-IDC_CLR_00], CC_FULLOPEN);

	if (dlg.DoModal() == IDOK) {
		// update color
		m_consoleSettings.consoleColors[wID-IDC_CLR_00] = dlg.GetColor();
		CWindow(hWndCtl).Invalidate();
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////

void DlgSettingsConsole::LoadSettings() {

}

//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////

void DlgSettingsConsole::SaveSettings() {

	DoDataExchange(DDX_SAVE);

	m_consoleSettings.strShell		= LPCTSTR(m_strShell);
	m_consoleSettings.strInitialDir	= LPCTSTR(m_strInitialDir);

	m_consoleSettings.Save(m_pOptionsRoot);
}

//////////////////////////////////////////////////////////////////////////////


