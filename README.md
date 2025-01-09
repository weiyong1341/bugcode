一些代码模板


demo 

#### 1.


在这里是一些解决小方案


1. 读取摄像头，并使用检测
2. 有多个检测
3. 推送数据到rtmp
4. 接受参数，修改检测参数


5. 使用单个线程读取视频，并推送
6. 使用一个线程读取数据，再使用一个线程推送数据
7. 读取视频，做检测
8. 使用硬解码读取视频


9. ncnn mnn openvino rknn tensorrt onnx


cpp-http-lib-0.12.6 
cmake -DCMAKE_INSTALL_PREFIX=/root/workspace/3rd -DCMAKE_BUILD_TYPE=Release ..


opencv-4.7.0
cmake -DWITH_IPP=OFF -DWITH_ADE=OFF -DBUILD_PERF_TESTS=OFF -DBUILD_TESTS=OFF -DCMAKE_INSTALL_PREFIX=/work/3rd/opencv ..
cmake -DWITH_IPP=OFF -DWITH_ADE=OFF -DBUILD_PERF_TESTS=OFF -DBUILD_TESTS=OFF -DBUILD_opencv_world=ON  -DCMAKE_INSTALL_PREFIX=/work/3rd/opencv ..
cmake -DWITH_IPP=OFF -DWITH_ADE=OFF -DBUILD_PERF_TESTS=OFF -DBUILD_TESTS=OFF -DCMAKE_INSTALL_PREFIX=/work/3rd/opencv -DOPENCV_EXTRA_MODULES_PATH=/root/workspace/opencv_demo/opencv_contrib-4.7.0/modules ..


pybind-2.10.4
g++ -O3 -Wall -shared -std=c++11 -fPIC  $(python3-config --includes) -I./pybind11/include example.cpp -o example$(python3-config --extension-suffix)

conda activate base
cmake -DCMAKE_INSTALL_PREFIX=/root/workspace/pybind11_demo/pybind11 ..
编译pybind11的时候，需要进入conda虚拟环境

ffmpeg-4.4.3
 ./configure --prefix=/root/workspace/ffmpeg_demo/ffmpeg --enable-shared

tinyxml2-8.0.0


这里主要是
c++
python
cuda
gtk
qt
duilib