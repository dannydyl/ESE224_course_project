#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <filesystem>


using namespace std;


class Node{
    int filenumber;
    string line;
    string time;
    string remark;
    Node* next;
    Node* prev;
   
    friend class LinkedList;
};

class Node2{
    int filenumber2;
    string startdate;
    string enddate;
    string substationName;
    string hospitalName;
    string surgeryTeam;
    string surgeryType;
    string surgeryTimeString;
    string difficultyLevelString;
    int surgeryTime;
    int difficultyLevel;
    Node2* next;
    Node2* prev;
   
    friend class LinkedList2;
};

class LinkedList{
public:
    LinkedList();
    ~LinkedList();
    bool empty()const;
    void addnode(string& line_, string& time_, string& remark_);
    void remove(int filn);
    void removefront();
    void displayall();
    void displaybysub(string& sub); // only display tickets of input substation
    void frequentword(string& word);
    string& returntime(int i);


   
private:
    Node* head;
    Node* tail;
    int n=0;
};

class LinkedList2{
public:
    LinkedList2();
    ~LinkedList2();
    bool empty()const;
    void addnode(string& start, string& end, string& subs, string& hosname, string& surname, string& surtype, int& surtime, int& dlevel);
    void addnewsurgeon(int filn, string& newsur);
    void remove(int filn);
    void removesur(int filn, string& surname);
    void removefront();
    void displayall();
    void displaybysub(string& sub); // only display tickets of input substation
    float displaysurgeryperformed(string& surname); // average difficulty level
    float difficultlevelaveragebyhospital();
    void displayavebysub();
    string teamwithhighestdifficultylevel();
    float averageSurgeryTime(string& surname);
    string highestdlevelteaminEB();
    string highestdlevelteaminOF();
    string highestdlevelteaminRL();
    string highestdlevelteaminTM();
    string highestdlevelteaminHD();
    int countnumofeachdlevel(int i);
    int numofsurperhour();
    int numofsurinhos(string& hosname);
   
   
private:
    Node2* head;
    Node2* tail;
    int n=0;
};

LinkedList2::LinkedList2(){
    head = new Node2;
    tail = new Node2;
   
    head -> next = tail;
    tail -> prev = head;
   
    head -> prev = NULL;
    tail -> next = NULL;
}

LinkedList2::~LinkedList2(){
    while(!empty()) removefront();
}

bool LinkedList2::empty()const{
    return (head->next == tail);
}

LinkedList::LinkedList(){
    head = new Node;
    tail = new Node;
   
    head -> next = tail;
    tail -> prev = head;
   
    head -> prev = NULL;
    tail -> next = NULL;
}

LinkedList::~LinkedList(){
    while(!empty()) removefront();
}

bool LinkedList::empty()const{
    return (head->next == tail);
}

void LinkedList::addnode(string &line_, string &time_, string &remark_){
    Node* NewNode = new Node;
    n++;
   
    NewNode -> filenumber = n;
    NewNode -> line = line_;
    NewNode -> time = time_;
    NewNode -> remark = remark_;
   
    if(head -> next == tail){
        NewNode -> next = tail;
        NewNode -> prev = head;
        tail -> prev = NewNode;
        head -> next = NewNode;
       
    }
    else{
        NewNode -> prev = head;
        NewNode -> next = head -> next;
        head -> next -> prev = NewNode;
        head -> next = NewNode;
    }
   
}

void LinkedList2::addnode(string& start, string& end, string& subs, string& hosname, string& surname, string& surtype, int& surtime, int& dlevel){
    Node2* NewNode = new Node2;
    n++;
   
    NewNode -> filenumber2 = n;
    NewNode -> startdate = start;
    NewNode -> enddate = end;
    NewNode -> substationName = subs;
    NewNode -> hospitalName = hosname;
    NewNode -> surgeryTeam = surname;
    NewNode -> surgeryType = surtype;
    NewNode -> surgeryTime = surtime;
    NewNode -> difficultyLevel = dlevel;
   
   
    if(head -> next == tail){
        NewNode -> next = tail;
        NewNode -> prev = head;
        tail -> prev = NewNode;
        head -> next = NewNode;
       
    }
    else{
        NewNode -> prev = head; // adding to the front
        NewNode -> next = head -> next;
        head -> next -> prev = NewNode;
        head -> next = NewNode;
    }
   
}

