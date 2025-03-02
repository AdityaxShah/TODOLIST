#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class ToDoList {
private:
    string filename;
public:
    ToDoList(string file) : filename(file) {}
    void addTask();
    void viewTasks();
    void deleteTask();
};

void ToDoList::addTask() {
    ofstream file(filename, ios::app);
    if (!file) {
        cout << "Error opening file!" << endl;
        return;
    }
    string task;
    cout << "Enter task: ";
    getline(cin, task);
    file << task << endl;
    file.close();
    cout << "Task added successfully!" << endl;
}

void ToDoList::viewTasks() {
    ifstream file(filename);
    if (!file) {
        cout << "No tasks found." << endl;
        return;
    }
    string task;
    int count = 1;
    while (getline(file, task)) {
        cout << count++ << ". " << task << endl;
    }
    file.close();
}

void ToDoList::deleteTask() {
    ifstream file(filename);
    if (!file) {
        cout << "No tasks to delete." << endl;
        return;
    }
    vector<string> tasks;
    string task;
    while (getline(file, task)) {
        tasks.push_back(task);
    }
    file.close();
    if (tasks.empty()) {
        cout << "No tasks available." << endl;
        return;
    }
    int taskNum;
    cout << "Enter task number to delete: ";
    cin >> taskNum;
    cin.ignore();
    if (taskNum < 1 || taskNum > tasks.size()) {
        cout << "Invalid task number!" << endl;
        return;
    }
    ofstream outFile(filename);
    for (size_t i = 0; i < tasks.size(); i++) {
        if (i != taskNum - 1) {
            outFile << tasks[i] << endl;
        }
    }
    outFile.close();
    cout << "Task deleted successfully!" << endl;
}

int main() {
    ToDoList todo("tasks.txt");
    int choice;
    while (true) {
        cout << "\nTo-Do List" << endl;
        cout << "1. Add Task" << endl;
        cout << "2. View Tasks" << endl;
        cout << "3. Delete Task" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();
        switch (choice) {
            case 1:
                todo.addTask();
                break;
            case 2:
                todo.viewTasks();
                break;
            case 3:
                todo.deleteTask();
                break;
            case 4:
                exit(0);
            default:
                cout << "Invalid choice! Try again." << endl;
        }
    }
    return 0;
}
