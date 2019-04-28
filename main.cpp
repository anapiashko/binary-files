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
    struct name name;
    enum gender gender;
    char nation[30];
    int growth;
    int weight;
    struct data_birth data_birth;
    int number_ph;
    struct full_address address;
    long long card;
    unsigned long long bank_count;
};

void init_clients(client *pClient, int size);

client *init_array(int size);

void init_file(char *file, client *array, int size);

void display_array(client *pClient, int size);

void display_client(client client);

void add_clients(char *file, client *&pClient, int &size, int numberOfPeopleToAdd = 1);

void delete_one_from_clients(char *file, client *&pClient, int &size, int position);

void display_file(char *file);

void add_clients_to_end_of_file(char *file, client *array, int size, int numberOfPeopleToAdd);

void remove_element_from_file(char *file, int Position);

void shell_sort(client *array, int Dimension);

int menu();

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
    client *clients = init_array(size);
    void (*pointers_f[])(client *a, int b) = {init_clients, display_array, shell_sort};
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
                display_client(clients[person - 1]);
                break;
            }
            case 5: {
                int numberOfPeopleToAdd;
                cout << "How many people do you want to add_clients to your database? ";
                cin >> numberOfPeopleToAdd;
                cin.ignore();
                add_clients(file, clients, size, numberOfPeopleToAdd);
                break;
            }
            case 6: {
                int position;
                cout << " which person do you want to delete : ";
                cin >> position;
                delete_one_from_clients(file, clients, size, position);
                break;
            }
            case 7: {
                cout << setw(8) << "Bye!" << endl;
                system("pause");
                return 0;
            }
            case 8: {
                cout << "----------------------------" << endl;
                cout << "info in program: " << endl;
                display_array(clients, size);
                cout << "----------------------------" << endl;
                cout << "info in file: " << endl;
                display_file(file);
                cout << "----------------------------" << endl;
            }
        }
    }
}

