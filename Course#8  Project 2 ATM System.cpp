
#include <iostream>
#include<string>
#include<vector>
#include<fstream>
using namespace std;
enum EnChoose{QuickWithdraw=1,NormalWithdraw=2,Deposit=3,CheckBalance=4,Logout=5};
enum EnQuickDraw{Twenty=1,fifty=2,OneHundred=3,TwoHundreds=4,FourHundreds=5,sixHundreds=6,EightHundreds=7,OneThousand=8,Exit=9};
struct stInfo
{
	string AccountNumber = "";
	string PinCode = "";
	string Name = "";
	string Phone = "";
	double Balance = 0;
	bool MarkToDelete = false;
};
void Login();
void ATMMainMenueScreen();

stInfo LocalClient;

stInfo ConvertLineToClientData(vector<string>split)
{
	stInfo Client;
	Client.AccountNumber = split[0];
	Client.PinCode = split[1];
	Client.Name = split[2];
	Client.Phone = split[3];
	Client.Balance = stod(split[4]);

	return Client;
}
vector<string> Split(string S, string Seperator = "#//#")
{
	vector<string> split;
	int Pos = 0;
	string Word = "";
	while ((Pos = S.find(Seperator)) != std::string::npos)
	{
		Word = S.substr(0, Pos);
		if (Word != "")
		{
			split.push_back(Word);
		}

		S.erase(0, Pos + Seperator.length());
	}

	if (S != "")
	{
		split.push_back(S);
	}

	return split;
}
vector<stInfo>vClient()
{
	vector<stInfo>vclient;
	fstream Houssam;
	Houssam.open("Houssam.txt", ios::in);
	if (Houssam.is_open())
	{
		string Line = "";
		stInfo Client;
		while (getline(Houssam, Line))
		{
			Client = ConvertLineToClientData(Split(Line));
			vclient.push_back(Client);
		}

		Houssam.close();
	}

	return vclient;
}
void GoBackToMainMenueScreen()
{
	cout << "\n\n Press Any Key To Go Back To Main Menue \n";
	system("pause>0");
	ATMMainMenueScreen();
}
string ReadAccountNumber()
{
	string AccountNumber;
	cout << " Enter AccountNumber ? ";
	getline(cin >> ws, AccountNumber);
	return AccountNumber;
}
string ReadPinCode()
{
	string PinCode;
	cout << " Enter Pin Code ?  ";
	getline(cin >> ws, PinCode);
	return PinCode;
}
bool IsClientInFileByAccountNumber(vector<stInfo>vclient, stInfo& Client, string AccountNumber,string PinCode)
{
	for (stInfo& C : vclient)
	{
		if (C.AccountNumber == AccountNumber&&C.PinCode==PinCode)
		{
			Client = C;
			return true;
		}
	}
	return false;
}
EnChoose YourChoice(string Message)
{
	short Choose;
	do
	{
		cout << Message << "   ";
		cin >> Choose;
	} while (Choose < 1 || Choose>5);

	return (EnChoose)Choose;
}
void CheckBalanceScreen()
{
	cout << "====================================================\n";
	cout << "\t\t Check Balance Screen \n";
	cout << "====================================================\n";
	cout << " Your Balance Is : " << LocalClient.Balance << endl;
}
EnQuickDraw ChooseYourDraw(string Message)
{
	short Draw;
	do
	{
		cout << Message << "    ";
		cin >> Draw;
	} while (Draw < 1 || Draw>9);

	return (EnQuickDraw)Draw;
}
string ConvertDataToLine(stInfo Client,string Seperator="#//#")
{
	string Line = "";
	Line += Client.AccountNumber + Seperator;
	Line += Client.PinCode + Seperator;
	Line += Client.Name + Seperator;
	Line += Client.Phone + Seperator;
	Line += to_string(Client.Balance);

	return Line;
}
void SaveDataInFile(vector<stInfo> vclient)
{
	fstream Houssam;
	Houssam.open("Houssam.txt", ios::out);
	if (Houssam.is_open())
	{
		string Line;
		for (stInfo& C : vclient)
		{
			Line = ConvertDataToLine(C);
			Houssam << Line << endl;
		}

		Houssam.close();
	}
}
bool CanIDoThisTransaction(int NumberOfMoney)
{
	if (LocalClient.Balance > NumberOfMoney)
		return true;
	else
	{
		cout << " \n The Amount Exceeds Your Balance , Make Another Choise .\n";
		return false;
	}
}
bool DrawYourMonenyQuickly(int NumberOfMoney)
{
	if (!CanIDoThisTransaction(NumberOfMoney))
		return false;



	vector<stInfo> vclient = vClient();
	char Answer = 'Y';
	cout << "\n\n Are You Sure You want Perform This Transaction [Y/N] ?  ";
	cin >> Answer;
	if (toupper(Answer) == 'Y')
	{
		for (stInfo& C : vclient)
		{
			if (C.AccountNumber == LocalClient.AccountNumber && C.PinCode == LocalClient.PinCode)
			{
				LocalClient.Balance -= NumberOfMoney;
				C = LocalClient;
				break;
			}
		}
		SaveDataInFile(vclient);
		cout << "\n\n Done SuccessFully , New Balance Is : " << LocalClient.Balance << endl;
		return true;
	}
	else
	{
		cout << "\n\n You refuse Perfom This Transaction \n";
		return false;
	}
}
void QuickWithDrawSwitchCase(EnQuickDraw Choose)
{
	switch (Choose)
	{
	case::EnQuickDraw::Twenty:
		DrawYourMonenyQuickly(20);
		GoBackToMainMenueScreen();
		break;

	case::EnQuickDraw::fifty:
		DrawYourMonenyQuickly(50);
		GoBackToMainMenueScreen();
		break;

	case::EnQuickDraw::OneHundred:
		DrawYourMonenyQuickly(100);
		GoBackToMainMenueScreen();
		break;

	case::EnQuickDraw::TwoHundreds:
		DrawYourMonenyQuickly(200);
		GoBackToMainMenueScreen();
		break;

	case::EnQuickDraw::FourHundreds:
		DrawYourMonenyQuickly(400);
		GoBackToMainMenueScreen();
		break;

	case::EnQuickDraw::sixHundreds:
		DrawYourMonenyQuickly(600);
		GoBackToMainMenueScreen();
		break;
	case::EnQuickDraw::EightHundreds:
		DrawYourMonenyQuickly(800);
		GoBackToMainMenueScreen();
		break;

	case::EnQuickDraw::OneThousand:
		DrawYourMonenyQuickly(1000);
		GoBackToMainMenueScreen();
		break;

	case::EnQuickDraw::Exit:
		ATMMainMenueScreen();
		break;
	}
}
void QuickWithDrawMenue()
{
	cout << "=====================================================\n";
	cout << "\t\t Quick Withdraw \n";
	cout << "=====================================================\n";
	cout << "\t [1] 20            [2] 50 \n";
	cout << "\t [3] 100           [4] 200 \n";
	cout << "\t [5] 400           [6] 600 \n";
	cout << "\t [7] 800           [8] 1000 \n";
	cout << "\t [9] Exit \n";
	cout << "=====================================================\n";
	cout << "Your Balance Is : " << LocalClient.Balance << endl;
	EnQuickDraw Choose = ChooseYourDraw("Choose What To withdraw From [1] to [8] ? ");

	QuickWithDrawSwitchCase(Choose);
}
void NormalWithdrawScreen()
{
	cout << "=======================================================\n";
	cout << "\t\t Normal WithDraw Screen \n";
	cout << "=======================================================\n";
}

