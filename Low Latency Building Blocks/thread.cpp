#include <iostream>
#include <thread>
#include <chrono> // For std::chrono_literals

// Function to print a message from a separate thread
void printMessage(const std::string& message) {
    std::cout << "Thread message: " << message << std::endl;
}

int main() {
    // Set core ID for the thread (comment out for no pinning)
    int core_id = 1; // Change to a valid core ID on your system

    // Create a thread with the printMessage function
    std::thread myThread(printMessage, "Hello from the thread!");

    // Wait for the thread to finish
    myThread.join();

    std::cout << "Main thread: Thread finished." << std::endl;

    return 0;
}
