#include<iostream>
#include<string.h>
#include<time.h>
#include<stdlib.h>
#include<stdio.h>
// #include<conio.h>
//
using namespace std;
class PerDeck;
class PlayingCard
{
private:
	int nValue;//扑克牌实际面值
	char achFace[3];//扑克牌字符串A,2,......10,J,Q,K
	char chSuit;//扑克牌花色
public:
	friend class PerDeck;
	PlayingCard();//将对象清零
	void ShowCard();//显示面值花色
	void CardMake(int);//给一张扑克牌赋值(面值,花色)
};

class Deck
{
private:
	PlayingCard m_cardarray[54];
	int nLastDelt;
public:
	friend class PerDeck;
	Deck();
	void MakeDeck();//将52张牌清零(没有大,小王)
	void DealOne();//删除开头一张牌
	void ShowDeck();//依次逐张显示这副牌
	void DeckShuff(int);//用于洗牌,参数是洗牌次数
	void RemoveCard();//清零删除掉的那张牌
};

class PerDeck
{
private:
	PlayingCard myCard[20];
	int nNum;
public:
	PerDeck() {}
	void MakePerDeck(Deck &, int);
	void Show();
	void SortFace();
	void SortSuit();
	int Delete(int n);
};

class PlayDeck
{
private:
	PerDeck myDeck[4];
public:
	PlayDeck() {}
	void PlayCard(Deck &);
	void Show();
	int DeleteOne(int row, int column);
	int DeleteAll(int, int, int ,int);
	void SortDeckFace(int);
	void SortDeckSuit(int);
	void s(int);
};

void ProgramInit();//初始化,并输出信息
void CenterText(char ShellText[80]);//居中显示
int GetNumber();//键入整数型
char GetKey();//键入字符串型
void DeckMakeDiver();//主要算法(生成扑克牌,洗牌,删除等)
int GetRandInt(int min, int max);//在min到max间选随机值
void ProgClose();//暂停,供用户查看中间运行结果


int main(void)
{
	srand((unsigned)time(NULL));
	int nCardNum = 0;
	ProgramInit();
	DeckMakeDiver();
	ProgClose();
	return 1;
}

void PlayDeck::PlayCard(Deck &k)
{
	int a, b, c, d;
	char g[200] = { "依次输入四位玩家手里的牌数：" };
	CenterText(g);
	cout << endl;
	cin >> a >> b >> c >> d;
	if (a + b + c + d > 54)
	{
		char g[200] = { "超过牌的张数，退出游戏。" };
		CenterText(g);
		exit(0);
	}
	myDeck[0].MakePerDeck(k, a);
	myDeck[1].MakePerDeck(k, b);
	myDeck[2].MakePerDeck(k, c);
	myDeck[3].MakePerDeck(k, d);
}

void PlayDeck::Show()
{
	char a[200] = { "玩家1" };
	char b[200] = { "玩家2" };
	char c[200] = { "玩家3" };
	char d[200] = { "玩家4" };
	CenterText(a);
	cout << endl;
	myDeck[0].Show();
	CenterText(b);
	cout << endl;
	myDeck[1].Show();
	CenterText(c);
	cout << endl;
	myDeck[2].Show();
	CenterText(d);
	cout << endl;
	myDeck[3].Show();
}

int PlayDeck::DeleteOne(int row, int column)
{
	myDeck[row - 1].Delete(column);
	return 1;
}

int PlayDeck::DeleteAll(int a, int b, int c, int d)
{
	myDeck[0].Delete(a);
	myDeck[1].Delete(b);
	myDeck[2].Delete(c);
	myDeck[3].Delete(d);
	return 1;
}

void PlayDeck::SortDeckFace(int b)
{
	myDeck[b - 1].SortFace();
}

void PlayDeck::SortDeckSuit(int b)
{
	myDeck[b - 1].SortSuit();
}

void PlayDeck::s(int a)
{
	myDeck[a - 1].Show();
}

