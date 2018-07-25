//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <mshtml.h>
#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "sgcWebSocket"
#pragma link "sgcWebSocket_Classes"
#pragma link "sgcWebSocket_Server"
#pragma resource "*.dfm"
TmForm *mForm;

//cmd
const WORD UDP_SERVER_PORT = 11000;

//---------------------------------------------------------------------------
__fastcall TmForm::TmForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TmForm::FormCreate(TObject *Sender)
{
	SetPermissions();

    Initialize();
}
//---------------------------------------------------------------------------
void __fastcall TmForm::FormCloseQuery(TObject *Sender, bool &CanClose)
{
//
}
//---------------------------------------------------------------------------
void __fastcall TmForm::Initialize()
{
	WebBrowser1->Navigate(L"http://muin.iotc365.com");

	IdUDPServer1->DefaultPort = UDP_SERVER_PORT;
	IdUDPServer1->Bindings->Clear();
	SHandle = IdUDPServer1->Bindings->Add();
	SHandle->IP = "0.0.0.0";
	SHandle->Port = UDP_SERVER_PORT;
	IdUDPServer1->Active = true;
}
//---------------------------------------------------------------------------
void __fastcall TmForm::SetPermissions()
{
	#ifdef _Windows
	UnicodeString cHomePath = "SOFTWARE";
	UnicodeString cFeatureBrowserEmulation =
		"Microsoft\\Internet Explorer\\Main\\FeatureControl\\FEATURE_BROWSER_EMULATION\\";
	int cIE11 = 11011;
	UnicodeString sKey = ExtractFileName(ParamStr(0));
	TRegIniFile *Reg = new TRegIniFile(cHomePath);

	__try {
		TRegistry *reg1 = dynamic_cast<TRegistry*>(Reg);
		if (Reg->OpenKey(cFeatureBrowserEmulation, true) &&
			!(reg1->KeyExists(sKey) && reg1->ReadInteger(sKey) == cIE11))
		{
			reg1->WriteInteger(sKey, cIE11);
		}
	}
	__finally {
		Reg->Free();
	}
	#endif
}
//---------------------------------------------------------------------------
void __fastcall TmForm::Delay(unsigned int _time)
{
	#if defined(_PLAT_MSWINDOWS)
	MSG msg;
	DWORD dwStart;

	dwStart = GetTickCount();

	while(GetTickCount() - dwStart < _time)
	{
		while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
    #endif
}
//---------------------------------------------------------------------------
void __fastcall TmForm::JsonToArray(String sJsonData)
{
//
}
//---------------------------------------------------------------------------
String __fastcall TmForm::GetJsonResult(String url)
{
    String result;

//	TIdHTTP *HTTP = new TIdHTTP(this);
//	try {
//		HTTP->ProtocolVersion = pv1_1;
//		HTTP->Request->Accept = "application/json";
//		HTTP->Request->ContentType = "application/json, charset=utf-8";
////		HTTP->IOHandler->DefStringEncoding = enUTF8;
//		//ssl ÀÏ°æ¿ì libeay32.dll, ssleay32.dll copy
//		result = HTTP->Get(url);
//	}
//	catch (Exception &e)
//	{
//
//	}
//
//	HTTP->Free();
	return result;
}
//---------------------------------------------------------------------------

void __fastcall TmForm::SOCKET_SERVER_SEND(String sIPAddr, unsigned int nPort, String sMessage)
{
	if(sIPAddr != NULL && nPort > 0)
	{
		char host[100];
		sprintf(host, "%s", AnsiString(sIPAddr).c_str());
		sIPAddr = UtilHelper->GetIpByDomainName(host);

		if(sIPAddr == "0.0.0.0")
		{
//			Console_Write("sMessage faild");
            return;
		}

        #if defined(_PLAT_MSWINDOWS)
		OutputDebugString(sIPAddr.c_str());
		#endif
//		sprintf(debuf_buf, "sMessage => %s", AnsiString(sMessage).c_str());
//		Console_Write(debuf_buf);

		SHandle->SendTo(sIPAddr, nPort, sMessage, Id_IPv4, enUTF8);
		Application->ProcessMessages();
	}
}
//---------------------------------------------------------------------------

void __fastcall TmForm::ExecBrowserJavascript(String sFunc)
{
	try
	{
		IHTMLDocument2 *Doc;
		IHTMLInputElement *Elem;

		WebBrowser1->Document->QueryInterface(::IID_IHTMLDocument2,(void**)&Doc);

		IHTMLWindow2 *hWin;
		HRESULT hr = Doc->get_parentWindow(&hWin);
		if (SUCCEEDED(hr))
		{
			VARIANT vVRT;
			VariantInit(&vVRT);
			hWin->execScript(sFunc.c_str(), L"javascript", &vVRT);
	//		hWin->execScript(sFunc.c_str(), NULL, &vVRT);
			VariantClear(&vVRT);
			hWin->Release();
		}
		Doc->Release();


	} catch (Exception &ex)
	{
	}
}
//---------------------------------------------------------------------------
void __fastcall TmForm::IdUDPServer1UDPRead(TIdUDPListenerThread *AThread, const TIdBytes AData,
          TIdSocketHandle *ABinding)
{
	String sRecvData = BytesToString(AData, enUTF8);

	if (!sRecvData.IsEmpty())
	{
		DynamicArray<String> lstRecvData = SplitString(sRecvData, "#");

		if(lstRecvData.Length > 1)
		{
		}
		else
		{
			SOCKET_SERVER_SEND(ABinding->PeerIP, ABinding->PeerPort, edtReturnV->Text);
		}

        lstRecvData.Length == 0;

		memset(&send_buf, 0, sizeof(send_buf));
	}
}
//---------------------------------------------------------------------------
void __fastcall TmForm::sgcWSServer1Connect(TsgcWSConnection *Connection)
{
//
}
//---------------------------------------------------------------------------
void __fastcall TmForm::sgcWSServer1Disconnect(TsgcWSConnection *Connection, int Code)
{
//
}
//---------------------------------------------------------------------------
void __fastcall TmForm::sgcWSServer1Error(TsgcWSConnection *Connection, const UnicodeString Error)
{
//
}
//---------------------------------------------------------------------------
void __fastcall TmForm::sgcWSServer1Exception(TsgcWSConnection *Connection, Exception *E)
{
//
}
//---------------------------------------------------------------------------
void __fastcall TmForm::sgcWSServer1Message(TsgcWSConnection *Connection, const UnicodeString Text)
{
//
}
//---------------------------------------------------------------------------
