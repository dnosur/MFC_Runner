
// RunnerDlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "Runner.h"
#include "RunnerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Диалоговое окно CRunnerDlg



CRunnerDlg::CRunnerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_RUNNER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	gravity = 2;

	dinoRect = CRect(50, upStateDinoSize, 100, 250);

	for (int i = 0; i < MAX_OBSTACLES; i++) {
		obstacles[i] = CRect(300, 200, 320, 300);
	}

	start = false;
}

void CRunnerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CRunnerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_KEYDOWN()
	ON_WM_SYSKEYUP()
	ON_WM_KEYUP()
END_MESSAGE_MAP()


// Обработчики сообщений CRunnerDlg

BOOL CRunnerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetWindowPos(NULL, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SWP_NOMOVE | SWP_NOZORDER);
	StartGame();
	 
	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CRunnerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CRunnerDlg::OnPaint()
{
	if (!start) {
		return;
	}

	CPaintDC dc(this);

	CBrush dinoBrush(RGB(0, 0, 255)); 
	CBrush obstacleBrush(RGB(255, 0, 0)); 

	CRect modifiedDinoRect = dinoRect;
	if (isDownButton)
	{
		modifiedDinoRect.top = modifiedDinoRect.bottom - 25; // Уменьшение высоты куба
	}

	dc.FillRect(modifiedDinoRect, &dinoBrush);
	//dc.FillRect(obstacleRect, &obstacleBrush);

	for (int i = 0; i < MAX_OBSTACLES; i++) {
		dc.FillRect(obstacles[i], &obstacleBrush);
	}

	CString scoreText;
	scoreText.Format(_T("Score: %d"), score);
	dc.TextOut(10, 10, scoreText);

	CString speedText;
	scoreText.Format(_T("Speed: %d"), 100 - speed);
	dc.TextOut(80, 10, scoreText);

	CDialogEx::OnPaint();
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CRunnerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CRunnerDlg::MoveObstacle()
{
	for (int i = 0; i < MAX_OBSTACLES; i++) {
		obstacles[i].OffsetRect(-10, 0);
		if (obstacles[i].right >= 0)
		{
			continue;
		}

		GenerateRandomObstacle(currentObstacleIndex);
		currentObstacleIndex = currentObstacleIndex + 1 >= MAX_OBSTACLES ? 0 : currentObstacleIndex + 1;
		score++;

		if (speed <= maxSpeed) {
			continue;
		}

		if (score < upSpeedScore) {
			continue;
		}

		upSpeedScore *= upCoef;
		speed -= 2;

		minObstacleDistance += 4;
		maxObstacleDistance += 4;
	}
}

void CRunnerDlg::StartGame()
{
	speed = 50;
	maxSpeed = 15;

	minObstacleDistance = 200;
	maxObstacleDistance = 300;

	downSlideSpeed = 5;

	StartGameDlg startGameDlg(speed, maxSpeed, minObstacleDistance, maxObstacleDistance, downSlideSpeed);
	if (!startGameDlg.DoModal() || !startGameDlg.success) {
		EndDialog(1);
		return;
	}

	score = 0;
	upSpeedScore = 5;

	int speedDifferance = startGameDlg.speed - speed;

	maxSpeed -= startGameDlg.maxSpeed - maxSpeed;
	speed -= speedDifferance;

	minObstacleDistance = startGameDlg.minObstacleDistance;
	maxObstacleDistance = startGameDlg.maxObstacleDistance;

	int obstacleDistance = (abs(speedDifferance) / 2) * 4;
	minObstacleDistance = speedDifferance > 0 ? minObstacleDistance + obstacleDistance : minObstacleDistance - obstacleDistance;
	maxObstacleDistance = speedDifferance > 0 ? minObstacleDistance + obstacleDistance : minObstacleDistance - obstacleDistance;

	downSlideSpeed = startGameDlg.downSlideSpeed;

	GenerateRandomObstacles();
	currentObstacleIndex = 0;

	timerID = SetTimer(1, speed, nullptr);
	start = true;
	Invalidate();
}

void CRunnerDlg::Jump()
{
	if (!isJumping)
	{
		return;
	}

	dinoRect.OffsetRect(0, jumpVelocity);
	jumpVelocity += isDownButton ? gravity + downSlideSpeed : gravity;
	if (dinoRect.bottom >= 250)
	{
		Landing();
	}
	else if (jumpVelocity > 0)
	{
		isFalling = TRUE;
	}
}

void CRunnerDlg::CheckCollision()
{
	CRect dinoTemp = dinoRect;
	CRect modifiedDinoRect = dinoRect;
	if (isDownButton)
	{
		modifiedDinoRect.top = modifiedDinoRect.bottom - 25; // Уменьшение высоты куба
	}

	if (!dinoTemp.IntersectRect(&modifiedDinoRect, &obstacles[currentObstacleIndex]))
	{
		return;
	}

	GameOver();
}

void CRunnerDlg::GenerateRandomObstacle(int index)
{
	const int farestObstacleIndex = !index ? MAX_OBSTACLES - 1 : index - 1;
	const int left = obstacles[farestObstacleIndex].left + GenerateRandomNumber(minObstacleDistance, maxObstacleDistance);

	if (rand() % 2 > 0) {
		int height = (rand() % 40) + 50;
		obstacles[index] = CRect(
			left, 
			250 - height, 
			left + 20, 
			250
		);
		return;
	}

	obstacles[index] = CRect(
		left, 
		250 - 200, 
		left + 20, 
		250 - 45
	);
}

void CRunnerDlg::GenerateRandomObstacles()
{
	for (int i = 0; i < MAX_OBSTACLES; i++) {
		GenerateRandomObstacle(i);
	}
}

void CRunnerDlg::Landing()
{
	dinoRect.MoveToY(200);
	isJumping = FALSE;
	isFalling = FALSE;
	jumpVelocity = 0;
}

void CRunnerDlg::GameOver()
{
	KillTimer(timerID);
	start = false;

	GameOverDialog gameOver(score);
	if (!gameOver.DoModal() || !gameOver.retry) {
		EndDialog(1);
		return;
	}

	StartGame();
}

int CRunnerDlg::GenerateRandomNumber(int minValue, int maxValue)
{
	return minValue + (rand() % (maxValue - minValue + 1));
}

void CRunnerDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1)
	{
		MoveObstacle();
		if (isJumping)
		{
			Jump();
		}
		CheckCollision();
		Invalidate();
	}

	CDialogEx::OnTimer(nIDEvent);
}


void CRunnerDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_SPACE && !isJumping && !isFalling)
	{
		isJumping = TRUE;
		isDownButton = FALSE;
		jumpVelocity = -20; 
	}

	//Down
	if (nChar == DOWN_ARROW) {
		isDownButton = true;
	}

	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CRunnerDlg::OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	
	CDialogEx::OnSysKeyUp(nChar, nRepCnt, nFlags);
}


void CRunnerDlg::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == DOWN_ARROW) {
		isDownButton = false;
	}

	CDialogEx::OnKeyUp(nChar, nRepCnt, nFlags);
}
