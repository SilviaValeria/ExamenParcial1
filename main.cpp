#include <fstream>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

std::mutex fileMutex;

void writer(const std::string& filename, int tid) 
{
    
    std::string line = "Thread " + std::to_string(tid) + " -> Hola!  escribi esta linea :) \n";

    
    std::lock_guard<std::mutex> guard(fileMutex);

    std::ofstream out(filename, std::ios::app);
    if (!out)
    {
        std::cerr << "Error, no se pudo abrir el archivo " << filename << "\n";
        return;
    }
    out << line;
}

int main() 
{
    const std::string filename = "salida.txt";

    
    {
        std::ofstream clear(filename, std::ios::trunc);
        if (!clear) 
        {
            std::cerr << "Error,  no se pudo crear/limpiar el archivo \n";
            return 1;
        }
    }

    std::vector<std::thread> threads;
    threads.reserve(5);

    for (int i = 1; i <= 5; i++) 
    {
        threads.emplace_back(writer, filename, i);
    }

    for (auto& t : threads) 
    {
        t.join();
    }

    std::cout << "Listo :)  Revisa el archivo: " << filename << "\n";
    return 0;
}
