
// RunnerDlg.h: файл заголовка
//

#pragma once
#include "StartGameDlg.h"
#include "GameOverDialog.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#define DOWN_ARROW 83

#define MAX_OBSTACLES 4

// Диалоговое окно CRunnerDlg
class CRunnerDlg : public CDialogEx
{
// Создание
public:
	CRunnerDlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RUNNER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	CRect dinoRect;

	CRect obstacles[MAX_OBSTACLES];
	int minObstacleDistance;
	int maxObstacleDistance;
	int currentObstacleIndex;
	
	UINT_PTR timerID;

	bool isJumping;
	bool isFalling;

	bool isDownButton;

	int jumpOffset;
	int jumpVelocity;
	int gravity;

	int speed;
	int maxSpeed;
	int downSlideSpeed;

	int score;
	int upSpeedScore;

	const double upCoef = 1.5;

	const int upStateDinoSize = 200;
	const int downStateDinoSize = 225;

	bool start;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	void StartGame();
	void GameOver();

	void MoveObstacle();
	void Jump();
	void CheckCollision();
	void GenerateRandomObstacle(int index);
	void GenerateRandomObstacles();

	void Landing();
	
	int GenerateRandomNumber(int minValue, int maxValue);
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
};
