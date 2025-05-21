#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <fstream>
#include <iostream>
#include <vector>

extern "C" {
#include "aes.h"
}

using namespace std;

int padding_size = 0;
vector<uint8_t> decry_data;

void encrypt_ecb(string origin_path, string save_path)
{
	vector<vector<uint8_t>> data;
	vector<uint8_t> key = {1, 2, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};

	ifstream input(origin_path, std::ios::binary);
	
	input.seekg(0, std::ios::end);
	long fileSize = static_cast<ios::streamoff>(input.tellg());
	input.seekg(0, std::ios::beg);
	padding_size = 16 - fileSize % 16;
	
	vector<uint8_t> tmp(16);
	if (input.is_open()) {
		while (true)
		{
			input.read((char*)tmp.data(), 16);		
			if (fileSize % 16 == 0) {
				if (input.eof()) { break; }
				data.emplace_back(tmp);
			}
			else {

				data.emplace_back(tmp);
				if (input.eof()) { break; }
			}
		}
	}
	input.close();

	struct AES_ctx ctx;
	AES_init_ctx(&ctx, key.data());
	for (int i=0; i<data.size(); i++)
	{
		AES_ECB_encrypt(&ctx, data[i].data());
	}
	
	ofstream out_file(save_path, std::ios::binary);
	for (int i = 0; i < data.size(); i++) {
		out_file.write((char*)data[i].data(), data[i].size());
	}
	out_file.close();

}

void decrypt_ecb(string save_path) {
	ifstream input(save_path, std::ios::binary);

	input.seekg(0, std::ios::end);
	long fileSize = static_cast<ios::streamoff>(input.tellg());
	input.seekg(0, std::ios::beg);
	
	if (fileSize % 16 != 0) {
		printf("文件大小不对\n");
		return;
	}
	
	decry_data.resize(fileSize);
	struct AES_ctx ctx;

	vector<uint8_t> key = { 1, 2, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
	AES_init_ctx(&ctx, key.data());

	if (input.is_open()) {
		vector<uint8_t> data(16);
		int index = 0;

		while (true)
		{
			input.read(reinterpret_cast<char*>(data.data()), data.size());
			if (input.eof()) {
				break;
			}
			AES_ECB_decrypt(&ctx, data.data());
			copy(data.begin(), data.end(), decry_data.begin() + index * 16);
			index++;
		}
	
	}
	input.close();

	decry_data.erase(decry_data.end() - 10, decry_data.end());
}

int main(void)
{
	encrypt_ecb("mnist.onnx", "save.bin");
	decrypt_ecb("save.bin");

	// 测试
	vector<uint8_t> origin_data;

	ifstream input("mnist.onnx", std::ios::binary);
	input.seekg(0, std::ios::end);
	long fileSize = static_cast<ios::streamoff>(input.tellg());
	input.seekg(0, std::ios::beg);

	origin_data.resize(fileSize);
	input.read((char*) origin_data.data(), fileSize);


	for (int i = 0; i < origin_data.size(); i++) {
		if (origin_data[i] != decry_data[i]) {
			printf("加密错误\n");
		};
	}
	printf("done\n");

	return 0;
}




