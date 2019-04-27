#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

enum gender {
    male = 1, female
};
struct name {
    char first[15];
    char second[15];
    char third[15];
};
struct data_birth {
    int number;
    int month;
    int year;
};
struct full_address {
    int index;
    char country[15];
    char region[15];
    char city[15];
    char street[15];
    unsigned number_house : 8;
};
struct client {
    name name;
    gender gender;
    char nation[30];
    int growth;
    int weight;
    data_birth data_birth;
    int number_ph;
    full_address adress;
    long long card;
    unsigned long long bahk_count;
};
client* InitArray(int Dimension);

void InitClient(client* array, int i);

void DisplayArray(client* array, int Dimension);

void DisplayClient(client a);

void add(client *&array, int &Dimension, int a = 1 );

int delete_(client *&array, int &Dimension);

void InitFile(char* file, client* array, int Dimension);

void DisplayFile(char* file);

void AddToEndFile(char* file, client* array, int Dimension, int n);

void RemoveElementFromFile(char* file, int Position);

void shell_sort(client* array, int Dimension);

int menu();

int main(int argc, char* argv[]) {
/*
	char password[] = "password";

	if (argc != 2) {
		cout << "you forgot to enter password" << endl;
		return 1;
	}

	if (strcmp(password, argv[1])) {
		cout << "password is wrong." << endl;
		return 1;
	}*/
    char file[] = "clients.txt";
    int size;
    cout << "Number of clients : ";
    cin >> size;
    client* b = InitArray(size);
    void(*pointers_f[])(client* a, int b) = { InitClient,DisplayArray, shell_sort };
    while (true) {
        int a = menu();
        switch (a) {
            default: {
                (*pointers_f[a - 1])(b, size);
                break;
            }
            case 4: {
                int person;
                cout << "Which person do you to see? ";
                cin >> person;
                DisplayClient(b[person - 1]);
                break;
            }
            case 5: {
                int a;
                cout << "How many people do you want to add to your database? ";
                cin >> a;
                cin.ignore();
                add(b, size, a);
                AddToEndFile(file, b, size, a);
                DisplayFile(file);
                break;
            }
            case 6: {
                int position = delete_(b, size) ;
                RemoveElementFromFile(file,position);
                DisplayArray(b , size);
                break;
            }
            case 7: {
                cout << setw(8) << "Bye!" << endl;
                system("pause");
                return 0;
            }
        }
    }
}
int menu() {
    int n;
    cout << "    Menu" << endl;
    cout << "1) Enter massiv" << endl;
    cout << "2) Output of an array" << endl;
    cout << "3) Sorting array" << endl;
    cout << "4) Output data about one person " << endl;
    cout << "5) Add structure " << endl;
    cout << "6) Delete structure " << endl;
    cout << "7) Exit " << endl;
    cout << "Choose : ";
    cin >> n;
    cin.ignore();
    if (n >= 1 && n <= 7)
        return n;
    else {
        cout << " Incorrect input! " << endl;
        menu();
    }
}
void shell_sort(client* array, int Dimension) {
    int i, j, k;
    client temp;
    int t;
    for (k = Dimension/2; k > 0; k /= 2)
        for (i = k; i < Dimension; i++){
            temp = array[i];
            t = array[i].growth;
            for (j = i; j >= k; j -= k){
                if(t < array[j - k].growth)
                    array[j] = array[j - k];
                else
                    break;
            }
            array[j] = temp;
        }
}
void RemoveElementFromFile(char* file, int Position) {
    ifstream fin;
    ofstream fout;
    fin.open(file, ios::binary);
    fin.seekg(0, ios_base::end);
    int n = fin.tellg() / sizeof(client);
    char new_file[] = "new_file.txt";

    fin.seekg((Position-1) * sizeof(client), ios_base::beg);
    int before = fin.tellg() / sizeof(client);
    client* temper = new client[before];
    fin.read((char*)temper, sizeof(temper));
    fout.open(new_file, ios::binary);
    fout.write((char*)temper, sizeof(temper));
    fout.close();

    fin.seekg((Position) * sizeof(client), ios_base::beg);
    client* temper2 = new client[n-before-1];
    fin.read((char*)temper2, sizeof(temper2));
    fout.open(new_file, ios::binary | ios::app);
    fout.write((char*)temper2, sizeof(temper2));
    fout.close();

    delete[] temper;
    delete[] temper2;

    fin.close();
    remove(file);
    rename(new_file, file);
    DisplayFile(file);
}
void AddToEndFile(char* file , client* array, int Dimension , int n) {
    ofstream fout;
    fout.open(file,ios::binary | ios::app);
    client* arr;
    arr = array + Dimension-n;
    for (int i = 0; i < n; i++) {
        fout.write((char*)(arr+i), sizeof(client));
    }
    fout.close();
}
void DisplayFile(char* file) {
    ifstream fin;
    fin.open(file, ios::binary);
    client cl;
    while (fin.read((char*)&cl, sizeof(client))) {
        DisplayClient(cl);
    }
    fin.close();
}
void InitFile(char* file, client* array, int Dimension) {
    ofstream fout;
    fout.open(file, ios::binary);
    for(int i = 0; i < Dimension; i++){
        fout.write((char*)&array[i], sizeof(client));
    }
    fout.close();
}
int delete_(client *&array, int &Dimension) {
    int d;
    cout << " which person do you want to delete : ";
    cin >> d;
    client* arr = new client[Dimension - 1];
    for (int i = d - 1; i < Dimension; i++) {
        arr[i] = array[i + 1];
    }
    Dimension--;
    delete[] array;
    array = arr;
    cout << "The data was successfully deleted " << endl;
    return d;
}
void add(client *&array, int &Dimension, int a) {
    client* arr = new client[Dimension + a];
    for (int i = 0; i < Dimension; i++) {
        arr[i] = array[i];
    }
    for (int j = Dimension; j < Dimension + a; j++) {
        int s;
        cout << " your first name : ";
        cin.getline(arr[j].name.first, 15);
        cout << "second : ";
        cin.getline(arr[j].name.second, 15);
        cout << "third : ";
        cin.getline(arr[j].name.third, 15);
        cout << " your gender \n 1) male \n 2) female : " << endl;
        cin >> s;
        arr[j].gender = (gender)s;
        cin.ignore();
        cout << "your nationality : ";
        cin.getline(arr[j].nation, 15);
        cout << "your growth : ";
        cin >> arr[j].growth;
        cout << "weight : ";
        cin >> arr[j].weight;
        cin.ignore();
        cout << "data of your birth : " << endl << "number ";
        cin >> arr[j].data_birth.number;
        cout << "month ";
        cin >> arr[j].data_birth.month;
        cout << "year ";
        cin >> arr[j].data_birth.year;
        cout << "your number : ";
        cin >> arr[j].number_ph;
        cout << "your adress : " << endl << " index : ";
        cin >> arr[j].adress.index;
        cin.ignore();
        cout << "country : ";
        cin.getline(arr[j].adress.country, 15);
        cout << "region : ";
        cin.getline(arr[j].adress.region, 15);
        cout << "city : ";
        cin.getline(arr[j].adress.city, 15);
        cout << "street : ";
        cin.getline(arr[j].adress.street, 15);
        cout << " house number : ";
        cin >> s;
        arr[j].adress.number_house = s;
        cin.ignore();
        cout << "number of your credit card : ";
        cin >> arr[j].card;
        cout << "number of your bank account : ";
        cin >> arr[j].bahk_count;
        cin.ignore();
    }
    Dimension += a;
    delete[] array;
    array = arr;
}
void DisplayClient(client a) {
    cout << "full name : " << a.name.first << " " << a.name.second << " " <<
         a.name.third << endl;
    if (a.gender == 1)
        cout << " male gender" << endl;
    if (a.gender == 2)
        cout << " female gender" << endl;
    cout << "nationality: " << a.nation << endl;
    cout << " growth " << a.growth << endl;
    cout << "weight " << a.weight << endl;
    cout << "date of birth : " << a.data_birth.number << "." << a.data_birth.month
         << "." << a.data_birth.year << endl;
    cout << " your number : " << a.number_ph << endl;
    cout << " adress : " << a.adress.index << ";" << a.adress.country << "," <<
         a.adress.region << "," << a.adress.city << "," << a.adress.street << ","
         << a.adress.number_house << endl;
    cout << " number of your credit card : " << a.card << endl;
    cout << "bank count " << a.bahk_count << endl;
}
void DisplayArray(client* array, int Dimension) {
    for (int i = 0; i < Dimension; i++) {
        cout << "full name : " << array[i].name.first << " " << array[i].name.second << " " <<
             array[i].name.third << endl;
        if (array[i].gender == 1)
            cout << " male gender" << endl;
        if (array[i].gender == 2)
            cout << " female gender" << endl;
        cout << "nationality: " << array[i].nation << endl;
        cout << " growth " << array[i].growth << endl;
        cout << "weight " << array[i].weight << endl;
        cout << "date of birth : " << array[i].data_birth.number << "." << array[i].data_birth.month
             << "." << array[i].data_birth.year << endl;
        cout << " your number : " << array[i].number_ph << endl;
        cout << " adress : " << array[i].adress.index << ";" << array[i].adress.country << "," <<
             array[i].adress.region << "," << array[i].adress.city << "," << array[i].adress.street << ","
             << array[i].adress.number_house << endl;
        cout << " number of your credit card : " << array[i].card << endl;
        cout << "bank count " << array[i].bahk_count << endl;
    }
}
void InitClient(client* array, int Dimension) {
    for (int i = 0; i < Dimension; i++) {
        cout << "Client " << i + 1 << endl;
        int s;
        cout << " your first name : ";
        cin.getline(array[i].name.first, 15);
        cout << "second : ";
        cin.getline(array[i].name.second, 15);
        cout << "third : ";
        cin.getline(array[i].name.third, 15);
        cout << " your gender \n 1) male \n 2) female : " << endl;
        cin >> s;
        array[i].gender = (gender)s;
        cin.ignore();
        cout << "your nationality : ";
        cin.getline(array[i].nation, 15);
        cout << "your growth : ";
        cin >> array[i].growth;
        cout << "weight : ";
        cin >> array[i].weight;
        cin.ignore();
        cout << "data of your birth : " << endl << "number ";
        cin >> array[i].data_birth.number;
        cout << "month ";
        cin >> array[i].data_birth.month;
        cout << "year ";
        cin >> array[i].data_birth.year;
        cout << "your number : ";
        cin >> array[i].number_ph;
        cout << "your adress : " << endl << " index : ";
        cin >> array[i].adress.index;
        cin.ignore();
        cout << "country : ";
        cin.getline(array[i].adress.country, 15);
        cout << "region : ";
        cin.getline(array[i].adress.region, 15);
        cout << "city : ";
        cin.getline(array[i].adress.city, 15);
        cout << "street : ";
        cin.getline(array[i].adress.street, 15);
        cout << " house number : ";
        cin >> s;
        array[i].adress.number_house = s;
        cin.ignore();
        cout << "number of your credit card : ";
        cin >> array[i].card;
        cout << "number of your bank account : ";
        cin >> array[i].bahk_count;
        cin.ignore();
    }
    char file[] = "clients.txt";
    InitFile(file, array, Dimension);
    DisplayFile(file);
}
client* InitArray(int Dimension) {
    client* array = new client[Dimension];
    return array;
}