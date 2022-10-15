#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <optional>
#include <cassert>
#include <unordered_map>
namespace local
{

template<class T>
T rand()
{
	return std::rand();
}


template<class T = int>
std::string toBinary(T val)
{
	std::string bin;
	for(size_t i = 0; i < sizeof(T) * 8; i++)
	{
		T shifted = val >> i;
		std::string bit(std::to_string(shifted & 0x1));
		bin += bit;
	}

	return "0b" + bin;
}

}

template<class T>
std::vector<T> genArray(int size, int max = RAND_MAX)
{
	std::vector<T> array;
	array.resize(size);
	for(auto &v : array)
		v = local::rand<T>() % max;
	return array;
}


template<typename T>
std::ostream& operator<<(std::ostream& ostr, const std::vector<T>& vec)
{
	ostr << "[";
	for(const auto& v : vec)
		ostr << v << " ";

	return ostr << "]";
}

template<class T>
void swap(T& v1, T& v2)
{
	auto tmp = v1;
	v1 = v2;
	v2 = tmp;
}

class InsertionSort
{
public:
	template<class T>
	static void sort(std::vector<T>& array)
	{
		for(size_t i = 0; i < array.size() - 1; i++)
		{
			if(array[i] > array[i+1])
			{
				swap(array[i], array[i+1]);
				for(int j = i - 1; j >= 0; j--)
				{
					if(array[j] > array[j+1])
						swap(array[j], array[j+1]);
				}
			}
		}
	}
private:
	InsertionSort();
};

class HeapSort
{
public:
	template<class T>
	static void sort(std::vector<T>& array)
	{
		// make array a maxheap
		for(size_t i = 1; i <= array.size(); i++)
			maxHeapify(array, array.size() - i, array.size() - 1);


		for(size_t i = 1; i < array.size(); i++)
		{
			swap(array[0], array[array.size() - i]);
			maxHeapify(array, 0, array.size() - i - 1);
		}
	}
private:
	static inline size_t pI(size_t i)
	{
		return i / 2;
	}

	static inline size_t lI(size_t i)
	{
		return 2 * i;
	}

	static inline size_t rI(size_t i)
	{
		return 2 * i + 1;
	}

	template<class T>
	static void maxHeapify(std::vector<T>& array, size_t i, size_t last)
	{
		auto largest = i;
		if(lI(i) <= last && array[lI(i)] > array[largest])
			largest = lI(i);
		if(rI(i) <= last && array[rI(i)] > array[largest])
			largest = rI(i);
		if(largest != i)
		{
			swap(array[i], array[largest]);
			maxHeapify(array, largest, last);
		}
	}

	HeapSort();
};

class CountingSort
{
public:
	template<class T>
	static void sort(std::vector<T>& array)
	{

		for(size_t i = 0; i < sizeof(T) * 8; i++)
		{
			std::vector<size_t> C(2, 0);
			for(auto& v : array)
				C[(v >> i ) & 0x1]++;

			C[1] += C[0];
			typename std::remove_reference<decltype(array)>::type b = array;
			for(int j = 0; j < b.size(); j++)
			{
				size_t dataIndex = b.size() - j - 1;
				size_t index = (array[dataIndex] >> i) % 2;
				b[C[index] - 1] = array[dataIndex];
				C[index]--;
			}
			b.swap(array);
		}


	}
};

class Timer
{
public:
	void start() {
		before = std::chrono::system_clock::now();
	}
	void stop() {
		after = std::chrono::system_clock::now();
	}

	template<class DurationType>
	unsigned long check()  { return std::chrono::duration_cast<DurationType>(after - before).count(); }

	std::string runtime()
	{
		return std::to_string(check<std::chrono::milliseconds>() / 1000) + " sec "
				+ std::to_string(check<std::chrono::milliseconds>() % 1000) + " msec "
				+ std::to_string(check<std::chrono::microseconds>() % 1000) + " nsec "
				+ std::to_string(check<std::chrono::nanoseconds>() % 1000) + "usec";
	}

private:
	std::chrono::system_clock::time_point before;
	std::chrono::system_clock::time_point after;
};

template<class AlgType, class T>
void sort(std::vector<T>& array)
{
	AlgType::sort(array);
}

template<class T>
bool isSorted(const T& val)
{
	for(int i = 0; i < val.size() - 1; i++)
		if(val[i] > val[i+1])
			return false;

	return true;
}
int main(int argc, char** argv)
{
	auto array = genArray<int>(std::stoul(argv[1]), std::stoul(argv[2]));
	assert(!isSorted(array));
	auto sortedArray = array;
	auto timer = Timer();
	timer.start();
	sort<InsertionSort>(sortedArray);
	timer.stop();
	assert(isSorted(sortedArray));
	std::cout << "Insertionsort runtime " << timer.runtime() << std::endl;

	sortedArray = array;
	timer.start();
	sort<HeapSort>(sortedArray);
	timer.stop();
	if(!isSorted(sortedArray))
	{
		std::cout << array << std::endl;

		std::cout << sortedArray << std::endl;
		assert(false);
	}
	std::cout << "Heapsort runtime: " << timer.runtime() << std::endl;

	sortedArray = array;
	timer.start();
	sort<CountingSort>(sortedArray);
	timer.stop();
	if(!isSorted(sortedArray))
	{
		std::cout << array << std::endl;

		std::cout << sortedArray << std::endl;
		assert(false);

	}
	std::cout << "Counting runtime " << timer.runtime() << std::endl;




}
