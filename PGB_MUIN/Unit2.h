//---------------------------------------------------------------------------

#ifndef Unit2H
#define Unit2H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "ZylSerialPort.hpp"
//---------------------------------------------------------------------------
class ThwsForm : public TForm
{
__published:	// IDE-managed Components
	TMemo *Memo1;
	TButton *btnGate;
	TZylSerialPort *IO_coin_bill_IN_con_OUT_6;
	TZylSerialPort *RS485_2;
	TZylSerialPort *halin_3;
	TZylSerialPort *bill_out_4;
	TZylSerialPort *printer_5;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall btnGateClick(TObject *Sender);
	void __fastcall IO_coin_bill_IN_con_OUT_6Receive(TObject *Sender, AnsiString Buffer);

private:	// User declarations
    void __fastcall SET_LOG_MEMO1(String sData);

public:		// User declarations
	void __fastcall Init_HW_COM();
    void __fastcall OPEN_SIGNAL();

	__fastcall ThwsForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE ThwsForm *hwsForm;
//---------------------------------------------------------------------------
#endif
