//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ZylSerialPort"
#pragma resource "*.dfm"
ThwsForm *hwsForm;


char rx1_buf[50], buf[50];
char *p1 = new char[5000];
unsigned int coin_num10, coin_num50, coin_num, coin_500_cnt;
long in_100, in_500, in_1000, in_5000, in_10000, in_coin, in_bill;
long out_100, out_500, out_1000, out_5000, out_100_db = 0, out_500_db = 0,
	out_1000_db = 0, out_5000_db = 0;
unsigned char ActiveStatus;
char loop1_flag;
char loop2_flag, reset_flag;
int run_com6;


//---------------------------------------------------------------------------
__fastcall ThwsForm::ThwsForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall ThwsForm::FormCreate(TObject *Sender)
{
    Init_HW_COM();
}
//---------------------------------------------------------------------------
void __fastcall ThwsForm::SET_LOG_MEMO1(String sData)
{
	int memo_cnt = Memo1->Lines->Count;
	if (memo_cnt > 5000)
	{
		Memo1->Lines->Clear();
	}
	Memo1->Lines->Add(Now().FormatString(L"[hh:nn:ss:zzz]") + " " + sData);
}
//---------------------------------------------------------------------------
void __fastcall ThwsForm::Init_HW_COM()
{
	/*
	t_money_1->Port = spCOM1;
	t_money_1->BaudRate = br009600;
	t_money_1->Open();

	halin_3->Port = spCOM3;
	halin_3->BaudRate = br019200;
	halin_3->Open();

	bill_out_4->Port = spCOM4;
	bill_out_4->BaudRate = br009600;
	bill_out_4->Open();

	printer_5->Port = spCOM5;
	printer_5->BaudRate = br019200;
	printer_5->Open();

	*/
	try {

		IO_coin_bill_IN_con_OUT_6->Port = spCOM6;
		IO_coin_bill_IN_con_OUT_6->BaudRate = br019200;
		IO_coin_bill_IN_con_OUT_6->Open();

		IO_coin_bill_IN_con_OUT_6->SendData
			((char *)"SF2345678912345678901234567890123456789E", 40);
//		halin_3->SendData((char *)"Sread_OF_E", 10);
	}
	catch (Exception &ex)
	{
		SET_LOG_MEMO1(ex.ClassName() + " - " + ex.Message);
	}
}
//---------------------------------------------------------------------------
void __fastcall ThwsForm::OPEN_SIGNAL()
{
	try {
		IO_coin_bill_IN_con_OUT_6->SendData
			((char *)"SGO345678912345678901234567890123456789E", 40);
	}
	catch (Exception &ex)
	{
		SET_LOG_MEMO1(ex.ClassName() + " - " + ex.Message);
	}
}
//---------------------------------------------------------------------------
void __fastcall ThwsForm::btnGateClick(TObject *Sender)
{
	OPEN_SIGNAL();
}
//---------------------------------------------------------------------------

