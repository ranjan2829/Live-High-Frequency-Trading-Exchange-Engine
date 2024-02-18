#include "thread_utils.h" // Include the header file where the Common namespace is defined

// Function to be executed by the thread
void printMessage(const std::string& message) {
    std::cout << "Thread message: " << message << std::endl;
}

int main() {
    // Set the CPU core ID for the thread (change as needed)
    int core_id = 0;

    // Create and start a thread with core affinity
    auto myThread = Common::createAndStartThread(core_id, "My Thread", printMessage, "Hello from the thread!");

    // Wait for the thread to finish
    myThread->join();

    std::cout << "Main thread: Thread finished." << std::endl;

    return 0;
}
