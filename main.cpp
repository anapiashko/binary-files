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
    name _name;
    gender _gender;
    char nation[30];
    int growth;
    int weight;
    data_birth _data_birth;
    int number_ph;
    full_address address;
    long long card;
    unsigned long long bank_count;
};

client *InitArray(int Dimension);

void InitClient(client *array, int i);

void DisplayArray(client *array, int Dimension);

void DisplayClient(client a);

void add(client *&array, int &Dimension, int a = 1);

void deleteOneFromClients(client *&array, int position);

void InitFile(char *file, client *array, int Dimension);

void DisplayFile(char *file);

void AddToEndFile(char *file, client *array, int Dimension, int n);

void RemoveElementFromFile(char *file, int Position);

void shell_sort(client *array, int Dimension);

int menu();

int getPositionToRemove();

int main(int argc, char *argv[]) {
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
    client *clients = InitArray(size);
    void (*pointers_f[])(client *a, int b) = {InitClient, DisplayArray, shell_sort};
    while (true) {
        int a = menu();
        switch (a) {
            default: {
                (*pointers_f[a - 1])(clients, size);
                break;
            }
            case 4: {
                int person;
                cout << "Which person do you to see? ";
                cin >> person;
                DisplayClient(clients[person - 1]);
                break;
            }
            case 5: {
                int a;
                cout << "How many people do you want to add to your database? ";
                cin >> a;
                cin.ignore();
                add(clients, size, a);
                AddToEndFile(file, clients, size, a);
                DisplayFile(file);
                break;
            }
            case 6: {
                int position = getPositionToRemove();

                deleteOneFromClients(clients, position);
                RemoveElementFromFile(file, position);

                DisplayArray(clients, size);
                break;
            }
            case 7: {
                cout << setw(8) << "Bye!" << endl;
                system("pause");
                return 0;
            }
            case 8: {
                DisplayFile(file);
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
    cout << "8) Display " << endl;
    cout << "Choose : ";
    cin >> n;
    cin.ignore();
    if (n >= 1 && n <= 8)
        return n;
    else {
        cout << " Incorrect input! " << endl;
        menu();
    }
}

void shell_sort(client *array, int Dimension) {
    int i, j, k;
    client temp;
    int t;
    for (k = Dimension / 2; k > 0; k /= 2)
        for (i = k; i < Dimension; i++) {
            temp = array[i];
            t = array[i].growth;
            for (j = i; j >= k; j -= k) {
                if (t < array[j - k].growth)
                    array[j] = array[j - k];
                else
                    break;
            }
            array[j] = temp;
        }
}

void RemoveElementFromFile(char *file, int Position) {
    ifstream fin;
    ofstream fout;
    fin.open(file, ios::in | ios::binary);
    fin.seekg(0, ios_base::end);
    int n = fin.tellg() / sizeof(client);
    char new_file[] = "new_file.txt";

    fin.seekg((Position - 1) * sizeof(client), ios_base::beg);
    int before = fin.tellg() / sizeof(client);
    client *temper = new client[before];
    fin.read((char *) temper, sizeof(temper));
    fout.open(new_file, ios::out | ios::binary);
    fout.write((char *) temper, sizeof(temper));
    fout.close();

    fin.seekg((Position) * sizeof(client), ios_base::beg);
    client *temper2 = new client[n - before - 1];
    fin.read((char *) temper2, sizeof(temper2));
    fout.open(new_file, ios::out | ios::binary | ios::app);
    fout.write((char *) temper2, sizeof(temper2));
    fout.close();

    delete[] temper;
    delete[] temper2;

    fin.close();
    remove(file);
    rename(new_file, file);
    DisplayFile(file);
}

void AddToEndFile(char *file, client *array, int Dimension, int n) {
    ofstream fout;
    fout.open(file, ios::binary | ios::app);
    client *arr;
    arr = array + Dimension - n;
    for (int i = 0; i < n; i++) {
        fout.write((char *) (arr + i), sizeof(client));
    }
    fout.close();
}

void DisplayFile(char *file) {

    cout << "info in file: " << endl;

    ifstream fin;
    fin.open(file, ios::in | ios::binary);

    while (!fin.eof()) {
        client cl;
        fin.read((char *) &cl, sizeof(client));
        DisplayClient(cl);
    }
    fin.close();
}

void InitFile(char *file, client *array, int Dimension) {
    ofstream fout;
    fout.open(file, ios::out | ios::binary);
    for (int i = 0; i < Dimension; i++) {
        fout.write((char *) &array[i], sizeof(client));
    }
    fout.close();
}

int getPositionToRemove() {
    int d;
    cout << " which person do you want to delete : ";
    cin >> d;

    return d;
}

void deleteOneFromClients(client *&array, int position) {
    int dimension = sizeof(array);
    client *arr = new client[dimension - 1];
    for (int i = position - 1; i < dimension; i++) {
        arr[i] = array[i + 1];
    }
    delete[] array;
    array = arr;
    cout << "The data was successfully deleted " << endl;
}

void add(client *&array, int &Dimension, int a) {
    client *arr = new client[Dimension + a];
    for (int i = 0; i < Dimension; i++) {
        arr[i] = array[i];
    }
    for (int j = Dimension; j < Dimension + a; j++) {
        int s;
        cout << " your first name : ";
        cin.getline(arr[j]._name.first, 15);
        cout << "second : ";
        cin.getline(arr[j]._name.second, 15);
        cout << "third : ";
        cin.getline(arr[j]._name.third, 15);
        cout << " your gender \n 1) male \n 2) female : " << endl;
        cin >> s;
        arr[j]._gender = (gender) s;
        cin.ignore();
        cout << "your nationality : ";
        cin.getline(arr[j].nation, 15);
        cout << "your growth : ";
        cin >> arr[j].growth;
        cout << "weight : ";
        cin >> arr[j].weight;
        cin.ignore();
        cout << "data of your birth : " << endl << "number ";
        cin >> arr[j]._data_birth.number;
        cout << "month ";
        cin >> arr[j]._data_birth.month;
        cout << "year ";
        cin >> arr[j]._data_birth.year;
        cout << "your number : ";
        cin >> arr[j].number_ph;
        cout << "your address : " << endl << " index : ";
        cin >> arr[j].address.index;
        cin.ignore();
        cout << "country : ";
        cin.getline(arr[j].address.country, 15);
        cout << "region : ";
        cin.getline(arr[j].address.region, 15);
        cout << "city : ";
        cin.getline(arr[j].address.city, 15);
        cout << "street : ";
        cin.getline(arr[j].address.street, 15);
        cout << " house number : ";
        cin >> s;
        arr[j].address.number_house = s;
        cin.ignore();
        cout << "number of your credit card : ";
        cin >> arr[j].card;
        cout << "number of your bank account : ";
        cin >> arr[j].bank_count;
        cin.ignore();
    }
    Dimension += a;
    delete[] array;
    array = arr;
}

void DisplayClient(client a) {
    cout << "full _name : " << a._name.first << " " << a._name.second << " " <<
         a._name.third << endl;
    if (a._gender == 1)
        cout << " male gender" << endl;
    if (a._gender == 2)
        cout << " female gender" << endl;
    cout << "nationality: " << a.nation << endl;
    cout << " growth " << a.growth << endl;
    cout << "weight " << a.weight << endl;
    cout << "date of birth : " << a._data_birth.number << "." << a._data_birth.month
         << "." << a._data_birth.year << endl;
    cout << " your number : " << a.number_ph << endl;
    cout << " address : " << a.address.index << ";" << a.address.country << "," <<
         a.address.region << "," << a.address.city << "," << a.address.street << ","
         << a.address.number_house << endl;
    cout << " number of your credit card : " << a.card << endl;
    cout << "bank account " << a.bank_count << endl;
}

void DisplayArray(client *array, int Dimension) {

    cout << "info in program: " << endl;

    for (int i = 0; i < Dimension; i++) {
        DisplayClient(array[i]);
    }
}

void InitClient(client *array, int Dimension) {
//    for (int i = 0; i < Dimension; i++) {
//        cout << "Client " << i + 1 << endl;
//        int s;
//        cout << " your first name : ";
//        cin.getline(array[i]._name.first, 15);
//        cout << "second : ";
//        cin.getline(array[i]._name.second, 15);
//        cout << "third : ";
//        cin.getline(array[i]._name.third, 15);
//        cout << " your gender \n 1) male \n 2) female : " << endl;
//        cin >> s;
//        array[i]._gender = (gender)s;
//        cin.ignore();
//        cout << "your nationality : ";
//        cin.getline(array[i].nation, 15);
//        cout << "your growth : ";
//        cin >> array[i].growth;
//        cout << "weight : ";
//        cin >> array[i].weight;
//        cin.ignore();
//        cout << "data of your birth : " << endl << "number ";
//        cin >> array[i]._data_birth.number;
//        cout << "month ";
//        cin >> array[i]._data_birth.month;
//        cout << "year ";
//        cin >> array[i]._data_birth.year;
//        cout << "your number : ";
//        cin >> array[i].number_ph;
//        cout << "your address : " << endl << " index : ";
//        cin >> array[i].address.index;
//        cin.ignore();
//        cout << "country : ";
//        cin.getline(array[i].address.country, 15);
//        cout << "region : ";
//        cin.getline(array[i].address.region, 15);
//        cout << "city : ";
//        cin.getline(array[i].address.city, 15);
//        cout << "street : ";
//        cin.getline(array[i].address.street, 15);
//        cout << " house number : ";
//        cin >> s;
//        array[i].address.number_house = s;
//        cin.ignore();
//        cout << "number of your credit card : ";
//        cin >> array[i].card;
//        cout << "number of your bank account : ";
//        cin >> array[i].bank_count;
//        cin.ignore();
//    }
    char file[] = "clients.txt";
    InitFile(file, array, Dimension);
    DisplayFile(file);
}

client *InitArray(int Dimension) {
    client *array = new client[Dimension];

    for (int i = 0; i < Dimension; i++) {
        array[i].bank_count = i + 1;
    }

    return array;
}