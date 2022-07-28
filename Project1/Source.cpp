#include <iostream>
#include <vector>
#include <conio.h>
#include <fstream>
#include <string>
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
	MusicPlayer() { }

	vector<M>GetPlaylistMy()const { return PlaylistMy; }
	vector<M>GetPlaylistDefault()const { return PlaylistDefault; }
	vector<M>GetMusic()const { return Music; }
	void ClearPlaylistMy() { PlaylistMy.clear(); }
	void ClearMusicList() { Music.clear(); }
	void AddMyplaylist(vector<M>& tmp) { tmp.clear(); }
	void ClearPlaylistDefault() { PlaylistDefault.clear(); }
	void PrintPlaylist(const vector<M>&tmp)const
	{
		if (!tmp.empty())
			for (int i = 0; i < tmp.size(); i++)
			{
				cout << i + 1 << ": " << tmp[i].ispolnitel << "/ " << tmp[i].songname << endl;
			}
		else
			cout << "Music list is empty.\n";
	}
	vector<M> Add_ByIspolnitel(const string &name)
	{
		vector<M>tmp;
		if (!Music.empty())
			for (int i = 0; i < Music.size(); i++)
			{
				if (Music[i].ispolnitel == name)
				{
					tmp.push_back(Music[i]);
				}
			}
		else
			cout << "Music list is empty.\n";
		return tmp;
	}
	void Print_MusicByIspolnitel(const string& name)const
	{
		for (int i = 0; i < Music.size(); i++)
		{
			if (Music[i].ispolnitel == name)
				cout <<"[" << i + 1 << "]" << Music[i].ispolnitel << "/" << Music[i].songname << endl;
		}
	}
	void AddMusicList(vector<M>& tmp)
	{
		string str = "a";
		int i = 0;
		if (!tmp.empty())
			i = tmp.size() - 1;
		cout << "0. Exit.\n~~~~~~~~~~~~~~~~~~~~~~~~~\n";
		while (str[0] != '0')
		{
			cout << "Ispolnitel: ";
			cin >> str;
			if (str[0] != '0')
			{
				tmp.resize(i + 1);
				tmp[i].ispolnitel = str;
				cout << "Songname: ";
				cin >> str;
				tmp[i].songname = str;
				i++;
			}
		}
	}
	void Save_PlaylistMy(const vector<M>& tmp, const string&n)const
	{
		ofstream Savefile(n);
		if (Savefile.is_open())
		{
			for (int i = 0; i < tmp.size(); i++)
			{
				Savefile <<"[" << i + 1 << "]" << tmp[i].ispolnitel << "/" << tmp[i].songname << endl;
			}
			Savefile.close();
		}
		else
			cout << "File isnt open.\n";
	}
	void Load_PlaylistMy(vector<M>&tmp, const string& n)
	{
		ifstream Loadfile(n);
		if (Loadfile.is_open())
		{
			string str;
			string str2;
			int k = 0;
			int o = 0;
			while (!Loadfile.eof())
			{	
				getline(Loadfile, str);
				if (str.size() > 2)
				{	
					str2.resize(0);				
					for (int i = 3; str[i] != '/'; i++)
					{
						str2 += str[i];
						o = i;
					}
					tmp.resize(k + 1);
					tmp[k].ispolnitel = str2;
					str2.resize(0);
					for (int i = o+2; i<str.size(); i++)
					{
						str2 += str[i];
					}
					tmp[k].songname = str2;
					k++;
				}				
			}
			Loadfile.close();
		}
		else
			cout << "File isnt open.\n";
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
			cout << "3.All music.\n";
			cout << "ESC. Exit.\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
			vvod = _getch();
			switch (vvod)
			{
			case'1':
			{
				char vvod2;
				system("cls");
				cout << "\t~~~~~~~~~~~~~~~~~~ Music player ~~~~~~~~~~~~~~~~~~\n";
				cout << "1.Save to file.\n";
				cout << "2.Read from file.\n";
				cout << "3.Show this playlist.\n";
				cout << "ESC. Exit.\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
				vvod2 = _getch();
				switch (vvod2)
				{
				case'1':
				{
					system("pause");
					break;
				}
				default:
					break;
				}
				break;
			}
			case'2':
			{
				char vvod2;
				do
				{
					system("cls");
					cout << "\t~~~~~~~~~~~~~~~~~~ Music player ~~~~~~~~~~~~~~~~~~\n";
					cout << "1.Save to file.\n";
					cout << "2.Read from file.\n";
					cout << "3.Show this playlist.\n";
					cout << "ESC. Exit.\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
					vvod2 = _getch();
					switch (vvod2)
					{
					case'1':
					{
						Save_PlaylistMy(GetPlaylistMy(),"PlaylistMy.txt");
						system("pause");
						break;
					}
					case'2':
					{
						Load_PlaylistMy(PlaylistMy, "PlaylistMy.txt");
						system("pause");
						break;
					}
					case'3':
					{
						PrintPlaylist(GetPlaylistMy());
						system("pause");
						break;
					}
					default:
						break;
					}
				} while (vvod2 != 27);
				break;
			}
			case'3':
			{
				char vvod2;
				do
				{
					system("cls");
					cout << "\t~~~~~~~~~~~~~~~~~~ Music player ~~~~~~~~~~~~~~~~~~\n";
					cout << "1.Add Music.\n";
					cout << "2.Search.\n";
					cout << "3.Show this playlist.\n";
					cout << "4.Save playlist.\n";
					cout << "5.Load playlist.\n";
					cout << "ESC. Exit.\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
					vvod2 = _getch();
					switch (vvod2)
					{
					case'1':
					{
						AddMusicList(Music);
						system("pause");
						break;
					}
					case'2':
					{
						string str;
						cout << "\tPoisk.\nIspolnitel: ";
						cin >> str;
						Print_MusicByIspolnitel(str);
						Add_ByIspolnitel(str);
						system("pause");
						break;
					}
					case'3':
					{
						PrintPlaylist(GetMusic());
						system("pause");
						break;
					}
					case'4':
					{
						Save_PlaylistMy(GetMusic(),"Music.txt");
						system("pause");
						break;
					}
					case'5':
					{
						Load_PlaylistMy(Music, "Music.txt");
						system("pause");
						break;
					}
					default:
						break;
					}
				} while (vvod2 != 27);
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
	A.Menu();
}