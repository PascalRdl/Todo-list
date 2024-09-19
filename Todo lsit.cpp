#include <iostream>
#include <vector>
#include <string>
#include <fstream>  // For file I/O

void showMenu();
void addTask(std::vector<std::string>& tasks);
void viewTasks(const std::vector<std::string>& tasks);
void deleteTask(std::vector<std::string>& tasks);
void saveTasks(const std::vector<std::string>& tasks);
void loadTasks(std::vector<std::string>& tasks);

int main() {
    std::vector<std::string> tasks;

    // Load tasks from the file when the program starts
    loadTasks(tasks);

    int choice;

    do {
        showMenu();
        std::cin >> choice;
        std::cin.ignore(); // To consume newline character after entering choice

        switch (choice) {
        case 1:
            addTask(tasks);
            break;
        case 2:
            viewTasks(tasks);
            break;
        case 3:
            deleteTask(tasks);
            break;
        case 4:
            std::cout << "Exiting and saving tasks...\n";
            saveTasks(tasks);  // Save tasks to file when exiting
            break;
        default:
            std::cout << "Invalid option, please try again.\n";
        }
    } while (choice != 4);

    return 0;
}

void showMenu() {
    std::cout << "\nTo-Do List Menu:\n";
    std::cout << "1. Add Task\n";
    std::cout << "2. View Tasks\n";
    std::cout << "3. Delete Task\n";
    std::cout << "4. Exit\n";
    std::cout << "Choose an Option: ";
}

void addTask(std::vector<std::string>& tasks) {
    std::string task;
    std::cout << "Enter the task: ";
    std::getline(std::cin, task);
    tasks.push_back(task);  // Add task to vector
    std::cout << "Task has been added\n";
}

void viewTasks(const std::vector<std::string>& tasks) {
    if (tasks.empty()) {
        std::cout << "No tasks to show.\n";
    }
    else {
        std::cout << "Your tasks:\n";
        for (size_t i = 0; i < tasks.size(); ++i) {
            std::cout << i + 1 << ". " << tasks[i] << "\n";
        }
    }
}

void deleteTask(std::vector<std::string>& tasks) {
    if (tasks.empty()) {
        std::cout << "No tasks to delete.\n";
    }
    else {
        int taskIndex;
        std::cout << "Enter the task number to delete: ";
        std::cin >> taskIndex;
        std::cin.ignore();  
        if (taskIndex > 0 && taskIndex <= tasks.size()) {
            tasks.erase(tasks.begin() + (taskIndex - 1)); 
            std::cout << "Task deleted.\n";
        }
        else {
            std::cout << "Invalid task number.\n";
        }
    }
}

void saveTasks(const std::vector<std::string>& tasks) {
    std::ofstream outFile("tasks.txt");
    if (outFile.is_open()) {
        for (const std::string& task : tasks) {
            outFile << task << "\n";
        }
        outFile.close();  
        std::cout << "Tasks saved successfully!\n";
    }
    else {
        std::cout << "Unable to open file for saving tasks.\n";
    }
}

void loadTasks(std::vector<std::string>& tasks) {
    std::ifstream inFile("tasks.txt");  
    if (inFile.is_open()) {
        std::string task;
        while (std::getline(inFile, task)) {
            tasks.push_back(task);  
        }
        inFile.close();  
        std::cout << "Tasks loaded successfully!\n";
    }
    else {
        std::cout << "No previous tasks found or unable to open file.\n";
    }
}
