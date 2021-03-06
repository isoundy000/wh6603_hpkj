#pragma once

#include "Stdafx.h"
#include "JettonView.h"
#include "CardControl.h"
#include "HistoryRecord.h"
#include "AdminControlDlg.h"

//////////////////////////////////////////////////////////////////////////

//消息定义
#define IDM_HINT_OX					WM_USER+99							//提示消息
#define IDM_START					WM_USER+100							//开始消息
#define IDM_READY					WM_USER+101							//摊牌消息
#define IDM_OX						WM_USER+102							//牛牛消息
#define IDM_MAX_SCORE				WM_USER+103							//最大加注
#define IDM_SEND_CARD_FINISH		WM_USER+104							//发牌完成
#define IDM_SHOW_VALUE				WM_USER+105							//点数信息
#define IDM_SHOW_INFO				WM_USER+106							//提示信息
#define IDM_OX_ENABLE				WM_USER+107							//牛牛按钮
#define IDM_SORT					WM_USER+108							//扑克分类
#define IDM_RESORT					WM_USER+109							//重排消息

#define IDM_SHORTCUT_KEY			WM_USER+111							//快捷键
#define IDM_BANKER					WM_USER+112							//做庄消息
#define IDM_CLICK_CARD				WM_USER+114							//点击消息
#define IDM_YU_YIN					(WM_USER+209)						//语音控制


#define MY_VIEW_CHAIRID				2									//椅子位置

#define	DRAW_HEIGHT						34								//绘画高度
/////////////////////////////////////////////////////////////////////////
//结构定义

//筹码状态
struct tagJettonStatus
{
	//属性信息
	WORD							wMoveCount;							//移动次数
	WORD							wMoveIndex;							//移动索引

	//筹码信息
	CPoint							ptFrom;								//出发位置
	CPoint							ptDest;								//目的位置
	CPoint							ptCourse;							//过程位置
	SCORE						lGold;								//筹码数目

	//移动形式
	INT								iMoveType;							//移动形式
};

//发牌子项
struct tagSendCardItem
{
	WORD							wChairID;							//发牌用户
	BYTE							cbCardData;							//发牌数据
};

//数组说明
typedef CWHArray<tagSendCardItem,tagSendCardItem &> CSendCardItemArray;

//////////////////////////////////////////////////////////////////////////

//游戏视图
class CGameClientView : public CGameFrameViewGDI
{
	//数据变量
protected:
	BYTE							m_cbIndex;							//牛牛表情
	WORD							m_wBankerUser;						//庄家用户
	SCORE							m_lTableScore[GAME_PLAYER];			//下注数目
	BYTE							m_bOxValue[GAME_PLAYER];			//牛牛数据
	BYTE							m_bOpenCardUser[GAME_PLAYER];		//摊牌用户
	BYTE							m_bCallUser;						//等待叫庄
	BYTE                            m_cbDynamicJoin;                    //动态加入
	bool							m_bInvest;							//等待下注
	bool							m_bShowSocre[GAME_PLAYER];			//显示积分
	bool							m_bUserAction;						//等待标志
	bool							m_bJettonAction;					//移动标示
	tagJettonStatus					m_JettonStatus[GAME_PLAYER];		//筹码信息
	SCORE							m_lMoveGold[GAME_PLAYER];			//筹码信息
    

	//牌型数据
public:
	tagHistoryScore	*				m_pHistoryScore[GAME_PLAYER];		//积分信息
	bool							m_bShowScore;						//积分状态
	bool							m_bShow;							//显示牌型
	bool							m_bLookOnUser;						//旁观标志
	bool							m_bOpenCard;						//等待摊牌

	//动画变量
protected:
	CPoint							m_SendCardPos;						//发牌位置
	WORD							m_wSendCount;						//移动次数
	WORD							m_wSendIndex;						//移动次数
	CPoint							m_SendEndingPos[GAME_PLAYER];		//桌牌位置
	CPoint							m_SendStartPos;						//始发位置
	CSendCardItemArray				m_SendCardItemArray;				//发牌数组

	//按钮控件
public:
	CSkinButton						m_btHintOx;							//提示按钮
	CSkinButton						m_btStart;							//开始按钮
	CSkinButton						m_btOpenCard;						//摊牌按钮
	CSkinButton						m_btOx;								//牛牛按钮
	CSkinButton						m_btBanker;							//庄家按钮
	CSkinButton						m_btIdler;							//闲家按钮
	CSkinButton						m_btScore;							//看分按钮
	CSkinButton						m_btYuYin;							//语音按钮

	//控件变量
public:
	CCardControl					m_CardControl[GAME_PLAYER];			//用户扑克
	CCardControl					m_CardControlOx[GAME_PLAYER];		//用户扑克

	CAdminControlDlg				m_AdminDlg;							//管理员控制
	CButton							m_btOpenAdmin;
	//位置信息
protected:
	CPoint							m_PointBanker[GAME_PLAYER];			//庄家位置
	CPoint							m_ptJeton[GAME_PLAYER];				//金币位置
	CPoint							m_ptValue[GAME_PLAYER];				//点数位置
	CPoint							m_ptOpenTag[GAME_PLAYER];			//摊牌位置
	CPoint							m_ptCard[GAME_PLAYER];				//金币位置
	CSize							m_sizeHistory;						//积分大小

