#include <stdio.h>
#include <vector>
#include <map>
#include <iostream>
#include <unordered_map>
#include <algorithm>

using namespace std;


// 合并两个有序数组
// 1. 合并两个数组，然后排序
// 2. 两个指针，分别循环数组
void code_88(){

    vector<int> nums1 = { 1, 2, 3 };
    vector<int> nums2 = { 4, 5, 6 };

    int m = 3;
    int n = 3;

	vector<int> tmp;


    for(int i=0, j=0; i < m || j < n;){
        
		if (i >= m) {
			tmp.emplace_back(nums2[j]);
			j++;
		}else if (j >= n) {
			tmp.emplace_back(nums1[i]);
			i++;

		}else if (nums1[i] < nums2[j]) {
			tmp.emplace_back(nums1[i]);
			i++;
		}else {
			tmp.emplace_back(nums2[j]);
			j++;
		}
        
    }

	printf("");
    
}

// 原地移除元素，原地是指在这个数组中的操作，不要新建数组
// 1. 排序之后，删除所有的
// 2. 因为这里不在乎删除之后的顺序, 
// 使用双指针，把跑的快的指针的数据赋值给跑的慢的指针
int code_27() {


	vector<int> nums = { 3, 2, 2, 3 };
	int val = 3;
	int left = 0;
	for (int right = 0; right < nums.size() - 1; right++) {
		if (nums[right] != val) {
			nums[left] = nums[right];
			left++;
		}
	}
	return left;
}

// 删除有序数组中的重复项
// 只要是数组，那么就应该判断大小为空

int code_26() {

	vector<int> nums = { 0,0,1,1,1,2,2,3,3,4 };

	if (nums.size() == 0) {
		return 0;
	}
	
	int left = 1;
	for (int right = 1; right < nums.size(); right++) {
		if (nums[left] != nums[right]) {
			nums[left] = nums[right];
			left++;
		}
	}

	
	return left;
}

int code_80() {


	vector<int> nums = { 1,1,1,2,2,3 };

	if (nums.size() == 0) {
		return 0;
	}

	int left = 1;
	
	int prev = nums[0];
	int prev_id = 0;

	for (int right = 1; right < nums.size(); right++) {

		if (prev != nums[right]) {
			nums[left] = nums[right];
			prev = nums[right];
			prev_id = right;
			left++;
			
		}
		else {
			if (right - prev_id < 2) {
				nums[left] = nums[right];
				left++;
			}
		}
	}



	return left;
}


int code_169() {

	vector<int> nums = { 2,2,1,1,1,2,2 };
	unordered_map<int, int> map;

	int key;
	for (int i = 0; i < nums.size(); i++) {
		if (map.count(nums[i]) == 0) {
			map[nums[i]] = 1;
		}
		else {
			map[nums[i]] = map[nums[i]] + 1;
		}

		if (map[nums[i]] > nums.size() / 2) {
			key = nums[i];
		}
	}
	return key;


	
	/*for (auto it = map.begin(); it != map.end(); it++) {
		if (it->second > nums.size() / 2) {
			return it->second;
		}
	}*/
	



	return 0;
}

// 轮转是指每次轮转一个位置，然后把轮转次数用完
// 解决方法是直接计算最后的位置，而不是一直重复

void code_150() {
	vector<int> nums = { 1, 2 };
	int k = 4;

	int n = nums.size();
	vector<int> newArr(n);

	for (int i = 0; i < n; ++i) {
		newArr[(i + k) % n] = nums[i];
	}
	nums.assign(newArr.begin(), newArr.end());



	printf("");
	
}

int code_121() {

	vector<int> prices = { 7,1,4,3,1 };
	
	int min_price = 1e5;
	int max_profit = 0;

	for (int i = 0; i < prices.size(); i++) {
		min_price = min(prices[i], min_price);
		max_profit = max(prices[i] - min_price, max_profit);
	}

	return max_profit;

}

int code_122() {

	int profit = 0;

	return profit;

}

// 一次上2层或者上1层，最后到3层
// 如果还有一层就到顶了，就向上一步
// 如果还有两层就到顶了，就向上一步，或者向上两步
void back(vector<int>& steps, int num, int step, int& res) {

	std::cout << "step:" << step << std::endl;
	for (int s : steps) {

		std::cout << "step: " << step << " " << s << std::endl;
		if (s + step > num) {
			return;
		}
		if (s + step == num) {
			std::cout << "res:" << res << std::endl;
			res++;
			return;
		}
		//step = s + step; 这里不能直接更改step，否则在使用s=2的时候，就把s=1上的数据用在这里了
		back(steps, num, s + step, res);

	}

}

int code_back() {
	int num = 3;
	int res = 0;
	int step = 0;
	vector<int> steps = { 1, 2 };
	back(steps, num, step, res);
	std::cout << res << std::endl;
	return 0;
}

bool code_55() {
	vector<int> nums = { 3,2,1,0,4 };
	

	int most = 0;

	for (int i = 0; i < nums.size(); i++) {
		if (i <= most) {
			most = max(most, nums[i] + i);
			if (most >= nums.size() - 1) {
				return true;
			}
		}
	}
	return false;

}

void code_45() {
	vector<int> nums = {2, 3, 1, 1,  4};

	int most = 0;
	int step = 0;
	int end = 0;

	for (int i = 0; i < nums.size(); i++) {
		if (i <= most) {
			most = max(most, nums[i] + i);

			if (i == end) {
				end = most;
				step++;
			}
		}
	}

	return;



}


int code_275() {
	vector<int> citations = { 1,3,1 };

	

	// 针对每篇论文，获得超过h次的数量
	// h的最大值是论文的数量
	// 找出引用数量大于索引值的最大值

	vector<int> h_num(citations.size() + 1, 0);
	int res = 0;

	for (int h = 0; h <= citations.size(); h++) {

		for (int i = 0; i < citations.size(); i++) {
			if (citations[i] >= h) {
				h_num[h]++;
			}
		}
		if (h_num[h] >= h) {
			res = h;
		}


	}

	return res;
}

void code_380() {

}

void code_238() {
	vector<int> nums = { 1, 2, 3, 4 };

	unordered_map<int, int> res;

}

int code_134() {
	vector<int> gas = {1, 2, 3, 4, 5 };
	vector<int> cost = {3, 4, 5, 1, 2 };


	int num = gas.size();





	int res = gas[0];

	for (int i = 1; i < gas.size(); i++) {
		res = res - cost[i - 1];

		if (res < 0) {
			return -1;
		}
		res = res + gas[i];


	}


}





int main(){
	code_275();

    return 0;
}