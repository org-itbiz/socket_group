//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "sUnit.h"
#include "iotc_define.h"
#include "UtilHelper.h"
#include "json.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "AdvGrid"
#pragma link "AdvObj"
#pragma link "AdvUtil"
#pragma link "BaseGrid"
#pragma resource "*.dfm"
TServerForm *ServerForm;

//---------------------------------------------------------------------------
__fastcall TServerForm::TServerForm(TComponent* Owner)
	: TForm(Owner)
{
    Cfg_FilePath = new CONFIG_FILE_PATH;
}
//---------------------------------------------------------------------------
void __fastcall TServerForm::FormCreate(TObject *Sender)
{
	ApplicationPath = ExtractFilePath(ParamStr(0));
	ConfigPath = ChangeFilePath("config.ini", ApplicationPath);

    GetConfigInfo();

	Cfg_FilePath->sLocaleInfo = "ConfigXls";

	ftp_Host = "iotc365.com";
	ftp_Port = 21;
	ftp_Username = "iotcweb";
	ftp_Password = "qwer1234";

	sFtpDir = "iotc365.com\\test_locale";

	IdUDPServer1->DefaultPort = UDP_SERVER_PORT;
	IdUDPServer1->Bindings->Clear();
	SHandle = IdUDPServer1->Bindings->Add();
	SHandle->IP = "0.0.0.0";
	SHandle->Port = UDP_SERVER_PORT;

    Edit1->Text = "return 값";

	IdUDPServer1->Active =true;
}
//---------------------------------------------------------------------------
void __fastcall TServerForm::FormCloseQuery(TObject *Sender, bool &CanClose)
{
	//
	FtpDisconnect();
}
//---------------------------------------------------------------------------
void __fastcall TServerForm::SET_LOG_MEMO1(String data)
{
	int memo_cnt = Memo1->Lines->Count;
	if (memo_cnt > 1000)
	{
		Memo1->Lines->Clear();
	}
	Memo1->Lines->Add(Now().FormatString(L"[hh:nn:ss:zzz]") + " " + data);

	memset(&debuf_buf, 0, sizeof(debuf_buf));
}
//---------------------------------------------------------------------------
void __fastcall TServerForm::SET_LOG_MEMO2(String data)
{
	int memo_cnt = Memo2->Lines->Count;
	if (memo_cnt > 1000)
	{
		Memo2->Lines->Clear();
	}
	Memo2->Lines->Add(Now().FormatString(L"[hh:nn:ss:zzz]") + " " + data);

//	memset(&debuf_buf, 0, sizeof(debuf_buf));
}
//---------------------------------------------------------------------------

