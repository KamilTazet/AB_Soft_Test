#include <iostream>
#include <deque>
#include <mutex>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <sstream>
#define WRITERS_AMOUNT 3
#define READERS_AMOUNT 5
#define ITER 5
#define SLEEP_SEC 1
int writers_counter = 0;
int readers_counter = 0;
std::mutex resource_access, writer_mutex, reader_mutex, reader_lock;


void reader(int prm, std::deque<int> * data_queue) {
	int num = prm;
	int i = 0;
    int value;
	for(i; i < ITER; i++) {
        std::stringstream reader_stream;
        std::stringstream reader_processing_stream;
        reader_lock.lock();
        reader_mutex.lock();
        readers_counter++;
        if(readers_counter == 1) {
            resource_access.lock();
        }
        reader_mutex.unlock();
        reader_lock.unlock();
		if(!data_queue->empty()) {
			value = data_queue->front();
			data_queue->pop_front();
			reader_stream << "Reader " << num << " read value " << value << " from queue" << std::endl;
		}
		else {
			reader_stream << "Deque is empty" << std::endl;
			value = 0;
		}
		std::cout << reader_stream.str();
        reader_mutex.lock();
        readers_counter--;
        if(readers_counter == 0) {
        	resource_access.unlock();
        }
        reader_mutex.unlock();
		if(value != 0) {
			reader_processing_stream << "Reader " << num << " start processing value " << value << std::endl;
			std::cout << reader_processing_stream.str();
			reader_processing_stream.str(std::string());
			std::this_thread::sleep_for(std::chrono::seconds(SLEEP_SEC));
			reader_processing_stream << "Reader " << num << " finish processing value " << value << std::endl;
			std::cout << reader_processing_stream.str();
		}
    }
}

void writer(int prm, std::deque<int> * data_queue) {
	int num = prm;
	int j = 0;
    int value;
	for(j; j < ITER; j++) {
        std::stringstream writer_stream;
        writer_mutex.lock();
        writers_counter++;
        if(writers_counter == 1) {
            reader_lock.lock();
        }
        writer_mutex.unlock();
        resource_access.lock();
        value = 1 + std::rand() % 100;
        data_queue->push_back(value);
        writer_stream << "Writer " << num << " write value " << value << " in queue" << std::endl;
        writer_stream << "Writer counter = " << writers_counter << std::endl;
		// std::this_thread::sleep_for(std::chrono::seconds(SLEEP_SEC));
		std::cout << writer_stream.str();
        resource_access.unlock();
        writer_mutex.lock();
        writers_counter--;
        if(writers_counter == 0) {
            reader_lock.unlock();
        }
        writer_mutex.unlock();
    }
}


int main() {
	std::deque<int> data_queue;
	std::thread Writers[WRITERS_AMOUNT];
    std::thread Readers[READERS_AMOUNT];
	std::cout << "Количество итераций: " << ITER << std::endl;
	std::cout << "Количество писателей: " << WRITERS_AMOUNT << std::endl;
	std::cout << "Количество читателей: " << READERS_AMOUNT << std::endl;
    int i;
	for(i = 0; i < WRITERS_AMOUNT; i++) {
		Writers[i] = std::thread(writer, i, &data_queue);
	}
    for(i = 0; i < READERS_AMOUNT; i++) {
        Readers[i] = std::thread(reader, i, &data_queue);
    }
	for(i = 0; i < WRITERS_AMOUNT; i++) {
		Writers[i].join();
	}
	for(i = 0; i < READERS_AMOUNT; i++) {
		Readers[i].join();
	}
}