void LinkedList2::addnewsurgeon(int filn, string& newsur){
    Node2* cur = head -> next;
   
    while(cur != tail){
        if(cur ->filenumber2 == filn){
            cur -> surgeryTeam += ',' + newsur;
           
        }
       
        cur = cur->next;
    }
}
void LinkedList::remove(int filn){
   
    Node* cur = head -> next;
   
    if(cur->filenumber == filn){
        cur -> next -> prev = cur -> prev;
        cur -> prev -> next = cur -> next;
       
        delete cur;
    }
    else{
        cur = cur -> next;
    }
   
}

void LinkedList2::remove(int filn){
   
    Node2* cur = head -> next;
   
    if(cur->filenumber2 == filn){
        cur -> next -> prev = cur -> prev;
        cur -> prev -> next = cur -> next;
       
        delete cur;
    }
    else{
        cur = cur -> next;
    }
   
}

void LinkedList2::removesur(int filn, string& surname){
    Node2* cur = head -> next;
   
    while(cur != tail) {
        if(cur -> filenumber2 == filn){
            size_t pos = cur->surgeryTeam.find(surname);
           
            if(pos != string::npos){
                cur->surgeryTeam.erase(pos, surname.length());
            }
        }
       
        cur = cur->next;
    }
}

void LinkedList::removefront(){
    Node* cur = head -> next;
   
    head -> next = cur -> next;
    cur -> next -> prev = head;
   
    delete cur;
}

void LinkedList2::removefront(){
    Node2* cur = head -> next;
   
    head -> next = cur -> next;
    cur -> next -> prev = head;
   
    delete cur;
}


int LinkedList2::countnumofeachdlevel(int i){
    Node2* cur = head -> next;
    int count=0;
    while(cur != tail){
        if(cur -> difficultyLevel == i){
            count++;
        }
        cur = cur -> next;
    }


    return count;
}


int LinkedList2::numofsurperhour(){
    Node2* cur = head -> next;
    int count = 0;
    while(cur != tail){
        if(cur->surgeryTime > 60){
            count ++;
        }
        cur = cur -> next;
    }
    return count;


}


int LinkedList2::numofsurinhos(string& hosname){
    Node2* cur = head -> next;
    int count = 0;
    while(cur != tail){
        if(cur -> hospitalName == hosname){
            count++;
        }
        cur = cur -> next;
    }
    return count;
}


void LinkedList::displayall(){
    Node* cur = head -> next;
   
    while(cur != tail){
        cout << "Line: " << cur->filenumber << ' ';
        cout << "Time: " << cur->time << ' ';
        cout << "Remark: " << cur->remark << endl;
       
        cur = cur->next;
    }
}
void LinkedList2::displayall(){
    Node2* cur = head -> next;
   
    while(cur != tail){
        cout << "Start date: " << cur->startdate << ' ';
        cout << "End date: " << cur->enddate << ' ';
        cout << "Substation Name: " << cur -> substationName << ' ';
        cout << "Hospital Name: " << cur -> hospitalName << ' ';
        cout << "Surgery Team Name: " << cur -> surgeryTeam << ' ';
        cout << "Surgery Time: " << cur -> surgeryTime << ' ';
        cout << "Difficulty Level: " << cur -> difficultyLevel << endl;
       
        cur = cur-> next;
    }
}
void LinkedList::displaybysub(string& sub){ //
    Node* cur = head -> next;
    string substation;
   
    while(cur != tail){
        if(cur->remark.substr(0,2) == sub){
            cout << "Line: " << cur->filenumber << ' ';
            cout << "Time: " << cur->time << ' ';
            cout << "Remark: " << cur->remark << endl;
        }
       
        cur = cur->next;
    }
   
   
       
}


float LinkedList2::averageSurgeryTime(string& surname){
    Node2* cur = head->next;
    int sumtime = 0;
    int count = 0;


    while(cur != tail){
        if(cur->surgeryTeam == surname){
            sumtime += cur->surgeryTime;
            count++;
        }




        cur = cur->next;
    }


    float average = sumtime / count;


    return average;
}


string& LinkedList2::teamwithhighestdifficultylevel(){ // returns a name of a team who has highest average difficulty level
    Node2* cur = head -> next;
    string team1;
    int dlevel=0;
    int count =0;
    team1 = cur->surgeryTeam;
    cur = cur->next;
    while(cur != tail){
        if(cur-> surgeryTeam == team1){
            dlevel += cur->difficultyLevel;
            count++;
        }
       




        cur = cur -> next;
    }
    

}


