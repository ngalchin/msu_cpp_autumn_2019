#include <chrono>
#include <iostream>

#define N 10000

class Timer
{
    using clock_t = std::chrono::high_resolution_clock;
    using microseconds = std::chrono::microseconds;
public:
    Timer()
        : start_(clock_t::now())
    {
    }

    ~Timer()
    {
        const auto finish = clock_t::now();
        const auto us = 
            std::chrono::duration_cast<microseconds>
                (finish - start_).count();
        std::cout << us << " us" << std::endl;
    }

private:
    const clock_t::time_point start_;
};

void init_1(int** A)
{
        for (int i = 0; i < N; i++)
        {
                for (int j = 0; j < N; j++)
                {
                        A[i][j] = 3*i +2*j + 1;
                }
        }
}

int sum_by_rows(int** A)
{
        Timer t;

        int sum = 0;

        for (int i = 0; i < N; i++)
        {
                for (int j = 0; j < N; j++)
                {
                        sum += A[i][j];
                }

        }

        return sum;

}

int main()
{

	int** matrix = new int*[N];
	for(size_t i = 0 ; i < N ; ++i)
    		matrix[i] = new int[N];

	int result;

	init_1(matrix);
	
	result = sum_by_rows(matrix);	


	for(size_t i = 0 ; i < N ; ++i)
    		delete matrix[i];
	delete[] matrix;

	return 0;

}
