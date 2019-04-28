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

void InitClients(client *pClient, int size);

client *InitArray(int size);

void InitFile(char *file, client *array, int size);

void DisplayArray(client *pClient, int size);

void DisplayClient(client client);

void AddToClients(client *&pClient, int &size, int numberOfPeopleToAdd = 1);

void DeleteOneFromClients(client *&pClient, int &size, int position);

void DisplayFile(char *file);

void AddElementToEndOfFile(char *file, client *array, int size, int n);

void RemoveElementFromFile(char *file, int Position);

void ShellSort(client *array, int Dimension);

int Menu();

int GetPositionToRemove();

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


//    client kek[3];
//    int lol = sizeof(kek);
//
//    client* kek2 = new client[3];
//    int lol2 = 3 * sizeof(client);

    char file[] = "clients.txt";
    int size;
    cout << "Number of clients : ";
    cin >> size;
    client *clients = InitArray(size);
    void (*pointers_f[])(client *a, int b) = {InitClients, DisplayArray, ShellSort};
    while (true) {
        int a = Menu();
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
                int numberOfPeopleToAdd;
                cout << "How many people do you want to AddToClients to your database? ";
                cin >> numberOfPeopleToAdd;
                cin.ignore();
                AddToClients(clients, size, numberOfPeopleToAdd);
                AddElementToEndOfFile(file, clients, size, numberOfPeopleToAdd);
                break;
            }
            case 6: {
                int position = GetPositionToRemove();

                DeleteOneFromClients(clients, size, position);
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

int Menu() {
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
        Menu();
    }
}

void ShellSort(client *array, int Dimension) {
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
    delete[] temper;

    fin.seekg((Position) * sizeof(client), ios_base::beg);
    client *temper2 = new client[n - before - 1];
    fin.read((char *) temper2, sizeof(temper2));
    fout.open(new_file, ios::out | ios::binary | ios::app);
    fout.write((char *) temper2, sizeof(temper2));
    fout.close();
    delete[] temper2;

    fin.close();
    remove(file);
    rename(new_file, file);
    DisplayFile(file);
}

void AddElementToEndOfFile(char *file, client *array, int size, int n) {
    ofstream fout;
    fout.open(file, ios::binary | ios::app);
    client *arr;
    arr = array + size - n;
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

void InitFile(char *file, client *array, int size) {
    ofstream fout;
    fout.open(file, ios::out | ios::binary);

    for (int i = 0; i < size; ++i) {
        fout.write((char *) &array[i], sizeof(client));
    }

    fout.close();
}

int GetPositionToRemove() {
    int d;
    cout << " which person do you want to delete : ";
    cin >> d;

    return d;
}

void DeleteOneFromClients(client *&pClient, int &size, int position) {
    client *arr = new client[size - 1];
    for (int i = 0; i < position - 1; i++) {
        arr[i] = pClient[i];
    }
    for (int i = position - 1; i < size; i++) {
        arr[i] = pClient[i + 1];
    }
    delete[] pClient;
    pClient = arr;
    cout << "The data was successfully deleted " << endl;
}

void AddToClients(client *&pClient, int &size, int numberOfPeopleToAdd) {
    client *arr = new client[size + numberOfPeopleToAdd];
    for (int i = 0; i < size; i++) {
        arr[i] = pClient[i];
    }
    for (int j = size; j < size + numberOfPeopleToAdd; j++) {
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
    size += numberOfPeopleToAdd;
    delete[] pClient;
    pClient = arr;
}

void DisplayClient(client client) {
    cout << "full _name : " << client._name.first << " " << client._name.second << " " <<
         client._name.third << endl;
    if (client._gender == 1)
        cout << " male gender" << endl;
    if (client._gender == 2)
        cout << " female gender" << endl;
    cout << "nationality: " << client.nation << endl;
    cout << " growth " << client.growth << endl;
    cout << "weight " << client.weight << endl;
    cout << "date of birth : " << client._data_birth.number << "." << client._data_birth.month
         << "." << client._data_birth.year << endl;
    cout << " your number : " << client.number_ph << endl;
    cout << " address : " << client.address.index << ";" << client.address.country << "," <<
         client.address.region << "," << client.address.city << "," << client.address.street << ","
         << client.address.number_house << endl;
    cout << " number of your credit card : " << client.card << endl;
    cout << "bank account " << client.bank_count << endl;
}

void DisplayArray(client *pClient, int size) {

    cout << "info in program: " << endl;

    for (int i = 0; i < size; i++) {
        DisplayClient(pClient[i]);
    }
}

void InitClients(client *pClient, int size) {
//    for (int i = 0; i < size; i++) {
//        cout << "Client " << i + 1 << endl;
//        int s;
//        cout << " your first name : ";
//        cin.getline(pClient[i]._name.first, 15);
//        cout << "second : ";
//        cin.getline(pClient[i]._name.second, 15);
//        cout << "third : ";
//        cin.getline(pClient[i]._name.third, 15);
//        cout << " your gender \n 1) male \n 2) female : " << endl;
//        cin >> s;
//        pClient[i]._gender = (gender)s;
//        cin.ignore();
//        cout << "your nationality : ";
//        cin.getline(pClient[i].nation, 15);
//        cout << "your growth : ";
//        cin >> pClient[i].growth;
//        cout << "weight : ";
//        cin >> pClient[i].weight;
//        cin.ignore();
//        cout << "data of your birth : " << endl << "number ";
//        cin >> pClient[i]._data_birth.number;
//        cout << "month ";
//        cin >> pClient[i]._data_birth.month;
//        cout << "year ";
//        cin >> pClient[i]._data_birth.year;
//        cout << "your number : ";
//        cin >> pClient[i].number_ph;
//        cout << "your address : " << endl << " index : ";
//        cin >> pClient[i].address.index;
//        cin.ignore();
//        cout << "country : ";
//        cin.getline(pClient[i].address.country, 15);
//        cout << "region : ";
//        cin.getline(pClient[i].address.region, 15);
//        cout << "city : ";
//        cin.getline(pClient[i].address.city, 15);
//        cout << "street : ";
//        cin.getline(pClient[i].address.street, 15);
//        cout << " house number : ";
//        cin >> s;
//        pClient[i].address.number_house = s;
//        cin.ignore();
//        cout << "number of your credit card : ";
//        cin >> pClient[i].card;
//        cout << "number of your bank account : ";
//        cin >> pClient[i].bank_count;
//        cin.ignore();
//    }

    for (int i = 0; i < size; i++) {
        pClient[i].bank_count = i + 1;
    }

    char file[] = "clients.txt";
    InitFile(file, pClient, size);
    DisplayFile(file);
}

client *InitArray(int size) {
    client *pClient = new client[size];
    return pClient;
}