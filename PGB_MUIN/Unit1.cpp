//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <mshtml.h>
#include "iotc_define.h"
//#include "json.h"
#include "Unit1.h"
#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//#pragma link "jsoncpp.lib"
#pragma link "sgcWebSocket"
#pragma link "sgcWebSocket_Classes"
#pragma link "sgcWebSocket_Server"
#pragma resource "*.dfm"
TmForm *mForm;

//---------------------------------------------------------------------------
__fastcall TmForm::TmForm(TComponent* Owner)
	: TForm(Owner)
{
	ioDevice = new IOTC_DEVICE;

	UtilHelper = new TUtilHelper;
}
//---------------------------------------------------------------------------
void __fastcall TmForm::FormCreate(TObject *Sender)
{
	ioDevice->sConfigPath = "C:\\Users\\Public\\Documents\\iotc\\d\\s\\io_config.ini";

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
    GetConfigInfo();
//	sprintf(ioDevice->sMacAddress, "%s", AnsiString(UtilHelper->GetMacAddress()).c_str());
//	ioDevice->sMacAddress = UtilHelper->GetMacAddress();

//	hwsForm->SET_LOG_MEMO1(ioDevice->sMacAddress);

	UTF8String info_json = GetJsonResult(ioDevice->sRequestUrl);

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

				if(ioDevice->sDeviceGuid.UpperCase() == (LItemArr->Items[j]->Value()).UpperCase())
				{
//					sprintf(ioDevice->sWebUrl, "%s", AnsiString(APK_INFO[i][_C_WEB_URL]).c_str());
					ioDevice->sWebUrl = APK_INFO[i][_C_WEB_URL];
					ioDevice->nUDPPort = StrToInt(APK_INFO[i][_C_UDP_PORT]);
				}
			}
		}
		LItemArr->Free();
	}
	LJsonArr->Free();

//	hwsForm->SET_LOG_MEMO1(ioDevice->sWebUrl);

	if(ioDevice->sWebUrl != "")
	{
		sgcWSServer1->Active = true;

//		WebBrowser1->EnableCaching = false;
		WebBrowser1->Navigate(ioDevice->sWebUrl);
	}


	IdUDPServer1->DefaultPort = ioDevice->nUDPPort;

	if(IdUDPServer1->Active)
	{
		IdUDPServer1->Active = false;

		IdUDPServer1->Bindings->Clear();
		SHandle = IdUDPServer1->Bindings->Add();
		SHandle->IP = "0.0.0.0";
		SHandle->Port = ioDevice->nUDPPort;
		IdUDPServer1->Active = true;
	}
	else
	{
		IdUDPServer1->Bindings->Clear();
		SHandle = IdUDPServer1->Bindings->Add();
		SHandle->IP = "0.0.0.0";
		SHandle->Port = ioDevice->nUDPPort;
		IdUDPServer1->Active = true;
    }
}
//---------------------------------------------------------------------------

void __fastcall TmForm::CreateConfigInfo(String FileName)
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

void __fastcall TmForm::GetConfigInfo()
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

void __fastcall TmForm::SetConfigInfo()
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

	TIdHTTP *HTTP = new TIdHTTP(this);
	try {
		HTTP->ProtocolVersion = pv1_1;
		HTTP->Request->Accept = "application/json";
		HTTP->Request->ContentType = "application/json, charset=utf-8";
//		HTTP->IOHandler->DefStringEncoding = enUTF8;
		//ssl 일경우 libeay32.dll, ssleay32.dll copy
		result = HTTP->Get(url);
	}
	catch (Exception &e)
	{

	}

	HTTP->Free();

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
			if(sRecvData == "GTOP1")
			{
				int state = hwsForm->OPEN_SIGNAL();
				SOCKET_SERVER_SEND(ABinding->PeerIP, ABinding->PeerPort, IntToStr(state));
			}
			else
			{
				SOCKET_SERVER_SEND(ABinding->PeerIP, ABinding->PeerPort, edtReturnV->Text);
			}
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
void __fastcall TmForm::btnHWFormClick(TObject *Sender)
{
	hwsForm->Show();
}
//---------------------------------------------------------------------------
void __fastcall TmForm::Button1Click(TObject *Sender)
{
	Initialize();

	hwsForm->SET_LOG_MEMO1(ioDevice->sDeviceGuid);
	hwsForm->SET_LOG_MEMO1(ioDevice->sRequestUrl);
	hwsForm->SET_LOG_MEMO1(ioDevice->nUDPPort);
}
//---------------------------------------------------------------------------

