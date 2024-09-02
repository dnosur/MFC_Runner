// StartGameDlg.cpp: файл реализации
//

#include "pch.h"
#include "Runner.h"
#include "afxdialogex.h"
#include "StartGameDlg.h"


// Диалоговое окно StartGameDlg

IMPLEMENT_DYNAMIC(StartGameDlg, CDialogEx)

void StartGameDlg::SetSlider(int& value, int sliderId, int staticId, int sliderSize)
{
	CSliderCtrl* slider = (CSliderCtrl*)GetDlgItem(sliderId);
	CStatic* label = (CStatic*)GetDlgItem(staticId);

	slider->SetRange(0, sliderSize);
	value = slider->GetPos();

	CString str;
	str.Format(L"%d", value);
	label->SetWindowTextW(str);
}

void StartGameDlg::SetSliderPos(int value, int sliderId, int staticId, int sliderSize)
{
	CSliderCtrl* slider = (CSliderCtrl*)GetDlgItem(sliderId);
	CStatic* label = (CStatic*)GetDlgItem(staticId);

	slider->SetRange(0, sliderSize);
	slider->SetPos(value);

	CString str;
	str.Format(L"%d", value);
	label->SetWindowTextW(str);
}

StartGameDlg::StartGameDlg(
	int speed, int maxSpeed, 
	int minObstacleDistance, int maxObstacleDistance, 
	int downSlideSpeed, 
	CWnd* pParent
) : speed(speed), maxSpeed(maxSpeed),
	minObstacleDistance(minObstacleDistance), maxObstacleDistance(maxObstacleDistance),
	downSlideSpeed(downSlideSpeed),
	success(false),
	CDialogEx(IDD_DIALOG1, pParent)
{
}

StartGameDlg::~StartGameDlg()
{
}

void StartGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(StartGameDlg, CDialogEx)
	ON_WM_ACTIVATE()
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SPEED_SLIDER, &StartGameDlg::OnNMCustomdrawSpeedSlider)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_MAX_SPEED_SLIDER, &StartGameDlg::OnNMCustomdrawMaxSpeedSlider)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_MIN_OBSTALCE_DISTANCE_SLIDER, &StartGameDlg::OnNMCustomdrawMinObstalceDistanceSlider)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_MAX_OBSTALCE_DISTANCE_SLIDER, &StartGameDlg::OnNMCustomdrawMaxObstalceDistanceSlider)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_DOWN_SLIDE_SPEED_SLIDER, &StartGameDlg::OnNMCustomdrawDownSlideSpeedSlider)
	ON_BN_CLICKED(IDOK, &StartGameDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &StartGameDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// Обработчики сообщений StartGameDlg


void StartGameDlg::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CDialogEx::OnActivate(nState, pWndOther, bMinimized);

	SetSliderPos(speed, IDC_SPEED_SLIDER, IDC_SPEED_EDIT, 100);
	SetSliderPos(maxSpeed, IDC_MAX_SPEED_SLIDER, IDC_MAX_SPEED_EDIT, 30);

	SetSliderPos(minObstacleDistance, IDC_MIN_OBSTALCE_DISTANCE_SLIDER, IDC_MIN_OBSTALCE_DISTANCE, 1000);
	SetSliderPos(minObstacleDistance, IDC_MAX_OBSTALCE_DISTANCE_SLIDER, IDC_MAX_OBSTALCE_DISTANCE, 1000);

	SetSliderPos(downSlideSpeed, IDC_DOWN_SLIDE_SPEED_SLIDER, IDC_DOWN_SLIDE_SPEED_EDIT, 20);
}


void StartGameDlg::OnNMCustomdrawSpeedSlider(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	SetSlider(speed, IDC_SPEED_SLIDER, IDC_SPEED_EDIT, 100);
	*pResult = 0;
}


void StartGameDlg::OnNMCustomdrawMaxSpeedSlider(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	SetSlider(maxSpeed, IDC_MAX_SPEED_SLIDER, IDC_MAX_SPEED_EDIT, 30);
	*pResult = 0;
}


void StartGameDlg::OnNMCustomdrawMinObstalceDistanceSlider(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	SetSlider(minObstacleDistance, IDC_MIN_OBSTALCE_DISTANCE_SLIDER, IDC_MIN_OBSTALCE_DISTANCE, 1000);
	*pResult = 0;
}


void StartGameDlg::OnNMCustomdrawMaxObstalceDistanceSlider(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	SetSlider(minObstacleDistance, IDC_MAX_OBSTALCE_DISTANCE_SLIDER, IDC_MAX_OBSTALCE_DISTANCE, 1000);
	*pResult = 0;
}


void StartGameDlg::OnNMCustomdrawDownSlideSpeedSlider(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	SetSlider(downSlideSpeed, IDC_DOWN_SLIDE_SPEED_SLIDER, IDC_DOWN_SLIDE_SPEED_EDIT, 20);
	*pResult = 0;
}


void StartGameDlg::OnBnClickedOk()
{
	success = true;
	CDialogEx::OnOK();
}


void StartGameDlg::OnBnClickedCancel()
{
	success = false;
	CDialogEx::OnCancel();
}
