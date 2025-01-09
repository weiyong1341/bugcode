
#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

#if 0
using namespace cv;
using namespace std;


void draw(vector<int> data, int i, int j, int s = -1) {

	cv::Mat image(300, 500, CV_8UC3, cv::Scalar(0, 0, 0));
	for (int k = 0; k < data.size(); k++) {

		int w = 40;
		int h = data[k] * 30;
		int x = k * (w + 10);
		int y = 0;


		if (k == i || k == j) {
			rectangle(image, cv::Point(x, y), cv::Point(x + w, y + h), cv::Scalar(255, 255, 0), -1);
		}
		else {
			rectangle(image, cv::Point(x, y), cv::Point(x + w, y + h), cv::Scalar(0, 255, 0), -1);
		}

		if (k == s && s > 0) {
			putText(image, format("%d", data[s]), cv::Point(x + w / 3, y + 10), 1, 1, cv::Scalar(255, 0, 0), 1);
		}
		else {
			putText(image, format("%d", data[k]), cv::Point(x + w / 3, y + 10), 1, 1, cv::Scalar(0, 0, 255), 1);
		}

	}
	cv::imshow("image", image);
	cv::waitKey(1);

}

void swap(vector<int>& data, int i, int j) {
	int tmp = data[i];
	data[i] = data[j];
	data[j] = tmp;
}



void bubble_sort(vector<int>& data) {
	std::cout << "冒泡排序" << std::endl;

	for (int i = 0; i < data.size() - 1; i++) {
		for (int j = 0; j < data.size() - 1; j++) {
			if (data[j] > data[j + 1]) {
				draw(data, j, j + 1);
				swap(data, j, j + 1);
			}
			draw(data, j, j + 1);
		}
	}
}

void select_sort(vector<int>& data) {
	std::cout << "选择排序" << std::endl;
	for (int i = 0; i < data.size() - 1; i++) {
		for (int j = i + 1; j < data.size(); j++) {
			if (data[i] > data[j]) {
				draw(data, i, j);
				swap(data, i, j);
			}
			draw(data, i, j);
		}
	}
}


void insert_sort(vector<int>& data) {
	// 插入排序
	for (int i = 1; i < data.size(); i++) {

		int temp = data[i];

		//// while 实现
		//int j = i - 1;
		////如果不先判断j大于等于0，可能会导致溢出
		//while (j >= 0 && data[j] > temp ) {
		//	draw(data, j + 1, j);
		//	data[j + 1] = data[j];
		//	// data[j] = temp;
		//	draw(data, j + 1, j);
		//	j--;
		//}

		//draw(data, j + 1, j);
		//data[j + 1] = temp;
		//draw(data, j + 1, j);



		// for 实现
		int j = i - 1;
		for (; j >= 0; j--) {
			if (data[j] > temp) {
				draw(data, j + 1, j, i);
				data[j + 1] = data[j];
				draw(data, j + 1, j, i);
			}
			else {
				break;
			}
		}

		
		j++;

		draw(data, j + 1, j);
		data[j] = temp;
		draw(data, j + 1, j);


	}
}


void shell_sort(vector<int>& data) {



	for (int gap = data.size(); gap > 0; gap /= 2) {
	 
	}

	
}

void merge_sort(vector<int>& data, int left, int right) {

	if ((right - left) < 2) {
		return;
	}

	int mid = left + (right - left) / 2;


	merge_sort(data, left, mid + 1);
	merge_sort(data, mid, right);

}

void test4() {
}

int main2()
{
	std::vector<int> data = { 2, 8, 5, 3, 7, 5, 4, 9, 6, 1 };
	//insert_sort(data);
	test4();

	
	cv::waitKey();
	return 0;
}
#endif