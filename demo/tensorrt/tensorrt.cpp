// 使用生产者消费者，将gpu使用率提高到99%

#include <thread>
#include <mutex>
#include <condition_variable>
#include <cuda_runtime_api.h>
#include <vector>
#include <queue>
#include <iostream>
#include <NvInfer.h>
#include <NvOnnxParser.h>
#include <cuda_runtime_api.h>
#include <fstream>

using namespace std;
using namespace nvinfer1;
using namespace nvonnxparser;


int buffersize = 10;
vector<vector<void*>> inputs;
queue<int> buffers;


mutex mtx;

condition_variable consumer_cond;
condition_variable producer_cond;

class Logger : public ILogger
{
    void log(Severity severity, const char* msg) noexcept override
    {
        // suppress info-level messages
        if (severity <= Severity::kWARNING)
            std::cout << msg << std::endl;
    }
} logger;

void producer(){

    while (true)
    {
        
        unique_lock<mutex> lock(mtx);
        producer_cond.wait(lock, []{ return buffers.size() < buffersize; });

        // 添加数据
        int index = 0;
        if(buffers.size() > 0){
            index = (buffers.back() + 1) % 10;
        }

        buffers.push(index);
        cout << "push: " << index << endl;
        lock.unlock();
        consumer_cond.notify_one();
    }
    
}

void consumer(){

    if(inputs.size() < buffersize){
        printf("显存未分配\n");
        return;
    }
    // 转换模型
    printf("初始化\n");
    IBuilder* builder = createInferBuilder(logger);
    
    auto flag = 1U << static_cast<uint32_t>(nvinfer1::NetworkDefinitionCreationFlag::kEXPLICIT_BATCH);

    INetworkDefinition* network = builder->createNetworkV2(flag);
    IBuilderConfig* config = builder->createBuilderConfig();

    // 加载模型
    printf("加载模型\n");
    std::ifstream inEngineFile("resnet.trt", std::ios::binary);

    inEngineFile.seekg(0, std::ifstream::end);
    int64_t fsize = inEngineFile.tellg();
    inEngineFile.seekg(0, std::ifstream::beg);
    std::vector<char> inEngineData(fsize);
    inEngineFile.read(inEngineData.data(), fsize);


    // 模型前向
    printf("模型前向\n");
    IRuntime* runtime = createInferRuntime(logger);
    ICudaEngine* engine = runtime->deserializeCudaEngine(inEngineData.data(), fsize, nullptr);
    IExecutionContext* context = engine->createExecutionContext();

    while (true)
    {
        unique_lock<mutex> lock(mtx);
        consumer_cond.wait(lock, []{ return !buffers.empty(); });

        int index = buffers.front();
        buffers.pop();
        cout << "get: " << index <<  endl;
        lock.unlock();

        context->executeV2(inputs[index].data());
        cout << "finish: " << index << endl;

        producer_cond.notify_one();
    }
    
    
}


int main(){
    // 分配显存空间
    
    for(int i=0; i<buffersize; i++){
        void* input;
        void* output;
        cudaMalloc(&input, 1 * 3 * 224 * 224 * sizeof(float));
        cudaMalloc(&output, 1 * 1000 * sizeof(float));
        inputs.push_back(vector<void*>{input, output});
    }


    thread t1(producer);
    thread t2(consumer);


    t1.join();
    t2.join();

    return 0;
}