bool IsNumberOfMoneyToDrawMultipleOf5(int NumberOfMoney)
{
	if ((NumberOfMoney % 5) == 0)
		return true;
	else
		return false;
}
bool DrawYourMonenyNormaly(int NumberOfMoney)
{
	if (!CanIDoThisTransaction(NumberOfMoney))
		return false;


	vector<stInfo> vclient = vClient();
	char Answer = 'Y';
	cout << "\n\n Are You Sure You want Perform This Transaction [Y/N] ?  ";
	cin >> Answer;
	if (toupper(Answer) == 'Y')
	{
		for (stInfo& C : vclient)
		{
			if (C.AccountNumber == LocalClient.AccountNumber && C.PinCode == LocalClient.PinCode)
			{
				LocalClient.Balance -= NumberOfMoney;
				C = LocalClient;
				break;
			}
		}
		SaveDataInFile(vclient);
		cout << "\n\n Done SuccessFully , New Balance Is : " << LocalClient.Balance << endl;
		return true;
	}
	else
	{
		cout << "\n\n You refuse Perfom This Transaction \n";
		return false;
	}
}
void NormalWithDraw()
{
	NormalWithdrawScreen();
	int NumberOfMoneyToDraw = 0;
	cout << "\n Enter an Amount Multiple Of 5's ?  ";
	cin >> NumberOfMoneyToDraw;
	while (!IsNumberOfMoneyToDrawMultipleOf5(NumberOfMoneyToDraw))
	{
		system("cls");
		NormalWithdrawScreen();
		cout << "\n(" << NumberOfMoneyToDraw << ")" << " is Not able To Mod On 5 \n";
		cout << "\n Enter an Amount Multiple Of 5's ?  ";
		cin >> NumberOfMoneyToDraw;
	}

	DrawYourMonenyNormaly(NumberOfMoneyToDraw);
}
void DepositScreen()
{
	cout << "=============================================================\n";
	cout << "\t\t Deposite Screen \n";
	cout << "=============================================================\n";
}
int PositiveAmount()
{
	int Amount;
	cout << " Enter a Positive Deposit Amount ?  ";
	cin >> Amount;
	return Amount;
}
bool DepositYourMonenyInYourAccount(int NumberOfMoney)
{
	vector<stInfo> vclient = vClient();
	char Answer = 'Y';
	cout << "\n\n Are You Sure You want Perform This Transaction [Y/N] ?  ";
	cin >> Answer;
	if (toupper(Answer) == 'Y')
	{
		for (stInfo& C : vclient)
		{
			if (C.AccountNumber == LocalClient.AccountNumber && C.PinCode == LocalClient.PinCode)
			{
				LocalClient.Balance += NumberOfMoney;
				C = LocalClient;
				break;
			}
		}
		SaveDataInFile(vclient);
		cout << "\n\n Done SuccessFully , New Balance Is : " << LocalClient.Balance << endl;
		return true;
	}
	else
	{
		cout << "\n\n You refuse Perfom This Transaction \n";
		return false;
	}
}
void DepositeYourMoney()
{
	DepositScreen();
	int Amount = PositiveAmount();
	DepositYourMonenyInYourAccount(Amount);
}
void ATMMainMenueSwitchCase(EnChoose Choose)
{
	switch (Choose)
	{
	case::EnChoose::QuickWithdraw:
		system("cls");
		QuickWithDrawMenue();
		break;

	case::EnChoose::NormalWithdraw:
		system("cls");
		NormalWithDraw();
		GoBackToMainMenueScreen();
		break;

	case::EnChoose::Deposit:
		system("cls");
		DepositeYourMoney();
		GoBackToMainMenueScreen();
		break;

	case::EnChoose::CheckBalance:
		system("cls");
		CheckBalanceScreen();
		GoBackToMainMenueScreen();
		break;

	case::EnChoose::Logout:
		system("cls");
		Login();
		break;
	}
}
void ATMMainMenueScreen()
{
	system("cls");
	cout << "=========================================================\n";
	cout << "\t\t ATM Main Menue Screen \n";
	cout << "=========================================================\n";
	cout << "\t [1] Quick Withdraw \n";
	cout << "\t [2] Normal Withdraw \n";
	cout << "\t [3] Deposit \n";
	cout << "\t [4] Check Balance \n";
	cout << "\t [5] Logout \n";
	cout << "=========================================================\n";
	EnChoose Choose = YourChoice("Choose What Do you Want To Do ? [1 to 5]? ");

	ATMMainMenueSwitchCase(Choose);
}
void LoginScreen()
{
	cout << "_______________________________________\n";
	cout << "\t\t Login Screen \n";
	cout << "_______________________________________\n";
}
void Login()
{
	LoginScreen();
	vector <stInfo> vclient = vClient();
	string AccountNumber = ReadAccountNumber();
	string PinCode = ReadPinCode();
	if (!IsClientInFileByAccountNumber(vclient, LocalClient, AccountNumber, PinCode))
	{
		system("cls");
		LoginScreen();
		cout << " Invalide AccountNumber / PinCode \n";
		AccountNumber = ReadAccountNumber();
		PinCode = ReadPinCode();
	}

	ATMMainMenueScreen();
}
int main()
{
	Login();
}