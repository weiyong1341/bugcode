#include <stdio.h>
#include <vector>
#include <map>

//#include <cuda_runtime.h>
//#include <cuda_runtime_api.h>
//#include <cuda.h>
//#include <device_launch_parameters.h>

#include <string>
#include <iostream>

#define N 32

using namespace std;

#if 1
vector<int> twoSum(vector<int>& nums, int target) {


	// for(int i=0; i<nums.size() - 1; i++){
	//     for(int j=i + 1; j<nums.size(); j++){
	//         if((nums[i] + nums[j]) == target){
	//             return {i, j};
	//         }
	//     }
	// }

	// return {0, 0};

	map<int, int> contain;

	for (int i = 0; i < nums.size(); i++) {
		int diff = target - nums[i];
		if (contain.count(diff) > 0) {
			return { contain[diff], i };
		}
		contain[nums[i]] = i;
	}
	return { 0, 0 };
}

#endif




struct ListNode {
	int val;
	ListNode *next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode *next) : val(x), next(next) {}
	
};


ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {

	ListNode *head = nullptr, *tail = nullptr;



	int extra = 0;
	while (l1 || l2) {

		int n1 = l1 ? l1->val : 0;
		int n2 = l2 ? l2->val : 0;


		int sum = n1 + n2 + extra;
		extra = sum / 10;

		if (!head) {
			head = tail = new ListNode(sum % 10);
		}
		else {
			tail->next = new ListNode(sum % 10);
			tail = tail->next;
		}

		if (l1) {
			l1 = l1->next;
		}
		if (l2) {
			l2 = l2->next;
		}
		
	}

	if (extra > 0) {
		tail->next = new ListNode(extra);
	}
	return head;
}

void test2() {


	ListNode* node1 = new ListNode(9);
	node1->next = new ListNode(9);
	node1->next->next = new ListNode(9);


	ListNode* node2 = new ListNode(9);
	node2->next = new ListNode(9);

	addTwoNumbers(node1, node2);
}


void test3() {
	string s = "abcabcbb";

	int size = 0;
	for (int i = 0; i < s.size() ; i++) {
		int sub_length = 1;
		for (int j = i + 1; j < s.size(); j++) {
			if (s[i] != s[j]) {
				sub_length++;
			}
			else
			{
				break;
			}
		}

		if (size < sub_length) {
			size = sub_length;
		}
	}

	std::cout << size << std::endl;


}


double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {


	int i = 0, j = nums1.size() - 1, m = 0, n = nums2.size() - 1;

	while (i == j && m == n) {

	}

	return 0;

}

void test4(){
	/*vector<int>data1 = { 2, 7, 11, 15 };
	vector<int>data2 = { 2, 7, 11, 15 };

	findMedianSortedArrays(data1, data2);*/

}


void fun(int a) {
	cout << "int" << endl;
}

void fun(int* a) {
	cout << "point" << endl;
}


void binarySearch() {
	vector<int> data = { 1, 2, 4, 5, 6 };
	int i = 0, j = data.size() - 1;

	int target = 3;

	while (i <= j)
	{
		int middle = (j - i) / 2;
		int val = data[middle];

		if (val == target) {
			std::cout << middle << std::endl;
			break;
		}
		else if (val < target) {
			j = middle;
		}
		else {
			i = middle;
		}
		
	}
	std::cout << "none" << std::endl;



}

int main3() {

	void fun(int* a);
	fun(NULL);
	binarySearch();

	//vector<int>data = { 2, 7, 11, 15 };
	//test4();

	return 0;
}



#if 0
__global__ void VecAdd(float* A, float* B, float* C) {

	int i = threadIdx.x;
	C[i] = A[i] + B[i];
}

void test(){


	dim3 threadPerBlock(16, 16);
	dim3 numBlock(N / threadPerBlock.x, N / threadPerBlock.y);

	float A[2] = { 1, 1 };
	float B[2] = { 1, 1 };
	float C[2] = { 1, 1 };

	VecAdd << <numBlock, threadPerBlock >> > (A, B, C);


}
#endif