string& LinkedList::returntime(int i){
    Node* cur = head->next;
    for(int j=0;j<i;j++){
        cur = cur -> next;
    }
    return cur->time;
}


string LinkedList2::highestdlevelteaminEB(){
    Node2* cur = head -> next;
    int levelfort11 = 0;
    int levelfort12 = 0;
    int levelfort13 = 0;
    int levelfort14 = 0;
    int levelfort15 = 0;
    int count = 15;


    while(cur != tail){
        if(cur -> substationName == "EB"){
            if(cur -> surgeryTeam == "T11"){
                levelfort11 += cur -> difficultyLevel;


            }
            if(cur -> surgeryTeam == "T12"){
                levelfort12 += cur -> difficultyLevel;
            }
            if(cur -> surgeryTeam == "T13"){
                levelfort13 += cur -> difficultyLevel;
            }
            if(cur -> surgeryTeam == "T14"){
                levelfort14 += cur -> difficultyLevel;
            }
            if(cur -> surgeryTeam == "T15"){
                levelfort15 += cur -> difficultyLevel;
            }


        }


        cur = cur -> next;
    }


    int highest = levelfort11;


    if(levelfort12 > highest){
        highest = levelfort12;
    }
    if(levelfort13 > highest){
        highest = levelfort13;
    }
    if(levelfort14 > highest){
        highest = levelfort14;
    }
    if(levelfort15 > highest){
        highest = levelfort15;
    }


    if(highest == levelfort11){
        return "T11";
    }
    if(highest == levelfort12){
        return "T12";
    }
    if(highest == levelfort13){
        return "T13";
    }
    if(highest == levelfort14){
        return "T14";
    }
    if(highest == levelfort15){
        return "T15";
    }


}


string LinkedList2::highestdlevelteaminOF(){
    Node2* cur = head -> next;
    int levelfort21 = 0;
    int levelfort22 = 0;
    int levelfort23 = 0;
    int levelfort24 = 0;
    int levelfort25 = 0;
    int count = 15;


    while(cur != tail){
        if(cur -> substationName == "OF"){
            if(cur -> surgeryTeam == "T21"){
                levelfort21 += cur -> difficultyLevel;
            }
            if(cur -> surgeryTeam == "T22"){
                levelfort22 += cur -> difficultyLevel;
            }
            if(cur -> surgeryTeam == "T23"){
                levelfort23 += cur -> difficultyLevel;
            }
            if(cur -> surgeryTeam == "T24"){
                levelfort24 += cur -> difficultyLevel;
            }
            if(cur -> surgeryTeam == "T25"){
                levelfort25 += cur -> difficultyLevel;
            }


        }


        cur = cur -> next;
    }


    int highest = levelfort21;


    if(levelfort22 > highest){
        highest = levelfort22;
    }
    if(levelfort23 > highest){
        highest = levelfort23;
    }
    if(levelfort24 > highest){
        highest = levelfort24;
    }
    if(levelfort25 > highest){
        highest = levelfort25;
    }


    if(highest == levelfort21){
        return "T21";
    }
    if(highest == levelfort22){
        return "T22";
    }
    if(highest == levelfort23){
        return "T23";
    }
    if(highest == levelfort24){
        return "T24";
    }
    if(highest == levelfort25){
        return "T25";
    }
}


string LinkedList2::highestdlevelteaminRL(){
    Node2* cur = head -> next;
    int levelfort31 = 0;
    int levelfort32 = 0;
    int levelfort33 = 0;
    int levelfort34 = 0;
    int levelfort35 = 0;
    int count = 15;


    while(cur != tail){
        if(cur -> substationName == "RL"){
            if(cur -> surgeryTeam == "T31"){
                levelfort31 += cur -> difficultyLevel;
            }
            if(cur -> surgeryTeam == "T32"){
                levelfort32 += cur -> difficultyLevel;
            }
            if(cur -> surgeryTeam == "T33"){
                levelfort33 += cur -> difficultyLevel;
            }
            if(cur -> surgeryTeam == "T34"){
                levelfort34 += cur -> difficultyLevel;
            }
            if(cur -> surgeryTeam == "T35"){
                levelfort35 += cur -> difficultyLevel;
            }


        }


        cur = cur -> next;
    }


    int highest = levelfort31;


    if(levelfort32 > highest){
        highest = levelfort32;
    }
    if(levelfort33 > highest){
        highest = levelfort33;
    }
    if(levelfort34 > highest){
        highest = levelfort34;
    }
    if(levelfor35 > highest){
        highest = levelfort35;
    }


    if(highest == levelfort31){
        return "T31";
    }
    if(highest == levelfort32){
        return "T32";
    }
    if(highest == levelfort33){
        return "T33";
    }
    if(highest == levelfort34){
        return "T34";
    }
    if(highest == levelfort35){
        return "T35";
    }
}


