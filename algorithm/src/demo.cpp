
#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

#if 0

using namespace cv;
using namespace std;

void draw_range(vector<int>& data, int start, int end, cv::Scalar color=cv::Scalar(0, 255, 0)){
	cv::Mat image(300, 480, CV_8UC3, cv::Scalar(0, 0, 0));
	for (int k = 0; k < data.size(); k++) {

		int w = 40;
		int h = data[k] * 30;
		int x = k * (w + 10);
		int y = 0;

		if (k >= start && k <= end) {
			rectangle(image, cv::Point(x, y), cv::Point(x + w, y + h), cv::Scalar(0, 255, 0), -1);
		}
		else {
			rectangle(image, cv::Point(x, y), cv::Point(x + w, y + h), cv::Scalar(255, 255, 0), -1);
		}

		putText(image, format("%d", data[k]), cv::Point(x + w / 3, y + 10), 1, 1, cv::Scalar(0, 0, 255), 1);

	}

	cv::imshow("image", image);
	cv::waitKey();
}

void draw(vector<int> data, int i, int j, int s=-1){

	cv::Mat image(300, 480, CV_8UC3, cv::Scalar(0, 0, 0));
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

		if (k == s) {
			putText(image, format("%d", data[s]), cv::Point(x + w / 3, y + 10), 1, 1, cv::Scalar(255, 0, 0), 1);
		}
		else {
			putText(image, format("%d", data[k]), cv::Point(x + w / 3, y + 10), 1, 1, cv::Scalar(0, 0, 255), 1);
		}
		
	}
	cv::imshow("image", image);
	cv::waitKey();
	
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


	for (int i = 0; i < data.size(); i++) {

		int temp = data[i];

		int k = i - 1;


		for (int j = i - 1; j >= 0; j--) {
			int m;
			if (data[j] > temp) {
				draw(data, j + 1, j, i);
				data[j + 1] = data[j];
				data[j] = temp;
				k = j;
				draw(data, j + 1, j, i);
			}
			else {
				break;
			}
		}

		draw(data, k, k + 1);
		data[k + 1] = temp;
		draw(data, k, k + 1);



	}
}

void shell_sort(vector<int>& data) {
}

void merge_sort(vector<int>& data, int left, int right) {


	if (left < right) {

		int mid = left + (right - left) / 2;

		merge_sort(data, left, mid);
		merge_sort(data, mid + 1, right);

		std::cout << left << " " << mid << " " << right << std::endl;


		

		int n1 = mid - left + 1;
		int n2 = right - mid;


		vector<int> datal(n1);
		vector<int> datar(n2);


		for(int i=0; i < n1; i++){
			datal[i] = data[left + i];
		}
		

		for (int j = 0; j < n2; j++) {
			datar[j] = data[mid + 1 + j];
		}



		// 合并数据
		int i = 0;
		int j = 0;
		int k = left;

		draw_range(data, left, right);

		while (i < n1 && j < n2) {

			if (datal[i] < datar[j]) {
				data[k++] = datal[i++];
			}
			else {
				data[k++] = datar[j++];
			}
		}

		while (i < n1) {
			data[k++] = datal[i++];
		}

		while (j < n2) {
			data[k++] = datar[j++];
		}
		draw_range(data, left, right);


	}

}



int main2()
{
	
	std::vector<int> data = {2, 8, 5, 3, 7, 5, 4, 9, 6, 1 };
	merge_sort(data, 0, data.size() - 1);

	cv::waitKey();
	return 0;
}




#endif