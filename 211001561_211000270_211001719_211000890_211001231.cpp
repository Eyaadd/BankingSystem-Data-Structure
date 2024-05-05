#include <iostream>
using namespace std;

int generateID();
void mainMenu();
void clientHomeMSG();
void transactionsMenuMSG();

class Transaction {
private:
    int transactionID;
    string transactionName;
    string transactionDate;

public:
    Transaction() {
        transactionID = -1;
        transactionName = "";
        transactionDate = "";
    }

    Transaction(int id, string name, string date) {
        transactionID = id;
        transactionName = name;
        transactionDate = date;
    }

    int getTransactionID() { return transactionID; }
    string getTransactionName() { return transactionName; }
    string getTransactionDate() { return transactionDate; }

    void setTransactionID(int id) { transactionID = id; }
    void setTransactionName(string name) { transactionName = name; }
    void setTransactionDate(string date) { transactionDate = date; }

    void printTransaction() {
        cout << "Transaction ID: " << transactionID << endl;
        cout << "Transaction Name: " << transactionName << endl;
        cout << "Transaction Date: " << transactionDate << endl;
    }
};

class Client{
protected:
    string clientName;
    string clientEmail;
    string clientPhone;
    string clientAddress;
    string clientPassword;
    int clientID;
    Transaction transactions[5];
    int transaction_counter=0;

public:
    Client(){
        clientName = "";
        clientEmail = "";
        clientPhone = "";
        clientAddress = "";
        clientID=0;
    }
    Client(string name, string email, string phone, string address)
    {
        clientName = name;
        clientEmail = email;
        clientPhone = phone;
        clientAddress = address;
    }

    void setName(string name) { clientName = name; }
    void setEmail(string email) { clientEmail = email; }
    void setPhone(string phone) { clientPhone = phone; }
    void setAddress(string address) { clientAddress = address; }
    void setPassword(string password) { clientPassword = password; }
    void setID(int id) { clientID = id; }
    void setTransaction(Transaction t, int index)
    {
        transactions[index] = t;
        if(transactions[index].getTransactionID()==-1)
            transaction_counter--;
        else
            transaction_counter++;
    }

    string getName() { return clientName; }
    string getEmail() { return clientEmail; }
    string getPhone() { return clientPhone; }
    string getAddress() { return clientAddress; }
    string getPassword() { return clientPassword; }
    int getID() { return clientID; }
    Transaction getTransaction(int index) { return transactions[index]; }
    int get_TC(){return transaction_counter;}

    void printClientInfo()
    {
        cout << "Name: " << clientName << endl;
        cout << "Email: " << clientEmail << endl;
        cout << "Phone: " << clientPhone << endl;
        cout << "Address: " << clientAddress << endl;
        cout << "ID: " << clientID << endl;
    }
};

template <class T>
class LinkedListNode{
public:
    T data;
    LinkedListNode *next;

    LinkedListNode(){
        data = 0;
        next = nullptr
        ;
    }

    LinkedListNode(T D)
    {
        data = D;
        next = nullptr
        ;
    }
};

template <class T>
class ClientsLinkedList:public Client{
    LinkedListNode<T> *head[10];
    LinkedListNode<T> *tail[10];
    LinkedListNode<T> *C[10];
    int listSize[10];
    
public:
    ClientsLinkedList()
    {
        for(int i=0 ; i<10 ; i++){
            head[i] = tail[i] = C[i] = nullptr;
            listSize[i]=0;
        }
    }

    void newClientMenu(T data)
    {

        LinkedListNode<T>* newNode = new LinkedListNode<T>(data);
        int ids=generateID();
        newNode->data.setID(ids);
        
        if(C[ids%10]==nullptr){

            cout<<"Enter E-Mail"<<endl;
            cin >>clientEmail;
            newNode->data.setEmail(clientEmail);

            for(int i=0;i<10;i++){
                LinkedListNode<T>* here = C[i];
                while(here != nullptr
                ){
                    if(here->data.getEmail() == newNode->data.getEmail()){
                        cout<<"Employee already exists"<<endl;
                        delete newNode;
                        return ;
                    }
                    here=here->next;
                }
            }

            cout<<"Enter Full Name"<<endl;
            cin >>clientName;
            newNode->data.setName(clientName);
            cout<<"Enter Phone Number"<<endl;
            cin >>clientPhone;
            newNode->data.setPhone(clientPhone);
            cout<<"Enter Password"<<endl;
            cin >>clientPassword;
            newNode->data.setPassword(clientPassword);
            cout<<"Enter Address"<<endl;
            cin >>clientAddress;
            newNode->data.setAddress(clientAddress);

            C[ids%10]=head[ids%10]=tail[ids%10]=newNode;
            
            listSize[ids%10]++;
            return ;
        }
        
        cout<<"Enter E-Mail"<<endl;
        cin >> clientEmail;
        newNode->data.setEmail(clientEmail);
        for(int i=0;i<10;i++){
            LinkedListNode<T>* here = C[i];
            while(here != nullptr
            ){
                if(here->data.getEmail() == newNode->data.getEmail()){
                        cout<<"Employee already exists"<<endl;
                        delete newNode;
                        return ;
                    }
                here=here->next;
            }
        }

        cout<<"Enter Full Name"<<endl;
        cin >>clientName;
        newNode->data.setName(clientName);
        cout<<"Enter Phone Number"<<endl;
        cin >>clientPhone;
        newNode->data.setPhone(clientPhone);
        cout<<"Enter Password"<<endl;
        cin >>clientPassword;
        newNode->data.setPassword(clientPassword);
        cout<<"Enter Address"<<endl;
        cin >>clientAddress;
        newNode->data.setAddress(clientAddress);
        
        
        tail[ids%10]->next=newNode;
        tail[ids%10]=tail[ids%10]->next;

        listSize[ids%10]++;
        return;
    }

