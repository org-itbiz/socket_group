//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <System.IOUtils.hpp>
#include <System.IniFiles.hpp>
#include <System.JSON.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Memo.hpp>
#include <FMX.ScrollBox.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.TabControl.hpp>
#include <FMX.Types.hpp>
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdGlobal.hpp>
#include <IdSocketHandle.hpp>
#include <IdUDPBase.hpp>
#include <IdUDPClient.hpp>
#include <IdUDPServer.hpp>
#include <IdHTTP.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>


#include "UtilHelper.h"
#include <IdIPWatch.hpp>
#include <FMX.WebBrowser.hpp>
#include "sgcWebSocket.hpp"
#include "sgcWebSocket_Classes.hpp"
#include "sgcWebSocket_Classes_Indy.hpp"
#include "sgcWebSocket_Server.hpp"
#if defined(_PLAT_MSWINDOWS)
#include <System.Win.Registry.hpp>
#endif
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TPanel *pnlDebug;
	TTabControl *TabControl1;
	TTabItem *TabItem1;
	TTabItem *TabItem2;
	TMemo *Memo1;
	TIdUDPClient *IdUDPClient1;
	TButton *Button1;
	TButton *Button2;
	TIdUDPServer *IdUDPServer1;
	TButton *Button3;
	TIdIPWatch *IdIPWatch1;
	TButton *Button4;
	TLabel *Label1;
	TWebBrowser *WebBrowser1;
	TTimer *Timer1;
	TsgcWebSocketServer *sgcWSServer;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall IdUDPServer1UDPRead(TIdUDPListenerThread *AThread, const TIdBytes AData,
          TIdSocketHandle *ABinding);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall sgcWSServerMessage(TsgcWSConnection *Connection, const UnicodeString Text);
	void __fastcall sgcWSServerConnect(TsgcWSConnection *Connection);
	void __fastcall sgcWSServerDisconnect(TsgcWSConnection *Connection, int Code);
	void __fastcall WebBrowser1DidFinishLoad(TObject *ASender);

private:	// User declarations
	TIdSocketHandle * SHandle;

    void __fastcall Initialize();
	void __fastcall SET_LOG_MEMO1(String data);
	void __fastcall Delay(unsigned int _time);
	void __fastcall SetPermissions();
	void __fastcall SOCKET_SERVER_SEND(String sIPAddr, unsigned int nPort, String sMessage);
	void __fastcall SOCKET_CLIENT_SEND(String sIPAddr, unsigned int nPort, String sMessage);
	String __fastcall GetInternetIP(String sDomain);
	void __fastcall JsonArrToArray(String sJsonData);
	String __fastcall GetJSONInfo(String url);
	void __fastcall ExecWebBrowserJavascript(String strFunc);

public:		// User declarations

	char debuf_buf[1024*100];
	char http_buf[1024];

	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
