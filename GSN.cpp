#include <iostream>
#include <fstream>
#include <limits>
#include <utf8cpp/utf8.h>
using namespace std;

int valid_int_input(string prompt){
	int value;
	while (true) {
		cout << prompt;
		cin >> value;
		if (cin) break;
		cout << "\033[31mPodaj poprawne wartości.\033[39m" << endl;
		cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
	}
	return value;
}

// Hack for handling polish characters
int test_length(int length, string generated_nickname){
	bool if_valid;
	for (int i = 0; i < length; i++){
		if_valid = utf8::is_valid(generated_nickname.begin()+i, generated_nickname.begin()+i+1);
		if (!if_valid){
			length++,
			i++;
		}
	}
	return length;
}


int main(){
	string version = "1.0.0-cpp";
	string author = "oliwier975PL & workonfire";

	cout << "\033[97m         (        )  " << endl;
	cout << "\033[93m (       )\\ )  ( /(  " << endl;
	cout << "\033[33m )\\ )   (()/(  )\\()) " << endl;
	cout << "\033[91m(()/(    /(_))((_)\\  " << endl;
	cout << "\033[31m /(_))_ (_))   _((_) " << endl;
	cout << "\033[31m(_)) __|/ __| | \\| | " << endl;
	cout << "\033[31m  | (_ |\\__ \\ | .` | " << endl;
	cout << "\033[31m   \\___||___/ |_|\\_| " << endl << endl;
	cout << "\033[39mGenerator Spierdolonych Nicków v" << version << endl;
	cout << "\033[93mby " << author << "\033[39m" << endl << endl;

	int how_many_times = valid_int_input("Ilość nicków do wygenerowania: ");
	
	if (how_many_times == 69) {
		cout << "\033[91m▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄" << endl;
		cout << "\033[93m██ ███ █▄▄ ██▄██ ██ █ ▄▀▄ ██" << endl;
		cout << "\033[92m██ █ █ █▀▄███ ▄█ ██ █ █▄█ ██" << endl;
		cout << "\033[94m██▄▀▄▀▄█▄▄▄█▄▄▄██▄▄▄█▄███▄██" << endl;
		cout << "\033[95m▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀\033[39m" << endl;
	}

	int max_length = valid_int_input("Maksymalna ilość znaków: ");
	
	string save_to_file   ,
	       generate_number;
	//TODO
	//char strip_polish_chars;

	cout << "\033[31mUWAGA: Jeśli jakieś nicki będą przekraczały ustalony limit znaków, zostaną one przycięte.\033[39m" << endl;

	cout << "Zapisać wynik do pliku? (y/N): ";
	cin >> save_to_file;
	save_to_file = tolower(save_to_file[0]);

	cout << "Doklejać losową liczbę? (y/N): ";
	cin >> generate_number;
	generate_number = tolower(generate_number[0]);

	//TODO
	//cout << "Usunąć polskie znaki? (y/N): ";
	//cin >> strip_polish_chars;
	//strip_polish_chars = tolower(strip_polish_chars);
	
	string line;
	int lines[2] = {0};

        ifstream file[2];
	file[0].open("dictionaries/adjectives.txt");
	if (!file[0]){
		cout << "Wystąpił błąd w trakcie odczytywania pliku adjectives.txt" << endl;
		return EXIT_FAILURE;
	}

        while (getline(file[0], line))
          ++lines[0];

	file[1].open("dictionaries/nouns.txt");
	if (!file[1]){
		cout << "Wystąpił błąd w trakcie odczytywania pliku nouns.txt" << endl;
		return EXIT_FAILURE;
	}

	while (getline(file[1], line))
	  ++lines[1];

	string adjectives[lines[0]];

	file[0].clear();
	file[0].seekg(0);

	for (int i = 0; i < lines[0]; i++)
		getline(file[0], adjectives[i]);

	
	string nouns[lines[1]];

	file[1].clear();
	file[1].seekg(0);
	
	for (int i = 0; i < lines[1]; i++)
		getline(file[1], nouns[i]);


	string adjective     			  ,
	       noun          			  ,
	       generated_nick			  ;

        string* generated_nicknames = new string[how_many_times];

	srand((unsigned int)time(NULL));

	cout << "Generowanie nicków..." << endl << endl;

	for (int i = 1; i <= how_many_times; i++){
	  adjective = adjectives[rand() % lines[0]];
	  noun = nouns[rand() % lines[1]];
	  if ( rand() % 2 == 1)
		  noun = "_" + noun;
	  else
		  noun[0] = toupper(noun[0]); //TODO: Support for polish chars
	  generated_nick = adjective + noun;
	  if (generate_number == "y")
	    generated_nick = generated_nick + to_string(rand() % 100 + 1);
	  int new_length = test_length(max_length, generated_nick);
	  if (generated_nick.length() > new_length)
		  generated_nick.erase(new_length, std::string::npos);
	  generated_nicknames[i-1] = generated_nick;
	  cout << "\033[96m>> " << generated_nicknames[i-1] << endl;
	}

	cout << endl << "\033[92mGotowe.\033[39m" << endl;;

	if (save_to_file == "y"){
		ofstream outputFile("output.txt");
		for (int i = 0; i < how_many_times; i++)
			outputFile << generated_nicknames[i] << endl;
		outputFile.close();
		cout << "\033[92mZapisano nicki do pliku.\033[39m" << endl;
	}

	delete[] generated_nicknames;
	return EXIT_SUCCESS;
}
