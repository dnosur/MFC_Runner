#pragma once
#include "afxdialogex.h"


// Диалоговое окно StartGameDlg

class StartGameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(StartGameDlg)

	void SetSlider(int& value, int sliderId, int staticId, int sliderSize = 30);
	void SetSliderPos(int value, int sliderId, int staticId, int sliderSize = 30);

	int speed, maxSpeed;
	int minObstacleDistance, maxObstacleDistance;

	int downSlideSpeed;

	bool success;
public:
	StartGameDlg(
		int speed, int maxSpeed, 
		int minObstacleDistance, int maxObstacleDistance, 
		int downSlideSpeed, 
		CWnd* pParent = nullptr
	);   // стандартный конструктор
	virtual ~StartGameDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnNMCustomdrawSpeedSlider(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMCustomdrawMaxSpeedSlider(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMCustomdrawMinObstalceDistanceSlider(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMCustomdrawMaxObstalceDistanceSlider(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMCustomdrawDownSlideSpeedSlider(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
