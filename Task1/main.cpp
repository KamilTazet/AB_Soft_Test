#include <iostream>
#include <deque>
#include <mutex>
#include <thread>
#include <chrono>
#include <sstream>
#define WRITERS_AMOUNT 4
#define READERS_AMOUNT 4
#define ITER 3
#define SLEEP_SEC 2
std::mutex access_read, access_write;
std::deque<int> data_queue;

void reader(int prm) {
	int num1 = prm;
	int i = 0;
    int r;
	for(i; i < ITER; i++) {
        std::stringstream reader_stream;
		access_read.lock();
        reader_stream << std::endl;
        reader_stream << "Reader " << num1 << " current deque:" << std::endl;
        for(auto it = data_queue.begin(); it != data_queue.end(); it++) {
            reader_stream << *it << " ";
        }
        reader_stream << std::endl;
		if(!data_queue.empty()) {
			r = data_queue.front();
			data_queue.pop_front();
			reader_stream << "Reader " << num1 << " read value " << r << " from queue" << std::endl;
			// reader_stream << std::endl;
		}
		else {
			reader_stream << "Очередь пуста" << std::endl;
		}
		reader_stream << std::endl;
		std::cout << reader_stream.str();
        std::this_thread::sleep_for(std::chrono::seconds(SLEEP_SEC));
		access_read.unlock();
	}

}


void writer(int prm) {
	int num2 = prm;
	int j = 0;
    int r;
	for(j; j < ITER; j++){
        std::stringstream writer_stream;
		access_write.lock();
		r=1+rand()%100;
        writer_stream << std::endl;
		writer_stream << "Writer " << num2 << " current deque:" << std::endl;
		for(auto it = data_queue.begin(); it != data_queue.end(); it++) {
			writer_stream << *it << " ";
		}
		writer_stream << std::endl;
		data_queue.push_back(r);
		writer_stream << "Writer " << num2 << " write value " << r << " in queue" << std::endl;
		writer_stream << std::endl;
		std::cout << writer_stream.str();
        std::this_thread::sleep_for(std::chrono::seconds(SLEEP_SEC));
		access_write.unlock();
	}
}


int main() {
	std::thread Writers[WRITERS_AMOUNT];
    std::thread Readers[READERS_AMOUNT];
	std::cout << "Количество итераций: " << ITER << std::endl;
	std::cout << "Количество писателей: " << WRITERS_AMOUNT << std::endl;
	std::cout << "Количество читателей: " << READERS_AMOUNT << std::endl;
    int i;
	for(i = 0; i < WRITERS_AMOUNT; i++) {
		Writers[i] = std::thread(writer, i);
	}
	for(i = 0; i < READERS_AMOUNT; i++) {
		Readers[i] = std::thread(reader, i);
	}
	for(i = 0; i < WRITERS_AMOUNT; i++) {
		Writers[i].join();
	}
	for(i = 0; i < READERS_AMOUNT; i++) {
		Readers[i].join();
	}
	std::cout << "Finale deque state:" << std::endl;
	for(auto it = data_queue.begin(); it != data_queue.end(); it++) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}
