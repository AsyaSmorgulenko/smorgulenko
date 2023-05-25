//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <fstream>

#include <System.StrUtils.hpp>

#include "Unit3.h"
#include "Unit2.h"
#include "Unit4.h"
#include "Unit5.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm3 *Form3;

struct Product {
	int id;
	char name[50];
	double price;
	double weight;
	char manufacturer[50];
	char material[50];
	char gem[50];
	double gemWeight;
};

//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner)
	: TForm(Owner)
{
}
//-------------------------------------РАБОТА С ФОРМОЙ---------------------------------------------
void __fastcall TForm3::FormCreate(TObject *Sender) //называем коллонки
{
		StringGrid1->Cells[0][0]="№";
		StringGrid1->Cells[1][0]="Название изделия";
		StringGrid1->Cells[2][0]="Цена";
		StringGrid1->Cells[3][0]="Вес изделия";
		StringGrid1->Cells[4][0]="Изготовитель";
		StringGrid1->Cells[5][0]="Основной материал";
		StringGrid1->Cells[6][0]="Драгоценный камень";
		StringGrid1->Cells[7][0]="Вес камня в каратах";

		Form4 = new TForm4(this);
		Form4->ShowModal();
		Form4->Free();
}
//---------------------------------------------------------------------------

void __fastcall TForm3::N10Click(TObject *Sender)
{       //подговливаем форму к редактированию
		Form2->Button1->Caption = "Добавить"; // переименовываем на "Редактировать"
		Form2->ShowModal();
		int rCount;
  for (int i = 0; i < StringGrid1->RowCount; i++)
  {
	  rCount = i;
  }
  StatusBar2->Panels->Items[0]->Text = "Число элементов: " + IntToStr(rCount);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::N11Click(TObject *Sender)
{
	if (StringGrid1->Row > 0) { // Если выбрана строка
		// Заполняем поля на Form2 данными из выбранной строки
		Form2->Edit1->Text = StringGrid1->Cells[1][StringGrid1->Row];
		Form2->Edit2->Text = StringGrid1->Cells[2][StringGrid1->Row];
		Form2->Edit3->Text = StringGrid1->Cells[3][StringGrid1->Row];
		Form2->Edit4->Text = StringGrid1->Cells[4][StringGrid1->Row];
		Form2->Edit5->Text = StringGrid1->Cells[5][StringGrid1->Row];
		Form2->Edit6->Text = StringGrid1->Cells[6][StringGrid1->Row];
		Form2->Edit7->Text = StringGrid1->Cells[7][StringGrid1->Row];
		Form2->Button1->Caption = "Редактировать"; // Переименовываем Button1 на "Редактировать"
		Form2->ShowModal(); // Открываем Form2
	} else {
		ShowMessage("Выберите строку для редактирования");
	}
}
//---------------------------------------------------------------------------
//УДАЛЕНИЕ СТРОКИ
void __fastcall TForm3::N12Click(TObject *Sender)
{
	int row = StringGrid1->Row; // присваиваем номер строки
	if (row >= 1 && row < StringGrid1->RowCount)
	{
		if (MessageDlg("Вы действительно хотите удалить эту строку?\n Изделие:" +   StringGrid1->Cells[1][row] +  "\n По цене: " + StringGrid1->Cells[2][row] + "\n По весу: " + StringGrid1->Cells[3][row] + "\n Производителя: " + StringGrid1->Cells[4][row]+ "\n С основным материалом: "+ StringGrid1->Cells[5][row]+ "\n Драгоценным камнем: :" + StringGrid1->Cells[6][row]+"\n Весом в каратах: "+ StringGrid1->Cells[7][row], mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrYes)
		//выбираем эмблемку и выводимое сообщение
		{
			for (int i = row; i < StringGrid1->RowCount - 1; i++)
			{
			//проходимся по всей табличке
				for (int j = 0; j < StringGrid1->ColCount; j++)
				{
					StringGrid1->Cells[j][i] = StringGrid1->Cells[j][i + 1]; //поднимаем все строки на 1 вверх
				}
			}
			StringGrid1->RowCount--; //меняем количество строк

			 //перезаписываем номера
			 for (int i = 1; i < StringGrid1->RowCount; i++)
			{
				StringGrid1->Cells[0][i] = IntToStr(i);
			}



        }
	}
      int rCount;
  for (int i = 0; i < StringGrid1->RowCount; i++)
  {
	  rCount = i;
  }
  StatusBar2->Panels->Items[0]->Text = "Число элементов: " + IntToStr(rCount);
}
//---------------------------------------------------------------------------------





//---------------------------РАБОТА С БИНАРНЫМ ФАЙЛОМ-------------------------------------------------------
//создание
void __fastcall TForm3::N2Click(TObject *Sender) //кнопка создать
{
	SaveDialog1->Filter = "Binary files (*.bin)|*.bin";
	SaveDialog1->DefaultExt = "bin"; //присваиваем формат

	if (SaveDialog1->Execute()) {
		std::ofstream outFile(SaveDialog1->FileName.c_str(), std::ios::out | std::ios::binary);
		if (!outFile)
		{
			ShowMessage("Ошибка при создании файла!");
		}
		else
		{
			ShowMessage("Файл создан");
			outFile.close(); //закрываем
		}
	}
}
//---------------------------------------------------------------------------

// открытие
void __fastcall TForm3::N3Click(TObject *Sender)
{
	OpenDialog1->Filter = "Binary files (*.bin)|*.bin";
	OpenDialog1->DefaultExt = "bin";
	if (OpenDialog1->Execute()) {
		std::ifstream inFile(OpenDialog1->FileName.c_str(), std::ios::in | std::ios::binary);
		if (!inFile)
		{
			ShowMessage("Ошибка");
		} else
		{
			currentFileName = OpenDialog1->FileName;

			Product product;
			StringGrid1->RowCount = 2;
			while (inFile.read((char*)&product, sizeof(Product)))
			//записываем файл
			{
				StringGrid1->Cells[0][StringGrid1->RowCount - 1] = product.id;
				StringGrid1->Cells[1][StringGrid1->RowCount - 1] = product.name;
				StringGrid1->Cells[2][StringGrid1->RowCount - 1] = product.price;
				StringGrid1->Cells[3][StringGrid1->RowCount - 1] = product.weight;
				StringGrid1->Cells[4][StringGrid1->RowCount - 1] = product.manufacturer;
				StringGrid1->Cells[5][StringGrid1->RowCount - 1] = product.material;
				StringGrid1->Cells[6][StringGrid1->RowCount - 1] = product.gem;
				StringGrid1->Cells[7][StringGrid1->RowCount - 1] = product.gemWeight;
				StringGrid1->RowCount++; //
			}
			StringGrid1->RowCount--;
			inFile.close();
		}
	}
      int rCount;
  for (int i = 0; i < StringGrid1->RowCount; i++)
  {
	  rCount = i;
  }
  StatusBar2->Panels->Items[0]->Text = "Число элементов: " + IntToStr(rCount);
}

//------------------------------------------------------------------------
//сохранение
 void __fastcall TForm3::N4Click(TObject *Sender)
{
	if (!currentFileName.IsEmpty()) {
		std::ofstream outFile(currentFileName.c_str(), std::ios::out | std::ios::binary);
		if (!outFile) {
			ShowMessage("Ошибка");
		} else {
			Product product;
			for (int i = 1; i < StringGrid1->RowCount; i++)
			 {
				product.id = StrToInt(StringGrid1->Cells[0][i]);
				strncpy(product.name, AnsiString(StringGrid1->Cells[1][i]).c_str(), sizeof(product.name));
				product.price = StrToFloat(StringGrid1->Cells[2][i]);
				product.weight = StrToFloat(StringGrid1->Cells[3][i]);
				strncpy(product.manufacturer, AnsiString(StringGrid1->Cells[4][i]).c_str(), sizeof(product.manufacturer));
				strncpy(product.material, AnsiString(StringGrid1->Cells[5][i]).c_str(), sizeof(product.material));
				strncpy(product.gem, AnsiString(StringGrid1->Cells[6][i]).c_str(), sizeof(product.gem));
				product.gemWeight = StrToFloat(StringGrid1->Cells[7][i]);
				outFile.write((char*)&product, sizeof(Product));
			}
			outFile.close();
			ShowMessage("Файл сохранен");
		}
	} else
	{
		ShowMessage("Ошибка: нет открытого файла для сохранения");
	}
}


//---------------------------------------------------------------------------
void __fastcall TForm3::N5Click(TObject *Sender) //сохранить как
{
	SaveDialog1->Filter = "Binary files (*.bin)|*.bin";
	SaveDialog1->DefaultExt = "bin";
	if (SaveDialog1->Execute()) {
		currentFileName = SaveDialog1->FileName;
		std::ofstream outFile(currentFileName.c_str(), std::ios::out | std::ios::binary);
		if (!outFile) {
			ShowMessage("Ошибка");
		} else {
			Product product;
			for (int i = 1; i < StringGrid1->RowCount; i++)
			{
				product.id = StrToInt(StringGrid1->Cells[0][i]);
				strncpy(product.name, AnsiString(StringGrid1->Cells[1][i]).c_str(), sizeof(product.name));
				product.price = StrToFloat(StringGrid1->Cells[2][i]);
				product.weight = StrToFloat(StringGrid1->Cells[3][i]);
				strncpy(product.manufacturer, AnsiString(StringGrid1->Cells[4][i]).c_str(), sizeof(product.manufacturer));
				strncpy(product.material, AnsiString(StringGrid1->Cells[5][i]).c_str(), sizeof(product.material));
				strncpy(product.gem, AnsiString(StringGrid1->Cells[6][i]).c_str(), sizeof(product.gem));
				product.gemWeight = StrToFloat(StringGrid1->Cells[7][i]);
				outFile.write((char*)&product, sizeof(Product));
			}
			outFile.close();
			ShowMessage("Файл сохранен");
		}
	}
}






//--------------------------------------ПОИСК ПО КРИТЕРИЮ----------------------------------------------
void __fastcall TForm3::N7Click(TObject *Sender)
{
     UnicodeString searchText = InputBox("Поиск", "Введите номер изделия", "");
  int searchType = MessageDlg("Поиск по полному совпадению?", mtConfirmation, TMsgDlgButtons() << mbYes << mbNo << mbCancel, 0);
  // Полное совпадение
  if (searchType == mrYes) {
 for (int i = 1; i < StringGrid1->RowCount; i++) {
 if (StringGrid1->Cells[0][i] == searchText) {
  StringGrid1->Row = i; // выделить найденную строку
  ShowMessage("Найдено изделие по номеру\nHомер изделия: " + searchText +"\nНазвание изделия: "+StringGrid1->Cells[1][i]+"\nЦена изделия: "+StringGrid1->Cells[2][i]+"\nВес изделия: "+StringGrid1->Cells[3][i]+"\nИзготовитель: "+StringGrid1->Cells[4][i]+"\nОсновной материал: "+StringGrid1->Cells[5][i]+"\nДрагоценный камень: "+StringGrid1->Cells[6][i]+"\nВес камня: "+StringGrid1->Cells[7][i]);
  return;   }
 }  }
  // Начало строки
  else if (searchType == mrNo) { for (int i = 1; i < StringGrid1->RowCount; i++) {
   if (AnsiStartsText(searchText, StringGrid1->Cells[0][i]))    {
  StringGrid1->Row = i; // выделить найденную строку
  ShowMessage("Найден номер изделия: " + StringGrid1->Cells[0][i]+"\nНазвание изделия: "+StringGrid1->Cells[1][i]+"\nЦена изделия: "+StringGrid1->Cells[2][i]+"\nВес изделия: "+StringGrid1->Cells[3][i]+"\nИзготовитель: "+StringGrid1->Cells[4][i]+"\nОсновной материал: "+StringGrid1->Cells[5][i]+"\nДрагоценный камень: "+StringGrid1->Cells[6][i]+"\nВес камня: "+StringGrid1->Cells[7][i]);
  return;
  }
 }
  }
  // Отмена
  else {
 return;  }
  ShowMessage("Изделие по номеру не найдено");
}


void __fastcall TForm3::N22Click(TObject *Sender)
{

	UnicodeString searchText = InputBox("Поиск", "Введите название изделия", "");   int searchType = MessageDlg("Поиск по полному совпадению?", mtConfirmation, TMsgDlgButtons() << mbYes << mbNo << mbCancel, 0);
   // Полное совпадение
   if (searchType == mrYes) {
 for (int i = 1; i < StringGrid1->RowCount; i++)
  {   if (StringGrid1->Cells[1][i] == searchText) {
  StringGrid1->Row = i; // выделить найденную строку
  ShowMessage("Найдено изделие по названию\nНомер изделия: " + StringGrid1->Cells[0][i] +"\nНазвание изделия: "+StringGrid1->Cells[1][i]+"\nЦена изделия: "+StringGrid1->Cells[2][i]+"\nВес изделия: "+StringGrid1->Cells[3][i]+"\nИзготовитель: "+StringGrid1->Cells[4][i]+"\nОсновной материал: "+StringGrid1->Cells[5][i]+"\nДрагоценный камень: "+StringGrid1->Cells[6][i]+"\nВес камня: "+StringGrid1->Cells[7][i]);
  return;   }
 }  }
  // Начало строки
  else if (searchType == mrNo) {
 for (int i = 1; i < StringGrid1->RowCount; i++) {
   if (AnsiStartsText(searchText, StringGrid1->Cells[1][i]))    {
  StringGrid1->Row = i; // выделить найденную строку
  ShowMessage("Найдено изделие по названию\nНомер изделия: " +StringGrid1->Cells[0][i]  +"\nНазвание изделия: "+StringGrid1->Cells[1][i]+"\nЦена изделия: "+StringGrid1->Cells[2][i]+"\nВес изделия: "+StringGrid1->Cells[3][i]+"\nИзготовитель: "+StringGrid1->Cells[4][i]+"\nОсновной материал: "+StringGrid1->Cells[5][i]+"\nДрагоценный камень: "+StringGrid1->Cells[6][i]+"\nВес камня: "+StringGrid1->Cells[7][i]);
  return;   }
 }  }
  // Отмена
  else {
 return;  }
 ShowMessage("Изделие по названию не найдено");


}
//---------------------------------------------------------------------------
void __fastcall TForm3::N23Click(TObject *Sender)
{

		UnicodeString searchText = InputBox("Поиск", "Введите цену изделия", "");   int searchType = MessageDlg("Поиск по полному совпадению?", mtConfirmation, TMsgDlgButtons() << mbYes << mbNo << mbCancel, 0);
   // Полное совпадение
   if (searchType == mrYes) {
 for (int i = 1; i < StringGrid1->RowCount; i++) {   if (StringGrid1->Cells[2][i] == searchText) {
  StringGrid1->Row = i; // выделить найденную строку
  ShowMessage("Найдено изделие по цене\nНомер изделия: " + StringGrid1->Cells[0][i] +"\nНазвание изделия: "+StringGrid1->Cells[1][i]+"\nЦена изделия: "+StringGrid1->Cells[2][i]+"\nВес изделия: "+StringGrid1->Cells[3][i]+"\nИзготовитель: "+StringGrid1->Cells[4][i]+"\nОсновной материал: "+StringGrid1->Cells[5][i]+"\nДрагоценный камень: "+StringGrid1->Cells[6][i]+"\nВес камня: "+StringGrid1->Cells[7][i]);
  return;   }
 }  }
  // Начало строки
  else if (searchType == mrNo) {
 for (int i = 1; i < StringGrid1->RowCount; i++) {
   if (AnsiStartsText(searchText, StringGrid1->Cells[2][i]))    {
  StringGrid1->Row = i; // выделить найденную строку
  ShowMessage("Найдено изделие по цене\nНомер изделия: " +StringGrid1->Cells[0][i]  +"\nНазвание изделия: "+StringGrid1->Cells[1][i]+"\nЦена изделия: "+StringGrid1->Cells[2][i]+"\nВес изделия: "+StringGrid1->Cells[3][i]+"\nИзготовитель: "+StringGrid1->Cells[4][i]+"\nОсновной материал: "+StringGrid1->Cells[5][i]+"\nДрагоценный камень: "+StringGrid1->Cells[6][i]+"\nВес камня: "+StringGrid1->Cells[7][i]);
  return;   }
 }  }
  // Отмена
  else {
 return;  }
 ShowMessage("Изделие по цене не найдено");

}
//---------------------------------------------------------------------------
void __fastcall TForm3::N24Click(TObject *Sender)
{
			UnicodeString searchText = InputBox("Поиск", "Введите вес изделия", "");   int searchType = MessageDlg("Поиск по полному совпадению?", mtConfirmation, TMsgDlgButtons() << mbYes << mbNo << mbCancel, 0);
   // Полное совпадение
   if (searchType == mrYes) {
 for (int i = 1; i < StringGrid1->RowCount; i++) {   if (StringGrid1->Cells[3][i] == searchText) {
  StringGrid1->Row = i; // выделить найденную строку
  ShowMessage("Найдено изделие по весу\nНомер изделия: " + StringGrid1->Cells[0][i] +"\nНазвание изделия: "+StringGrid1->Cells[1][i]+"\nЦена изделия: "+StringGrid1->Cells[2][i]+"\nВес изделия: "+StringGrid1->Cells[3][i]+"\nИзготовитель: "+StringGrid1->Cells[4][i]+"\nОсновной материал: "+StringGrid1->Cells[5][i]+"\nДрагоценный камень: "+StringGrid1->Cells[6][i]+"\nВес камня: "+StringGrid1->Cells[7][i]);
  return;   }
 }  }
  // Начало строки
  else if (searchType == mrNo) {
 for (int i = 1; i < StringGrid1->RowCount; i++) {
   if (AnsiStartsText(searchText, StringGrid1->Cells[3][i]))    {
  StringGrid1->Row = i; // выделить найденную строку
  ShowMessage("Найдено изделие по весу\nНомер изделия: " +StringGrid1->Cells[0][i]  +"\nНазвание изделия: "+StringGrid1->Cells[1][i]+"\nЦена изделия: "+StringGrid1->Cells[2][i]+"\nВес изделия: "+StringGrid1->Cells[3][i]+"\nИзготовитель: "+StringGrid1->Cells[4][i]+"\nОсновной материал: "+StringGrid1->Cells[5][i]+"\nДрагоценный камень: "+StringGrid1->Cells[6][i]+"\nВес камня: "+StringGrid1->Cells[7][i]);
  return;   }
 }  }
  // Отмена
  else {
 return;  }
 ShowMessage("Изделие по весу не найдено");
}
//---------------------------------------------------------------------------
void __fastcall TForm3::N25Click(TObject *Sender)
{
			UnicodeString searchText = InputBox("Поиск", "Введите производителя изделия", "");   int searchType = MessageDlg("Поиск по полному совпадению?", mtConfirmation, TMsgDlgButtons() << mbYes << mbNo << mbCancel, 0);
   // Полное совпадение
   if (searchType == mrYes) {
 for (int i = 1; i < StringGrid1->RowCount; i++) {   if (StringGrid1->Cells[4][i] == searchText) {
  StringGrid1->Row = i; // выделить найденную строку
  ShowMessage("Найдено изделие по весу\nНомер изделия: " + StringGrid1->Cells[0][i] +"\nНазвание изделия: "+StringGrid1->Cells[1][i]+"\nЦена изделия: "+StringGrid1->Cells[2][i]+"\nВес изделия: "+StringGrid1->Cells[3][i]+"\nИзготовитель: "+StringGrid1->Cells[4][i]+"\nОсновной материал: "+StringGrid1->Cells[5][i]+"\nДрагоценный камень: "+StringGrid1->Cells[6][i]+"\nВес камня: "+StringGrid1->Cells[7][i]);
  return;   }
 }  }
  // Начало строки
  else if (searchType == mrNo) {
 for (int i = 1; i < StringGrid1->RowCount; i++) {
   if (AnsiStartsText(searchText, StringGrid1->Cells[4][i]))    {
  StringGrid1->Row = i; // выделить найденную строку
  ShowMessage("Найдено изделие по производителю\nНомер изделия: " +StringGrid1->Cells[0][i]  +"\nНазвание изделия: "+StringGrid1->Cells[1][i]+"\nЦена изделия: "+StringGrid1->Cells[2][i]+"\nВес изделия: "+StringGrid1->Cells[3][i]+"\nИзготовитель: "+StringGrid1->Cells[4][i]+"\nОсновной материал: "+StringGrid1->Cells[5][i]+"\nДрагоценный камень: "+StringGrid1->Cells[6][i]+"\nВес камня: "+StringGrid1->Cells[7][i]);
  return;   }
 }  }
  // Отмена
  else {
 return;  }
 ShowMessage("Изделие по производителю не найдено");
}
//---------------------------------------------------------------------------

void __fastcall TForm3::N26Click(TObject *Sender)
{
			UnicodeString searchText = InputBox("Поиск", "Введите основной материал изделия", "");   int searchType = MessageDlg("Поиск по полному совпадению?", mtConfirmation, TMsgDlgButtons() << mbYes << mbNo << mbCancel, 0);
   // Полное совпадение
   if (searchType == mrYes) {
 for (int i = 1; i < StringGrid1->RowCount; i++) {   if (StringGrid1->Cells[5][i] == searchText) {
  StringGrid1->Row = i; // выделить найденную строку
  ShowMessage("Найдено изделие по основному материалу\nНомер изделия: " + StringGrid1->Cells[0][i] +"\nНазвание изделия: "+StringGrid1->Cells[1][i]+"\nЦена изделия: "+StringGrid1->Cells[2][i]+"\nВес изделия: "+StringGrid1->Cells[3][i]+"\nИзготовитель: "+StringGrid1->Cells[4][i]+"\nОсновной материал: "+StringGrid1->Cells[5][i]+"\nДрагоценный камень: "+StringGrid1->Cells[6][i]+"\nВес камня: "+StringGrid1->Cells[7][i]);
  return;   }
 }  }
  // Начало строки
  else if (searchType == mrNo) {
 for (int i = 1; i < StringGrid1->RowCount; i++) {
   if (AnsiStartsText(searchText, StringGrid1->Cells[5][i]))    {
  StringGrid1->Row = i; // выделить найденную строку
  ShowMessage("Найдено изделие по основному материалу\nНомер изделия: " +StringGrid1->Cells[0][i]  +"\nНазвание изделия: "+StringGrid1->Cells[1][i]+"\nЦена изделия: "+StringGrid1->Cells[2][i]+"\nВес изделия: "+StringGrid1->Cells[3][i]+"\nИзготовитель: "+StringGrid1->Cells[4][i]+"\nОсновной материал: "+StringGrid1->Cells[5][i]+"\nДрагоценный камень: "+StringGrid1->Cells[6][i]+"\nВес камня: "+StringGrid1->Cells[7][i]);
  return;   }
 }  }
  // Отмена
  else {
 return;  }
 ShowMessage("Изделие по основному материалу не найдено");
}
//---------------------------------------------------------------------------
void __fastcall TForm3::N27Click(TObject *Sender)
{
			UnicodeString searchText = InputBox("Поиск", "Введите драгоценный камень изделия", "");   int searchType = MessageDlg("Поиск по полному совпадению?", mtConfirmation, TMsgDlgButtons() << mbYes << mbNo << mbCancel, 0);
   // Полное совпадение
   if (searchType == mrYes) {
 for (int i = 1; i < StringGrid1->RowCount; i++) {   if (StringGrid1->Cells[6][i] == searchText) {
  StringGrid1->Row = i; // выделить найденную строку
  ShowMessage("Найдено изделие по драгоценному камню\nНомер изделия: " + StringGrid1->Cells[0][i] +"\nНазвание изделия: "+StringGrid1->Cells[1][i]+"\nЦена изделия: "+StringGrid1->Cells[2][i]+"\nВес изделия: "+StringGrid1->Cells[3][i]+"\nИзготовитель: "+StringGrid1->Cells[4][i]+"\nОсновной материал: "+StringGrid1->Cells[5][i]+"\nДрагоценный камень: "+StringGrid1->Cells[6][i]+"\nВес камня: "+StringGrid1->Cells[7][i]);
  return;   }
 }  }
  // Начало строки
  else if (searchType == mrNo) {
 for (int i = 1; i < StringGrid1->RowCount; i++) {
   if (AnsiStartsText(searchText, StringGrid1->Cells[6][i]))    {
  StringGrid1->Row = i; // выделить найденную строку
  ShowMessage("Найдено изделие по драгоценному камню\nНомер изделия: " +StringGrid1->Cells[0][i]  +"\nНазвание изделия: "+StringGrid1->Cells[1][i]+"\nЦена изделия: "+StringGrid1->Cells[2][i]+"\nВес изделия: "+StringGrid1->Cells[3][i]+"\nИзготовитель: "+StringGrid1->Cells[4][i]+"\nОсновной материал: "+StringGrid1->Cells[5][i]+"\nДрагоценный камень: "+StringGrid1->Cells[6][i]+"\nВес камня: "+StringGrid1->Cells[7][i]);
  return;   }
 }  }
  // Отмена
  else {
 return;  }
 ShowMessage("Изделие по драгоценному камню не найдено");
}
//---------------------------------------------------------------------------
void __fastcall TForm3::N28Click(TObject *Sender)
{
	UnicodeString searchText = InputBox("Поиск", "Введите вес драгоценного камня изделия", "");   int searchType = MessageDlg("Поиск по полному совпадению?", mtConfirmation, TMsgDlgButtons() << mbYes << mbNo << mbCancel, 0);
   // Полное совпадение
   if (searchType == mrYes) {
 for (int i = 1; i < StringGrid1->RowCount; i++) {   if (StringGrid1->Cells[7][i] == searchText) {
  StringGrid1->Row = i; // выделить найденную строку
  ShowMessage("Найдено изделие по весу драгоценного камня\nНомер изделия: " + StringGrid1->Cells[0][i] +"\nНазвание изделия: "+StringGrid1->Cells[1][i]+"\nЦена изделия: "+StringGrid1->Cells[2][i]+"\nВес изделия: "+StringGrid1->Cells[3][i]+"\nИзготовитель: "+StringGrid1->Cells[4][i]+"\nОсновной материал: "+StringGrid1->Cells[5][i]+"\nДрагоценный камень: "+StringGrid1->Cells[6][i]+"\nВес камня: "+StringGrid1->Cells[7][i]);
  return;   }
 }  }
  // Начало строки
  else if (searchType == mrNo) {
 for (int i = 1; i < StringGrid1->RowCount; i++) {
   if (AnsiStartsText(searchText, StringGrid1->Cells[7][i]))    {
  StringGrid1->Row = i; // выделить найденную строку
  ShowMessage("Найдено изделие по весу драгоценного камня\nНомер изделия: " +StringGrid1->Cells[0][i]  +"\nНазвание изделия: "+StringGrid1->Cells[1][i]+"\nЦена изделия: "+StringGrid1->Cells[2][i]+"\nВес изделия: "+StringGrid1->Cells[3][i]+"\nИзготовитель: "+StringGrid1->Cells[4][i]+"\nОсновной материал: "+StringGrid1->Cells[5][i]+"\nДрагоценный камень: "+StringGrid1->Cells[6][i]+"\nВес камня: "+StringGrid1->Cells[7][i]);
  return;   }
 }  }
  // Отмена
  else {
 return;  }
 ShowMessage("Изделие по весу драгоценного камня не найдено");
}
//---------------------------------------------------------------------------


//-------------------------------------СОРТИВКА ПО ЦЕНЕ------------------------------------------------
void __fastcall TForm3::N16Click(TObject *Sender)  //по возрастанию
{
//количество иттераций
for (int i = 1; i < StrToInt(StringGrid1->RowCount); i++) { // начинаем с 1, чтобы пропустить заголовок таблицы
		for (int j = i + 1; j < StrToInt(StringGrid1->RowCount); j++) {
			if (StrToInt(StringGrid1->Cells[2][j]) < StrToInt(StringGrid1->Cells[2][i])) {
				// меняем местами строки, если значение в следующей строке меньше значения в текущей
				for (int k = 0; k < StringGrid1->ColCount; k++) {
					UnicodeString temp = StringGrid1->Cells[k][i];
					StringGrid1->Cells[k][i] = StringGrid1->Cells[k][j];
					StringGrid1->Cells[k][j] = temp;
				}
			}
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm3::N17Click(TObject *Sender) //по убыванию
{
//количество иттераций
  for (int i = 1; i < StringGrid1->RowCount; i++) { // начинаем с 1, чтобы пропустить заголовок таблицы
		for (int j = i + 1; j < StringGrid1->RowCount; j++) {
			if (StrToInt(StringGrid1->Cells[2][j]) > StrToInt(StringGrid1->Cells[2][i])) {
				// меняем местами строки, если значение в следующей строке больше значения в текущей
				for (int k = 0; k < StringGrid1->ColCount; k++) {
					UnicodeString temp = StringGrid1->Cells[k][i];
					StringGrid1->Cells[k][i] = StringGrid1->Cells[k][j];
					StringGrid1->Cells[k][j] = temp;
				}
			}
		}
	}
}
//---------------------------------------------------------------------------



//-----------------------------------О ПРОГРАММЕ--------------------------------------------------
void __fastcall TForm3::N21Click(TObject *Sender) //О программе
{
	ShowMessage("Дата внесения последних изменений:24.05.2023.\n Автор: Сморгуленко Василиса ");
}
//---------------------------------------------------------------------------

void __fastcall TForm3::N19Click(TObject *Sender)//задание
{
	ShowMessage("ВАРИАНТ 48. В ювелирном магазине следующие сведения заносятся в файл: название изделия, цена, вес изделия, изготовитель, основной материал, драгоценный камень, вес камня (в каратах). Написать программу, формирующую список изделий отсортированный в порядке возрастания цены. Выдать список изделий, вес камня в которых превышает заданный.");
}
//СПРАВКА
 void __fastcall TForm3::N20Click(TObject *Sender)
{
	 ShowMessage(" Руководство по работе с программой ювелирный магазин Pink Star\n В главном меню есть такие разделы как\n- Файл:\n 1. Создать. Создает новый файл для ввода данных о зверях и птицах.\n2. Открыть. Позволяет выбрать и открыть существующий файл с данными.\n3. Сохранить. Сохраняет текущие данные в открытый файл.\n4. Сохранить как. Позволяет сохранить текущие данные в новый файл.\n-Правка\n1. Добавить. Дает возможность заполнить данные о новом элементе.\n2. Редактировать. Позволяет изменить данные об элементе.\n3. Удалить. Удаляет строку, в которой выделена ячейка.\n-Обработка\n1. Поиск. Позволяет найти определенные данные, используя различные параметры поиска.\n2. Сортировка. Позволяет сортировать элементы по возрастанию, убыванию и алфафиту.\n-О программе\n1. Задание.Показывает информацию о выполняемой задаче.\n2. Справка. Показывает руководство работы с программой.\n3. О программе. Показывает информацию о версии продукта.\n ");
}
void __fastcall TForm3::FormClose(TObject *Sender, TCloseAction &Action)
{
	// Проверяем, сохранены ли данные
	if (!dataSaved)
	{
		if (MessageBox(NULL, L"Вы не сохранили ваши данные. Вы хотите сохранить их перед выходом?", L"Предупреждение", MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			N4Click(NULL);
		}
	}
}
//---------------------------------------------------------------------------


void __fastcall TForm3::StringGrid1SelectCell(TObject *Sender, int ACol, int ARow,
		  bool &CanSelect)
{
	   StatusBar2->Panels->Items[2]->Text = "Выделенная строка: " + IntToStr(ARow);
	   StatusBar2->Panels->Items[3]->Text = "Столбец: " + IntToStr(ACol);
}
//---------------------------------------------------------------------------


// ПО ВЕСУ ИЗДЕЛИЯ
void __fastcall TForm3::N35Click(TObject *Sender)  //по возрастанию
{
  //количество иттераций
for (int i = 1; i < StrToInt(StringGrid1->RowCount); i++) { // начинаем с 1, чтобы пропустить заголовок таблицы
		for (int j = i + 1; j < StrToInt(StringGrid1->RowCount); j++) {
			if (StrToInt(StringGrid1->Cells[3][j]) < StrToInt(StringGrid1->Cells[3][i])) {
				// меняем местами строки, если значение в следующей строке меньше значения в текущей
				for (int k = 0; k < StringGrid1->ColCount; k++) {
					UnicodeString temp = StringGrid1->Cells[k][i];
					StringGrid1->Cells[k][i] = StringGrid1->Cells[k][j];
					StringGrid1->Cells[k][j] = temp;
				}
			}
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm3::N36Click(TObject *Sender) //по убыванию
{
  //количество иттераций
  for (int i = 1; i < StringGrid1->RowCount; i++) { // начинаем с 1, чтобы пропустить заголовок таблицы
		for (int j = i + 1; j < StringGrid1->RowCount; j++) {
			if (StrToInt(StringGrid1->Cells[3][j]) > StrToInt(StringGrid1->Cells[3][i])) {
				// меняем местами строки, если значение в следующей строке больше значения в текущей
				for (int k = 0; k < StringGrid1->ColCount; k++) {
					UnicodeString temp = StringGrid1->Cells[k][i];
					StringGrid1->Cells[k][i] = StringGrid1->Cells[k][j];
					StringGrid1->Cells[k][j] = temp;
				}
			}
		}
	}
}
//---------------------------------------------------------------------------
 //ПО ВЕСУ КАМНЯ В КАРАТАХ
void __fastcall TForm3::N38Click(TObject *Sender) //по возрастанию
{
	//количество иттераций
for (int i = 1; i < StrToInt(StringGrid1->RowCount); i++) { // начинаем с 1, чтобы пропустить заголовок таблицы
		for (int j = i + 1; j < StrToInt(StringGrid1->RowCount); j++) {
			if (StrToInt(StringGrid1->Cells[7][j]) < StrToInt(StringGrid1->Cells[7][i])) {
				// меняем местами строки, если значение в следующей строке меньше значения в текущей
				for (int k = 0; k < StringGrid1->ColCount; k++) {
					UnicodeString temp = StringGrid1->Cells[k][i];
					StringGrid1->Cells[k][i] = StringGrid1->Cells[k][j];
					StringGrid1->Cells[k][j] = temp;
				}
			}
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm3::N39Click(TObject *Sender)// по убыванию
{
	  //количество иттераций
  for (int i = 1; i < StringGrid1->RowCount; i++) { // начинаем с 1, чтобы пропустить заголовок таблицы
		for (int j = i + 1; j < StringGrid1->RowCount; j++) {
			if (StrToInt(StringGrid1->Cells[7][j]) > StrToInt(StringGrid1->Cells[7][i])) {
				// меняем местами строки, если значение в следующей строке больше значения в текущей
				for (int k = 0; k < StringGrid1->ColCount; k++) {
					UnicodeString temp = StringGrid1->Cells[k][i];
					StringGrid1->Cells[k][i] = StringGrid1->Cells[k][j];
					StringGrid1->Cells[k][j] = temp;
				}
			}
		}
	}
}
//---------------------------------------------------------------------------
//ПО НОМЕРУ

void __fastcall TForm3::N41Click(TObject *Sender)
{
       //количество иттераций
for (int i = 1; i < StrToInt(StringGrid1->RowCount); i++) { // начинаем с 1, чтобы пропустить заголовок таблицы
		for (int j = i + 1; j < StrToInt(StringGrid1->RowCount); j++) {
			if (StrToInt(StringGrid1->Cells[0][j]) < StrToInt(StringGrid1->Cells[0][i])) {
				// меняем местами строки, если значение в следующей строке меньше значения в текущей
				for (int k = 0; k < StringGrid1->ColCount; k++) {
					UnicodeString temp = StringGrid1->Cells[k][i];
					StringGrid1->Cells[k][i] = StringGrid1->Cells[k][j];
					StringGrid1->Cells[k][j] = temp;
				}
			}
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm3::N42Click(TObject *Sender)
{
  	  //количество иттераций
  for (int i = 1; i < StringGrid1->RowCount; i++) { // начинаем с 1, чтобы пропустить заголовок таблицы
		for (int j = i + 1; j < StringGrid1->RowCount; j++) {
			if (StrToInt(StringGrid1->Cells[0][j]) > StrToInt(StringGrid1->Cells[0][i])) {
				// меняем местами строки, если значение в следующей строке больше значения в текущей
				for (int k = 0; k < StringGrid1->ColCount; k++) {
					UnicodeString temp = StringGrid1->Cells[k][i];
					StringGrid1->Cells[k][i] = StringGrid1->Cells[k][j];
					StringGrid1->Cells[k][j] = temp;
				}
			}
		}
	}
}
//---------------------------------------------------------------------------
//ПО АЛФАВИТУ

void __fastcall TForm3::N44Click(TObject *Sender)
{
  for (int i = 1; i < StringGrid1->RowCount; i++) { // начинаем с 1, чтобы пропустить заголовок таблицы
		for (int j = i + 1; j < StringGrid1->RowCount; j++) {
			if (StringGrid1->Cells[1][j].CompareIC(StringGrid1->Cells[1][i]) < 0) {
				// меняем местами строки, если значение в следующей строке меньше значения в текущей
				for (int k = 1; k < StringGrid1->ColCount; k++) {
					UnicodeString temp = StringGrid1->Cells[k][i];
					StringGrid1->Cells[k][i] = StringGrid1->Cells[k][j];
					StringGrid1->Cells[k][j] = temp;
				}
			}
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm3::N45Click(TObject *Sender)
{
	 for (int i = 1; i < StringGrid1->RowCount; i++) { // начинаем с 1, чтобы пропустить заголовок таблицы
		for (int j = i + 1; j < StringGrid1->RowCount; j++) {
			if (StringGrid1->Cells[4][j].CompareIC(StringGrid1->Cells[4][i]) < 0) {
				// меняем местами строки, если значение в следующей строке меньше значения в текущей
				for (int k = 1; k < StringGrid1->ColCount; k++) {
					UnicodeString temp = StringGrid1->Cells[k][i];
					StringGrid1->Cells[k][i] = StringGrid1->Cells[k][j];
					StringGrid1->Cells[k][j] = temp;
				}
			}
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm3::N46Click(TObject *Sender)
{
	 for (int i = 1; i < StringGrid1->RowCount; i++) { // начинаем с 1, чтобы пропустить заголовок таблицы
		for (int j = i + 1; j < StringGrid1->RowCount; j++) {
			if (StringGrid1->Cells[5][j].CompareIC(StringGrid1->Cells[5][i]) < 0) {
				// меняем местами строки, если значение в следующей строке меньше значения в текущей
				for (int k = 1; k < StringGrid1->ColCount; k++) {
					UnicodeString temp = StringGrid1->Cells[k][i];
					StringGrid1->Cells[k][i] = StringGrid1->Cells[k][j];
					StringGrid1->Cells[k][j] = temp;
				}
			}
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm3::N47Click(TObject *Sender)
{
    for (int i = 1; i < StringGrid1->RowCount; i++) { // начинаем с 1, чтобы пропустить заголовок таблицы
		for (int j = i + 1; j < StringGrid1->RowCount; j++) {
			if (StringGrid1->Cells[6][j].CompareIC(StringGrid1->Cells[6][i]) < 0) {
				// меняем местами строки, если значение в следующей строке меньше значения в текущей
				for (int k = 1; k < StringGrid1->ColCount; k++) {
					UnicodeString temp = StringGrid1->Cells[k][i];
					StringGrid1->Cells[k][i] = StringGrid1->Cells[k][j];
					StringGrid1->Cells[k][j] = temp;
				}
			}
		}
	}
}
//---------------------------------------------------------------------------



void __fastcall TForm3::N48Click(TObject *Sender)
{
   Form5->ShowModal();
}
//---------------------------------------------------------------------------