	//界面变量
protected:
	CBitImageEx						m_ImageCard;						//扑克资源
	CBitImageEx						m_ImageViewBack;					//背景资源
	CBitImageEx						m_ImageViewCenter;					//背景资源
	CBitImageEx						m_ImageJeton;						//筹码资源
	CBitImageEx						m_ImageOpenCard;					//摊牌资源
	CBitImageEx						m_ImageScore;						//筹码资源

	CPngImageEx						m_ImageOxValueZero;					//牛值资源
	CPngImageEx						m_ImageDoulbeOx;					//牛牛资源
	CPngImageEx						m_ImageNumber;						//数字资源
	CPngImageEx						m_ImageOxValue;						//牛值资源
	CPngImageEx						m_ImageWaitCall;					//等待资源
	CPngImageEx 					m_ImageTimeBack;					//时间背景
	CPngImageEx 					m_ImageTimeNumber;					//时间数字
	CPngImageEx						m_ImageBanker;						//庄家资源
	CPngImageEx						m_PngUserBack;						//玩家底框
	CPngImageEx						m_PngHistoryScore;					//历史积分

	CPngImageEx						m_PngAutoOpen;						//自动开牌
	CPngImageEx						m_PngWaitBet;						//等待下注
	CPngImageEx						m_PngWaitOpen;						//等待开牌
	CPngImageEx						m_PngOpenTag;						//开牌标示
	CPngImageEx                     m_PngReady;                         //准备标识

	//提示变量
protected:
	CToolTipCtrl					m_ToolTipCtrl;						//提示控件
	CSize                           m_SizeFace;
	CPoint                          SizeTimeBack;
	
	//12-7-31
	CPngImageEx						m_PngOffLine;
	CPoint							m_ptOffLine[GAME_PLAYER];

public:
	CJettonView						m_JettonView;
	CDFontEx                        m_ViewFontEx;                       //视图字体
	         

	//函数定义
public:
	//构造函数
	CGameClientView();
	//析构函数
	virtual ~CGameClientView();
	//消息解释
	virtual BOOL PreTranslateMessage(MSG * pMsg);

	//WIN7支持
public:
	//是否特殊绘制
	virtual bool RealizeWIN7() { return true; }

	//重载函数
protected:
	//命令函数
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);

	//继承函数
private:
	//重置界面
	virtual VOID ResetGameView();
	//调整控件
	virtual VOID RectifyControl(int nWidth, int nHeight);
	//绘画界面
	virtual void DrawGameView(CDC * pDC, int nWidth, int nHeight);

	//功能函数
public:	
	//绘画时间
	void DrawUserTimerEx(CDC * pDC, int nXPos, int nYPos, WORD wTime, WORD wTimerArea=99);
	//获取接口
	//IGameFrameEngine *GetGameFrameEngine(){return m_pIGameFrameEngine;}
	//提示信息
	void SetUserAction(bool bWait);
	//动画判断
	bool IsDispatchCard();
	//完成发牌
	void FinishDispatchCard();
	//发送扑克
	void DispatchUserCard(WORD wChairID, BYTE cbCardData);
	//设置下注
	void SetUserTableScore(WORD wChairID, SCORE lTableScore,bool bMove=false);
	//庄家标志
	void SetBankerUser(WORD wBankerUser);
	//等待叫庄
	void SetWaitCall(BYTE bCallUser);
	//等待标志
	void SetWaitInvest(bool Invest);
	//设置动态加入标志
	void SetUserDynamicJoin(BYTE cbDynamicJoin) { m_cbDynamicJoin=cbDynamicJoin; };
	//左上信息
	//void SetScoreInfo(LONGLONG lTurnMaxScore,LONGLONG lTurnLessScore);
	//显示牌型
	void DisplayTypeEx(bool bShow);
	//设置点数
	void SetUserOxValue(WORD wChiarID,BYTE bValue);
	//获取点数
	BYTE GetValue(WORD wChiarID){return m_bOxValue[wChiarID];}
	//显示摊牌
	void ShowOpenCard(WORD wChiarID,BOOL bShow=TRUE);
	//显示积分
	void ShowScore(WORD wChiarID,bool bShow);
	//艺术字体
	void DrawTextString(CDC * pDC, LPCTSTR pszString, COLORREF crText, COLORREF crFrame, int nXPos, int nYPos);
	//艺术字体
	void DrawTextString(CDC * pDC, LPCTSTR pszString, COLORREF crText, COLORREF crFrame, LPRECT lpRect);
	//积分按钮
	VOID OnBnClickedScore();
	//设置积分
	bool SetHistoryScore(WORD wChairID,tagHistoryScore * pHistoryScore);
	//绘制动画
	void DrawMoveAnte( WORD wViewChairID, SCORE lTableScore);
	//移动筹码
	bool MoveJetton();
	//绘制用户图像
	void DrawUserReadyEx(CDC *pDC,int nXPos,int nYPos);
	
		//管理员控制
	VOID OpenAdminWnd();

	//消息映射
protected:
	//建立函数
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//定时器消息
	afx_msg void OnTimer(UINT nIDEvent);

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////
