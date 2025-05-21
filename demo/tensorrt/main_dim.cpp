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
    bool parse_flag = parser->parseFromFile("/work/tensorrt_demo/resnet50_dim.onnx", static_cast<int>(nvinfer1::ILogger::Severity::kWARNING));


    nvinfer1::IBuilderConfig* config = builder->createBuilderConfig();

    nvinfer1::IOptimizationProfile* profile = builder->createOptimizationProfile();
    profile->setDimensions("input", nvinfer1::OptProfileSelector::kMIN, nvinfer1::Dims4(1, 3, 224, 224));
    profile->setDimensions("input", nvinfer1::OptProfileSelector::kOPT, nvinfer1::Dims4(2, 3, 224, 224));
    profile->setDimensions("input", nvinfer1::OptProfileSelector::kMAX, nvinfer1::Dims4(4, 3, 224, 224));

    config->setMaxWorkspaceSize(1<<20);
    config->addOptimizationProfile(profile);


    // nvinfer1::IOptimizationProfile* profileCalib = builder->createOptimizationProfile();
    // const int calibBatchSize{256};
    // // We do not need to check the return of setDimension and setCalibrationProfile here as all dims are explicitly set
    // profileCalib->setDimensions("input", nvinfer1::OptProfileSelector::kMIN, nvinfer1::Dims4{calibBatchSize, 3, 224, 224});
    // profileCalib->setDimensions("input", nvinfer1::OptProfileSelector::kOPT, nvinfer1::Dims4{calibBatchSize, 3, 448, 448});
    // profileCalib->setDimensions("input", nvinfer1::OptProfileSelector::kMAX, nvinfer1::Dims4{calibBatchSize, 3, 448, 448});
    // config->setCalibrationProfile(profileCalib);

    auto dims = network->getInput(0)->getDimensions();


    nvinfer1::ICudaEngine* engine = builder->buildEngineWithConfig(*network, *config);
    
    // nvinfer1::IHostMemory* engine_host = builder->buildSerializedNetwork(*network, *config);
    // nvinfer1::IRuntime *runtime =  nvinfer1::createInferRuntime(logger);
    // nvinfer1::ICudaEngine* engine = runtime->deserializeCudaEngine(engine_host->data(), engine_host->size());

    nvinfer1::IExecutionContext* exec_context = engine->createExecutionContext();


    void* device_buffers[2];
    float* host_buffers[2];

    host_buffers[0] = (float*)malloc(3 * 3 * 224 * 224 * sizeof(float));
    host_buffers[1] = (float*)malloc(3 * 1000 * sizeof(float));

    cudaMalloc(&device_buffers[0], 3 * 3 * 224 * 224 * sizeof(float));
    cudaMalloc(&device_buffers[1], 3 * 1000 * sizeof(float));

    // exec_context->setBindingDimensions(0, nvinfer1::Dims4(3, 3, 224, 224));
    // exec_context->executeV2(device_buffers);


    cv::Mat img = cv::imread("dog_224x224.jpg");

    int num = 3;
    int channels = 3;
    int height = 224;
    int width = 224;

    cv::Mat mean(height, width, CV_32FC3, cv::Scalar(0.485, 0.456, 0.406));
    cv::Mat std(height, width, CV_32FC3, cv::Scalar(0.229, 0.224, 0.225));

    cv::cvtColor(img, img , cv::COLOR_BGR2RGB);
    img.convertTo(img, CV_32FC3, 1/255.);
    img -= mean;
    img /= std;

    
    
    for(int n=0; n<num; n++){
        for(int h=0; h<height; h++){
            for(int w=0; w<width; w++){
                for(int c=0; c<channels; c++){
                    // batch偏移，channel便宜，height偏移，+ w
                    int offset = n * channels * width * height + height * width * c + h * width + w;
                    float val = img.at<cv::Vec3f>(h, w)[c];
                    host_buffers[0][offset] = val;
                }   
            }
        }
    }

    cudaMemcpy(device_buffers[0], host_buffers[0], 3 * 3 * 224 * 224 * sizeof(float), cudaMemcpyHostToDevice);

    exec_context->setBindingDimensions(0, nvinfer1::Dims4(3, 3, 224, 224));
    exec_context->executeV2(device_buffers);

    
    cudaMemcpy(host_buffers[1], device_buffers[1], 3 * 1000 * sizeof(float), cudaMemcpyDeviceToHost);

    std::vector<float> results(host_buffers[1] + 1 * 1000, host_buffers[1] + 2 * 1000);
    int idx = std::max_element(results.begin(), results.end()) - results.begin();
    std::cout << idx << std::endl;

    return 0;
}