// GameOverDialog.cpp: файл реализации
//

#include "pch.h"
#include "Runner.h"
#include "afxdialogex.h"
#include "GameOverDialog.h"


// Диалоговое окно GameOverDialog

IMPLEMENT_DYNAMIC(GameOverDialog, CDialogEx)

GameOverDialog::GameOverDialog(int score, CWnd* pParent /*=nullptr*/)
	: score(score), CDialogEx(IDD_DIALOG2, pParent)
{

}

GameOverDialog::~GameOverDialog()
{
}

void GameOverDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(GameOverDialog, CDialogEx)
	ON_WM_PAINT()
    ON_BN_CLICKED(IDOK, &GameOverDialog::OnBnClickedOk)
    ON_BN_CLICKED(IDCANCEL, &GameOverDialog::OnBnClickedCancel)
END_MESSAGE_MAP()


// Обработчики сообщений GameOverDialog


void GameOverDialog::OnPaint()
{
    CPaintDC dc(this);

    m_fontGameOver.CreatePointFont(300, _T("Arial"));
    m_colorGameOver = RGB(255, 0, 0);

    m_fontScore.CreatePointFont(200, _T("Arial"));
    m_colorScore = RGB(229, 200, 130);

    m_strScore.Format(_T("Score: %d"), score);

    CFont* pOldFont = dc.SelectObject(&m_fontGameOver);
    dc.SetTextColor(m_colorGameOver);
    dc.SetBkMode(TRANSPARENT);

    CRect rectGameOver;
    GetClientRect(&rectGameOver);
    rectGameOver.top = 20;
    rectGameOver.bottom = 100;
    dc.DrawText(_T("Game Over!"), &rectGameOver, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    dc.SelectObject(&m_fontScore);
    dc.SetTextColor(m_colorScore);

    CRect rectScore;
    GetClientRect(&rectScore);
    rectScore.top = 100;
    rectScore.bottom = 180;
    dc.DrawText(m_strScore, &rectScore, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    dc.SelectObject(pOldFont);
}


void GameOverDialog::OnBnClickedOk()
{
    retry = true;
    CDialogEx::OnOK();
}


void GameOverDialog::OnBnClickedCancel()
{
    retry = false;
    CDialogEx::OnCancel();
}