string LinkedList2::highestdlevelteaminTM(){
    Node2* cur = head -> next;
    int levelfort41 = 0;
    int levelfort42 = 0;
    int levelfort43 = 0;
    int levelfort44 = 0;
    int levelfort45 = 0;
    int count = 15;


    while(cur != tail){
        if(cur -> substationName == "TM"){
            if(cur -> surgeryTeam == "T41"){
                levelfort41 += cur -> difficultyLevel;
            }
            if(cur -> surgeryTeam == "T42"){
                levelfort42 += cur -> difficultyLevel;
            }
            if(cur -> surgeryTeam == "T43"){
                levelfort43 += cur -> difficultyLevel;
            }
            if(cur -> surgeryTeam == "T44"){
                levelfort44 += cur -> difficultyLevel;
            }
            if(cur -> surgeryTeam == "T45"){
                levelfort45 += cur -> difficultyLevel;
            }


        }


        cur = cur -> next;
    }


    int highest = levelfort41;


    if(levelfort42 > highest){
        highest = levelfort42;
    }
    if(levelfort43 > highest){
        highest = levelfort43;
    }
    if(levelfort44 > highest){
        highest = levelfort44;
    }
    if(levelfort45 > highest){
        highest = levelfort45;
    }


    if(highest == levelfort41){
        return "T41";
    }
    if(highest == levelfort42){
        return "T42";
    }
    if(highest == levelfort43){
        return "T43";
    }
    if(highest == levelfort44){
        return "T44";
    }
    if(highest == levelfort45){
        return "T45";
    }
}


string LinkedList2::highestdlevelteaminHD(){
    Node2* cur = head -> next;
    int levelfort51 = 0;
    int levelfort52 = 0;
    int levelfort53 = 0;
    int levelfort54 = 0;
    int levelfort55 = 0;
    int count = 15;


    while(cur != tail){
        if(cur -> substationName == "HD"){
            if(cur -> surgeryTeam == "T51"){
                levelfort51 += cur -> difficultyLevel;
            }
            if(cur -> surgeryTeam == "T52"){
                levelfort52 += cur -> difficultyLevel;
            }
            if(cur -> surgeryTeam == "T53"){
                levelfort53 += cur -> difficultyLevel;
            }
            if(cur -> surgeryTeam == "T54"){
                levelfort54 += cur -> difficultyLevel;
            }
            if(cur -> surgeryTeam == "T55"){
                levelfort55 += cur -> difficultyLevel;
            }


        }


        cur = cur -> next;
    }


    int highest = levelfort51;


    if(levelfort52 > highest){
        highest = levelfort52;
    }
    if(levelfort53 > highest){
        highest = levelfort53;
    }
    if(levelfort54 > highest){
        highest = levelfort54;
    }
    if(levelfort55 > highest){
        highest = levelfort55;
    }


    if(highest == levelfort51){
        return "T51";
    }
    if(highest == levelfort52){
        return "T52";
    }
    if(highest == levelfort53){
        return "T53";
    }
    if(highest == levelfort54){
        return "T54";
    }
    if(highest == levelfort55){
        return "T55";
    }
}


float LinkedList2::displaysurgeryperformed(string& surname){ // returns the average of difficulty level by input surgery team
    Node2* cur = head -> next;
    Node2* cur2;
    Node2* cur3;
    float dlevelaverage = 0, average1;
    int count=0;
   
       
    while(cur != tail){
        if(cur -> surgeryTeam == surname){
            dlevelaverage += cur -> difficultyLevel;
            count++;
        }


        cur = cur -> next;
    }


    return dlevelaverage;




        // for(cur= head->next; cur == tail;cur = cur -> next){
        //     for(cur2 = head->next; cur2 == tail;cur2 = cur2->next){
        //         if(cur2->surgeryTeam == cur->surgeryTeam){
        //             if(cur2->filenumber2 != cur-> filenumber2){
        //                 count++;
        //                 dlevelaverage += cur2->difficultyLevel;
        //             }
                   
        //         }
        //     }
        //     average1 = dlevelaverage/count;
        //     cout << "Average difficulty level of " << cur->surgeryTeam << " is " << average1;
           
        // }
   
}