void Deck::MakeDeck()//对生成的52张牌逐个赋值
{
	nLastDelt = 53;//51
	while (nLastDelt > -1)
	{
		m_cardarray[nLastDelt].CardMake(nLastDelt);
		nLastDelt--;
	}
}
void Deck::ShowDeck()//显示一副扑克牌
{
	char a[200] = { "完整的一副牌" };
	int nIndex = nLastDelt + 1;
	int nNewLine = 0;
	CenterText(a);
	cout << endl;
	while (nIndex <= 53)//51
	{
		if (nNewLine % 11 == 0)cout << endl;
		m_cardarray[nIndex].ShowCard();
		nNewLine++;
		nIndex++;
	}
}

void Deck::DeckShuff(int times)//洗牌算法
{
	char a[200] = { "洗牌......" };
	int x, nSplit;
	CenterText(a);
	cout << endl;
	for (x = 0; x <= times; x++)
	{
		nSplit = GetRandInt(20, 35);
		Deck TopDeck;
		Deck BottomDeck;
		int i;
		int nBottomNum = 1;
		int nTopNum = 1;
		for (i = 0; i <= nSplit - 1;)
		{
			TopDeck.m_cardarray[nTopNum] = this->m_cardarray[i];
			nTopNum++;
			i++;
		}
		for (i = (nSplit); i < 54;)//52
		{
			BottomDeck.m_cardarray[nBottomNum] = this->m_cardarray[i];
			nBottomNum++;
			i++;
		}
		int nOutNum = 0;
		int nNumToTop;
		int nNumToBottom;
		int j;
		int h = 0;
		nBottomNum = 54 - nSplit;//52
		nTopNum = nSplit;
		while (nOutNum < 53)//51
		{
			nNumToTop = GetRandInt(2, 7);
			nNumToBottom = GetRandInt(2, 7);
			for (j = 0; j <= nNumToBottom; j++)
			{
				if (nBottomNum > 0)
				{
					this->m_cardarray[nOutNum] = BottomDeck.m_cardarray[nBottomNum];
					nOutNum++;
					nBottomNum--;
				}
				for (h = 0; h <= nNumToTop; h++)
				{
					if ((nTopNum > 0) && (nOutNum <= 54))//52
					{
						this->m_cardarray[nOutNum] = TopDeck.m_cardarray[nTopNum];
						nOutNum++;
						nTopNum--;
					}
				}
			}
		}
	}
	this->nLastDelt = -1;
}

void Deck::RemoveCard()//将删除的那张牌清零
{
	m_cardarray[nLastDelt] = PlayingCard();//清零
}

void Deck::DealOne()//从一副扑克牌中删除一张牌
{
	if (nLastDelt != 53)//51
	{
		nLastDelt++;
		cout.width(5);
		cout << endl;
		cout << "   删除牌:";
		m_cardarray[nLastDelt].ShowCard();
		RemoveCard();
	}
	else
	{
		cout << "这副牌全部删除完了";
		ProgClose();
	}
}

Deck::Deck()//初始化一副扑克牌，将52张扑克牌均清零
{
	int lastdelt = 0;
	for (int i = 0; i <= 53; i++)//51
	{
		m_cardarray[i] = PlayingCard();
	}
}

void ProgramInit()//程序一开始的提示信息
{
	char a[100] = { "扑克牌游戏" };
	char b[100] = { "单击<Return>键开始......" };
	CenterText(a);
	cout << endl << '\n';
	CenterText(b);
	cin.get();
}

char GetKey()//从键盘接收一个字符，将其作为函数返回值
{
	char x;
	x = cin.get();
	cout << endl;
	return x;
}

void CenterText(char ShellText[80])//居中算法
{
	int nCenter;
	int nLength;
	nLength = strlen(ShellText);
	nCenter = (80 - nLength) / 2;
	for (; nCenter != 0; nCenter--)
	{
		cout << " ";
	}
	cout << ShellText;
}

