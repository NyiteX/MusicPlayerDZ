#include <iostream>
#include <vector>
#include <conio.h>
using namespace std;

class MusicPlayer
{
	struct M
	{
		string ispolnitel;
		string songname;
	};
	vector<M>PlaylistDefault;
	vector<M>PlaylistMy;
	vector<M>Music;
public:
	MusicPlayer() { Menu(); }

	vector<M>GetPlaylistMy()const { return PlaylistMy; }
	vector<M>GetPlaylistDefault()const { return PlaylistDefault; }
	void ClearPlaylistMy() { PlaylistMy.clear(); }
	void ClearPlaylistDefault() { PlaylistDefault.clear(); }
	void PrintAllMusic()const
	{
		if (!Music.empty())
			for (int i = 0; i < Music.size(); i++)
			{
				cout << i + 1 << ": " << Music[i].ispolnitel << "/ " << Music[i].songname << endl;
			}
		else
			cout << "Music list is empty.\n";
	}
	void PrintPlaylistDefault()const
	{
		if (!PlaylistDefault.empty())
			for (int i = 0; i < PlaylistDefault.size(); i++)
			{
				cout << i + 1 << ": " << Music[i].ispolnitel << "/ " << Music[i].songname << endl;
			}
		else
			cout << "Music list is empty.\n";
	}
	void SearchByIspolnitel(const string &name)
	{
		for (int i = 0; i < Music.size(); i++)
		{
			if (Music[i].ispolnitel == name)
				cout <<i+1<<": " << Music[i].ispolnitel<<"/ "<<Music[i].songname<<endl;
		}
	}
	void Menu()
	{
		char vvod;
		do
		{
			system("cls");
			cout << "\t~~~~~~~~~~~~~~~~~~ Music player ~~~~~~~~~~~~~~~~~~\n";
			cout << "1.Default playlist.\n";
			cout << "2.My playlist.\n";
			cout << "3.Default playlist.\n";
			cout << "ESC. Exit.\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
			vvod = _getch();
			switch (vvod)
			{
			case'1':
			{
				system("pause");
				break;
			}
			case'2':
			{
				system("pause");
				break;
			}
			case'3':
			{
				system("pause");
				break;
			}
			default:
			{
				cout << "Wrong input.\n";
				system("pause");
				break;
			}			
			}
		} while (vvod != 27);
	}

	~MusicPlayer()
	{
		PlaylistDefault.clear();
		PlaylistMy.clear();
		Music.clear();
	}
};

int main()
{
	MusicPlayer A;
}