int menu() {
    int n;
    cout << "    menu" << endl;
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

void remove_element_from_file(char *file, int Position) {
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
    display_file(file);
}

void add_clients_to_end_of_file(char *file, client *array, int size, int numberOfPeopleToAdd) {
    ofstream fout;
    fout.open(file, ios::binary | ios::app);
    client *arr;
    arr = array + size - numberOfPeopleToAdd;
    for (int i = 0; i < numberOfPeopleToAdd; i++) {
        fout.write((char *) (arr + i), sizeof(client));
    }
    fout.close();
}

void display_file(char *file) {

    ifstream fin;
    fin.open(file, ios::in | ios::binary);

    while (!fin.eof()) {
        client cl;
        fin.read((char *) &cl, sizeof(client));
        display_client(cl);
    }
    fin.close();
}

void init_file(char *file, client *array, int size) {
    ofstream fout;
    fout.open(file, ios::out | ios::binary);

    for (int i = 0; i < size; ++i) {
        fout.write((char *) &array[i], sizeof(client));
    }

    fout.close();
}

void delete_one_from_clients(char *file, client *&pClient, int &size, int position) {
    client *new_pClient = new client[size - 1];
    for (int i = 0; i < position - 1; i++) {
        new_pClient[i] = pClient[i];
    }
    for (int i = position - 1; i < size; i++) {
        new_pClient[i] = pClient[i + 1];
    }
    delete[] pClient;
    pClient = new_pClient;

    remove_element_from_file(file, position);

    cout << "The data was successfully deleted " << endl;
}

void add_clients(char *file, client *&pClient, int &size, int numberOfPeopleToAdd) {
    client *new_pClient = new client[size + numberOfPeopleToAdd];
    for (int i = 0; i < size; i++) {
        new_pClient[i] = pClient[i];
    }
    for (int j = size; j < size + numberOfPeopleToAdd; j++) {
        int s;
        cout << " your first name : ";
        cin.getline(new_pClient[j].name.first, 15);
        cout << "second : ";
        cin.getline(new_pClient[j].name.second, 15);
        cout << "third : ";
        cin.getline(new_pClient[j].name.third, 15);
        cout << " your gender \n 1) male \n 2) female : " << endl;
        cin >> s;
        new_pClient[j].gender = (gender) s;
        cin.ignore();
        cout << "your nationality : ";
        cin.getline(new_pClient[j].nation, 15);
        cout << "your growth : ";
        cin >> new_pClient[j].growth;
        cout << "weight : ";
        cin >> new_pClient[j].weight;
        cin.ignore();
        cout << "data of your birth : " << endl << "number ";
        cin >> new_pClient[j].data_birth.number;
        cout << "month ";
        cin >> new_pClient[j].data_birth.month;
        cout << "year ";
        cin >> new_pClient[j].data_birth.year;
        cout << "your number : ";
        cin >> new_pClient[j].number_ph;
        cout << "your address : " << endl << " index : ";
        cin >> new_pClient[j].address.index;
        cin.ignore();
        cout << "country : ";
        cin.getline(new_pClient[j].address.country, 15);
        cout << "region : ";
        cin.getline(new_pClient[j].address.region, 15);
        cout << "city : ";
        cin.getline(new_pClient[j].address.city, 15);
        cout << "street : ";
        cin.getline(new_pClient[j].address.street, 15);
        cout << " house number : ";
        cin >> s;
        new_pClient[j].address.number_house = s;
        cin.ignore();
        cout << "number of your credit card : ";
        cin >> new_pClient[j].card;
        cout << "number of your bank account : ";
        cin >> new_pClient[j].bank_count;
        cin.ignore();
    }
    size += numberOfPeopleToAdd;
    delete[] pClient;
    pClient = new_pClient;

    add_clients_to_end_of_file(file, pClient, size, numberOfPeopleToAdd);
}

void display_client(client client) {
    cout << "full name : " << client.name.first << " " << client.name.second << " " <<
         client.name.third << endl;
    if (client.gender == 1)
        cout << " male gender" << endl;
    if (client.gender == 2)
        cout << " female gender" << endl;
    cout << "nationality: " << client.nation << endl;
    cout << " growth " << client.growth << endl;
    cout << "weight " << client.weight << endl;
    cout << "date of birth : " << client.data_birth.number << "." << client.data_birth.month
         << "." << client.data_birth.year << endl;
    cout << " your number : " << client.number_ph << endl;
    cout << " address : " << client.address.index << ";" << client.address.country << "," <<
         client.address.region << "," << client.address.city << "," << client.address.street << ","
         << client.address.number_house << endl;
    cout << " number of your credit card : " << client.card << endl;
    cout << "bank account " << client.bank_count << endl;
}

void display_array(client *pClient, int size) {
    for (int i = 0; i < size; i++) {
        display_client(pClient[i]);
    }
}

void init_clients(client *pClient, int size) {
//    for (int i = 0; i < size; i++) {
//        cout << "Client " << i + 1 << endl;
//        int s;
//        cout << " your first name : ";
//        cin.getline(pClient[i].name.first, 15);
//        cout << "second : ";
//        cin.getline(pClient[i].name.second, 15);
//        cout << "third : ";
//        cin.getline(pClient[i].name.third, 15);
//        cout << " your gender \n 1) male \n 2) female : " << endl;
//        cin >> s;
//        pClient[i].gender = (gender)s;
//        cin.ignore();
//        cout << "your nationality : ";
//        cin.getline(pClient[i].nation, 15);
//        cout << "your growth : ";
//        cin >> pClient[i].growth;
//        cout << "weight : ";
//        cin >> pClient[i].weight;
//        cin.ignore();
//        cout << "data of your birth : " << endl << "number ";
//        cin >> pClient[i].data_birth.number;
//        cout << "month ";
//        cin >> pClient[i].data_birth.month;
//        cout << "year ";
//        cin >> pClient[i].data_birth.year;
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
    init_file(file, pClient, size);
    display_file(file);
}

client *init_array(int size) {
    client *pClient = new client[size];
    return pClient;
}