void __fastcall TServerForm::SOCKET_SEND(String sIPAddr, unsigned int nPort, String sMessage)
{
	if(sIPAddr != NULL && nPort > 0)
	{
//		sprintf(debuf_buf, "sMessage => %s", AnsiString(sMessage).c_str());
//		SET_LOG_MEMO1(debuf_buf);
		SET_LOG_MEMO1(sIPAddr);
		SET_LOG_MEMO1(nPort);

		SHandle->SendTo(sIPAddr, nPort, sMessage, Id_IPv4, enUTF8);



        return;

		int total_size = sMessage.Length();
		int max_size = 1000;
		int n_size = total_size / max_size;
		int left_size = total_size - n_size * max_size ;
		int page_size = left_size > 0 ? n_size + 1 : n_size;
//		SET_LOG_MEMO1(page_size);
		String str_message;
		for (int i = 0; i < page_size; i++)
		{
			if(i == page_size - 1)
			{
				str_message = sMessage.SubString(i*max_size+1, left_size);
				SET_LOG_MEMO1(i);
			}
			else
			{
				str_message = sMessage.SubString(i*max_size+1, max_size);
				SET_LOG_MEMO1(i);
			}

			SHandle->SendTo(sIPAddr, nPort, str_message, Id_IPv4, enUTF8);
//			Sleep(10);
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TServerForm::IdUDPServer1UDPRead(TIdUDPListenerThread *AThread, const TIdBytes AData,
          TIdSocketHandle *ABinding)
{
	String recv_data = BytesToString(AData, enUTF8);

	if (!recv_data.IsEmpty())
	{
		sprintf(debuf_buf, "recv_data => %s", AnsiString(recv_data).c_str());
		SET_LOG_MEMO1(debuf_buf);
//		ABinding->SendTo(ABinding->PeerIP, ABinding->PeerPort, recv_data, Id_IPv4, enUTF8);
//		Application->ProcessMessages();

		if(recv_data == CMD_GET_CONFIG)
		{
			sprintf(send_buf, "%s#%s", AnsiString(CMD_RETURN_CONFIG).c_str()
									 , AnsiString(test_config_data).c_str());
			SOCKET_SEND(ABinding->PeerIP, ABinding->PeerPort, send_buf);
		}
		else
		{

			SOCKET_SEND(ABinding->PeerIP, ABinding->PeerPort, Edit1->Text);
		}


		memset(&send_buf, 0, sizeof(send_buf));
	}
}
//---------------------------------------------------------------------------

void __fastcall TServerForm::btnCleanLogClick(TObject *Sender)
{
    Memo1->Lines->Clear();
}
//---------------------------------------------------------------------------

void __fastcall TServerForm::CreateConfigInfo(String FileName)
{
	if(!FileExists(FileName))
	{
		ForceDirectories(ExtractFilePath(FileName));
		//create
		MemIni = new TMemIniFile(FileName);


		SetConfigInfo();
	}
}
//---------------------------------------------------------------------------

void __fastcall TServerForm::GetConfigInfo()
{
	CreateConfigInfo(ConfigPath);

	for (int i = 1; i < ValueList->RowCount; i++)
	{
		if (ValueList->Keys[i] != "")
		{
			ValueList->DeleteRow(i);
		}
	}

	if (!MemIni)
	{
		MemIni = new TMemIniFile(ConfigPath);
	}
	else
	{
		MemIni->Rename(ConfigPath, true);
	}


	if (MemIni->SectionExists("Path"))
	{
		MemIni->ReadSectionValues("Path", ValueList->Strings);

		for (int i = 1; i < ValueList->RowCount; i++)
		{
			if (!ValueList->Keys[i].IsEmpty())
			{
				String sFile = ValueList->Values[ValueList->Keys[i]];
				if(!sFile.IsEmpty())
				{
					TStringList *lst = new TStringList;
					lst = AdvStringGrid4->GetXLSSheets(sFile);

					for (int i = 0; i < lst->Count; i++)
					{
						ListBox1->Items->Add(lst->Strings[i]);
					}
				}
			}
		}
	}





}
//---------------------------------------------------------------------------

void __fastcall TServerForm::SetConfigInfo()
{
	if (MemIni)
	{
		MemIni->UpdateFile();
	}
	else
	{

	}
}
//---------------------------------------------------------------------------

void __fastcall TServerForm::AddConfigFile()
{
	UnicodeString key, value;
	int in = 0;

	OpenDialog1->Filter = "Update files|*.XLS;*.XLSX";
	OpenDialog1->Title = "파일 선택";

	if (OpenDialog1->Execute()) {
		if (FileExists(OpenDialog1->FileName)) {
			value = OpenDialog1->FileName;
			key = ChangeFileExt(ExtractFileName(value), "");

			for (int i = 0; i < ValueList->VisibleRowCount; i++) {
				if (ValueList->Keys[i + 1] == key) {
					in = 1;
					break;
				}
			}

			if (in == 0) {
				ValueList->InsertRow(key, value, true);
			}
			else if (in == 1) {
				ValueList->Values[key] = value;
			}

			MemIni->WriteString("Path", key, value);
            SetConfigInfo();
		}
		else {
			SET_LOG_MEMO2("파일 불러오기 실패");
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TServerForm::ValueListDblClick(TObject *Sender)
{
	UnicodeString sFile = ValueList->Values[ValueList->Keys[ValueList->Row]];
	ShellExecuteA(NULL, "open", AnsiString(sFile).c_str(), NULL, NULL, SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------

void __fastcall TServerForm::N1Click(TObject *Sender)
{
    AddConfigFile();
}
//---------------------------------------------------------------------------

void __fastcall TServerForm::N2Click(TObject *Sender)
{
	int row = ValueList->Row;
	UnicodeString key = ValueList->Keys[row];

	MemIni->DeleteKey("Path", key);
    SetConfigInfo();
	ValueList->DeleteRow(row);
}
//---------------------------------------------------------------------------

void __fastcall TServerForm::N3Click(TObject *Sender)
{
	// 경로 열기
	UnicodeString sFilePath = ExtractFilePath(ValueList->Values[ValueList->Keys[ValueList->Row]]);
	ShellExecuteA(0, "explore", AnsiString(sFilePath).c_str(), NULL, NULL, SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------

UTF8String __fastcall TServerForm::ExcelToJsonArray(TAdvStringGrid *advGrid, String JsonFileName)
{
	Json::Value root;

	for (int i = 0; i < 50; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			if(UTF8String(advGrid->Cells[j][i]) != "")
			{
				root[i][j] = UTF8String(advGrid->Cells[j][i]).c_str();
			}
		}
	}
	UTF8String str_root = root.toStyledString().c_str();

	/*
	*/
	if(!str_root.IsEmpty())
	{
		int hFile = FileCreate(JsonFileName);
		if(hFile>=0)
		{
//			FileWrite(hFile, "\xEF\xBB\xBF",3); // UTF8
			FileWrite(hFile, "callback(",9); // callback start
			FileWrite(hFile, str_root.c_str(), str_root.Length());
			FileWrite(hFile, ")",1); //callback end
			FileClose(hFile);
		}
    }

	return str_root;
}
//---------------------------------------------------------------------------
void __fastcall TServerForm::FileUpdate()
{
	UnicodeString sFile = ValueList->Values[ValueList->Keys[ValueList->Row]];
	SET_LOG_MEMO2(sFile);

	// 프로그램 종료

//	UnicodeString dFile = ChangeFilePath(sFile, ExtractFilePath(sFile) + "temp");
//	setLogMemo(dFile);

//	UnicodeString nFile = ChangeFileExt(ExtractFileName(sFile), "") + "_new.exe";
	UnicodeString nFile = ChangeFileExt(sFile, ".new");
	SET_LOG_MEMO2(nFile);

    return;

//	FtpFileDownload(sFile);
	FileRenamed(sFile, nFile);

	// 프로그램 실행
//	ShellExecuteA(NULL, "open", AnsiString(sFile).c_str(), NULL, NULL, SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------
void __fastcall TServerForm::FileRenamed(UnicodeString sFile, UnicodeString nFile)
{
	// 파일 이름 바꾸기
	if (FileExists(sFile)) {
		DeleteFileA(AnsiString(sFile).c_str());
	}

	// nFile -> sFile 이름변경
	if (!RenameFile(nFile, sFile)) {
		SET_LOG_MEMO2("!이름 변경 실패");
	}
}
//---------------------------------------------------------------------------
void __fastcall TServerForm::FtpConnect()
{
	// FTP 접속
	if (IdFTP1->Connected() == false) {
		IdFTP1->Host = ftp_Host;
		IdFTP1->Port = ftp_Port;
		IdFTP1->Username = ftp_Username;
		IdFTP1->Password = ftp_Password;

		IdFTP1->Passive = true;

		IdFTP1->Connect();
		IdFTP1->TransferType = ftBinary;
		IdFTP1->ChangeDir("/");
	}
}
//---------------------------------------------------------------------------
void __fastcall TServerForm::FtpDisconnect()
{
	// FTP 접속 헤재
	if (IdFTP1->Connected()) {
		IdFTP1->Disconnect();
		IdFTP1->Quit();
	}
}
//---------------------------------------------------------------------------
void __fastcall TServerForm::FtpFileFound()
{
	FtpConnect();

	if (IdFTP1->Connected()) {
		UnicodeString filename = "";

	}

	FtpDisconnect();
}
//---------------------------------------------------------------------------
void __fastcall TServerForm::FtpFileUpload(UnicodeString sFile, String sSheetName)
{
	FtpConnect();

	// 파일 업로드
	if (IdFTP1->Connected()) {
		if (FileExists(sFile)) {
			UnicodeString iFile = ExtractFileName(sFile);

			IdFTP1->ChangeDir(sFtpDir);
            IdFTP1->List(NULL);
			int iCnt = 0;

			for (int i = 0; i < IdFTP1->DirectoryListing->Count; i++)
			{
				if (IdFTP1->DirectoryListing->Items[i]->ItemType == ditDirectory
					&& IdFTP1->DirectoryListing->Items[i]->FileName == sSheetName)
				{
					iCnt++;
				}

			}

			if(iCnt == 0)
			{
				IdFTP1->MakeDir(sSheetName);
                Sleep(10);
            }

			IdFTP1->TransferType = ftBinary;

			try {
				IdFTP1->ChangeDir(sSheetName);
				IdFTP1->List(NULL);

				for (int i = 0; i < IdFTP1->DirectoryListing->Count; i++) {
					if (IdFTP1->DirectoryListing->Items[i]->FileName == iFile) {
						IdFTP1->Delete(iFile);
						SET_LOG_MEMO2("ftp 파일 삭제");
						break;
					}
				}

				ProgressBar1->Max = FileSizeByName(sFile);
				ProgressBar1->Show();
				IdFTP1->Put(sFile, iFile, false);
				sprintf(debuf_buf, "upload file : http://iotc365.com/test_locale/%s/%s"
								, AnsiString(sSheetName).c_str()
								, AnsiString(iFile).c_str());
				SET_LOG_MEMO2(debuf_buf);
			} catch (Exception& e) {
				SET_LOG_MEMO2("upload file fail!");
			}
		}
		else {
			SET_LOG_MEMO2("not found file : " + sFile);
		}
	}

	FtpDisconnect();

//	cbFtpDirChange(NULL);
}
//---------------------------------------------------------------------------
AnsiString __fastcall TServerForm::WithoutFileExt(AnsiString fn)
{
 int dp=fn.Length();
 while (dp!=0 && fn[dp]!='.') dp--;

 if (dp) return fn.SubString(1,dp-1);

 return fn;
}
//---------------------------------------------------------------------------

void __fastcall TServerForm::Button6Click(TObject *Sender)
{
	String test_config_path = ValueList->Values["test_config"];

	if(!test_config_path.IsEmpty())
	{
		AdvStringGrid4->LoadFromXLS("http://iotc365.com/test_locale/test_config.xls");

		test_config_data = ExcelToJsonArray(AdvStringGrid4,"test_config");
	}

}
//---------------------------------------------------------------------------
void __fastcall TServerForm::Button7Click(TObject *Sender)
{
	String txt = "abcdefghijklmnopqrstuvwxyz1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int total_length = txt.Length();
	int max_length = 9;
	int cut_size = total_length / max_length;
	int page_size = total_length % max_length > 0 ? cut_size + 1 : cut_size;
	SET_LOG_MEMO1(page_size);
	for (int i = 0; i < page_size; i++)
	{
		SET_LOG_MEMO1(txt.SubString(i*max_length+1, max_length));
	}
}
//---------------------------------------------------------------------------
void __fastcall TServerForm::pM1Click(TObject *Sender)
{
	String sheet_name = ListBox1->Items->Strings[ListBox1->ItemIndex];

	UnicodeString sFile;
	int count = ValueList->RowCount;
	for (int i = 1; i < count; i++) {
		sFile = ValueList->Values[ValueList->Keys[i]];
		FtpFileUpload(sFile, sheet_name);
		AdvStringGrid4->LoadFromXLSSheet(sFile, sheet_name);

//		String sFileName = WithoutFileExt(ExtractFileName(sFile));

//		String sFilePath = ExtractFilePath(sFile);
		String temp_folder = ChangeFilePath("temp", ExtractFilePath(sFile));
		sFile = ChangeFilePath(sheet_name + ".json", temp_folder);

		if(!FileExists(sFile))
		{
			ForceDirectories(ExtractFilePath(sFile));
		}

		String str_config = ExcelToJsonArray(AdvStringGrid4, sFile);

		FtpFileUpload(sFile, sheet_name);
	}


}
//---------------------------------------------------------------------------

void __fastcall TServerForm::ListBox1ContextPopup(TObject *Sender, TPoint &MousePos,
          bool &Handled)
{
	if(ListBox1->ItemIndex == -1)
	{
        PopupMenu2->CloseMenu();
	}
}
//---------------------------------------------------------------------------

