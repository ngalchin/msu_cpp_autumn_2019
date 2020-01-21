#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <thread>
#include <string>


void merge_files(std::vector<std::string>& files)
{
	uint64_t a, b;
	std::ofstream output_stream ("output.bin", std::ios::binary);
	std::ifstream input_stream (files[0], std::ios::binary);

	auto *temp = new uint64_t [1024 * 1024];

	while (!input_stream.eof())
	{
		input_stream.read(reinterpret_cast<char *>(temp), 1024 * 1024);
		if (input_stream.gcount() > 0)
			output_stream.write(reinterpret_cast<const char *>(temp), input_stream.gcount());
	}
	input_stream.close();
	output_stream.close();
	std::fill_n(temp, 1024 * 1024, 0);

	for (int i = 1; i < files.size(); i++)
	{
		std::ifstream in_temp ("output.bin", std::ios::binary);
		std::ifstream in_next (files[i], std::ios::binary);
		std::ofstream out_tmp ("tmp.bin", std::ios::binary);

		while (!in_temp.eof())
		{
			in_temp.read(reinterpret_cast<char *>(temp), 1024 * 1024);
			if (in_temp.gcount() > 0)
				out_tmp.write(reinterpret_cast<const char *>(temp), in_temp.gcount());
		}
		in_temp.close();
		out_tmp.close();
		std::fill_n(temp, 1024 * 1024, 0);

		std::remove("output.bin");

		in_temp.open("tmp.bin", std::ios::binary);
		std::ofstream output_stream ("output.bin", std::ios::binary);

		in_temp.read((char *)&a, sizeof(a));
		in_next.read((char *)&b, sizeof(b));

		while (!in_next.eof())
		{
			if (in_temp.gcount())
			{
				if (a >= b)
				{
					output_stream.write((char *)&b, sizeof(b));
					in_next.read((char *)&b, sizeof(b));
				}else{
					output_stream.write((char *)&a, sizeof(a));
					in_temp.read((char *)&a, sizeof(a));
				}

			}else{
				while (!in_next.eof())
				{
					output_stream.write((char *)&b, sizeof(b));
					in_next.read((char *)&b, sizeof(b));
				}
			}
		}

		if (in_temp.gcount())
		{
			output_stream.write((char *)&a, sizeof(a));

			while (in_temp.eof())
			{
				in_temp.read((char *)temp, 1024 * 1024);
				output_stream.write((char *)temp, in_temp.gcount());
			} 
		}
	}
	delete [] temp;
	for (auto &one_file: files)
		std::remove(one_file.c_str());
	std::remove("tmp.bin");


}


void my_sort(std::ofstream& output_stream)
{
	std::ifstream input_stream ("input.bin", std::ios::binary);
	auto *temp = new uint64_t [1024 * 1024];
	std::vector<std::string> files;
	int i = 0; 
	while (!input_stream.eof())
	{
		input_stream.read(reinterpret_cast<char *>(temp), 1024 * 1024);
		std::string file = "tmp" + std::to_string(i) + ".bin";
		files.push_back(file);
		size_t amt = input_stream.gcount();

		if (amt > 0)
		{
			size_t half = amt / 16;

			std::thread thread1 ([temp, half]{std::sort(temp, temp + half);});
			std::thread thread2 ([temp, half]{std::sort(temp + half, temp + 2 * half);});
			thread1.join();
			thread2.join();
			output_stream.open(file, std::ios::binary);
			output_stream.write(reinterpret_cast<const char *>(temp), half * 8);
			output_stream.close();
			i+=1;
			file = "tmp" + std::to_string(i) + ".bin";
			files.push_back(file);

			output_stream.open(file, std::ios::binary);
			output_stream.write(reinterpret_cast<const char *>(temp + half), amt - half * 8);
			output_stream.close();
		}

	}
	merge_files(files);
	input_stream.close();
	delete [] temp;
}


int main()
{
	//Size of uint64_t - 8 byte
	std::ofstream input_file ("input.bin", std::ios::binary);
	for(int i = 0; i < 1024 * 1024; i++)
	{
		uint64_t unit = rand();
		input_file.write(reinterpret_cast<const char *>(&unit), sizeof(unit));	
	}
	input_file.close();

	my_sort(input_file);

	return 0;
}