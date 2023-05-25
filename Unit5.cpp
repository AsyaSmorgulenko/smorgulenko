//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit5.h"
#include "Unit6.h"
#include "Unit3.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm5 *Form5;

#include <System.StrUtils.hpp>
TStringGrid *TempGrid;
//---------------------------------------------------------------------------
__fastcall TForm5::TForm5(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm5::Button1Click(TObject *Sender)
{
   if (Edit1->Text.IsEmpty()) {
		  ShowMessage("Пожалуйста, введите вес камня");
		   return;
		}else{
		double requiredWeight = StrToFloat(Edit1->Text);

		// Подсчет количества продуктов, удовлетворяющих условию
		int count = 0;
		for(int i = 1; i < Form3->StringGrid1->RowCount; i++)
		{
			if(StrToFloat(Form3->StringGrid1->Cells[7][i]) > requiredWeight)
			{
				count++;
			}
		}

		// Если нет подходящих продуктов, выходим из функции
		if(count == 0)
		{
			ShowMessage("Нет продуктов с весом камня больше " + FloatToStr(requiredWeight));
			return;
		}

		// Сохраняем исходные данные
		TempGrid = new TStringGrid(this);
		TempGrid->ColCount = Form3->StringGrid1->ColCount;
		TempGrid->RowCount = Form3->StringGrid1->RowCount;
		for(int i = 0; i < Form3->StringGrid1->RowCount; i++)
		{
			for(int j = 0; j < Form3->StringGrid1->ColCount; j++)
			{
				TempGrid->Cells[j][i] = Form3->StringGrid1->Cells[j][i];
			}
		}


		Form6->StringGrid1->RowCount = count + 1;
		int rowNumber = 1;
		for(int i = 1; i < TempGrid->RowCount; i++)
		{
			if(StrToFloat(TempGrid->Cells[7][i]) > requiredWeight)
			{
				for(int j = 0; j < Form3->StringGrid1->ColCount; j++)
				{
					Form6->StringGrid1->Cells[j][rowNumber] = TempGrid->Cells[j][i];
				}
				rowNumber++;
			}
		}}
	   Form5->Close();
	   Form6->ShowModal();
	   Form5->Edit1->Clear();
}

//---------------------------------------------------------------------------
void __fastcall TForm5::Edit1KeyPress(TObject *Sender, System::WideChar &Key)
{
if (!std::isdigit(Key) && Key != VK_BACK && Key!=VK_RETURN)// Если это не цифра и не клавиша Backspace
{   ShowMessage("Введите только цифры без пробелов");
  Key = 0; // Отменить ввод
 }
}
//---------------------------------------------------------------------------
