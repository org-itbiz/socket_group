//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "Unit1.h"
#include "iotc_define.h"
#include "muin_set3.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "sgcWebSocket"
#pragma link "sgcWebSocket_Classes"
#pragma link "sgcWebSocket_Classes_Indy"
#pragma link "sgcWebSocket_Server"
#pragma link "sgcWebSocket"
#pragma resource "*.fmx"
TForm1 *Form1;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	ioDevice = new IOTC_DEVICE;

	UtilHelper = new TUtilHelper;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
	pnlDebug->Visible = false;

	#if defined(_PLAT_MSWINDOWS)
	ioDevice->sConfigPath = "C:\\Users\\Public\\Documents\\iotc\\d\\s\\io_config.ini";
	SetPermissions();
	#elif defined(_PLAT_ANDROID)
	ioDevice->sConfigPath = System::Ioutils::TPath::GetTempPath() + L"/" + Application->Title + L"/config.info";
	#endif

	Label1->Text = Application->Title;

}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCloseQuery(TObject *Sender, bool &CanClose)
{
	if (MemIni)
	{
		delete MemIni;
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Initialize()
{
	SET_LOG_MEMO1(ioDevice->sConfigPath);
    GetConfigInfo();
//	sprintf(ioDevice->sMacAddress, "%s", AnsiString(UtilHelper->GetMacAddress()).c_str());
//	ioDevice->sMacAddress = UtilHelper->GetMacAddress();
	String info_json = GetJsonResult(ioDevice->sRequestUrl);
	SET_LOG_MEMO1(ioDevice->sDeviceGuid.UpperCase());
	TJSONArray *LJsonArr = (TJSONArray*)TJSONObject::ParseJSONValue(TEncoding::UTF8->GetBytes(info_json), 0);
	for (int i = 0; i < LJsonArr->Count; i++)
	{
		SET_LOG_MEMO1(LJsonArr->Items[i]->ToString());
		TJSONArray *LItemArr = (TJSONArray*)TJSONObject::ParseJSONValue(
						TEncoding::UTF8->GetBytes(LJsonArr->Items[i]->ToString()), 0);
		for (int j = 0; j < LItemArr->Count; j++)
		{
			if (!LItemArr->Items[j]->Value().IsEmpty())
			{
				APK_INFO[i][j] = LItemArr->Items[j]->Value();
//				SET_LOG_MEMO1(LItemArr->Items[j]->Value());
				if(ioDevice->sDeviceGuid.UpperCase() == LItemArr->Items[j]->Value().UpperCase())
				{
					ioDevice->sWebUrl = APK_INFO[i][_C_WEB_URL];
				}
			}
		}
		LItemArr->Free();
	}
	LJsonArr->Free();

	SET_LOG_MEMO1(ioDevice->sWebUrl);

	String muin_set3_json = GetJsonResult(URL_GET_LOCALE_SETTING);

	JsonArrToArray(muin_set3_json);

	if(ioDevice->sWebUrl != "")
	{
		sgcWSServer->Active = true;
//		SET_LOG_MEMO1(sgcWSServer->Port);

		WebBrowser1->EnableCaching = false;
		WebBrowser1->Navigate(ioDevice->sWebUrl);

//		#if defined(_PLAT_MSWINDOWS)
//		String path = ChangeFilePath(APK_INFO[_L_CUSTOM][_C_WEB_URL], ExtractFilePath(ParamStr(0)));
//		SET_LOG_MEMO1(path);
//		WebBrowser1->Navigate(path);
//		#else
//		#if defined(_PLAT_ANDROID)
//		WebBrowser1->Navigate(APK_INFO[_L_CUSTOM][_C_WEB_URL]);
//		#endif
//		#endif
	}

	if(APK_INFO[_L_CUSTOM][_C_UDP_PORT] != "")
	{
//		SET_LOG_MEMO1(APK_INFO[_L_CUSTOM][_C_UDP_PORT]);
//		IdUDPServer1->DefaultPort = StrToInt(APK_INFO[_L_CUSTOM][_C_UDP_PORT]);
//		IdUDPServer1->Bindings->Clear();
//		SHandle = IdUDPServer1->Bindings->Add();
//		SHandle->IP = "0.0.0.0";
//		SHandle->Port = StrToInt(APK_INFO[_L_CUSTOM][_C_UDP_PORT]);
//
//		IdUDPServer1->Active =true;
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SET_LOG_MEMO1(String data)
{
	int memo_cnt = Memo1->Lines->Count;
	if (memo_cnt > 5000)
	{
		Memo1->Lines->Clear();
	}
	Memo1->Lines->Add(Now().FormatString(L"[hh:nn:ss:zzz]") + " " + data);

	memset(&debuf_buf, 0, sizeof(debuf_buf));
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Delay(unsigned int _time)
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
void __fastcall TForm1::SetPermissions()
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

void __fastcall TForm1::CreateConfigInfo(String FileName)
{
	if(!FileExists(FileName))
	{
		ForceDirectories(ExtractFilePath(FileName));
		//create
		MemIni = new TMemIniFile(FileName);

		ioDevice->sDeviceGuid = UtilHelper->CreateGuid();

		SetConfigInfo();
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::GetConfigInfo()
{
	CreateConfigInfo(ioDevice->sConfigPath);

    if (!MemIni) {
        MemIni = new TMemIniFile(ioDevice->sConfigPath);
    }
	else
	{
        MemIni->Rename(ioDevice->sConfigPath, true);
	}

	ioDevice->sDeviceGuid = MemIni->ReadString(L"Config", L"device_guid", ioDevice->sDeviceGuid);

	sprintf(http_buf, "%s?_t=%s", AnsiString(URL_DEVICE_BASE).c_str(),
				AnsiString(ioDevice->sDeviceGuid).c_str());

	ioDevice->sRequestUrl = http_buf;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::SetConfigInfo()
{
	if (MemIni)
	{
		MemIni->WriteString (L"Config", L"device_guid", ioDevice->sDeviceGuid);

		MemIni->UpdateFile();
	}
	else
	{

    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SOCKET_SERVER_SEND(String sIPAddr, unsigned int nPort, String sMessage)
{
	if(sIPAddr != NULL && nPort > 0)
	{
		if(IdUDPServer1->Active)
		{
			#if defined(_PLAT_ANDROID)
			sIPAddr = GetInternetIP(sIPAddr);
			#endif
			#if defined(_PLAT_MSWINDOWS)
			char host[100];
			sprintf(host, "%s", AnsiString(sIPAddr).c_str());
			sIPAddr = UtilHelper->GetIpByDomainName(host);
			#endif
			if(sIPAddr == "0.0.0.0")
			{
				SET_LOG_MEMO1("sMessage faild");
				return;
			}

			#if defined(_PLAT_MSWINDOWS)
			OutputDebugString(sIPAddr.c_str());
			#endif
			sprintf(debuf_buf, "sMessage => %s", AnsiString(sMessage).c_str());
			SET_LOG_MEMO1(debuf_buf);

			SHandle->SendTo(sIPAddr, nPort, sMessage, Id_IPv4, enUTF8);
			Application->ProcessMessages();
		}
	}
	else
	{
		SET_LOG_MEMO1("udp server not active.");
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SOCKET_CLIENT_SEND(String sIPAddr, unsigned int nPort, String sMessage)
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
	SET_LOG_MEMO1(debuf_buf);

	String recv_data = IdUDPClient1->ReceiveString(3000, enUTF8);

	if(!recv_data.IsEmpty())
	{
		sprintf(debuf_buf, "recv_data => %s", AnsiString(recv_data).c_str());
		SET_LOG_MEMO1(debuf_buf);

		String web_func = "WebMessage('" + recv_data + "')";
		ExecWebBrowserJavascript(web_func);
	}
//	Application->ProcessMessages();

}
//---------------------------------------------------------------------------
void __fastcall TForm1::IdUDPServer1UDPRead(TIdUDPListenerThread *AThread, const TIdBytes AData,
          TIdSocketHandle *ABinding)
{
	String recv_data = BytesToString(AData, enUTF8);

	if (!recv_data.IsEmpty())
	{
		DynamicArray<String> recv_list = SplitString(recv_data, "#");
		if(recv_list.Length > 0)
		{
			if(recv_list[0] == CMD_RETURN_CONFIG)
			{
				JsonArrToArray(recv_list[1]);
//				sprintf(debuf_buf, "recv_data => %s", AnsiString(recv_list[1]).c_str());
			};
//			SET_LOG_MEMO1(debuf_buf);
		}
		else
		{
			sprintf(debuf_buf, "recv_data => %s", AnsiString(recv_data).c_str());
			SET_LOG_MEMO1(debuf_buf);
		}

	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
	WebBrowser1->Reload();
//	SOCKET_SERVER_SEND(SERVER_365_DOMAIN, UDP_SERVER_PORT, "test");
//	UDP_CLIENT_TODO(SERVER_365_DOMAIN, UDP_SERVER_PORT, "test");
    return;

	String sMacAddress;
	#ifdef __ANDROID_API__

//	JEnumeration LInterfaces;
//	TJNetworkInterface LInterface;
	_di_JEnumeration LInterfaces;
	_di_JNetworkInterface LInterface;
//	TJavaArray__1<Byte> LAddress;

	LInterfaces = TJNetworkInterface::JavaClass->getNetworkInterfaces();
	SET_LOG_MEMO1(LInterfaces->hasMoreElements());

//	while (LInterfaces->hasMoreElements()) {
//		LInterface = TJNetworkInterface::Wrap(LInterfaces->nextElement());
//		SET_LOG_MEMO1(JStringToString(LInterface->getName()));

//			LAddress = LInterface->getHardwareAddress();

//		if (JStringToString(LInterface->getName())->Equals('wlan0')) {
//			LAddress = LInterface->getHardwareAddress();
//			strMacAddress.sprintf(L"%02x:%02x:%02x:%02x:%02x:%02x",
//                LAddress[0], LAddress[1], LAddress[2], LAddress[3], LAddress[4], LAddress[5]);
//			SET_LOG_MEMO(strMacAddress);
//		}
//	}
	#endif

}
//---------------------------------------------------------------------------

String __fastcall TForm1::GetInternetIP(String sDomain)
{
    UTF8String sJsonResult;

    TStringStream *ss = new TStringStream();
	TIdHTTP *idHttp = new TIdHTTP(this);
	try {
		idHttp->ProtocolVersion = pv1_1;
		idHttp->Request->Accept = "application/json";
		idHttp->Request->ContentType = "application/json";
		idHttp->ConnectTimeout = 3000;
        idHttp->ReadTimeout = 3000;
		//ssl 일경우 libeay32.dll, ssleay32.dll copy
		String request_data = request_data.sprintf(L"http://api.iotc365.com/api/get/ip_text?domain=%s&format=json", AnsiString(sDomain).c_str());

//		sJsonResult = idHttp->Get(request_data.Trim());
		idHttp->Get(request_data.Trim(), ss);
		ss->Position = 0;
		sJsonResult = ss->DataString.Trim();
        //jsonobj 로 변경
		//에러 생기면 rad 10.2 맞는지 확인
	}
	catch (Exception &e)
	{

	}

	idHttp->Free();
	delete idHttp;
    delete ss;

	return sJsonResult;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::JsonArrToArray(String sJsonData)
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
String __fastcall TForm1::GetJsonResult(String url)
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
//		SET_LOG_MEMO1(result);
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

void __fastcall TForm1::ExecWebBrowserJavascript(String strFunc)
{
	try {
		SET_LOG_MEMO1(strFunc);
		WebBrowser1->EvaluateJavaScript(strFunc);
	} catch (Exception &ex) {
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender)
{
	try
	{
		IdIPWatch1->Active = true; //Indy
		IdIPWatch1->ForceCheck();
		if(IdIPWatch1->IsOnline)
			Label1->Text = IdIPWatch1->CurrentIP;
		else
			Label1->Text = IdIPWatch1->LocalIP();
		SET_LOG_MEMO1(IdIPWatch1->LocalIP());

		IdIPWatch1->Active = false;
	}
	catch(Exception &ex)
	{

	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
    Timer1->Enabled = false;
	Initialize();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::sgcWSServerMessage(TsgcWSConnection *Connection, const UnicodeString Text)
{
//	SET_LOG_MEMO1("websocket message.");

//	SET_LOG_MEMO1(muin_set3[_L3_설정][_C3_DOMAIN]);
	SET_LOG_MEMO1(muin_set3[_L3_무인1][_C3_포트]);
	SOCKET_CLIENT_SEND(muin_set3[_L3_설정][_C3_DOMAIN], StrToInt(muin_set3[_L3_무인1][_C3_포트]), Text);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::sgcWSServerConnect(TsgcWSConnection *Connection)
{
	#ifdef _Windows
//	RoundRect1->Fill->Color = clLime;
	#endif
}
//---------------------------------------------------------------------------

void __fastcall TForm1::sgcWSServerDisconnect(TsgcWSConnection *Connection, int Code)
{
//    RoundRect1->Fill->Color = clRed;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::WebBrowser1DidFinishLoad(TObject *ASender)
{
	SET_LOG_MEMO1("___finish");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::WebBrowser1DidStartLoad(TObject *ASender)
{
	ClearWebSocketClients();
}
//-----------------------------------------------------------------

void __fastcall TForm1::ClearWebSocketClients()
{
	if (sgcWSServer->Active)
	{
		SET_LOG_MEMO1("ClearWebSocketClients");
		TIdContext *idContext;
		#ifdef _Windows
		TList *ClientsList = sgcWSServer->LockList();
		#endif
		#if defined(_PLAT_ANDROID)
        TList__1<TIdContext*> *ClientsList = sgcWSServer->LockList();
		#endif
		try {
			for (int i = 0; i < ClientsList->Count; i++)
			{
				idContext = static_cast<TIdContext*>(ClientsList->Items[i]);

				idContext->Connection->IOHandler->InputBuffer->Clear();
				idContext->Connection->Disconnect();
			}
		}
		__finally {
			sgcWSServer->UnLockList();
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Rectangle1Click(TObject *Sender)
{
//	String info_json = GetJsonResult(URL_WEB_BASE_INFO);
//	SET_LOG_MEMO1(info_json);
	if(pnlDebug->Visible)
	{
		pnlDebug->Visible = false;
	}
	else
	{
		pnlDebug->Visible = true;
		Initialize();
	}
}
//---------------------------------------------------------------------------
