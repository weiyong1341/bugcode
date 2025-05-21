#include <iostream>
#include <NvInfer.h>
#include <NvInferRuntime.h>
#include <NvInferRuntimeCommon.h>
#include <NvOnnxParser.h>
#include <cuda_runtime_api.h>
#include <vector>
#include <algorithm>
#include <opencv2/opencv.hpp>

// 不加noexcept
// 不加public
class Logger : public nvinfer1::ILogger{
    void log(Severity severity, nvinfer1::AsciiChar const* msg) noexcept {
        if(severity <= Severity::kERROR){
            std::cout << "[TensorRT Logger] " << msg << std::endl;
        }
    }

};

int main(){

    Logger logger;
    
    nvinfer1::IBuilder* builder = nvinfer1::createInferBuilder(logger);

    const auto explicitBatch = 1U << static_cast<uint32_t>(nvinfer1::NetworkDefinitionCreationFlag::kEXPLICIT_BATCH);  
    nvinfer1::INetworkDefinition* network = builder->createNetworkV2(explicitBatch);

    nvonnxparser::IParser *parser = nvonnxparser::createParser(*network, logger);
    bool parse_flag = parser->parseFromFile("/work/tensorrt_demo/resnet50.onnx", static_cast<int>(nvinfer1::ILogger::Severity::kWARNING));


    nvinfer1::IBuilderConfig* config = builder->createBuilderConfig();


    config->setMaxWorkspaceSize(1<<20);
    auto dims = network->getInput(0)->getDimensions();

    nvinfer1::ICudaEngine* engine = builder->buildEngineWithConfig(*network, *config);
    nvinfer1::IExecutionContext* exec_context = engine->createExecutionContext();

    int num = 10;
    int channels = 3;
    int height = 640;
    int width = 640;

    void* device_buffers[2];
    float* host_buffers[2];

    host_buffers[0] = (float*)malloc(num * channels * height * width * sizeof(float));
    host_buffers[1] = (float*)malloc(num * 1000 * sizeof(float));

    cudaMalloc(&device_buffers[0], num * channels * height * width * sizeof(float));
    cudaMalloc(&device_buffers[1], num * 1000 * sizeof(float));

    cv::Mat img;
    
    cv::Mat mean(height, width, CV_32FC3, cv::Scalar(0.485, 0.456, 0.406));
    cv::Mat std(height, width, CV_32FC3, cv::Scalar(0.229, 0.224, 0.225));
    auto start = std::chrono::high_resolution_clock::now();
    auto end = start;

    while (true)
    {
        img = cv::imread("dog_224x224.jpg");
        cv::resize(img, img, cv::Size(width, height));
        cv::cvtColor(img, img , cv::COLOR_BGR2RGB);
        img.convertTo(img, CV_32FC3, 1/255.);
        img -= mean;
        img /= std;

        start = std::chrono::high_resolution_clock::now();

        for(int n=0; n < num; n++){
            for(int h=0; h < height; h++){
                for(int w=0; w < width; w++){
                    for(int c=0; c < channels; c++){
                        // batch偏移，channel便宜，height偏移，+ w
                        int offset = n * channels * width * height + height * width * c + h * width + w;
                        float val = img.at<cv::Vec3f>(h, w)[c];
                        host_buffers[0][offset] = offset;
                    }   
                }
            }
        }
        
        end = std::chrono::high_resolution_clock::now();
        std::cout << "__________________________________________" << std::endl;
        std::cout << "图像处理：" << std::chrono::duration<double, std::milli>(end - start).count() << std::endl;
        start = end;

        cudaMemcpy(device_buffers[0], host_buffers[0], num * channels * height * width * sizeof(float), cudaMemcpyHostToDevice);
        exec_context->executeV2(device_buffers);
        cudaMemcpy(host_buffers[1], device_buffers[1], num * 1000 * sizeof(float), cudaMemcpyDeviceToHost);

        end = std::chrono::high_resolution_clock::now();
        std::cout << "前向时间：" << std::chrono::duration<double, std::milli>(end - start).count() << std::endl;
        start = end;

        std::vector<float> results(host_buffers[1] + 1 * 1000, host_buffers[1] + 2 * 1000);
        int idx = std::max_element(results.begin(), results.end()) - results.begin();
        end = std::chrono::high_resolution_clock::now();
        std::cout << "后处理时间：" << std::chrono::duration<double, std::milli>(end - start).count() << std::endl;
        std::cout << idx << std::endl;
    }
    
    return 0;
}
