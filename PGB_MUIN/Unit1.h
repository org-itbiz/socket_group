//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <System.Win.Registry.hpp>
#include <System.IOUtils.hpp>
#include <System.IniFiles.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <SHDocVw.hpp>
#include <Vcl.OleCtrls.hpp>
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdUDPBase.hpp>
#include <IdUDPServer.hpp>
#include "UtilHelper.h"
#include "sgcWebSocket.hpp"
#include "sgcWebSocket_Classes.hpp"
#include "sgcWebSocket_Server.hpp"
#include <IdGlobal.hpp>
#include <IdSocketHandle.hpp>
//---------------------------------------------------------------------------
class TmForm : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TWebBrowser *WebBrowser1;
	TIdUDPServer *IdUDPServer1;
	TsgcWebSocketServer *sgcWSServer1;
	TPanel *Panel2;
	TEdit *edtReturnV;
	TLabel *Label1;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall IdUDPServer1UDPRead(TIdUDPListenerThread *AThread, const TIdBytes AData,
          TIdSocketHandle *ABinding);
	void __fastcall sgcWSServer1Connect(TsgcWSConnection *Connection);
	void __fastcall sgcWSServer1Disconnect(TsgcWSConnection *Connection, int Code);
	void __fastcall sgcWSServer1Error(TsgcWSConnection *Connection, const UnicodeString Error);
	void __fastcall sgcWSServer1Exception(TsgcWSConnection *Connection, Exception *E);
	void __fastcall sgcWSServer1Message(TsgcWSConnection *Connection, const UnicodeString Text);


private:	// User declarations
	TIdSocketHandle * SHandle;

	void __fastcall Initialize();
	void __fastcall SetPermissions();
	void __fastcall Delay(unsigned int _time);
	String __fastcall GetJsonResult(String url);
	void __fastcall SOCKET_SERVER_SEND(String sIPAddr, unsigned int nPort, String sMessage);

	void __fastcall ExecBrowserJavascript(String sFunc);
	void __fastcall JsonToArray(String sJsonData);
	String __fastcall GetJSONInfo(String url);


public:		// User declarations
	char http_buf[1024], send_buf[1024];


	__fastcall TmForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TmForm *mForm;
//---------------------------------------------------------------------------
#endif
