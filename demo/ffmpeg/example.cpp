#include <iostream>
extern "C" {
#include <libavformat/avformat.h>
}

int main() {
    

    const AVInputFormat *inputFormat = NULL;
    void *opaque = NULL;

    while ((inputFormat = av_demuxer_iterate(&opaque))) {
        std::cout << "Input Format: " << inputFormat->name << std::endl;
    }

    return 0;
}
