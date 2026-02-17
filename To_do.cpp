#include <iostream>
#include <vector>
#include <string>
#include <limits> // Required for input limits

using namespace std;

// structure to hold task details
struct Task {
    string description;
    bool isCompleted;
};

// Function to add a task
void addTask(vector<Task>& tasks) {
    Task newTask;
    cout << "Enter task description: ";
    
    // Clear the input buffer before getting the line to avoid skipping input
    cin.ignore(); 
    getline(cin, newTask.description);
    
    newTask.isCompleted = false;
    tasks.push_back(newTask);
    cout << "Task added successfully!\n";
}

// Function to view all tasks
void viewTasks(const vector<Task>& tasks) {
    cout << "\n--- To-Do List ---\n";
    if (tasks.empty()) {
        cout << "List is empty.\n";
        return;
    }

    // Using a standard loop to be safe for older C++ compilers (Dev-C++)
    for (size_t i = 0; i < tasks.size(); ++i) {
        cout << i + 1 << ". [";
        if (tasks[i].isCompleted) {
            cout << "X";
        } else {
            cout << " ";
        }
        cout << "] " << tasks[i].description << "\n";
    }
    cout << "------------------\n";
}

// Function to mark a task as completed
void markTaskCompleted(vector<Task>& tasks) {
    if (tasks.empty()) {
        cout << "No tasks to mark.\n";
        return;
    }
    
    viewTasks(tasks); // Show list first so they know the number
    
    int index;
    cout << "Enter the number of the task to mark completed: ";
    cin >> index;

    if (index > 0 && index <= tasks.size()) {
        tasks[index - 1].isCompleted = true;
        cout << "Task marked as completed!\n";
    } else {
        cout << "Invalid task number.\n";
    }
}

// Function to remove a task
void removeTask(vector<Task>& tasks) {
    if (tasks.empty()) {
        cout << "No tasks to remove.\n";
        return;
    }

    viewTasks(tasks);

    int index;
    cout << "Enter the number of the task to remove: ";
    cin >> index;

    if (index > 0 && index <= tasks.size()) {
        // Erase the task at the specific position
        tasks.erase(tasks.begin() + (index - 1)); 
        cout << "Task removed successfully!\n";
    } else {
        cout << "Invalid task number.\n";
    }
}

int main() {
    vector<Task> tasks;
    int choice = 0;

    while (choice != 5) {
        cout << "\n1. Add Task\n";
        cout << "2. View Tasks\n";
        cout << "3. Mark Task as Completed\n";
        cout << "4. Remove Task\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        // Check if input is not a number (prevents infinite loop error)
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1:
                addTask(tasks);
                break;
            case 2:
                viewTasks(tasks);
                break;
            case 3:
                markTaskCompleted(tasks);
                break;
            case 4:
                removeTask(tasks);
                break;
            case 5:
                cout << "Exiting... Have a productive day!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
    return 0;
}