int GetNumber()//从键盘接收一个整数值，作为函数返回值
{
	char a[100] = { "请输入一个在0到51之间的整数,输入52退出." };
	int nInputInteger = 0;
	CenterText(a);
	cout << endl;
	cin >> nInputInteger;
	return nInputInteger;
}

void ProgClose()//程序暂停，按任意键继续
{
	cout << endl << endl;
	cout << "单击<Return>键继续......" << endl;
	cout << endl << endl;
	GetKey();
	cin.get();
}

void DeckMakeDiver()//主要程序操作部分，调用多个函数，包含完整生成一副牌，洗牌，显示，删除等操作
{
	Deck deck_1;
	deck_1.MakeDeck();
	deck_1.ShowDeck();
	GetKey();
	deck_1.DeckShuff(250);
	deck_1.ShowDeck();
	cout << endl << endl << endl;
	char y;
	PlayDeck F;
	F.PlayCard(deck_1);
	cout << endl << endl << endl;
	F.Show();
	int g = 0;
	do
	{
		char a[100] = { "游戏规则" };
		char b[100] = { "删除一位玩家的牌 输入1" };
		char c[100] = { "删除四位玩家的牌 输入2" };
		char d[100] = { "按牌的面值排序   输入3" };
		char e[100] = { "按牌的花色排序   输入4" };
		char f[100] = { "显示四位玩家手牌 输入5" };
		char q[100] = { "按    N(n)    退出游戏" };
		CenterText(a);
		cout << endl;
		CenterText(b);
		cout << endl;
		CenterText(c);
		cout << endl;
		CenterText(d);
		cout << endl;
		CenterText(e);
		cout << endl;
		CenterText(f);
		cout << endl;
		CenterText(q);
		cout << endl;
		cin >> g;
		if (g == 1)
		{
			int j, k;
			char h;
			cout << "请输入删除玩家的编号和牌号（从左往右数的第N张）" << endl;
			cin >> j >> k;
			F.DeleteOne(j, k);
			cout << endl << "是（Y)否（N）显示删除后的手牌?" << endl;
			cin >> h;
			h= toupper(h);
			if (h == 'Y')F.s(j);
			cout << endl;
		}
		if (g == 2)
		{
			int w, x, h, z;
			char y;
			cout << "请依次输入欲删除各玩家牌的序号。" << endl;
			cin >> w >> x >> h >> z;
			F.DeleteAll(w, x, h, z);
			cout << endl << "是（Y）否（N）显示删除后玩家的牌？" << endl;
			cin >> y;
			y = toupper(y);
			if (y == 'Y')F.Show();
			cout << endl;
		}
		if (g == 3)
		{
			int h;
			char y;
			cout << "请输入需要排序的玩家" << endl;
			cin >> h;
			F.SortDeckFace(h);
			cout << "是（Y）否（N）显示排序后的牌？" << endl;
			cin >> y;
			y = toupper(y);
			if (y == 'Y')F.s(h);
		}
		if (g == 4)
		{
			int x;
			char y;
			cout << "请输入需要排序玩家的序号" << endl;
			cin >> x;
			F.SortDeckSuit(x);
			cout << "是(Y)否(N)显示排序后的牌？"<< endl;
			cin >> y;
			y = toupper(y);
			if (y == 'Y')F.s(x);
		}
		if (g == 5)
		{
			F.Show();
		}
		if (g == 78 || g == 110)
		{
			goto loop;
		}
		cout << "是(Y)否(N)回到游戏规则菜单?" << endl;
		cout << endl;
		cin >> y;
		y= toupper(y);
	} while (y == 'Y'); 
loop:;
}

int GetRandInt(int nMin, int nMax)//返回min至max之间的任意一值（实际上是“洗牌算法”s的一部分）
{
	int nNumToReturn;
	nNumToReturn = rand();
	nNumToReturn = nNumToReturn % (nMax - nMin + 1) + nMin;
	return nNumToReturn;
}