    void display()
    {
        for(int i=0;i<10;i++){
            cout<<"inedex #"<<i+1<<": Linked List of "<<listSize[i]<<" Clients."<<endl;
            LinkedListNode<T>* temp=C[i];
            while(temp!=nullptr){
                temp->data.printClientInfo();
                temp=temp->next;
            }
            cout<<endl;
        }
        return;
    }

    int Partition(int arr[], int s, int e)
    {
        int pivot = arr[e];
        int pIndex = s;         int CPIndex = s;
        
        for(int i = s;i<e;i++){
            if(arr[i]<pivot){
                int temp = arr[i];      LinkedListNode<T>* tmp = C[i];
                arr[i] = arr[pIndex];   C[i]=C[CPIndex];
                arr[pIndex] = temp;     C[CPIndex] = tmp;
                pIndex++;               CPIndex ++;
            }
        }

        int temp = arr[e];      LinkedListNode<T>* tmp = C[e];
        arr[e] = arr[pIndex];   C[e] = C[CPIndex];
        arr[pIndex] = temp;     C[CPIndex]=tmp;
        
        return pIndex;
    }
        
    void QuickSort(int arr[],int s, int e)
    {
        if(s<e){
            int p = Partition(arr,s, e);
            QuickSort(arr,s, (p-1));  
            QuickSort(arr,(p+1), e);  
        }
    }

    void QSort()
    {
        for(int i=0;i<10;i++){
            listSize[i]=0;
            LinkedListNode<T>* here = C[i];
            while(here != nullptr){
                listSize[i]++;
                here=here->next;
            }
        }
        
        QuickSort(listSize,0,9);
        display();
    }  

    void loginMenu(string CE,string CP)
    {
        cout<<"\t\t\t\t\"Welcome back dear client\t\t\t\t"<<endl;
        cout<<"Please write your E-Mail"<<endl;
        cin >> CE;
        cout<<"Please write your password"<<endl;
        cin >> CP;
        for(int i=0;i<10;i++){
            LinkedListNode<T>* here = C[i];
            while(here != nullptr
            ){
                if(here->data.getEmail() == CE && here->data.getPassword() == CP){
                    clientHome(here->data);
                    return;
                }
                here=here->next;
            }
        }
        cout<<"Employee dosen't Exist, Please Enter Valid  Email or Password"<<endl;
            return;
    }

    void clientHome(Client CC)
    {
        int x;
        
        while(1)
        {
            clientHomeMSG();
            cin>>x;
            
            switch(x)
            {
                case 1:
                    transactionsMenu(CC);
                    break;

                case 2:
                {
                    cout<<"Client info:"<<endl;
                    CC.printClientInfo();
                }
                    break;

                case 3:
                    return;

                default:
                {   
                    cout<<"Enter Valid option"<<endl;
                    break;
                }
            }
        }   
    }
    
    void transactionsMenu(Client CC)
    {
        int x;
        
        while(1)
        {
            Transaction t;
            int tID;            //transaction ID
            string tN;          //transaction Name
            string tD;          //transaction Date
            int Cflag = 1;      //flag of create
            int Dflag = 1;      //flag of delete
            transactionsMenuMSG();
            
            cin>>x;

            switch(x)
            {
                case 1:
                {
                    cout<<"Enter ID: ";
                    cin>>tID;
                    
                    for(int i=0 ; i<5 ; i++){
                        if(CC.getTransaction(i).getTransactionID()==tID){
                            cout<<"ID already Exist"<<endl;
                            Cflag = 0;
                            break;
                        }
                    }

                    if(Cflag){
                        t.setTransactionID(tID);
                        cout<<"Enter Name: ";
                        cin>>tN;
                        t.setTransactionName(tN);
                        cout<<"Enter Date: ";
                        cin>>tD;
                        t.setTransactionDate(tD);
                        CC.setTransaction(t,CC.get_TC()%5);
                    }

                    
                }
                break;

                case 2:
                {   
                    if(CC.get_TC()==0){
                        cout << "No transactions have been made yet"<<endl;
                        break;
                    }

                    for(int i=0; i<5 ; i++){
                        if(CC.getTransaction(i).getTransactionID() == -1)
                            break;
                        CC.getTransaction(i).printTransaction();
                        cout<<endl;
                    }
                }
                break;

                case 3:
                {
                    if(CC.get_TC()==0){
                        cout << "No transactions exist to be deleted"<<endl;
                        break;
                    }

                    int TID;
                    cout<<"Enter ID: ";
                    cin >> TID;
                    for(int i=0; i<5 ; i++){
                        if(CC.getTransaction(i).getTransactionID() == TID){
                            Transaction td;
                            Cflag = 0;
                            CC.setTransaction(td,i);
                            break;
                        }
                    }

                    if(Cflag)
                        cout<<"ID not available"<<endl;
                }
                break;
                
                case 4:
                    return;

                default:
                {   
                    cout<<"Enter Valid option"<<endl;
                    break;
                }
            }
        }
    }
    
