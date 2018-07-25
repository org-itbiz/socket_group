//---------------------------------------------------------------------------

#ifndef mMainH
#define mMainH
//---------------------------------------------------------------------------
#include <System.Win.Registry.hpp>
#include <System.JSON.hpp>
#include <System.Classes.hpp>
#include <System.IOUtils.hpp>
#include <System.StrUtils.hpp>
#include <System.DateUtils.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Edit.hpp>
#include <FMX.Memo.hpp>
#include <FMX.ScrollBox.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.TabControl.hpp>
#include <FMX.Types.hpp>
#include <FMX.WebBrowser.hpp>
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdUDPBase.hpp>
#include <IdUDPClient.hpp>
#include <IdUDPServer.hpp>
#include "sgcWebSocket.hpp"
#include "sgcWebSocket_Classes.hpp"
#include "sgcWebSocket_Classes_Indy.hpp"
#include "sgcWebSocket_Server.hpp"
#include <IdGlobal.hpp>
#include <IdSocketHandle.hpp>
//---------------------------------------------------------------------------
class TmForm : public TForm
{
__published:	// IDE-managed Components
	TIdUDPClient *IdUDPClient1;
	TIdUDPServer *IdUDPServer1;
	TTimer *RegistMonitor;
	TToolBar *ToolBar1;
	TEdit *edtUrl;
	TPanel *Panel1;
	TWebBrowser *WebBrowser1;
	TPanel *PanelDebug;
	TEdit *edtJsfunc;
	TButton *btnJsfunc;
	TTimer *Timer1;
	TPanel *Panel2;
	TTabControl *TabControl1;
	TTabItem *TabItem1;
	TButton *btnUrlGo;
	TButton *btnReload;
	TMemo *Memo1;
	TButton *btnClear;
	TPanel *Panel3;
	TTimer *InitTimer;
	TTabItem *TabItem2;
	TsgcWebSocketServer *sgcWSServer;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall btnClearClick(TObject *Sender);
	void __fastcall InitTimerTimer(TObject *Sender);
	void __fastcall sgcWSServerMessage(TsgcWSConnection *Connection, const UnicodeString Text);
	void __fastcall sgcWSServerConnect(TsgcWSConnection *Connection);
	void __fastcall sgcWSServerDisconnect(TsgcWSConnection *Connection, int Code);
	void __fastcall IdUDPServer1UDPRead(TIdUDPListenerThread *AThread, const TIdBytes AData,
          TIdSocketHandle *ABinding);


private:	// User declarations
	String __fastcall GetJSONInfo(String url);
    void __fastcall JsonArrToArray(String sJsonData);

	void __fastcall SetPermissions();
	void __fastcall SET_LOG_MEMO(String strData);
	void __fastcall ExecWebBrowserJavascript(String strFunc);
    String __fastcall GetInternetIP(String sDomain);
	void __fastcall SOCKET_SERVER_SEND(String sIPAddr, unsigned int nPort, String sMessage);
	void __fastcall SOCKET_CLIENT_SEND(String sIPAddr, unsigned int nPort, String sMessage);
	void __fastcall DO_PROCESS(char tcp1_udp2_ws3, String recvData, String cmd, String distIP, String distPort);
	void __fastcall GetConfigInfo();
	void __fastcall SetConfigInfo();
	void __fastcall Delay(int _time);

public:		// User declarations
	TMemIniFile *MemIni;
	String ApplicationPath, ConfigPath;

	TIdSocketHandle * SHandle;

	char debuf_buf[1024*100];
	char http_buf[1024];

	__fastcall TmForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TmForm *mForm;
//---------------------------------------------------------------------------
#endif