void __fastcall ThwsForm::IO_coin_bill_IN_con_OUT_6Receive(TObject *Sender, AnsiString Buffer)
{
	char sensen[50];
	int len;

	run_com6 = 1;

	strcpy(buf, Buffer.c_str());
	len = strlen(buf);

	for (int cnt = 0; cnt < len; cnt++) {
		// SC-000-000-001-002-0123456789012345678CE
		rx1_buf[40] = buf[cnt];
		for (int i = 0; i < 40; i++)
			rx1_buf[i] = rx1_buf[i + 1];

		if (rx1_buf[0] == 'S' && rx1_buf[1] == 'm' && rx1_buf[39] == 'E') {
			// Memo1->Lines->Add( AnsiString(rx1_buf).c_str());

//			if (StrToInt(Form1->L7_->Caption) > 0) {
//				for (int ii = 0; ii < 40; ii++)
//					MCARD_data[ii] = rx1_buf[ii];
//				// Memo1->Lines->Add("MCARD_data");
//				// Memo1->Lines->Add( AnsiString(MCARD_data).c_str());
//				MCARD_Timer->Enabled = 1;
//				MCARD_flag = 1;
//			}
		}

		if (rx1_buf[0] == 'S' && rx1_buf[39] == 'E' && rx1_buf[1] != 'm') {
			sensen[1] = 'W';
			sensen[0] = 'S';
			sensen[39] = 'E';

			if (rx1_buf[1] == 'C' && rx1_buf[2] == '-' && rx1_buf[37] == 'c') {
				// Form1->Memo4->Lines->Add("coin in");
				for (int i = 0, k = 0, l = 0; i < 40; i++) {
					p1[k] = rx1_buf[i];
					k++;
					if (rx1_buf[i] == '-') {
						p1[k - 1] = 0;
						k = 0;
						l++;
						// if( l == 1 )car_num1 = p1;
						if (l == 2)
							coin_num10 = StrToInt(p1);
						if (l == 3)
							coin_num50 = StrToInt(p1);
						if (l == 4)
							coin_num = StrToInt(p1);
						if (l == 5)
							coin_500_cnt = StrToInt(p1);
					}
				}

				if (coin_num > 0)
					in_100 += 100; // * (coin_num);
				if (coin_500_cnt > 0)
					in_500 += 500; // * (coin_500_cnt);

			}
			if (rx1_buf[30] == '$' && rx1_buf[37] == 'p') {
				if (rx1_buf[31] == 'E' && rx1_buf[32] == 'S') {
					ActiveStatus = rx1_buf[33];
					sprintf(&sensen[30], "$%c%c%c%c", 'e', 's', ActiveStatus,
						(unsigned char)'e' + (unsigned char)'s' +
						(unsigned char)ActiveStatus);
					for (int k = 0; k < 40; k++) {
						if (sensen[k] == 0)
							sensen[k] += 0x30;
					}

					IO_coin_bill_IN_con_OUT_6->SendData((char *) sensen, 40);

					if (rx1_buf[33] == 0x0B) {
						Sleep(500L);
						sprintf(&sensen[30], "$%c%c%c%c", 'G', 'B', 0x3F, 0xC8);
						IO_coin_bill_IN_con_OUT_6->SendData
							((char *) sensen, 40);
					}
					break;
				}
				if (rx1_buf[31] == 0x67 && rx1_buf[32] == 0x62 && rx1_buf[33]
					== 0x05) {
					in_5000 += 5000;
					// in_bill = in_5000;
				}
				if (rx1_buf[31] == 0x67 && rx1_buf[32] == 0x62 && rx1_buf[33]
					== 0x01) {
					in_1000 += 1000;
					// in_bill = in_1000;
				}
				if (rx1_buf[31] == 0x67 && rx1_buf[32] == 0x62 && rx1_buf[33]
					== 0x0A) {
					in_10000 += 10000;
					// in_bill = in_10000;
				}
			}

			if (rx1_buf[1] == 'C' && rx1_buf[2] == '-' && rx1_buf[37] == 'o') {
				if (rx1_buf[3] == '1') {
//					if (jungsan_ing_flag3 == 0)
//						Button11Click(NULL); // 영수증 발행     검정선,빨간선 쇼트
				}

				if (rx1_buf[5] == '1') // 버튼키 활성화   노란선,하얀선 쇼트
				{

//				   in_car_flag = 1;
//
//				  if(jangbi == "출구무인정산기") {
//					  Form1->Button54Click(NULL);
//				   }// else Form1->Button38Click(NULL);

				}

//				if( in_car_flag == 1 && rx1_buf[5] == '0')
//				{
//				  if(jangbi == "출구무인정산기") {
//					  Form1->out_car_func( "BACK_CAR" );
//					 // Form1->Button54Click(NULL);
//				   in_car_flag = 0;
//				   }
//				}



				if (rx1_buf[7] == '1') // 경차판별기      파란색,녹색선 쇼트
				{
//					Form1->Label48->Caption = "경차할인";
				}
				if (rx1_buf[9] == '0')
					loop1_flag = 1;
				else
					loop1_flag = 0;
				if (rx1_buf[11] == '0')
					loop2_flag = 1;
				else
					loop2_flag = 0;
			}
			rx1_buf[40] = 0;
			break;

		}

	}

	run_com6 = 0;
}
//---------------------------------------------------------------------------