float LinkedList2::displayavebysub(){ // find the highest difficulty level average
    Node2* cur = head->next;
   
    float EB=0,OF=0,RL=0,TM=0,HD=0;
    int eb=0,of=0,rl=0,tm=0,hd=0;
   
    while(cur != tail){
        if(cur->substationName == "EB"){
            EB += cur->difficultyLevel;
            eb++;
        }
        if(cur->substationName == "OF"){
            OF += cur->difficultyLevel;
            of++;
        }
        if(cur->substationName == "RL"){
            RL += cur->difficultyLevel;
            rl++;
        }
        if(cur->substationName == "TM"){
            TM += cur->difficultyLevel;
            tm++;
        }
        if(cur->substationName == "HD"){
            HD += cur->difficultyLevel;
            hd++;
        }
        cur = cur->next;
    }
   
    cout << "EB substation average difficulty level: " << EB/eb << endl;
    cout << "OF substation average difficulty level: " << OF/of << endl;
    cout << "RL substation average difficulty level: " << RL/rl << endl;
    cout << "TM substation average difficulty level: " << TM/tm << endl;
    cout << "HD substation average difficulty level: " << HD/hd << endl;


    //find a highest


    float highest = EB/eb;


    if(OF/of > highest){
        highest = OF/of;
    }
    if(RL/rl > highest){
        highest = RL/rl;
    }
    if(TM/tm > highest){
        highest = TM/tm;
    }
    if(HD/hd > highest){
        highest = HD/hd;
    }


    return highest;
}
void LinkedList::frequentword(string &word){
    Node* cur = head -> next;
    int num=0;
   
    while(cur != tail){
        if(cur->remark.find(word)){
            num++;
        }
       
        cur = cur->next;
    }
   
    cout << "The word: " << word << " is found " << num << "times in all the tickets" << endl;
}
int main(){
    //get all csv file from folder
    //this might only work for C++ above 17 version
    //to change the C++ version in Visual Studio go to - under project > Properties > C/C++ > Language > C++ Language Standard
    //change it to the C++17 and apply change.
    string filePath;
    vector<string> allTicketFiles;
    //path to the folder where all csv tickets files are stored(make sure you only have csv files)
    string path = "/Users/dongyunlee/Desktop/SBU 2023 Spring/ESE224LAB/Course Project/tickets";
   
    LinkedList ticketList;
   
    for (const auto& entry : filesystem::directory_iterator(path)) {
        filePath = entry.path().string();
        cout << filePath << std::endl;
        allTicketFiles.push_back(filePath);//store all files in this vector
    }
    //loop through all the files and extarct the content of each file
    for (int i = 0; i < allTicketFiles.size(); i++) {
        ifstream inFile;
        string filePath = allTicketFiles.at(i);
        //need to handle first 3 lines differently
        int header;//to indentify 1st line
        int secondLine;//to indentify 2nd line
        int thirdLine;//to identify 3rd line
        string line;
        string time;
        string remark;
        string address;
        string address1;
        string fullAddress;//to store full address
        string status;//to store 3rd line
        string word;
        vector<string> Line;
        vector<string> Time;
        vector<string> Remark;
        inFile.open(filePath);
        if (inFile.is_open()) {
            cout << endl << endl << "File Number: " << i << endl;
            cout << "Reading: " << filePath<< " File" << endl;
        }
        else {
            cout << "Failed to open: " << filePath << endl;
        }
        header = 1;
        secondLine = 1;
        thirdLine = 1;
        while (!inFile.eof()) {
            if (header == 1) {
                getline(inFile, line, ',');
                getline(inFile, time, ',');
                getline(inFile, remark, ',');
                header = 0;
            }
            else if (secondLine == 1) {
                secondLine = 0;
                //get the content of 2nd line
                getline(inFile, line, ',');
                getline(inFile, time, ',');
                getline(inFile, remark, ',');
                getline(inFile, address, ',');
                getline(inFile, address1, ',');
                fullAddress = address + address1;
            }
            else if (thirdLine == 1) {
                getline(inFile, status);//you can store this status value in database
                cout << "3rd line is: " << status<< endl;
                thirdLine = 0;
            }
            else {//other remaining lines
                while (getline(inFile, word)) {//this loop will continue till end of the line
                    stringstream str(word);
                    getline(str, line, ',');
                    getline(str, time, ',');
                    getline(str, remark, ',');
                    Line.push_back(line);//store line number
                    Time.push_back(time);//store time
                    Remark.push_back(remark);//store comment
                }
                cout << "Total comments are : " << line << endl;
            }
        }
        for (int i = 0; i < Line.size(); i++) {
            cout << "Line: " << Line.at(i) << ' ';
            cout << "Time: " << Time.at(i) << ' ';
            cout << "Remark: " << Remark.at(i) << endl;
            ticketList.addnode(Line.at(i), Time.at(i), Remark.at(i));
        }
        inFile.close();
        //system("pause");
    }
     
    // opening hospital file


    string filepath2;
    string path2 = "/Users/dongyunlee/Desktop/SBU 2023 Spring/ESE224LAB/Course Project";
   
    ifstream inFile2;
    if(inFile2.is_open()){
        cout << endl << "Hospital file is open" << endl;
    }
    else{
        cout << "Failed to open hospital file" << endl;
    }
   
    LinkedList2 hospitalList;
   
    string line2;
    string startdate;
    string enddate;
    string substationName;
    string hospitalName;
    string surgeryTeam;
    string surgeryType;
    string surgeryTimeString;
    string difficultyLevelString;
    int surgeryTime;
    int difficultyLevel;
    string word2;
   
    vector<string> Line2;
    vector<string> StartDate;
    vector<string> EndDate;
    vector<string> SubstationName;
    vector<string> HospitalName;
    vector<string> SurgeryTeam;
    vector<string> SurgeryType;
    vector<int> SurgeryTime;
    vector<int> DifficultyLevel;
   
    while(!inFile2.eof()){
        getline(inFile2, word2);
        stringstream str2(word2);
        getline(str2, line2, ',');
        getline(str2, startdate, ',');
        getline(str2, enddate, ',');
        getline(str2, substationName, ',');
        getline(str2, hospitalName, ',');
        getline(str2, surgeryTeam, ',');
        getline(str2, surgeryType, ',');
        getline(str2, surgeryTimeString, ',');
        getline(str2, difficultyLevelString, ',');
       
        surgeryTime = stoi(surgeryTimeString);
        difficultyLevel = stoi(difficultyLevelString);
       
        Line2.push_back(line2);
        StartDate.push_back(startdate);
        EndDate.push_back(enddate);
        SubstationName.push_back(substationName);
        HospitalName.push_back(hospitalName);
        SurgeryTeam.push_back(surgeryTeam);
        surgeryType.push_back(surgeryType);
        SurgeryTime.push_back(surgeryTime);
        DifficultyLevel.push_back(difficultyLevel);
       
        inFile2.close();
       
       
       
       
    }
   
    for(int i=0;i<Line2.size();i++){
        hospitalList.addnode(StartDate.at(i), EndDate.at(i), SubstationName.at(i), HospitalName.at(i), SurgeryTeam.at(i), , SurgeryType.at(i), SurgeryTime.at(i), DifficultyLevel.at(i));
    }
   
   
    int CAP = 100; // for instant CAP has 100 capacity


    string s, H;


    for (all surgeries s at hospital H) {
        int N1 = hospitalList.countnumofeachdlevel(3);
        int N2 = hospitalList.numofsurperhour();
    }
    int N = hospitalList.numofsurinhos("EB");


    int expectedsur = N1 / N * N2;






    while (CAP > 0) {
    for (each hour of the estimated length of the power outage) {
        for (each surgery that is expected to occur, in the order of
            their expected number and complexity) {
            string team = hospitalList.highestdlevelteaminEB();
            in handling that surgery type, such as the team that
            has required least amount of time for that type of
            surgeries;
            assign team x to perform the surgery;
            CAP = CAP - 20;
            estimate the time moment when team x will finish the
            assigned surgery;
            }
        }
    }


    int TOT;

    while (there are unrepaired power outages){
        while (TOT > 0) {
                for (each unrepaired substation s in the decreasing order of their number of
                 customer hours) {
                use previous tickets for the same kind of outage type to
                estimate the number N of crew that should be sent to repair
                the outage at substation s;
                            assign N crews to repair the power outage;
                            TOT = TOT – N;
                            compute when the assigned crews are available again because they finished their
                 assigned job;
                }
        }
    }

   
   
   
    return 0;
}