PlayingCard::PlayingCard()//扑克牌对象的构造函数
{
	for (int i = 1; i <= 3;)
	{
		achFace[i] = ' ';
		i++;
	}
	chSuit = ' ';
	nValue = 0;
}

void PlayingCard::ShowCard()//在屏幕上显示一张扑克牌的面值及花色
{
	cout << "    ";
	cout << achFace;
	cout.width(1);
	// cout << chSuit;
	// printf("%c", chSuit);
	if (chSuit == 3) {
		cout << "黑桃";
	} else if (chSuit == 4) {
		cout << "方块";
	} else if (chSuit == 5) {
		cout << "梅花";
	} else if (chSuit == 6) {
		cout << "红桃";
	}

	cout << "    ";
}

void PlayingCard::CardMake(int nNum)//根据参数nNum生成一张扑克牌，nNum不同，生成的面值或花色不同
{
	int i = 0;
	char j;
	int nFaceNum = nNum % 13;
	if (nNum == 52)
	{
		strcpy(achFace, "S");
		goto loop;
	}
	if (nNum == 53)
	{
		strcpy(achFace, "B");
		goto loop;
	}
	switch (nFaceNum)
	{
	case 0:strcpy(achFace, "A"); break;
	case 9:strcpy(achFace, "10"); break;
	case 10:strcpy(achFace, "J"); break;
	case 11:strcpy(achFace, "Q"); break;
	case 12:strcpy(achFace, "K"); break;
	default:
		j = char(nFaceNum + 49);
		if (i < 3)
		{
			achFace[i] = ' '; i++;
			achFace[i] = j; i++;
			achFace[i] = '\0';
			break;
		}
	}
loop:;
	if (nNum <= 12)chSuit = 6;//红桃
	if (nNum > 12 && nNum <= 25)chSuit = 3;//黑桃
	if (nNum > 25 && nNum <= 38)chSuit = 5;//梅花
	if (nNum > 38 && nNum <= 51)chSuit = 4;//方块
	if (nFaceNum <= 9)nValue = nFaceNum + 1;
	if (nFaceNum >= 10)nValue = 10;
	if (nNum == 52) 
	{
		nValue = 11; 
		chSuit = 49;
	}
	if (nNum == 53) 
	{
		nValue = 12;
		chSuit = 50;
	}
}

void PerDeck::MakePerDeck(Deck &d, int a)
{
	nNum = a;
	int i = 0;
	while (i < a&&d.nLastDelt != 53)
	{
		myCard[i++ ] = d.m_cardarray[++d.nLastDelt];
	}
}

void PerDeck::Show()
{
	char a[100] = { "该玩家的牌:" };
	int nNewLine = 0;
	CenterText(a);
	cout << endl;
	while (nNewLine < nNum)
	{
		if (nNewLine % 5 == 0)
			cout << endl;
		myCard[nNewLine++].ShowCard();
	}
	cout << endl;
}

void PerDeck::SortFace()//冒泡
{
	PlayingCard k;
	for(int i=0;i<nNum;i++)
		for(int j=0;j+i<nNum-1;j++)
			if (myCard[j].nValue > myCard[j + 1].nValue)
			{
				k = myCard[j];
				myCard[j] = myCard[j + 1];
				myCard[j + 1] = k;
			}
}
void PerDeck::SortSuit()
{
	PlayingCard k;
	for (int i = 0; i<nNum; i++)
		for (int j = 0; j + i<nNum - 1; j++)
			if (myCard[j].chSuit> myCard[j + 1].chSuit)
			{
				k = myCard[j];
				myCard[j] = myCard[j + 1];
				myCard[j + 1] = k;
			}
}

int PerDeck::Delete(int n)
{
	if (n > nNum)
	{
		cout << "超出总牌数！"<<endl;
		return nNum;
	}
	else
	{
		cout.widen(5);
		cout << "    删除牌：";
		myCard[n - 1].ShowCard();
		while (n < nNum + 1)
		{
			myCard[n - 1] = myCard[n++];
		}
		return --nNum;
	}
}
