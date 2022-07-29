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
	bool Proverka(const string& A)
	{
		if (A.size() > 1)
		{
			if (A[0] != '0' || isdigit(A[0]) != 0)
			{
				for (int i = 1; i < A.size(); i++)
					if (isdigit(A[i]) == 0)
						return 0;
			}
			else
				return 0;
		}
		else
			if (isdigit(A[0]) != 0)
				return 1;
			else
				return 0;
		return 1;
	}

	vector<M>GetPlaylistMy()const { return PlaylistMy; }
	vector<M>GetPlaylistDefault()const { return PlaylistDefault; }
	vector<M>GetMusic()const { return Music; }
	bool Print_Playlist(const vector<M>&tmp)const
	{
		if (!tmp.empty())
		{
			for (int i = 0; i < tmp.size(); i++)
			{
				cout << "[" << i + 1 << "]" << tmp[i].ispolnitel << "/" << tmp[i].songname << endl;
			}
			return 1;
		}
		else
		{
			cout << "Music list is empty.\n";
			return 0;
		}
	}
	void Print_MusicByIspolnitel(vector<M>& tmp, const string& name)const
	{
		bool f = 0;
		if (!tmp.empty())
		{
			for (int i = 0; i < tmp.size(); i++)
			{
				if (tmp[i].ispolnitel == name)
				{
					cout << "[" << i + 1 << "]" << tmp[i].ispolnitel << "/" << tmp[i].songname << endl;
					f = 1;
				}
			}
		}
		else
			cout << "Music list is empty.\n";
		if (f == 0)
			cout << "Not found.\n";
	}
	void Add_ByIspolnitel(vector<M>&tmp, const string &name)
	{
		bool f = 0;
		if (!Music.empty())
		{
			tmp.clear();
			for (int i = 0; i < Music.size(); i++)
			{
				if (Music[i].ispolnitel == name)
				{
					tmp.push_back(Music[i]);
					f = 1;
				}
			}
		}
		else
			cout << "Music list is empty.\n";
		if (f == 0)
			cout << "Not found.\n";
	}
	void Add_MusicList(vector<M>& tmp)
	{
		string str = "a";
		int i = 0;
		if (!tmp.empty())
			i = tmp.size();
		system("cls");
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
				cout << endl;
			}
		}
	}
	void Add_toPlaylist(vector<M>& tmp)
	{
		string str = {"a"};
		int id = 0;
		while (Proverka(str)==0)
		{
			cout << "Get number of the song: ";
			cin >> str;
		}
		id = stoi(str);
		tmp.push_back(Music[id - 1]);
	}
	void Del_fromPlaylist(vector<M>& tmp)
	{
		if (!tmp.empty())
		{
			string str = { "a" };

			int end = tmp.size();
			while (Proverka(str) == 0)
			{
				cout << "Get number of the song: ";
				cin >> str;
				if (stoi(str) > tmp.size() || stoi(str)<1)
					str = "a";
			}

			tmp.erase(tmp.begin() + stoi(str) -1);
		}
		else
			cout << "Playlist is empty.\n";
	}
	void Save_PlaylistMy(const vector<M>& tmp, const string&n)const
	{
		char ch;
		cout << "1. Write fresh file.\n2. Write with old info.\n";
		ch = _getch();
		if (ch == '1')
		{
			ofstream Savefile(n);
			if (Savefile.is_open())
			{
				for (int i = 0; i < tmp.size(); i++)
				{
					Savefile << "[" << i + 1 << "]" << tmp[i].ispolnitel << "/" << tmp[i].songname << endl;
				}
				Savefile.close();
				cout << "Done.\n";
			}
			else
				cout << "File isnt open.\n";
			return;
		}
		if (ch == '2')
		{
			ofstream Savefile(n, ios::app);
			if (Savefile.is_open())
			{
				for (int i = 0; i < tmp.size(); i++)
				{
					Savefile << "[" << i + 1 << "]" << tmp[i].ispolnitel << "/" << tmp[i].songname << endl;
				}
				Savefile.close();
				cout << "Done.\n";
			}
			else
				cout << "File isnt open.\n";
			return;
		}
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
					str2.clear();				
					for (int i = 3; str[i] != '/'; i++)
					{
						str2 += str[i];
						o = i;
					}
					tmp.resize(k + 1);
					tmp[k].ispolnitel = str2;
					str2.clear();
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
			cout << "File wasnt open.\n";
	}
	void AppendPlaylists(vector<M>& A, const vector<M>& B)
	{
		for (int i = 0; i < B.size(); i++)
		{
			A.push_back(B[i]);
		}
		cout << "Done.\n";		
	}
	void CaseMenu(vector<M>& tmp, const string& n)
	{
		char vvod2;
		do
		{
			system("cls");
			cout << "\t~~~~~~~~~~~~~~~~~~ "<<n<<" ~~~~~~~~~~~~~~~~~~\n";
			cout << "1. Add Music(from 'All music').\n";
			cout << "2. Show this playlist.\n";
			cout << "3. Load from file.\n";
			cout << "4. Save to file.\n";
			cout << "5. Search by ispolnitel.\n";
			cout << "6. Delete music.\n";
			cout << "ESC. Main menu.\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
			vvod2 = _getch();
			switch (vvod2)
			{
			case'1':
			{
				if(Print_Playlist(Music))
				Add_toPlaylist(tmp);
				system("pause");
				break;
			}
			case'2':
			{
				Print_Playlist(tmp);
				system("pause");
				break;
			}
			case'3':
			{
				Load_PlaylistMy(tmp, n);
				system("pause");
				break;
			}
			case'4':
			{
				if (!tmp.empty())
					Save_PlaylistMy(tmp, n);
				else
					cout << "Playlist is empty.\n";
				system("pause");
				break;
			}
			case'5':
			{
				string str;
				system("cls");
				cout << "\t~~~~~~~~~~~~~~~~~~ Poisk ~~~~~~~~~~~~~~~~~~\nIspolnitel: ";
				cin >> str;
				Print_MusicByIspolnitel(Music, str);
				system("pause");
				break;
			}
			case'6':
			{
				system("cls");
				cout << "\t~~~~~~~~~~~~~~~~~~ Delete ~~~~~~~~~~~~~~~~~~\n";
				if (Print_Playlist(tmp))
				{
					char ch;
					cout << "\n1. Delete 1 song with id.\n2. Delete all.\n";	
					ch = _getch();
					if (ch == '1')
						Del_fromPlaylist(tmp);
					if (ch == '2')
						tmp.clear();
				}
				system("pause");
				break;
			}
			}
		} while (vvod2 != 27);
	}
	void Menu()
	{
		char vvod;
		do
		{
			system("cls");
			cout << "\t~~~~~~~~~~~~~~~~~~ Music player ~~~~~~~~~~~~~~~~~~\n";
			cout << "1. Default playlist.\n";
			cout << "2. My playlist.\n";
			cout << "3. All music.\n";
			cout << "4. 2 in 1 Playlists.\n";
			cout << "ESC. Exit.\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
			vvod = _getch();
			switch (vvod)
			{
			case'1':
			{
				CaseMenu(PlaylistDefault,"PlaylistDefault.txt");
				break;
			}
			case'2':
			{
				CaseMenu(PlaylistMy, "PlaylistMy.txt");
				break;
			}
			case'3':
			{
				char vvod2;
				do
				{
					system("cls");
					cout << "\t~~~~~~~~~~~~~~~~~~ All music ~~~~~~~~~~~~~~~~~~\n";
					cout << "1. Add Music.\n";
					cout << "2. Show this playlist.\n";
					cout << "3. Load playlist.\n";
					cout << "4. Save playlist.\n";
					cout << "5. Search + Add by ispolnitel.\n";
					cout << "6. Delete music.\n";
					cout << "ESC. Main menu.\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
					vvod2 = _getch();
					switch (vvod2)
					{
					case'1':
					{
						Add_MusicList(Music);
						system("pause");
						break;
					}
					case'2':
					{
						Print_Playlist(Music);
						system("pause");
						break;
					}
					case'3':
					{
						Load_PlaylistMy(Music, "Music.txt");						
						system("pause");
						break;
					}
					case'4':
					{
						Save_PlaylistMy(Music, "Music.txt");
						system("pause");
						break;
					}
					case'5':
					{
						string str;
						system("cls");
						cout << "\t~~~~~~~~~~~~~~~~~~ Poisk ~~~~~~~~~~~~~~~~~~\nIspolnitel: ";
						cin >> str;
						Print_MusicByIspolnitel(Music, str);
						cout << "\n\tWanna add all of them to 'MyPlayList' ?\n";
						cout << "1. Yes.\n2. No.\n";
						char vvod3 = _getch();
						if (vvod3 == '1')
						{
							Add_ByIspolnitel(PlaylistMy, str);
							cout << "Done.\n";
						}						
						system("pause");
						break;
					}
					case'6':
					{
						system("cls");
						cout << "\t~~~~~~~~~~~~~~~~~~ Delete ~~~~~~~~~~~~~~~~~~\n";
						if (Print_Playlist(Music))
						{
							char ch;
							cout << "\n1. Delete 1 song with id.\n2. Delete all.\n";
							ch = _getch();
							if (ch == '1')
								Del_fromPlaylist(Music);
							if (ch == '2')
								Music.clear();
						}
						system("pause");
						break;
					}
					}
				} while (vvod2 != 27);
				break;
			}
			case'4':
			{
				AppendPlaylists(PlaylistMy, PlaylistDefault);
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
	setlocale(LC_ALL, "ru");
	MusicPlayer A;
	A.Menu();
}