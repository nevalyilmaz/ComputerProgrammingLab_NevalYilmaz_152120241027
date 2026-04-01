#include <iostream>

using namespace std;

struct Package{
    string packageID;
    string destinationCity;
    int dimensions[3];
    Package* next;
};

struct courierName{
    string courierName;
    string vehicleType;
};
Package* stackTop = nullptr;

const int queuesize=5;
courierName courierQueue[queuesize];
int front = -1;
int rear = -1;

void pushPackage(string id, string city, int l, int w, int h) {
    Package* newPackage = new Package;
    newPackage->packageID = id;
    newPackage->destinationCity = city;
    newPackage->dimensions[0] = l;
    newPackage->dimensions[1] = w;
    newPackage->dimensions[2] = h;

    newPackage->next = stackTop;
    stackTop = newPackage;
}
void popPackage() {
    if (stackTop == nullptr) return;
    Package* temp = stackTop;
    stackTop = stackTop->next;
    delete temp;
}
bool isQueueFull() {
    return (front == (rear + 1) % queuesize);
}
bool isQueueEmpty() {
    return (front == -1);
}
void enqueueCourier(string name, string vehicle) {
    if (isQueueFull()) {
        cout << "Kurye sirasi dolu!" << endl;
        return;
    }
    if (front == -1) front = 0;

    rear = (rear + 1) % queuesize;
    courierQueue[rear].courierName = name;
    courierQueue[rear].vehicleType = vehicle;
    cout << "Kurye kaydedildi: " << name << endl;
}
void dequeueCourier() {
    if (isQueueEmpty()) return;

    if (front == rear) {
        front = -1;
        rear = -1;
    } else {
        front = (front + 1) % queuesize;
    }
}
void dispatch() {
    if (stackTop == nullptr) {
        cout << "Gonderilecek paket yok!" << endl;
        return;
    }
    if (isQueueEmpty()) {
        cout << "Bekleyen kurye yok!" << endl;
        return;
    }

    cout << "--- DISPATCH GERCEKLESTI ---" << endl;
    cout << "Kurye: " << courierQueue[front].courierName;
    cout << " -> Paket: " << stackTop->packageID << " (" << stackTop->destinationCity << ")" << endl;

    popPackage();
    dequeueCourier();
}
void display() {
    cout << "\n--- MEVCUT DURUM ---" << endl;

    cout << "Paketler (Stack): ";
    Package* temp = stackTop;
    if (!temp) cout << "Bos";
    while (temp) {
        cout << "[" << temp->packageID << "] -> ";
        temp = temp->next;
    }

    cout << "\nKuryeler (Queue): ";
    if (isQueueEmpty()) cout << "Bos";
    else {
        int i = front;
        while (true) {
            cout << "(" << courierQueue[i].courierName << ") ";
            if (i == rear) break;
            i = (i + 1) % queuesize;
        }
    }
    cout << "\n--------------------\n";
}
int main() {
    pushPackage("001", "Denizli",12,8,6);
    pushPackage("002", "Eskisehir",14,9,17);

    enqueueCourier("Faruk", "Motor");
    enqueueCourier("Bilal", "Araba");

    display();

    dispatch();

    display();

    return 0;
}