    void forgetPassword(string CE)
    {
            cout<<"Please write your E-Mail: "<<endl;
            cin >> CE;
            for(int i=0;i<10;i++){
                LinkedListNode<T>* here = C[i];
                while(here != nullptr
                ){
                    if(here->data.getEmail() == CE){
                        cout<<"Your Password is: "<<here->data.getPassword();
                        return;
                    }       
                    here=here->next;
                }
            }
            cout<<"Employee dosen't Exist, Please Enter Valid Email"<<endl;
            return;     
    }

    void BubbleSort(int i) {  
        LinkedListNode<T> *current = head[i], *index = nullptr;  
        Client temp;

        if(head[i] == nullptr) {  
            return;  
        }  
 
        while(current != nullptr) {  

            index = current->next;  
 
            while(index != nullptr) {  

                if(current->data.getID() > index->data.getID()) {  
                    temp = current->data;  
                    current->data = index->data;  
                    index->data = temp;  
                }  
                index = index->next;  
            }  
            current = current->next;  
        }      
    }

    void Bsort(){

        for(int i=0 ; i<10; i++)
            BubbleSort(i);
        display();
    }
};


int main(){
    ClientsLinkedList<Client>ll;
    int empty = 1;
    int option=0;
    while(option!=6)
    {
        mainMenu();
        Client client;
            cin>>option;
            switch (option)
            {
                case 1:
                {
                    if(empty){
                        cout<<"No Client Exist yet"<<endl;
                        break;
                    }
                    string email;
                    string password;
                    ll.loginMenu(email,password);
                }
                    break;
                    
                case 2:
                {
                    ll.newClientMenu(client);
                    empty = 0;
                }
                break;
                
                case 3:
                {
                    if(empty){
                        cout<<"No Client Exist yet"<<endl;
                        break;
                    }
                    string email;
                    ll.forgetPassword(email);
                }
                break;
                
                case 4:
                {
                    if(empty){
                        cout<<"No Client Exist yet"<<endl;
                        break;
                    }
                    ll.QSort();
                    
                }
                break;
                
                case 5:
                {
                    if(empty){
                        cout<<"No Client Exist yet"<<endl;
                        break;
                    }
                    ll.Bsort();
                }
                break;

                case 6:
                {
                    cout<<"Program Closed"<<endl;
                }
                break;

                default:
                {   
                    cout<<"Enter Valid option"<<endl;
                    break;
                }
            }
        
    }
    return 0;
}

void mainMenu()
{

        cout<<"==============================================="<<endl;

        cout<<"********* Welcome to the Banking System *********"<<endl;

        cout<<" CHOOSE ONE OF THE FOLLOWING OPTIONS"<<endl;
        cout<<" 1. login to your account"<<endl;
        cout<<" 2. New Client?"<<endl;
        cout<<" 3. forgot your password?"<<endl;
        cout<<" 4. Sort clients by linked list using the quick sort Algorithm"<<endl;
        cout<<" 5. Sort each linked list by the id of the clients"<<endl;
        cout<<" 6. Exit the program"<<endl;
        cout<<"==============================================="<<endl;
        cout<<" Enter your option please : ";

}

void clientHomeMSG(){
    cout<<"==============================================="<<endl;
    cout<<"******** Welcome to the Banking System ********"<<endl;
    cout<<"******** Welcome to the home page ********"<<endl;
    cout<<" CHOOSE ONE OF THE FOLLOWING OPTIONS : "<<endl;
    cout<<" 1. Transaction menu"<<endl;
    cout<<" 2. View personal info"<<endl;
    cout<<" 3. Logout"<<endl;
    cout<<"==============================================="<<endl;
    cout<<" Enter your option please : ";
}

void transactionsMenuMSG(){
    cout<<"==============================================="<<endl;
    cout<<"******** Welcome to the Banking System ********"<<endl;
    cout<<"******** Welcome to the transactions system ********"<<endl;
    cout<<" CHOOSE ONE OF THE FOLLOWING OPTIONS : "<<endl;
    cout<<" 1. Create a new transaction"<<endl;
    cout<<" 2. View your transactions"<<endl;
    cout<<" 3. Delete a transaction by its ID"<<endl;
    cout<<" 4. Return to Home Page"<<endl;
    cout<<"==============================================="<<endl;
    cout<<" Enter your option please : ";
}

int generateID(){
    static bool initialized = false;
    if (!initialized)
    {
        srand(time(0));
        initialized = true;
    }
    return rand();
}
