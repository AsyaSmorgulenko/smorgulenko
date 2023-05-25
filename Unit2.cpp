//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <cctype>
#include <System.Character.hpp>

#include "Unit2.h"
#include "Unit3.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
TForm3 *Form3;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------ЗАПОЛНЕНИЕ ФОРМЫ О НОВОМ ИЗДЕЛИИИ-----------------------
void __fastcall TForm2::Button1Click(TObject *Sender)
{
	if (Edit1->Text.IsEmpty() || Edit2->Text.IsEmpty() || Edit3->Text.IsEmpty() ||
		Edit4->Text.IsEmpty() || Edit5->Text.IsEmpty() || Edit6->Text.IsEmpty() ||
		Edit7->Text.IsEmpty()) {
		ShowMessage("Остались пустые поля поля");
	} else
	{
	//-------------------ДОБАВЛЕНИЕ------------------------
		if (Button1->Caption == "Добавить")
		{
			Edit1->SetFocus();
			Edit1->Text =  Edit1->Text.SubString(1,1).UpperCase()+Edit1->Text.SubString(2,Edit1->Text.Length());
			Edit4->Text =  Edit4->Text.SubString(1,1).UpperCase()+Edit4->Text.SubString(2,Edit4->Text.Length());
			Edit5->Text =  Edit5->Text.SubString(1,1).UpperCase()+Edit5->Text.SubString(2,Edit5->Text.Length());
			Edit6->Text =  Edit6->Text.SubString(1,1).UpperCase()+Edit6->Text.SubString(2,Edit6->Text.Length());
			Form3->StringGrid1->RowCount++; // добавляем строку
			int lastRow = Form3->StringGrid1->RowCount - 1;
			Form3->StringGrid1->Cells[0][lastRow] = IntToStr(lastRow);
			Form3->StringGrid1->Cells[1][lastRow] = Edit1->Text;  // перемещаемся по столбцам
			Form3->StringGrid1->Cells[2][lastRow] = Edit2->Text;
			Form3->StringGrid1->Cells[3][lastRow] = Edit3->Text;
			Form3->StringGrid1->Cells[4][lastRow] = Edit4->Text;
			Form3->StringGrid1->Cells[5][lastRow] = Edit5->Text;
			Form3->StringGrid1->Cells[6][lastRow] = Edit6->Text;
			Form3->StringGrid1->Cells[7][lastRow] = Edit7->Text;

		Form2->Edit1->Clear();
		Form2->Edit2->Clear();
		Form2->Edit3->Clear();
		Form2->Edit4->Clear();
		Form2->Edit5->Clear();
		Form2->Edit6->Clear();
		Form2->Edit7->Clear();
		Form2->Close();
		}


		//----------------------РЕДАКТИРОВАНИЕ-------------------------------------------
		else if (Button1->Caption == "Редактировать")
		{
			int lastRow = Form3->StringGrid1->Row;
            Edit1->Text =  Edit1->Text.SubString(1,1).UpperCase()+Edit1->Text.SubString(2,Edit1->Text.Length());
			Edit4->Text =  Edit4->Text.SubString(1,1).UpperCase()+Edit4->Text.SubString(2,Edit4->Text.Length());
			Edit5->Text =  Edit5->Text.SubString(1,1).UpperCase()+Edit5->Text.SubString(2,Edit5->Text.Length());
			Edit6->Text =  Edit6->Text.SubString(1,1).UpperCase()+Edit6->Text.SubString(2,Edit6->Text.Length());
			Form3->StringGrid1->Cells[1][lastRow] = Edit1->Text;
			Form3->StringGrid1->Cells[2][lastRow] = Edit2->Text;
			Form3->StringGrid1->Cells[3][lastRow] = Edit3->Text;
			Form3->StringGrid1->Cells[4][lastRow] = Edit4->Text;
			Form3->StringGrid1->Cells[5][lastRow] = Edit5->Text;
			Form3->StringGrid1->Cells[6][lastRow] = Edit6->Text;
			Form3->StringGrid1->Cells[7][lastRow] = Edit7->Text;

		Form2->Edit1->Clear();
		Form2->Edit2->Clear();
		Form2->Edit3->Clear();
		Form2->Edit4->Clear();
		Form2->Edit5->Clear();
		Form2->Edit6->Clear();
		Form2->Edit7->Clear();
		Form2->Close();
	}
}
}

//--------------------------ПЕРЕХОД ЧЕРЕЗ ENTER----------------------------------------------
void __fastcall TForm2::Edit1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	 if(Key == VK_RETURN) Edit2->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Edit2KeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	 if(Key == VK_RETURN) Edit3->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Edit3KeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	 if(Key == VK_RETURN) Edit4->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Edit4KeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	 if(Key == VK_RETURN) Edit5->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Edit5KeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	 if(Key == VK_RETURN) Edit6->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Edit6KeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	 if(Key == VK_RETURN) Edit7->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Edit7KeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	 if(Key == VK_RETURN) Button1->SetFocus();
}
//---------------------------------------------------------------------------


//----------------------------------ТИП ДАННЫХ В ФОРМЕ-------------------------------------
void __fastcall TForm2::Edit1KeyPress(TObject *Sender, System::WideChar &Key)
{
 if (!Character::IsLetter(Key) && Key != VK_BACK && Key!=VK_RETURN) // Если это не буква и не клавиша Backspace
	{   ShowMessage("Введите только буквы");
		Key = 0; // Отменить ввод
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Edit2KeyPress(TObject *Sender, System::WideChar &Key)
{
	if (!std::isdigit(Key) && Key != VK_BACK && Key!=VK_RETURN) // Если это не цифра и не клавиша Backspace
	{   ShowMessage("Введите только цифры");
		Key = 0; // Отменить ввод
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Edit3KeyPress(TObject *Sender, System::WideChar &Key)
{
	if (!std::isdigit(Key) && Key != VK_BACK && Key!=VK_RETURN) // Если это не цифра и не клавиша Backspace
	{   ShowMessage("Введите только цифры");
		Key = 0; // Отменить ввод
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Edit4KeyPress(TObject *Sender, System::WideChar &Key)
{
	if (!Character::IsLetter(Key) && Key != VK_BACK && Key!=VK_RETURN) // Если это не буква и не клавиша Backspace
	{   ShowMessage("Введите только буквы");
		Key = 0; // Отменить ввод
	}

}
//---------------------------------------------------------------------------

void __fastcall TForm2::Edit5KeyPress(TObject *Sender, System::WideChar &Key)
{
   if (!Character::IsLetter(Key) && Key != VK_BACK && Key!=VK_RETURN) // Если это не буква и не клавиша Backspace
	{   ShowMessage("Введите только буквы");
		Key = 0; // Отменить ввод
	}

}
//---------------------------------------------------------------------------

void __fastcall TForm2::Edit6KeyPress(TObject *Sender, System::WideChar &Key)
{
	if (!Character::IsLetter(Key) && Key != VK_BACK && Key!=VK_RETURN) // Если это не буква и не клавиша Backspace
	{   ShowMessage("Введите только буквы");
		Key = 0; // Отменить ввод
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Edit7KeyPress(TObject *Sender, System::WideChar &Key)
{
	if (!std::isdigit(Key) && Key != VK_BACK && Key!=VK_RETURN) // Если это не цифра и не клавиша Backspace
	{   ShowMessage("Введите только цифры");
		Key = 0; // Отменить ввод
	}
}
//---------------------------------------------------------------------------

