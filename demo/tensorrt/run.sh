g++ main.cpp -std=c++11 \
    -O2 \
    -I/work/3rd/TensorRT/include -I/usr/local/cuda/include -I/work/3rd/opencv/include/opencv4 \
    -L/work/3rd/TensorRT/lib  -L/usr/local/cuda/lib64 -L/work/3rd/opencv/lib \
    -Wl,-rpath=/work/3rd/TensorRT/lib -Wl,-rpath=/work/3rd/cudnn/lib64 -Wl,-rpath=/work/3rd/opencv/lib \
    -lnvinfer -lcudart -lnvonnxparser -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_imgcodecs -lopencv_video -lopencv_videoio