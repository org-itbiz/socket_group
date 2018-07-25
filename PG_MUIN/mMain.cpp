//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "mMain.h"
#include "muin_set3.h"
#include "UtilHelper.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "sgcWebSocket"
#pragma link "sgcWebSocket_Classes"
#pragma link "sgcWebSocket_Classes_Indy"
#pragma link "sgcWebSocket_Server"
#pragma resource "*.fmx"
TmForm *mForm;

#define URL_GET_APK_INFO          "http://iotc365.com/test_locale/apk/info.json"
#define URL_GET_LOCALE_SETTING    "http://iotc365.com/test_locale/muin_set3/muin_set3.json"

#define APK_INFO_ColCount 4
#define APK_INFO_LineCount 3

#define _C_NAME			1
#define _C_WEB_URL		2
#define _C_UDP_PORT		3

#define _L_CUSTOM       1
#define _C_DISC			2

String APK_INFO[APK_INFO_LineCount][APK_INFO_ColCount];

//---------------------------------------------------------------------------
__fastcall TmForm::TmForm(TComponent* Owner)
	: TForm(Owner)
{
	UtilHelper = new TUtilHelper;
}
//---------------------------------------------------------------------------
void __fastcall TmForm::FormCreate(TObject *Sender)
{
	SetPermissions();

//	Init_Sockets_Server(SOCKET_TYPE::UDP);

	InitTimer->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TmForm::FormCloseQuery(TObject *Sender, bool &CanClose)
{
//	wsServer->DisconnectAll();
//	wsServer->Active = false;

//	SetConfigInfo();
}
//---------------------------------------------------------------------------
String __fastcall TmForm::GetJSONInfo(String url)
{
    String result;

	Idhttp::TIdHTTP *HTTP = new Idhttp::TIdHTTP(this);
	try {
		HTTP->ProtocolVersion = pv1_1;
		HTTP->Request->Accept = "application/json";
		HTTP->Request->ContentType = "application/json, charset=utf-8";
//		HTTP->IOHandler->DefStringEncoding = enUTF8;
		//ssl 일경우 libeay32.dll, ssleay32.dll copy
		result = HTTP->Get(url);
        //jsonobj 로 변경
		//에러 생기면 rad 10.2 맞는지 확인
	}
	catch (Exception &e)
	{

	}

	HTTP->Free();
	return result;
}
//---------------------------------------------------------------------------
void __fastcall TmForm::JsonArrToArray(String sJsonData)
{
	TJSONArray *LJsonArr = (TJSONArray*)TJSONObject::ParseJSONValue(TEncoding::UTF8->GetBytes(sJsonData), 0);

	for (int i = 0; i < LJsonArr->Count; i++)
	{
		TJSONArray *LItemArr = (TJSONArray*)TJSONObject::ParseJSONValue(
						TEncoding::UTF8->GetBytes(LJsonArr->Items[i]->ToString()), 0);

		for (int j = 0; j < LItemArr->Count; j++)
		{
			if (!LItemArr->Items[j]->Value().IsEmpty())
			{
				muin_set3[i][j] = LItemArr->Items[j]->Value();
//				SET_LOG_MEMO1(LItemArr->Items[j]->Value());
			}
		}
		LItemArr->Free();
	}

	LJsonArr->Free();
}
//---------------------------------------------------------------------------
void __fastcall TmForm::InitTimerTimer(TObject *Sender)
{
	InitTimer->Enabled = false;

	String info_json = GetJSONInfo(URL_GET_APK_INFO);

	TJSONArray *LJsonArr = (TJSONArray*)TJSONObject::ParseJSONValue(TEncoding::UTF8->GetBytes(info_json), 0);
	for (int i = 0; i < LJsonArr->Count; i++)
	{
//		SET_LOG_MEMO1(LJsonArr->Items[i]->ToString());
		TJSONArray *LItemArr = (TJSONArray*)TJSONObject::ParseJSONValue(
						TEncoding::UTF8->GetBytes(LJsonArr->Items[i]->ToString()), 0);
		for (int j = 0; j < LItemArr->Count; j++)
		{
			if (!LItemArr->Items[j]->Value().IsEmpty())
			{
				APK_INFO[i][j] = LItemArr->Items[j]->Value();
//				SET_LOG_MEMO1(LItemArr->Items[j]->Value());
			}
		}
		LItemArr->Free();
	}
	LJsonArr->Free();

	String muin_set3_json = GetJSONInfo(URL_GET_LOCALE_SETTING);

	JsonArrToArray(muin_set3_json);

//	SET_LOG_MEMO1(APK_INFO[_L_CUSTOM][_C_NAME]);
//	SET_LOG_MEMO1(APK_INFO[_L_CUSTOM][_C_WEB_URL]);
//	SET_LOG_MEMO1(APK_INFO[_L_CUSTOM][_C_UDP_PORT]);

	if(APK_INFO[_L_CUSTOM][_C_WEB_URL] != "")
	{
		sgcWSServer->Active = true;

		edtUrl->Text = APK_INFO[_L_CUSTOM][_C_WEB_URL];
		WebBrowser1->Navigate(APK_INFO[_L_CUSTOM][_C_WEB_URL]);

	}

	if(muin_set3[_L3_무인1][_C3_포트] != "")
	{
//		SET_LOG_MEMO(APK_INFO[_L_CUSTOM][_C_UDP_PORT]);
		IdUDPServer1->DefaultPort = StrToInt(muin_set3[_L3_무인2][_C3_포트]);
		IdUDPServer1->Bindings->Clear();
		SHandle = IdUDPServer1->Bindings->Add();
		SHandle->IP = "0.0.0.0";
		SHandle->Port = StrToInt(muin_set3[_L3_무인2][_C3_포트]);

		IdUDPServer1->Active =true;
	}
}
//---------------------------------------------------------------------------
void __fastcall TmForm::GetConfigInfo()
{
	ApplicationPath = ExtractFilePath(ParamStr(0));
	ConfigPath = ChangeFileExt(ApplicationPath, "config.ini");

	MemIni = new TMemIniFile(ConfigPath);

	try {
		mForm->Width = MemIni->ReadInteger("PG-MUIN", "Width", 800);
		mForm->Height = MemIni->ReadInteger("PG-MUIN", "Height", 600);
		mForm->Top = MemIni->ReadInteger("PG-MUIN", "Top", 0);
		mForm->Left = MemIni->ReadInteger("PG-MUIN", "Left", 0);
		PanelDebug->Visible = MemIni->ReadBool("PG-MUIN", "Debug", false);
	}
	__finally {
		MemIni->Free();
	}
}
//---------------------------------------------------------------------------
void __fastcall TmForm::SetConfigInfo()
{
	MemIni = new TMemIniFile(ConfigPath);

	try {
		MemIni->WriteInteger("PG-MUIN", "Width", mForm->Width);
		MemIni->WriteInteger("PG-MUIN", "Height", mForm->Height);
		MemIni->WriteInteger("PG-MUIN", "Top", mForm->Top);
		MemIni->WriteInteger("PG-MUIN", "Left", mForm->Left);
		MemIni->WriteBool("PG-MUIN", "Debug", PanelDebug->Visible);

		MemIni->UpdateFile();
	}
	__finally {
		MemIni->Free();
	}
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
void __fastcall TmForm::SET_LOG_MEMO(String strData)
{
    Memo1->Lines->Add(Now().FormatString("[hh:nn:ss:zzz]") + " " + strData);
}
//---------------------------------------------------------------------------
void __fastcall TmForm::btnClearClick(TObject *Sender)
{
	Memo1->Lines->Clear();
}
//---------------------------------------------------------------------------
void __fastcall TmForm::ExecWebBrowserJavascript(String strFunc)
{
	try {
		SET_LOG_MEMO(strFunc);
		WebBrowser1->EvaluateJavaScript(strFunc);
	} catch (Exception &ex) {
	}
}
//---------------------------------------------------------------------------
String __fastcall TmForm::GetInternetIP(String sDomain)
{
    UTF8String strip;

	Idhttp::TIdHTTP *HTTP = new Idhttp::TIdHTTP(this);
	try {
		HTTP->ProtocolVersion = pv1_1;
		HTTP->Request->Accept = "application/json";
		HTTP->Request->ContentType = "application/json";
		//ssl 일경우 libeay32.dll, ssleay32.dll copy
		String request_data = request_data.sprintf(L"http://api.iotc365.com/api/get/ip_text?domain=%s&format=json", AnsiString(sDomain).c_str());

		strip = HTTP->Get(request_data);
        //jsonobj 로 변경
		//에러 생기면 rad 10.2 맞는지 확인
	}
	catch (Exception &e)
	{

	}

	HTTP->Free();
//	String request_data = request_data.sprintf(L"http://api.iotc365.com/api/get/ip_text?domain=%s&format=json", AnsiString(sDomain).c_str());
	return strip;
}
//---------------------------------------------------------------------------

void __fastcall TmForm::SOCKET_SERVER_SEND(String sIPAddr, unsigned int nPort, String sMessage)
{
	if(sIPAddr != NULL && nPort > 0)
	{
		#if defined(_PLAT_ANDROID)
		sIPAddr = GetInternetIP(sIPAddr);
		#endif
        #if defined(_PLAT_MSWINDOWS)
		char sHost[100];
		sprintf(sHost, "%s", AnsiString(sIPAddr).c_str());
		sIPAddr = UtilHelper->GetIpByDomainName(sHost);
		#endif

		if(sIPAddr == "0.0.0.0")
		{
			SET_LOG_MEMO("sMessage faild");
			return;
		}

        #if defined(_PLAT_MSWINDOWS)
		OutputDebugString(sIPAddr.c_str());
		#endif

		sprintf(debuf_buf, "sMessage => %s", AnsiString(sMessage).c_str());
		SET_LOG_MEMO(debuf_buf);

		SHandle->SendTo(sIPAddr, nPort, sMessage, Id_IPv4, enUTF8);
//		Application->ProcessMessages();
	}
}
//---------------------------------------------------------------------------
void __fastcall TmForm::SOCKET_CLIENT_SEND(String sIPAddr, unsigned int nPort, String sMessage)
{
	if(!IdUDPClient1->Active)
	{
        IdUDPClient1->Active = true;
	}

	IdUDPClient1->Host = sIPAddr;
	IdUDPClient1->Port = nPort;

	IdUDPClient1->Send(sMessage, enUTF8);
	Application->ProcessMessages();
	sprintf(debuf_buf, "sMessage => %s", AnsiString(sMessage).c_str());
	SET_LOG_MEMO(debuf_buf);

	String recv_data = IdUDPClient1->ReceiveString(5000, enUTF8);
//	Application->ProcessMessages();

	if(!recv_data.IsEmpty())
	{
		sprintf(debuf_buf, "recv_data => %s", AnsiString(recv_data).c_str());
		SET_LOG_MEMO(debuf_buf);

		String web_func = "WebMessage('" + recv_data + "')";
		ExecWebBrowserJavascript(web_func);
	}

}
//---------------------------------------------------------------------------

void __fastcall TmForm::sgcWSServerMessage(TsgcWSConnection *Connection, const UnicodeString Text)
{
	SET_LOG_MEMO(muin_set3[_L3_설정][_C3_DOMAIN]);
	SET_LOG_MEMO(muin_set3[_L3_무인1][_C3_포트]);
//	SOCKET_SERVER_SEND(muin_set3[_L3_설정][_C3_DOMAIN], StrToInt(muin_set3[_L3_무인1][_C3_포트]), Text);
	SOCKET_CLIENT_SEND(muin_set3[_L3_설정][_C3_DOMAIN], StrToInt(muin_set3[_L3_무인1][_C3_포트]), Text);
}
//---------------------------------------------------------------------------

void __fastcall TmForm::sgcWSServerConnect(TsgcWSConnection *Connection)
{
	SET_LOG_MEMO(Connection->Port);
}
//---------------------------------------------------------------------------

void __fastcall TmForm::sgcWSServerDisconnect(TsgcWSConnection *Connection, int Code)
{
	//
}
//---------------------------------------------------------------------------

void __fastcall TmForm::IdUDPServer1UDPRead(TIdUDPListenerThread *AThread, const TIdBytes AData,
          TIdSocketHandle *ABinding)
{
	String recv_data = BytesToString(AData, enUTF8);

	if (!recv_data.IsEmpty())
	{
		DynamicArray<String> recv_list = SplitString(recv_data, "#");
		if(recv_list.Length > 0)
		{
//			if(recv_list[0] == CMD_RETURN_CONFIG)
//			{
////				JsonArrToArray(recv_list[1]);
////				sprintf(debuf_buf, "recv_data => %s", AnsiString(recv_list[1]).c_str());
//			};
//			SET_LOG_MEMO(debuf_buf);
		}
		else
		{
			sprintf(debuf_buf, "recv_data => %s", AnsiString(recv_data).c_str());
			SET_LOG_MEMO(debuf_buf);

			String web_func = "WebMessage('" + recv_data + "')";
			ExecWebBrowserJavascript(web_func);
		}

	}
}
//---------------------------------------------------------------------------

