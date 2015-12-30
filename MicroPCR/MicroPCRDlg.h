
// MicroPCRDlg.h : ��� ����
//

#pragma once
#include "DeviceConnect.h"
#include "afxcmn.h"
#include ".\gridctrl_src\gridctrl.h"
#include "Chart.h"
#include "UserDefs.h"
#include "mmtimers.h"
#include "TempGraphDlg.h"
#include "CommThread.h"

// For magneto
#include "Magneto.h"
#include "afxwin.h"

// CMicroPCRDlg ��ȭ ����
class CMicroPCRDlg : public CDialog
{
private:
	CDeviceConnect *device;
	bool isConnected;
	
	CBitmap bmpProgress, bmpRecNotWork, bmpRecWork;
	bool openConstants, openGraphView;

	double m_cTemperature;

	CProgressCtrl m_cProgressBar;
	CGridCtrl m_cPidTable;
	CListCtrl m_cProtocolList;

	CMMTimers* m_Timer;

	CXYChart m_Chart;
	vector< double > sensorValues;

	int m_cGraphYMin;
	int m_cGraphYMax;

	bool isFirstDraw;

	void addSensorValue(double val);
	void clearSensorValue();

private:
	vector< PID > pids;
	float m_kp, m_ki, m_kd;

	void findPID();

	int m_cMaxActions;
	int m_cTimeOut;
	float m_cArrivalDelta;

	void initPidTable();
	void loadPidTable();
	void loadConstants();
	void saveConstants();
	void enableWindows();
	void opticGraphview();

	// for initialize
	void initValues();

	CString m_sProtocolName;
	int m_totalActionNumber;
	int m_currentActionNumber;
	
	Action *actions;
	
	void readProtocol(CString path);
	void displayList();
	CString getProtocolName(CString path);

	// for temporary
	void blinkTask();
	void timeTask();
	void PCREndTask();
	
	int m_blinkCounter, m_timerCounter;

	bool isRecording, recordFlag;
	bool blinkFlag;
	bool isStarted;	// PCR �÷���
	bool isCompletePCR;
	bool isTargetArrival;

	double m_startTime;
	DWORD m_recStartTime;
	double m_prevTargetTemp, m_currentTargetTemp;

	int m_nLeftTotalSecBackup;
	int m_nLeftSec, m_nLeftTotalSec;
	int m_timeOut;

	int m_leftGotoCount;
	int ledControl_wg, ledControl_r, ledControl_g, ledControl_b;

	CStdioFile m_recFile, m_recPDFile, m_recPDFile2;
	int m_recordingCount, m_cycleCount, m_cycleCount2;

	// ��ư�� ���� ���� ���� command ���� �����Ѵ�.
	BYTE currentCmd;
	bool isFanOn, isLedOn;

	// Photodiode ���� ����
	BYTE photodiode_h, photodiode_l;

	float m_cIntegralMax;

	CString loadedPID;

	// For temp graph
	CTempGraphDlg tempGraphDlg;
	int isTempGraphOn;

	// For target temp comparison
	bool targetTempFlag;
	bool freeRunning;
	int freeRunningCounter;

	bool emergencyStop;

	// 151203 siri For magneto
	CComboBox comPortList_magneto;
	CComboBox comPortList_Arduino;
	CTreeCtrl actionTreeCtrl;
	CProgressCtrl progressBar;
	CMagneto *magneto;
	int previousAction;
	double testStartTime;

	void selectTreeItem(int rootIndex, int childIndex);

	// siri 151205 - for arduino
	CCommThread m_Comm;
	BYTE readBuff[16];
	BYTE writeBuff[16];
	vector<BYTE> Read_Buffer;
	
	int CMicroPCRDlg::PIDControl(void);

	int m_target_temp;
	double arduino_Kp;
	double arduino_Ki;
	double arduino_Kd;
	double current_temp;
	double lastIntegral;
	double lastError;
	float integralMax;
	int pwmValue;

	int magnet_flag;
	int heating_target_temper;

	int protocol_size;

	bool isStarted2;	// ���� ��ư ����

// �����Դϴ�.
public:
	CMicroPCRDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.
	virtual ~CMicroPCRDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_MICROPCR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT SetSerial(WPARAM wParam, LPARAM lParam);

	virtual LRESULT OnmmTimer(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	BYTE m_cCompensation;
	BOOL OnDeviceChange(UINT nEventType, DWORD dwData);
	afx_msg void OnBnClickedButtonConstants();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void Serialize(CArchive& ar);
	afx_msg void OnBnClickedButtonConstantsApply();
	afx_msg void OnBnClickedButtonPcrStart();
	afx_msg void OnBnClickedButtonPcrOpen();
	afx_msg void OnBnClickedButtonPcrRecord();
	afx_msg void OnBnClickedButtonFanControl();
	afx_msg void OnBnClickedButtonEnterPidManager();
	afx_msg void OnBnClickedButtonLedControl();
	afx_msg void OnBnClickedCheckTempGraph();
	afx_msg void OnMoving(UINT fwSide, LPRECT pRect);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedButtonConnectMagneto();
	afx_msg void OnBnClickedButtonConnectMagneto2();
	afx_msg void OnBnClickedButtonConnectArduino();
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg HRESULT OnMotorPosChanged(WPARAM wParam, LPARAM lParam);
	afx_msg HRESULT OnWaitTimeChanged(WPARAM wParam, LPARAM lParam);
	afx_msg HRESULT OnStartPCR(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedButtonConnectArduino2();
	LONG OnReceives(UINT port, LONG IParam);
	afx_msg HRESULT OnArduinoMagnet(WPARAM wParam, LPARAM lParam);
	afx_msg HRESULT OnArduinoHeating(WPARAM wParam, LPARAM lParam);
};
