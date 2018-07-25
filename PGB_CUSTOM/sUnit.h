//---------------------------------------------------------------------------

#ifndef sUnitH
#define sUnitH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <System.IniFiles.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdUDPBase.hpp>
#include <IdUDPServer.hpp>
#include <IdGlobal.hpp>
#include <IdSocketHandle.hpp>
#include "AdvGrid.hpp"
#include "AdvObj.hpp"
#include "AdvUtil.hpp"
#include "BaseGrid.hpp"
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ValEdit.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.Menus.hpp>
#include <IdExplicitTLSClientServerBase.hpp>
#include <IdFTP.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>
//---------------------------------------------------------------------------
class CONFIG_FILE_PATH
{
public:
	String sLocaleInfo;
	String sLocaleCamera;
};
CONFIG_FILE_PATH *Cfg_FilePath;
//---------------------------------------------------------------------------

class TServerForm : public TForm
{
__published:	// IDE-managed Components
	TButton *btnCleanLog;
	TMemo *Memo1;
	TIdUDPServer *IdUDPServer1;
	TPageControl *PageControl1;
	TTabSheet *tabBase;
	TTabSheet *tabConfig2;
	TAdvStringGrid *AdvStringGrid4;
	TGroupBox *GroupBox3;
	TButton *Button2;
	TPanel *Panel1;
	TPanel *Panel2;
	TTabSheet *tabFile;
	TLabel *Label1;
	TPanel *Panel3;
	TSplitter *Splitter2;
	TPanel *Panel4;
	TButton *Button3;
	TButton *Button4;
	TButton *Button5;
	TPanel *PanelRight;
	TValueListEditor *ValueList;
	TPanel *Panel7;
	TMemo *Memo2;
	TOpenDialog *OpenDialog1;
	TPopupMenu *PopupMenu1;
	TMenuItem *N3;
	TMenuItem *N1;
	TMenuItem *N2;
	TButton *Button6;
	TButton *Button7;
	TIdFTP *IdFTP1;
	TProgressBar *ProgressBar1;
	TListBox *ListBox1;
	TButton *Button1;
	TPopupMenu *PopupMenu2;
	TMenuItem *pM1;
	TLabel *Label2;
	TEdit *Edit1;
	TLabel *Label3;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall IdUDPServer1UDPRead(TIdUDPListenerThread *AThread, const TIdBytes AData,
		  TIdSocketHandle *ABinding);
	void __fastcall btnCleanLogClick(TObject *Sender);
	void __fastcall ValueListDblClick(TObject *Sender);
	void __fastcall N1Click(TObject *Sender);
	void __fastcall N2Click(TObject *Sender);
	void __fastcall N3Click(TObject *Sender);
	void __fastcall Button6Click(TObject *Sender);
	void __fastcall Button7Click(TObject *Sender);
	void __fastcall pM1Click(TObject *Sender);
	void __fastcall ListBox1ContextPopup(TObject *Sender, TPoint &MousePos, bool &Handled);

private:	// User declarations
	TIdSocketHandle * SHandle;

	void __fastcall SET_LOG_MEMO1(String data);
	void __fastcall SET_LOG_MEMO2(String data);
	void __fastcall SOCKET_SEND(String sIPAddr, unsigned int nPort, String sMessage);

	void __fastcall CreateConfigInfo(String FileName);
	void __fastcall GetConfigInfo();
	void __fastcall SetConfigInfo();
	void __fastcall AddConfigFile();
	UTF8String __fastcall ExcelToJsonArray(TAdvStringGrid *advGrid, String JsonFileName);

	void __fastcall FileUpdate();
	void __fastcall FileRenamed(UnicodeString sFile, UnicodeString nFile);
	void __fastcall FtpDirCheck();

	void __fastcall FtpConnect();
	void __fastcall FtpDisconnect();
	void __fastcall FtpFileFound();
	void __fastcall FtpFileUpload(UnicodeString sFile, String sSheetName);
	AnsiString __fastcall WithoutFileExt(AnsiString fn);




public:		// User declarations

	TMemIniFile *MemIni;
	String ApplicationPath, ConfigPath;
	char debuf_buf[1024*100];
	char send_buf[1024*100];

	UnicodeString ftp_Host;
	unsigned short ftp_Port;
	UnicodeString ftp_Username;
	UnicodeString ftp_Password;

	UnicodeString sFtpDir;

    String test_config_data;

	__fastcall TServerForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TServerForm *ServerForm;
//---------------------------------------------------------------------------
#endif
