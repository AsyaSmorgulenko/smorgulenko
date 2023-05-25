//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit6.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm6 *Form6;
//---------------------------------------------------------------------------
__fastcall TForm6::TForm6(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm6::FormCreate(TObject *Sender)
{
    	StringGrid1->Cells[0][0]="№";
		StringGrid1->Cells[1][0]="Название изделия";
		StringGrid1->Cells[2][0]="Цена";
		StringGrid1->Cells[3][0]="Вес изделия";
		StringGrid1->Cells[4][0]="Изготовитель";
		StringGrid1->Cells[5][0]="Основной материал";
		StringGrid1->Cells[6][0]="Драгоценный камень";
		StringGrid1->Cells[7][0]="Вес камня в каратах";

}
//---------------------------------------------------------------------------
